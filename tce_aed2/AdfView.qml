import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

Item {
    anchors.fill: parent

    TextArea {
        anchors.fill: parent
        id: adfText
        readOnly: true
        text: "Not generated yet."
    }
}

