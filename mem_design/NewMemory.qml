import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

ColumnLayout {
    anchors.fill: parent
    anchors.topMargin: parent.height * 0.01
    anchors.bottomMargin: parent.height * 0.01
    anchors.leftMargin: parent.height * 0.01
    anchors.rightMargin: parent.height * 0.01

    GroupBox {
        title: "General options"
        width: parent.width
        Layout.fillWidth: true

        RowLayout {
            Layout.fillWidth: true
            width: parent.width

            Label {
                Layout.alignment: Qt.AlignVCenter
                text: "File name"
            }

            TextField {
                id: fileName
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }


    GridLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        width: parent.width
        rows: 1
        flow: GridLayout.TopToBottom

        GroupBox {
            Layout.alignment: Qt.AlignTop
            title: "Memory Options"

            GridLayout {
                rows: 4
                flow: GridLayout.TopToBottom

                Label {
                    Layout.alignment: Qt.AlignVCenter
                    text: "Address width"
                }

                Label {
                    Layout.alignment: Qt.AlignVCenter
                    text: "Memory width"
                }

                Label {
                    Layout.alignment: Qt.AlignVCenter
                    text: "Memory depth"
                }

                Label {
                    Layout.alignment: Qt.AlignVCenter
                    text: "Flip-flop break-even"
                }


                TextField {
                    id: addrWidth
                    validator: IntValidator {bottom: 1;}
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                }
                TextField {
                    id: memWidth
                    validator: IntValidator {bottom: 1;}
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                }
                TextField {
                    id: memDepth
                    validator: IntValidator {bottom: 1;}
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                }
                TextField {
                    id: ffBreakEven
                    validator: IntValidator {bottom: 1;}
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                }
            }
        }

        GroupBox {
            Layout.alignment: Qt.AlignTop
            title: "Generated interface"

            ColumnLayout {
                CheckBox {
                    text: "Chip Select"
                }
                CheckBox {
                    text: "Chip Select (negated)"
                }
                CheckBox {
                    text: "Write Enable"
                }
                CheckBox {
                    text: "Write Enable (negated)"
                    checked: true
                }
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            GroupBox {
                title: "Memory Type"

                RowLayout {
                    ExclusiveGroup { id: memEG }
                    RadioButton {
                        text: "Single-port"
                        checked: true
                        exclusiveGroup: memEG
                    }
                    RadioButton {
                        text: "Dual-port"
                        exclusiveGroup: memEG
                    }
                }
            }

            GroupBox {
                title: "Generation Algorithm"

                RowLayout {
                    ExclusiveGroup { id: algoEG }
                    RadioButton {
                        text: "Width-first"
                        exclusiveGroup: algoEG
                    }
                    RadioButton {
                        text: "Depth-first"
                        exclusiveGroup: algoEG
                    }
                    RadioButton {
                        text: "Size-first"
                        checked: true
                        exclusiveGroup: algoEG
                    }
                }
            }
        }
    }

    TextArea {
        Layout.fillHeight: true
        Layout.fillWidth: true
        text: "Memory Designer initialized\n\n"
        readOnly: true
    }

    Button {
        Layout.alignment: Qt.AlignRight
        text: "Generate"
        onClicked: {
            MemoryModel.setOption("fileName", fileName.text)
            MemoryModel.setOption("addrWidth", addrWidth.text)
            MemoryModel.setOption("memWidth", memWidth.text)
            MemoryModel.setOption("memDepth", memDepth.text)
            MemoryModel.setOption("ffBreakEven", ffBreakEven.text)
            statusBar.text =  "Generate clicked"
        }
    }
}
