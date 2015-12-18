import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    width: 640
    height: 480

    ListModel {
        id: libraryModel
        ListElement {
            title: "A Masterpiece"
            author: "Gabriel"
        }
        ListElement {
            title: "Brilliance"
            author: "Jens"
        }
        ListElement {
            title: "Outstanding"
            author: "Frederik"
        }
    }

    TableView {
        id: tableView
        anchors.fill: parent

        TableViewColumn {
            role: "title"
            title: "Title"
            width: 100
        }
        TableViewColumn {
            role: "author"
            title: "Author"
            width: 200
        }
        model: libraryModel
    }
}

