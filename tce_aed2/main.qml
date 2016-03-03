import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: Screen.width / 2
    height: Screen.height / 2
    title: "TCE aed2"

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("Edit")
            MenuItem {
                text: qsTr("Copy")
                onTriggered: console.log("Copy action triggered");
            }
            MenuItem {
                text: qsTr("Cut")
                onTriggered: console.log("Cut action triggered");
            }
            MenuItem {
                text: qsTr("Paste")
                onTriggered: console.log("Paste action triggered");
            }
        }
    }

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                iconSource: "icons/open_document.png"
                onClicked: {
                    console.log("try capture")
                    asmEditor.grabToImage(function(result) {
                        console.log("capure callback : ", result)
                        result.saveToFile("capture.png")
                        console.log("after saveTofile()")
                    })
                }
            }
            ToolButton {
                iconSource: "icons/save.png"
                action: Action {
                    id: saveAction
                    text: "&Save"
                    shortcut: "Ctrl+s"
                    onTriggered: CodeModel.save()
                    tooltip: "Save"
                }
            }
            ToolButton {
                iconSource: "icons/save_as.png"
            }
            ToolButton {
                iconSource: "icons/insert_row_left.png"
                onClicked: CodeModel.addColumnLeft()
            }
            ToolButton {
                iconSource: "icons/insert_row_right.png"
                onClicked: CodeModel.addColumnRight()
            }
            ToolButton {
                iconSource: "icons/delete_row.png"
            }
            ToolButton {
                iconSource: "icons/inesrt_column_below.png"
                onClicked: CodeModel.addRowBelow()
            }
            ToolButton {
                iconSource: "icons/insert_column_above.png"
                onClicked: CodeModel.addRowAbove()
            }
            ToolButton {
                iconSource: "icons/delete_column.png"
            }
            Item { Layout.fillWidth: true }
        }
    }

    TabView {
        anchors.fill: parent
        Tab {
            id: asmEditor
            title: "Assembly Editor"
            AsmEditor { id: asmEdit}
        }
        Tab {
            title: "ADF Source"
            AdfView {}
        }
    }




}

