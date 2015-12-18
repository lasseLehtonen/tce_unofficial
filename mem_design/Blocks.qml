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

    Layout.fillWidth: true
    Layout.fillHeight: true

    GroupBox {
        title: "Known Memory Blocks"
        Layout.fillWidth: true
        Layout.fillHeight: true

        TextArea {
            anchors.fill: parent
            text: ""
            readOnly: true
        }
    }

    GroupBox {
        title: "New Memory Block"
        width: parent.width
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignRight

        RowLayout {
            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: true

            Label {text: "width"}
            TextField {
                id: blockWidth
                text: "1"
                validator: IntValidator {bottom: 1;}
                Layout.alignment: Qt.AlignVCenter
            }
            Label {text: "depth"}
            TextField {
                id: blockDepth
                text: "1"
                validator: IntValidator {bottom: 1;}
                Layout.alignment: Qt.AlignVCenter
            }
            Button {
                text: "Add"
                onClicked: {
                    console.log("Block to add w", blockWidth.text, " d", blockDepth.text)
                }
            }

        }
    }
}

