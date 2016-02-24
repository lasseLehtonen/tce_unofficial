import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("TimingDraw Extra-Pro v42")


    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                iconSource: "icons/screen_shot.png"
                action: Action {
                    id: screenshotAction
                    text: "&Screenshot"
                    shortcut: "Ctrl+s"
                    onTriggered: {
                        actualContent.grabToImage(function(result) {
                            result.saveToFile("capture.png")
                            console.log("Screenshot taken")
                        })
                    }

                    tooltip: "Take screenshot"
                }
            }
            ToolButton {
                iconSource: "icons/screen_shot.png"
                action: Action {
                    id: addSignal
                    text: "addSignal"
                    shortcut: ""
                    onTriggered: {
                        printed.signals += 1
                        console.log("add Signal", printed.signals)
                    }

                    tooltip: "Add Signal"
                }
            }
            Item { Layout.fillWidth: true }
        }
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10
        color: "transparent"

        TabView {
            id: options
            width: parent.width
            Tab {
                title: "Generate"
                GenerateTab {}
            }

            Tab {
                title: "Colors"
                ColorTab {}
            }
            Tab {
                title: "Sizes"
                SizeTab {}
            }
            Tab {
                title: "Fonts"
                FontTab {}
            }
        }

        Rectangle {
            id: printed
            anchors.top: options.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 10
            color: "transparent"
            border.color: "red"
            border.width: 1

            property color color_bg: "#ffffff"
            property color color_text: "#000000"
            property color color_signal: "#000000"
            property real signalHeight: 50
            property int cycleWidth: 100
            property int trailingWidth: 0
            property real signalTextWidth: 100
            property string fontFamily: "Courier"
            property int fontPixelSize: 16
            property string valueFontFamily: "Courier"
            property int valueFontPixelSize: 16
            property int clockCycles: 2
            property int signalWidth: 2
            property int valueLeftMargin: 50
            property int globalMargin: 10
            property int signals: 0

            signal redraw

            Flickable {
                anchors.fill: parent
                anchors.margins: parent.border.width
                contentHeight: actualContent.height
                contentWidth: actualContent.width
                clip: true

                Rectangle {
                    id: actualContent
                    width: actualLayout.width + 2*printed.globalMargin
                    height: actualLayout.height + 2*printed.globalMargin
                    color: printed.color_bg
                    clip: true
                    ColumnLayout {
                        id: actualLayout
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 10
                        ClockSignal {}
                        ResetSignal {id: resetSignal; visible: false}
                        Repeater {
                            model: printed.signals
                            GenericSignal { row_id: index }
                        }
                    }
                }
            }
        }
    }
}

