import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Memory Designer")


    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Quit")
                onTriggered: Qt.quit();
            }
        }
    }

    TabView {
        id: tabContent
        anchors.fill: parent
        Layout.minimumHeight: 800
        Layout.minimumWidth: 600

        Tab{
            title: "New Memory"
            NewMemory {}
        }

        Tab{
            title: "Select Blocks"
            Blocks {}
        }

        Tab {
            title: "New Block"
            NewBlock {}
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

