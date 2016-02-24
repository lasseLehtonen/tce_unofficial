import QtQuick 2.0

Row {
    id: resetRow

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
            text:  "rst_n"
            color: printed.color_text

        }
    }
    LoHiCycle {
        id: firsrCycle
        width: printed.cycleWidth
        height: printed.signalHeight

        Connections {
            target: printed
            onRedraw: firsrCycle.redraw()
        }
    }
    Repeater {
        id: clockRepeater
        model: printed.clockCycles - 1
        HiCycle {
            width: printed.cycleWidth
            height: printed.signalHeight

            Connections {
                target: printed
                onRedraw: redraw()
            }
        }
    }

    Rectangle {
        color: printed.color_bg
        width: printed.trailingWidth
        height: printed.signalHeight
    }
}

