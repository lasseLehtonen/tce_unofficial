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
                        core.grabToImage(function(result) {
                            result.saveToFile("capture.png")
                            console.log("Screenshot taken")
                        })
                    }

                    tooltip: "Take screenshot"
                }
                onClicked: {

                }
            }
            Item { Layout.fillWidth: true }
        }
    }

    Rectangle {
        id: core
        anchors.fill: parent
        color: "black"

        Row {
            id: clockrow
            y: parent.height * 0.10
            width: parent.width
            height: parent.height / 10

            Repeater {
                model: 10

                Rectangle {
                    width: clockrow.width /12
                    height: clockrow.height
                    color: "transparent"
                    border.width: 1
                    border.color: "red"
                }
            }
        }

        Text {
            anchors.centerIn: parent
            text: "Fuck yeah"
            color: "green"
        }
    }
}

