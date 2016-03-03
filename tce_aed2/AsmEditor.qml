import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

ScrollView {
    anchors.fill: parent
    verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOn

    GridLayout {
        id: grid
        x: 10
        y: 10
        width: parent.width
        height: parent.height

        rows: CodeModel.rowCount() + 1
        columns: CodeModel.columnCount() + 1
        rowSpacing: 0
        columnSpacing: 0

        Connections {
            target: CodeModel
            onColumnInserted: {
                grid.columns = CodeModel.columnCount() + 1
                console.log("grid updated")
            }
            onRowInserted: {
                grid.rows = CodeModel.rowCount() + 1
                console.log("grid updated")
            }
            onTableWidthChanged: {
                console.log("row width", newWidth)
                grid.width = newWidth + 20
            }
        }

        Component {
            id:editor
            SlotEditor {}
        }


        Component {
            id: filler
            Rectangle {
                width: 0
                height: 0
                color: "transparent"
            }
        }


        Repeater {
            id: rowR
            model:  CodeModel.rowCount() + 1
            Repeater {
                id: columnR
                property int zrow: index
                model: CodeModel.columnCount() + 1

                Loader {
                    sourceComponent: {
                        if (zrow === CodeModel.rowCount()) {
                            Layout.fillHeight =  true
                            return filler
                        } else if (index === CodeModel.columnCount()) {
                            Layout.fillWidth =  true
                            return filler
                        } else {
                            return editor
                        }
                    }
                    property int xrow: zrow
                    property int xcolumn: index

                    Connections {
                        target: CodeModel
                        onColumnInserted: {
                            console.log("columnR updated")
                            if (xrow === 0 && xcolumn === 0) columnR.model = CodeModel.columnCount() + 1
                        }
                        onRowInserted: {
                            console.log("rowR updated")
                            if (xrow === 0 && xcolumn === 0) rowR.model = CodeModel.rowCount() + 1
                        }
                    }

                }

            }
        }


    }

}
