import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

Rectangle {
    anchors.fill: parent
    anchors.margins: 10
    color: "transparent"
    GridLayout {
        rows: 2
        columns: 2
        Label {
            text: "Reset"
        }
        CheckBox {
            onCheckedChanged: {
                if (checked === true)
                    resetSignal.visible = true
                else
                    resetSignal.visible = false
            }
        }
        Label {
            text: "Clock Cyles"
        }
        SpinBox {
            minimumValue: 2
            maximumValue: 99
            onValueChanged: printed.clockCycles = value
        }
    }
}

