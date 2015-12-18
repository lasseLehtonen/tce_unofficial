import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

ColumnLayout {
    anchors.fill: parent
    anchors.topMargin: parent.height * 0.01
    anchors.bottomMargin: parent.height * 0.01
    anchors.leftMargin: parent.height * 0.01
    anchors.rightMargin: parent.height * 0.01

    GroupBox {
        title: "General options"
        width: parent.width
        Layout.fillWidth: true

        RowLayout {
            Layout.fillWidth: true
            width: parent.width

            Label {
                Layout.alignment: Qt.AlignVCenter
                text: "File name"
            }

            TextField {
                id: fileName
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }

    GroupBox {
        title: "Memory Options"
        width: parent.width
        //Layout.fillWidth: true

        GridLayout {
            Layout.fillWidth: true
            width: parent.width
            rows: 3
            flow: GridLayout.TopToBottom

            Label {
                Layout.alignment: Qt.AlignVCenter
                text: "Address width"
            }

            Label {
                Layout.alignment: Qt.AlignVCenter
                text: "Memory width"
            }

            Label {
                Layout.alignment: Qt.AlignVCenter
                text: "Memory depth"
            }


            TextField {
                id: addrWidth
                validator: IntValidator {bottom: 1;}
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            TextField {
                id: memWidth
                validator: IntValidator {bottom: 1;}
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            TextField {
                id: memDepth
                validator: IntValidator {bottom: 1;}
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }

    GroupBox {
        title: "Memory Type"

        RowLayout {
            ExclusiveGroup { id: tabPositionGroup }
            RadioButton {
                text: "Single-port"
                checked: true
                exclusiveGroup: tabPositionGroup
            }
            RadioButton {
                text: "Dual-port"
                exclusiveGroup: tabPositionGroup
            }
        }
    }

    TextArea {
        Layout.fillHeight: true
        Layout.fillWidth: true
        text: "Memory Designer initialized\n\n"
        readOnly: true
    }

    Button {
        Layout.alignment: Qt.AlignRight
        text: "Generate"
        onClicked: statusBar.text =  "Generate clicked"
    }
}
