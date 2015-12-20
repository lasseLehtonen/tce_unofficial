import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
    title: "Memory Designer " + MemoryModel.saveFile

    FileDialog {
        id: fileOpenDialog
        title: "Please choose a file to open"
        nameFilters: [ "Memory database (*.mdb)", "All files (*)"]
        selectExisting: true
        onAccepted: {
            MemoryModel.open( fileOpenDialog.fileUrl )
            fileOpenDialog.close()
        }
        onRejected: {
            fileOpenDialog.close()
        }
    }

    FileDialog {
        id: fileSaveAsDialog
        selectExisting: false
        title: "Please choose a file to Save as"
        nameFilters: [ "Memory database (*.mdb)", "All files (*)"]
        onAccepted: {
            var f = fileSaveAsDialog.fileUrl
            MemoryModel.saveAs( f )
            fileSaveAsDialog.close()
        }
        onRejected: {
            fileSaveAsDialog.close()
        }
    }


    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: fileOpenDialog.open();
            }
            MenuItem {
                text: qsTr("&Save")
            }
            MenuItem {
                text: qsTr("&Save as")
                onTriggered: fileSaveAsDialog.open();
            }
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

