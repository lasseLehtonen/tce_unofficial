import QtQuick 2.0
import QtQuick.Controls 1.4

Row {
    id: genericRow
    property string name: "signal"
    property int row_id: 0

    Component {
        id: textshow

        Rectangle {
            id: signamerec
            color: printed.color_bg
            width: printed.signalTextWidth
            height: printed.signalHeight


            Text {
                id: signalName
                width: signamerec.width * 0.9
                height: signamerec.height * 0.9
                anchors.verticalCenter: signamerec.verticalCenter
                anchors.horizontalCenter: signamerec.horizontalCenterc
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: printed.fontFamily
                font.pixelSize: printed.fontPixelSize
                text:  genericRow.name
                color: printed.color_text
            }

            MouseArea {
                anchors.fill: parent
                onDoubleClicked: {
                    txLoader.sourceComponent = textEdit
                }
            }
        }
    }

    Component {
        id: textEdit
        Rectangle {
            id: signamerec
            color: printed.color_bg
            width: printed.signalTextWidth
            height: printed.signalHeight
            TextField {
                id: textField
                width: signamerec.width * 0.9
                height: signamerec.height * 0.9
                anchors.verticalCenter: signamerec.verticalCenter
                anchors.horizontalCenter: signamerec.horizontalCenterc
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text:  genericRow.name
                onAccepted: { genericRow.name = text; txLoader.sourceComponent = textshow }
                Component.onCompleted: textField.forceActiveFocus()
            }
        }
    }

    Loader {
        id: txLoader
        sourceComponent: textshow
    }



    Repeater {
        id: clockRepeater
        model: printed.clockCycles
        GenericCycle {
            width: printed.cycleWidth
            height: printed.signalHeight
            row_id: genericRow.row_id
            col_id: index
        }
    }

    Rectangle {
        color: printed.color_bg
        width: printed.trailingWidth
        height: printed.signalHeight
    }
}

