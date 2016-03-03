import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: rec
    height: textEdit.height
    width: textEdit.width

    TextField {
        id: textEdit
        text: ""

        property bool selected: false
        property color colorText: "#000000"
        property color colorBg: "white"

        style: TextFieldStyle {
            textColor: textEdit.colorText
            font.family: "Courier"
            font.pointSize: 10
            background: Rectangle {
                color: textEdit.colorBg //textEdit.selected ? "#eeeeff" : "#ffffff"
                radius: 2
                implicitWidth: 100
                implicitHeight: 24
                border.color: "#999"
                border.width: 1
            }
        }

        onDisplayTextChanged: {
            var len = (textEdit.__contentWidth / length) * (length+3)
            CodeModel.slotWidth(xrow, xcolumn, len)
            CodeModel.setCode(xrow, xcolumn, textEdit.text);
            //console.log("edited ")
        }

        onActiveFocusChanged: {
            //console.log("active foocus", activeFocus)
            if (activeFocus) {
                selected = true
                textEdit.colorText = "blue"
                textEdit.colorBg = "#eeeeff"
            } else {
                selected = false
                textEdit.colorText = "#010101"
                textEdit.colorBg = "white"
            }


        }

        Connections {
            target: CodeModel
            onColumnUpdated: {
                if (column === xcolumn) {
                    textEdit.width = CodeModel.columnWidth(column)
                }
            }
        }
        Component.onCompleted: text = CodeModel.code(xrow, xcolumn)
    }
}

