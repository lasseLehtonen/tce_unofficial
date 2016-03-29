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

    Flickable {
        anchors.fill: parent
        anchors.margins: 10
        contentHeight: grid.height
        contentWidth: grid.width
        clip: true

        GridLayout {
            id: grid
            width: CodeModel.codeWidth + 20 + 40
            height: CodeModel.codeHeight + 20 + 24

            rows: CodeModel.rows + 2
            columns: CodeModel.columns + 2
            rowSpacing: 0
            columnSpacing: 0

            property int selX: 0
            property int selY: 0

            Component {
                id:editor
                SlotEditor {
                }
            }


            Component {
                id: filler
                Rectangle {
                    width: 10
                    height: 10
                    color: "red"
                    visible: true
                }
            }

            Component {
                id: columnHeader
                Rectangle {
                    width: 100
                    height: 24
                    color: "transparent"
                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        text: xcolumn > 1 ? "Bus " + (xcolumn-1) : "Misc"
                        verticalAlignment: Qt.AlignVCenter
                    }
                }
            }

            Component {
                id: rowHeader
                Rectangle {
                    width: 40
                    height: 24
                    color: "transparent"
                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        text: xrow
                        verticalAlignment: Qt.AlignVCenter
                    }
                }
            }


            Repeater {
                id: rowR
                model:  CodeModel.rows + 2
                Repeater {
                    id: columnR
                    property int zrow: index
                    model: CodeModel.columns + 2

                    Loader {
                        //Component: Slot {}

                        sourceComponent: {
                            if (zrow === CodeModel.rows + 1) {
                                Layout.fillHeight =  true
                                return filler
                            } else if (index === CodeModel.columns + 1) {
                                Layout.fillWidth =  true
                                return filler
                            } else if (zrow === 0 && index > 0) {
                                return columnHeader
                            } else if (index === 0 && zrow > 0) {
                                return rowHeader
                            } else if (index === 0 && zrow === 0) {
                                return filler
                            } else {
                                return editor
                            }
                        }
                        focus: false
                        property int xrow: zrow
                        property int xcolumn: index


                    }

                }
            }

        }
    }

}
