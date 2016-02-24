import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: core
    color: printed.color_bg

    property string value: ""
    property int row_id: 0
    property int col_id: 0

    Component.onCompleted: {
        core.value = Signal.value(row_id, col_id)
        var type = Signal.type(row_id, col_id)
        console.log("cycle type is", type)
        switch (type) {
        case "hi": cycle.sourceComponent = hiCycle; break;
        case "hilo": cycle.sourceComponent = hiloCycle; break;
        case "lo": cycle.sourceComponent = loCycle; break;
        case "lohi": cycle.sourceComponent = lohiCycle; break;
        case "bus": cycle.sourceComponent = busCycle; break;
        case "busChange": cycle.sourceComponent = busChangeCycle; break;
        }
    }

    Component {
        id: hiCycle
        HiCycle {}
    }

    Component {
        id: loCycle
        LoCycle {}
    }

    Component {
        id: lohiCycle
        LoHiCycle {}
    }

    Component {
        id: hiloCycle
        HiLoCycle {}
    }

    Component {
        id: busCycle
        BusCycle {}
    }

    Component {
        id: busChangeCycle
        BusChangeCycle {}
    }

    Loader {
        id: cycle
        anchors.fill: parent
        sourceComponent: hiCycle
    }

    Component {
        id: textshow

        Rectangle {
            id: signamerec
            color: "transparent"
            width: printed.signalTextWidth
            height: printed.signalHeight


            Text {
                id: signalName
                height: signamerec.height * 0.9
                anchors.left: parent.left
                anchors.leftMargin: printed.valueLeftMargin
                //anchors.horizontalCenter: signamerec.horizontalCenter
                anchors.verticalCenter: signamerec.verticalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: printed.valueFontFamily
                font.pixelSize: printed.valueFontPixelSize
                text:  core.value
                color: printed.color_text
            }
        }
    }

    Component {
        id: textEdit
        Rectangle {
            id: signamerec
            color: "transparent"
            width: printed.signalTextWidth
            height: printed.signalHeight
            TextField {
                id: textField
                height: signamerec.height * 0.9
                anchors.left: parent.left
                anchors.horizontalCenter: signamerec.horizontalCenterc
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text:  core.value
                onAccepted: { core.value = text; Signal.addValue(row_id, col_id, text); txLoader.sourceComponent = textshow }
                Component.onCompleted: textField.forceActiveFocus()
            }
        }
    }

    Loader {
        id: txLoader
        sourceComponent: textshow
    }

    MouseArea {
        anchors.fill: parent
        onDoubleClicked: {
            txLoader.sourceComponent = textEdit
        }
        onClicked: {
            if (cycle.sourceComponent === hiCycle) {
                Signal.addType(row_id, col_id, "hilo")
                cycle.sourceComponent = hiloCycle
            } else if (cycle.sourceComponent === hiloCycle) {
                Signal.addType(row_id, col_id, "lo")
                cycle.sourceComponent = loCycle
            }else if (cycle.sourceComponent === loCycle) {
                Signal.addType(row_id, col_id, "lohi")
                cycle.sourceComponent = lohiCycle
            } else if (cycle.sourceComponent === lohiCycle){
                Signal.addType(row_id, col_id, "bus")
                cycle.sourceComponent = busCycle
            } else if (cycle.sourceComponent === busCycle){
                Signal.addType(row_id, col_id, "busChange")
                cycle.sourceComponent = busChangeCycle
            } else {
                Signal.addType(row_id, col_id, "hi")
                cycle.sourceComponent = hiCycle
            }
        }
    }
}

