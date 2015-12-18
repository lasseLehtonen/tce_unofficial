import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Memory Designer")


    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Save")
                onTriggered: statusBar.text = "Save action triggered"
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    TabView {
        id: tabContent
        anchors.fill: parent
        Layout.minimumHeight: 100
        Layout.minimumWidth: 100

        Tab{
            title: "New Definition"
            Definition {}
        }

        Tab{
            title: "Available Blocks"
            Blocks {}
        }
    }

    statusBar: StatusBar {
        width: parent.width
        implicitWidth: parent.width
        RowLayout {
            anchors.fill: parent
            Label {
                id: statusBar
                text: ""
                onTextChanged: { resetter.restart() }
                Timer {
                    id: resetter
                    interval: 3000
                    running: false
                    repeat: false
                    onTriggered: statusBar.text = ""
                }
            }
        }
    }

}

