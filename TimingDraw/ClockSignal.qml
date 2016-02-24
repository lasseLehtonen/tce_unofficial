import QtQuick 2.0

Row {
    id: clockRow

    Rectangle {
        color: printed.color_bg
        width: printed.signalTextWidth
        height: printed.signalHeight
        Text {
            id: clkText
            width: parent.width * 0.9
            height: parent.height * 0.9
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: printed.fontFamily
            font.pixelSize: printed.fontPixelSize
            text:  "clk"
            color: printed.color_text

        }
    }

    Repeater {
        id: clockRepeater
        model: printed.clockCycles
        ClockCycle {
            width: printed.cycleWidth
            height: printed.signalHeight

            Connections {
                target: printed
                onRedraw: redraw();
            }
        }
    }

    Rectangle {
        color: printed.color_bg
        width: printed.trailingWidth
        height: printed.signalHeight
    }
}

