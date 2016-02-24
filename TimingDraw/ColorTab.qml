import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

Rectangle {
    anchors.fill: parent
    anchors.margins: 10
    color: "transparent"

    GroupBox {
        title: "Color"
        ColumnLayout {
            GridLayout {
                rows: 2
                columns: 4
                Label {
                    text: "BG"
                }
                TextField {
                    text: printed.color_bg
                    onAccepted: printed.color_bg = text
                }

                Label {
                    text: "Signal"
                }
                TextField {
                    text: printed.color_signal
                    onAccepted: { printed.color_signal = text; printed.redraw() }
                }
                Label {
                    text: "Text"
                }
                TextField {
                    text: printed.color_text
                    onAccepted: printed.color_text = text
                }
            }
        }
    }
}

