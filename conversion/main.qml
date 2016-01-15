import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("conversion 0.42")

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
                tooltip: "Convert"
                iconSource: "beautify.png"
                onClicked: Engine.convert(srcFormat.currentIndex, targetFormat.currentIndex, spin1.value, spin2.value, spin3.value, srcText.text)
            }
            Item { Layout.fillWidth: true }
            /*CheckBox {
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }*/
        }
    }

    SplitView {
        id: root
        anchors.fill: parent
        orientation: Qt.Horizontal

        GroupBox {
            id: src
            title: "Source"
            width: root.width / 2

            ColumnLayout {
                anchors.fill: parent

                ComboBox {
                    id: srcFormat
                    width: 200
                    model: [ "Float" ]
                }

                TextArea {
                    id:srcText
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Connections {
                        target: Engine
                        onTextUpdated: {
                            srcText.text = text
                        }
                    }

                    DropArea {
                        anchors.fill: parent
                        onDropped: {
                            Engine.droppedText(drop.text)
                        }
                    }
                }

            }
        }

        GroupBox {
            id: target
            title: "Target"
            width: root.width / 2
            height: root.height

            ColumnLayout {
                anchors.fill: parent

                RowLayout {
                    Layout.fillWidth: true
                    ComboBox {
                        id: targetFormat
                        width: 200
                        model: [ "Float", "Fixed" ]
                        onActivated: {
                            console.log(currentText)
                            if (currentText === "Float") {
                                label1.text = "Exp bits"
                            } else {
                                label1.text = "Mag bits"
                            }
                        }
                    }

                    Label {
                        id: label1
                        text: "Exp bits"
                    }

                    SpinBox {
                        id: spin1
                        minimumValue: 0
                    }

                    Label {
                        id: label2
                        text: "Frac bits"
                    }

                    SpinBox {
                        id: spin2
                        minimumValue: 0
                    }

                    Label {
                        id: label3
                        text: "Vectorization"
                    }

                    SpinBox {
                        id: spin3
                        minimumValue: 1
                    }
                }

                TextArea {
                    id: dstText
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    readOnly: true

                    Connections {
                        target: Engine
                        onConverted: {
                            dstText.text = text
                        }
                    }
                }

            }
        }
    }

}

