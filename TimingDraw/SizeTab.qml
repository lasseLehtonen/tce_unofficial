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
        title: "Size"
        anchors.top: parent.top
        ColumnLayout {
            GridLayout {
                rows: 3
                columns: 6
                Label {
                    text: "Cycle width"
                }
                SpinBox {
                    minimumValue: 9
                    maximumValue: 9999
                    value: printed.cycleWidth
                    onValueChanged: printed.cycleWidth = value
                }

                Label {
                    text: "Signal Height"
                }
                SpinBox {
                    minimumValue: 9
                    maximumValue: 9999
                    value: printed.signalHeight
                    onValueChanged: printed.signalHeight = value
                }

                Label {
                    text: "Trailing Width"
                }
                SpinBox {
                    minimumValue: 0
                    maximumValue: 9999
                    value: printed.trailingWidth
                    onValueChanged: printed.trailingWidth = value
                }

                Label {
                    text: "Signal Spacing"
                }
                SpinBox {
                    minimumValue: 0
                    maximumValue: 9999
                    value: actualLayout.spacing
                    onValueChanged: actualLayout.spacing = value
                }

                Label {
                    text: "Signal Width"
                }
                SpinBox {
                    minimumValue: 1
                    maximumValue: 999
                    value: printed.signalWidth
                    onValueChanged: { printed.signalWidth = value; printed.redraw(); console.log("Sigw", value) }
                }

                Label {
                    text: "Signal Value Margin"
                }
                SpinBox {
                    minimumValue: 0
                    maximumValue: 999
                    value: printed.valueLeftMargin
                    onValueChanged: { printed.valueLeftMargin = value; printed.redraw(); console.log("valueLeftMargin", value) }
                }

                Label {
                    text: "Global Margin"
                }
                SpinBox {
                    minimumValue: 0
                    maximumValue: 999
                    value: printed.globalMargin
                    onValueChanged: { printed.globalMargin = value; printed.redraw(); console.log("valueLeftMargin", value) }
                }

                Label {
                    text: "Signal Text Width"
                }
                SpinBox {
                    minimumValue: 0
                    maximumValue: 999
                    value: printed.signalTextWidth
                    onValueChanged: { printed.signalTextWidth = value; printed.redraw(); console.log("valueLeftMargin", value) }
                }
            }
        }
    }
}

