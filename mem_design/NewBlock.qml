import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

ColumnLayout {
    id: root
    anchors.fill: parent
    anchors.margins: parent.height * 0.01

    Layout.fillWidth: true
    Layout.fillHeight: true

    RowLayout {
        width: parent.width
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignTop

        GroupBox {
            title: "Component Definition"
            width: root.width * 0.5
            Layout.fillHeight: true
            Layout.fillWidth: true

            TextArea {
                id: component
                font.family: "Courier"
                anchors.fill: parent
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: {"component mem_block_1024x32_sp port (\n" +
                       "CK  : in  std_logic;\n" +
                       "CSN : in  std_logic;\n" +
                       "WEN : in  std_logic;\n" +
                       "A   : in  std_logic_vector( 9 downto 0);\n" +
                       "D   : in  std_logic_vector(31 downto 0);\n" +
                       "Q   : out std_logic_vector(31 downto 0)\n" +
                       ");\n" +
                       "end component;"
                }
            }
        }

        GroupBox {
            title: "Component Instantiation"
            width: root.width * 0.5
            Layout.fillHeight: true
            Layout.fillWidth: true

            TextArea {
                id: instance
                font.family: "Courier"
                anchors.fill: parent
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: {"U_%%ID%% : mem_block_1024x32_sp port map (\n" +
                       "CK  => %%CLK%%,\n" +
                       "CSN => %%CS_N%%,\n" +
                       "WEN => %%WE_N%%,\n" +
                       "A   => %%ADDR%%,\n" +
                       "D   => %%WR_DATA%%,\n" +
                       "Q   => %%RD_DATA%%\n" +
                       ");"
                }
            }
        }
    }

    GroupBox {
        title: "Legend (Generateable Stuff)"
        Layout.fillWidth: true

        GridLayout {
            rows: 3
            flow: GridLayout.TopToBottom
            Label { text: "Address: %%ADDR%%, %%WR_ADDR%%, %%RD_ADDR%%" }
            Label { text: "Data: %%WR_DATA%%, %%RD_DATA%%" }
            Label { text: "Clk: %%CLK%%,  %%WR_CLK%%,  %%RD_CLK%%" }
            Label { text: "Identifier : %%ID%%" }
            Label { text: "Chip Select: %%CS%%, %%CS_N%%" }
            Label { text: "Write Enable: %%WE%%, %%WE_N%%" }
            Label { text: "Constants: %%ZERO%%, %%ONE%%" }
        }
    }

    Button {
        Layout.alignment: Qt.AlignRight
        text: "Add Block"
        onClicked: {
            statusBar.text =  "Add Block clicked"
            MemoryModel.addBlock(component.text, instance.text)
        }
    }

}

