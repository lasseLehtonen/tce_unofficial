import re, sqlite3, sys, string, math
import xml.etree.ElementTree as ET

class FU:
    
    def __init__(self, name):
        # general info
        self.name = name
        self.entity = ''
        self.entity_file = ''
        self.hdb_file =  ''
        self.hdb_fu_id = 0
        # port info
        self.p_clk = ''
        self.p_rstx = ''
        self.p_opcode = ''
        self.p_glock = ''
        self.p_glock_req = ''
        self.p_ports = set()
        self.p_loads = {}
        self.p_guards = {}
        self.p_widths = {}
        self.p_resolved_widths = {}
        self.p_exts = []
        self.p_generics = {}
        self.p_dirs = {}
        # operation info
        self.op_latency = {}
        self.op_codes = {}
        self.op_names = []

    def after_parses(self):
        width = str(int(math.ceil(math.sqrt(len(self.op_names)))))
        name = self.p_opcode
        self.p_widths[name] = width
        for p in self.p_ports:
            dir = 'output'
            if len(self.p_loads[p]) > 0:
                dir = 'input'
            self.p_dirs[p] = dir
        for p in self.p_ports:
            width = self.p_widths[p]
            for g in self.p_generics:
                value = self.p_generics[g]
                width = string.replace(width, g, value)
            self.p_resolved_widths[p] = width
        for p in self.p_exts:
            width = self.p_widths[p]
            for g in self.p_generics:
                value = self.p_generics[g]
                width = string.replace(width, g, value)
            self.p_resolved_widths[p] = width

    def parse_adf(self, file):
        try:
            tree = ET.parse(file)
            adfroot = tree.getroot()
        except:
            print('Err: Failed to open adf ' + file)
            quit()
        for fu in adfroot.findall('function-unit'):
            if fu.attrib['name'] == self.name:
                for op in fu.findall('operation'):
                    name = op.find('name').text
                    self.op_names.append(name)
                    min_latency = 1
                    pipe = op.find('pipeline')
                    for res in pipe.findall('resource'):
                        cycles = int(res.find('cycles').text)
                        if cycles > min_latency:
                            min_latency = cycles
                    for writes in pipe.findall('writes'):
                        cycles = int(writes.find('start-cycle').text) + 1
                        if cycles > min_latency:
                            min_latency = cycles
                    self.op_latency[name] = str(min_latency)


    def parse_hdb(self):
        if len(self.hdb_file) < 4:
            print('Not valid hdb : ' + self.hdb_file)
            quit()
        try:
            db = sqlite3.connect(self.hdb_file)
        except:
            print("Couldn't connect to " +  self.hdb_file)
            quit()
        c1 = db.cursor()
        c2 = db.cursor()
        impl = 0
        s1 = 'SELECT * FROM fu_implementation as impl WHERE impl.fu=?'
        for r in c1.execute(s1, (int(self.hdb_fu_id), )):
            impl = int(r[0])
            self.entity = r[1]
            self.p_opcode = r[2]
            self.p_clk = r[3]
            self.p_rstx = r[4]
            self.p_glock = r[5]
            self.p_glock_req = r[6]
        s1 = 'SELECT * FROM fu_implementation_parameter WHERE fu_impl=?'
        for r in c1.execute(s1, (impl, )):
            name = r[1]
            value = r[3]
            # haxor warning: if value is empty give it default value 32
            if len(value) < 1:
                value = '32'
            self.p_generics[name] = value
        s1 = 'SELECT * FROM fu_port_map WHERE fu_impl=?'
        for r in c1.execute(s1, (impl, )):
            name = r[1]
            width = r[2]
            load = r[3]
            guard = r[4]
            self.p_ports.add(name)
            self.p_loads[name] = load
            self.p_guards[name] = guard
            self.p_widths[name] = width
        s1 = 'SELECT * FROM fu_external_port WHERE fu_impl=?'
        for r in c1.execute(s1, (impl, )):
            name = r[1]
            dir = r[2]
            widht = r[3]
            if dir == 'OUT':
                self.p_dirs[name] = 'output'
            else:
                self.p_dirs[name] = 'input'
            self.p_exts.append(name)
            self.p_widths[name] = width
        s1 = 'SELECT op.name, map.opcode FROM opcode_map as map, operation as op WHERE map.fu_impl=? and map.operation=op.id'
        for r in  c1.execute(s1, (impl, )):
            name = r[0]
            code = r[1]
            self.op_codes[name] = code


    def pretty_print(self):
        print('')
        print('FU ' + self.name)
        print('  entity     : ' + self.entity)
        print '  operations : ', self.op_names
        print '  codes      : ', self.op_codes
        print '  latencies  : ', self.op_latency
        print('')
        print('  clk       : ' + self.p_clk)
        print('  rst_n     : ' + self.p_rstx)
        print('  glock     : ' + self.p_glock)
        print('  glockreq  : ' + self.p_glock_req)
        width = self.p_widths[self.p_opcode]
        print('  opcodes   : '  + self.p_opcode + ' [' + width + '-1:0]')
        for p in self.p_ports:
            dir = '  outport   : '
            if self.p_dirs[p] == 'input':
                dir = '  inport    : '
            width = self.p_widths[p]
            for g in self.p_generics:
                value = self.p_generics[g]
                width = string.replace(width, g, value)
            extra = ''
            if len(self.p_loads[p]) > 0:
                extra = ' (load:' + self.p_loads[p] + ')'
            if len(self.p_guards[p]) > 0:
                extra = extra + ' (guard:' + self.p_guards[p] + ')'
            print(dir + p + ' [' + width + '-1:0]' + extra)
        for p in self.p_exts:
            width = self.p_widths[p]
            for g in self.p_generics:
                value = self.p_generics[g]
                width = string.replace(width, g, value)
            print('  extport   : ' + p + ' [' + width + '-1:0]')
        print('')

    def print_sv_interface(self, ttaname):
        print('// TCE generated file.')
        print('interface ' + ttaname + '_' + self.name.lower() + '_if(')
        print('  ' + self.p_clk + ',')
        if len(self.p_glock) > 0:
            print('  ' + self.p_glock + ',')
        if len(self.p_glock_req) > 0:
            print('  ' + self.p_glock_req + ',')
        if len(self.p_opcode) > 0:
            print('  ' + self.p_opcode + ',')
        for p in self.p_ports:
            if len(p) > 0:
                print('  ' + p + ',')
            if len(self.p_loads[p]) > 0:
                print('  ' + self.p_loads[p] + ',')
        for p in self.p_exts:
            if len(p) > 0:
                print('  ' + p + ',')
        print('  ' + self.p_rstx + ');')
        print('')
        print('  input logic ' + self.p_clk + ';')
        if len(self.p_glock) > 0:
            print('  input logic ' + self.p_glock + ';')
        if len(self.p_glock_req) > 0:
            print('  output logic ' + self.p_glock_req + ';')
        if len(self.p_opcode) > 0:
            print('  input logic [' + self.p_widths[self.p_opcode] + '-1:0] ' + self.p_opcode + ';')
        for p in self.p_ports:
            print('  ' + self.p_dirs[p] + ' logic [' + self.p_resolved_widths[p] + '-1:0] ' + p + ';')
            if len(self.p_loads[p]) > 0:
                print('  input logic ' + self.p_loads[p] + ';')
            if len(self.p_guards[p]) > 0:
                print('  input logic ' + self.p_guards[p] + ';')
        for p in self.p_exts:
            print('  ' + self.p_dirs[p] + ' logic [' + self.p_resolved_widths[p] + '-1:0] ' + p + ';')
        print('  input logic ' + self.p_rstx + ';')
        print('')
        print('endinterface')
        print('')

    def print_uvm_monitor(self, ttaname):
        nname = ttaname + '_' + self.name.lower()
        print('// TCE generated file.')
        print('import uvm_pkg::*;')
        print('')
        print('class monitor_' + nname+ ' extends uvm_monitor;')
        print('  `include "uvm_macros.svh"')
        print('  `uvm_component_utils(monitor_' + nname + ')')
        print('')
        print('  virtual ' + nname + '_if ' + nname+ '_vif;')
        print('')
        print('  covergroup ' + nname + '_cg;')
        print('    opcode : coverpoint ' + nname + '_vif.' + self.p_opcode + ' {')
        for op in self.op_names:
            print('      bins ' + op + ' = {' + str(self.op_codes[op]) + '};')
        print('      illegal_bins unknown_opc = default;')
        print('    }')
        cpoint = 'crosscover : cross ' + self.p_opcode + ', '
        for p in self.p_ports:
            if self.p_dirs[p] == 'input':
                cpoint = cpoint + p + ', '
                print('    ' + p + ' : coverpoint ' + nname + '_vif.' + p + ' {')
                print('      bins zero = {0};')
                print('      bins neg = {[$:-1]};')
                print('      bins pos = {[1:$]};')
                print('    }')
        print('    ' + cpoint[:-2] + ';')
        print('  endgroup;')
        print('')
        print('  function new(string name, uvm_component parent = null);')
        print('    super.new(name, parent);')
        print('    ' + nname + '_cg = new;')
        print('  endfunction')
        print('')
        print('  function void build_phase(uvm_phase phase);')
        print('    super.build_phase(phase);')
        print('    if(!uvm_config_db#(virtual ' + nname+ '_if)::get(this, "", "' + nname +'_vif", ' + nname + '_vif))  begin')
        print('      `uvm_error("", "uvm_config_db::get failed miserably")')
        print('    end')
        print('  endfunction')
        print('')
        print('  task run_phase(uvm_phase phase);')
        print('    forever begin')
        print('      @(negedge ' + nname + '_vif.' +  self.p_clk + ')')
        print('      $display("Boo")')
        print('    end')
        print('  endtask')
        print('')
        print('  function void report_phase(uvm_phase phase);')
        print('  ')
        print('  endfunction')
        print('')
        print('endclass')
        print('')

class RF:
    name = ''

    def __init__(self, name):
        self.name = name

class IU:
    name = ''

    def __init__(self, name):
        self.name = name

class TTA:
    
    def __init__(self, name, adf, idf, tce):
        self.name = name
        self.idf_file = idf
        self.adf_file = adf
        self.tce_dir = tce
        # function units
        self.fus = []
        # register files
        self.rfs = []
        # immediate units
        self.ius = []

        # run magic
        self.parse_adf()
        self.parse_idf()
        self.replace_ulrs()
        self.parse_hdbs()
        for fu in self.fus:
            fu.after_parses()

    def print_fus(self):
        for f in self.fus:
            f.pretty_print()

    def print_fu(self, name):
        for fu in self.fus:
            if fu.name == name:
                fu.pretty_print()
                return
        print("didn't find fu " + name)
        quit()
            
    def print_sv_inteface(self, name):
        for fu in self.fus:
            if fu.name == name:
                fu.print_sv_interface(self.name)
                return
        print("didn't find fu " + name)
        quit()

    def print_uvm_monitor(self, name):
        for fu in self.fus:
            if fu.name == name:
                fu.print_uvm_monitor(self.name)
                return
        print("didn't find fu " + name)
        quit()

    def print_rfs(self):
        for f in self.rfs:
            print('RF : ' + f.name + ' id: ' + f.hdb_fu_id + ' in "' + f.hdb_file + '"')

    def print_ius(self):
        for f in self.ius:
            print('IU : ' + f.name + ' id: ' + f.hdb_fu_id + ' in "' + f.hdb_file + '"')

    def parse_adf(self):
        try:
            tree = ET.parse(self.adf_file)
            adfroot = tree.getroot()
        except:
            print('Err: Failed to open ' + self.adf_file)
            quit()
        for child in adfroot:
            if child.tag == 'function-unit':
                name = child.attrib['name']
                fu = FU(name)
                self.fus.append(fu)
            if child.tag == 'register-file':
                name = child.attrib['name']
                rf = RF(name)
                self.rfs.append(rf)
            if child.tag == 'immediate-unit':
                name = child.attrib['name']
                iu = IU(name)
                self.ius.append(iu)
        for fu in self.fus:
            fu.parse_adf(self.adf_file)

    def parse_idf(self):
        try:
            tree = ET.parse(self.idf_file)
            idfroot = tree.getroot()
        except:
            print('Err failed to open ' + self.idf_file)
            quit()
        for child in idfroot:
            if child.tag == 'fu':
                name = child.attrib['name']
                id = child.find('fu-id').text
                hdb = child.find('hdb-file').text
                for fu in self.fus:
                    if fu.name == name:
                        fu.hdb_fu_id = id
                        fu.hdb_file = hdb
            if child.tag == 'rf':
                name = child.attrib['name']
                id = child.find('rf-id').text
                hdb = child.find('hdb-file').text
                for rf in self.rfs:
                    if rf.name == name:
                        rf.hdb_fu_id = id
                        rf.hdb_file = hdb
            if child.tag == 'iu':
                name = child.attrib['name']
                id = child.find('rf-id').text
                hdb = child.find('hdb-file').text
                for iu in self.ius:
                    if iu.name == name:
                        iu.hdb_fu_id = id
                        iu.hdb_file = hdb
        
    def replace_ulrs(self):
        tce_re = re.compile('tce:([a-zA-Z0-9\/\.\-/_]+\.hdb)')
        for fu in self.fus:
            m = tce_re.match(fu.hdb_file)
            if m:
                fu.hdb_file = self.tce_dir + 'hdb/' + m.group(1)
        for iu in self.ius:
            m = tce_re.match(iu.hdb_file)
            if m:
                iu.hdb_file = self.tce_dir + 'hdb/' + m.group(1)
        for rf in self.rfs:
            m = tce_re.match(rf.hdb_file)
            if m:
                rf.hdb_file = self.tce_dir + 'hdb/' + m.group(1)

    def parse_hdbs(self):
        for fu in self.fus:
            fu.parse_hdb()