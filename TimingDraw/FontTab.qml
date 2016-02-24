import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

Rectangle {
    anchors.fill: parent
    anchors.margins: 10
    color: "transparent"
    Row {
        GroupBox {
            title: "Signal Names"
            anchors.top: parent.top
            ColumnLayout {
                GridLayout {
                    rows: 2
                    columns: 2
                    Label {
                        text: "Family"
                    }
                    TextField {
                        text: "Courier"
                        onAccepted: printed.fontFamily = text
                    }

                    Label {
                        text: "Pixel Size"
                    }
                    SpinBox {
                        minimumValue: 6
                        maximumValue: 99
                        value: printed.fontPixelSize
                        onValueChanged: printed.fontPixelSize = value
                    }
                }
            }
        }

        GroupBox {
            title: "Signal Values"
            anchors.top: parent.top
            ColumnLayout {
                GridLayout {
                    rows: 2
                    columns: 2
                    Label {
                        text: "Family"
                    }
                    TextField {
                        text: "Courier"
                        onAccepted: printed.valueFontFamily = text
                    }

                    Label {
                        text: "Pixel Size"
                    }
                    SpinBox {
                        minimumValue: 6
                        maximumValue: 99
                        value: printed.fontPixelSize
                        onValueChanged: printed.valueFontPixelSize = value
                    }
                }
            }
        }
    }
}

