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
                onClicked: Engine.convert(srcFormat.currentIndex, targetFormat.currentIndex, tspin1.value, tspin2.value, tspin3.value, spin1.value, spin2.value, spin3.value, srcText.text)
            }
            Item { Layout.fillWidth: true }
            /*CheckBox {
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }*/
        }
    }

    ColumnLayout {
        anchors.fill: parent

        GroupBox {
            title: "Source options"

            RowLayout {

                ComboBox {
                    id: srcFormat
                    width: 200
                    model: [ "Float (float)", "Float (binary)", "Float (hex)", "Fixed (binary)" ]
                    onActivated: {
                        if (index < 3) {
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
        }

        GroupBox {
            title: "Target options"

            RowLayout {

                ComboBox {
                    id: targetFormat
                    width: 200
                    model: [ "Float", "Float (hex)", "Fixed"]
                    onActivated: {
                        if (index < 2) {
                            tlabel1.text = "Exp bits"
                        } else {
                            tlabel1.text = "Mag bits"
                        }
                    }
                }

                Label {
                    id: tlabel1
                    text: "Exp bits"
                }

                SpinBox {
                    id: tspin1
                    minimumValue: 0
                }

                Label {
                    id: tlabel2
                    text: "Frac bits"
                }

                SpinBox {
                    id: tspin2
                    minimumValue: 0
                }

                Label {
                    id: tlabel3
                    text: "Vectorization"
                }

                SpinBox {
                    id: tspin3
                    minimumValue: 1
                }
            }
        }

        SplitView {
            id: root
            orientation: Qt.Horizontal
            Layout.fillHeight: true
            Layout.fillWidth: true

            GroupBox {
                id: src
                title: "Source"
                width: root.width / 2

                ColumnLayout {
                    anchors.fill: parent

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
}
