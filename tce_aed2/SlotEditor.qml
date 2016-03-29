import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import ase.sorsa.slot 1.0

Rectangle {
    id: rec
    width: textEdit.width
    height: textEdit.height


    TextField {
        id: textEdit
        width: slot.width > 100 ? slot.width : 100

        Slot {
            id: slot
            row: xrow
            column: xcolumn
            selected: textEdit.activeFocus
            width:  textEdit.__contentWidth + 10
            model: CodeModel

            onCodeChanged: { console.log("Code changed to ", code); textEdit.text = code;}
        }

        style: TextFieldStyle {
            textColor: slot.selected ? "blue" : "black"
            font.family: "Courier"
            font.pointSize: 10
            background: Rectangle {
                color: slot.selected ? "#eeeeff" : "white"
                radius: 2
                implicitWidth: 100
                implicitHeight: 24
                border.color: "#999"
                border.width: 1
            }
        }

        onDisplayTextChanged: {
            var len = (textEdit.__contentWidth / length) * (length+3)
            slot.width = len
            slot.code = text
        }
        //onDisplayTextChanged: slot.code = text
        onEditingFinished: { textEdit.focus = false }
        Component.onCompleted: { text = CodeModel.code(xrow, xcolumn) }
    }
}

