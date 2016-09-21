import sys, re, os
from tce_tools import TTA

adf = ''
idf = ''
name = ''
try:
    tce_root = os.environ['TCE_INSTALL_DIR']
except:
    tce_root = ''

adf_re = re.compile('[a-z0-9_\-\.\/]+.adf$')
idf_re = re.compile('[a-z0-9_\-\.\/]+.idf$')
name_re = re.compile('name=([a-zA-z0-9_]+)')
tce_re = re.compile('tce=([a-zA-Z\.\/_\-]+)')

for a in sys.argv: 
    if adf_re.match(a):
        adf = a
        continue
    if idf_re.match(a):
        idf = a
        continue
    if name_re.match(a):
        name = name_re.match(a).group(1)
        continue
    if tce_re.match(a):
        tce_root = tce_re.match(a).group(1)
        continue

if adf == '' or idf == '' or name == '' or tce_root == '':
    print('Err: Fix: Provide enough parameters.')
    quit()

if tce_root[-1] != '/':
    tce_root = tce_root + '/'


processor = TTA(name, adf, idf, tce_root)


#processor.print_rfs()
#processor.print_ius()

if 'print-fus' in sys.argv:
    processor.print_fus()
    quit()

print_fu_re = re.compile('^print-fu-([a-zA-Z0-9_]+)$')
for a in sys.argv:
    m = print_fu_re.match(a)
    if m:
        processor.print_fu(m.group(1))


print_sv_iface_re = re.compile('^print-sv-interface-fu-([a-zA-Z0-9_]+)$')
for a in sys.argv:
    m = print_sv_iface_re.match(a)
    if m:
        processor.print_sv_inteface(m.group(1))

print_sv_iface_re = re.compile('^print-uvm-monitor-fu-([a-zA-Z0-9_]+)$')
for a in sys.argv:
    m = print_sv_iface_re.match(a)
    if m:
        processor.print_uvm_monitor(m.group(1))
