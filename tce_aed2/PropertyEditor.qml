import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

Item {
    anchors.fill: parent

    GroupBox {
        title: "General"
        GridLayout {
            rows: 1
            columns: 2

            Label { text: "Project Name" }
            TextField {
                text: "default"
                id: projectName
                onTextChanged: window.title = "TCE aed2 - " + text + ".tceprj"
                onEditingFinished: {
                    if (text === "") {
                        text = "default"
                    }
                }
            }

        }
    }
}

