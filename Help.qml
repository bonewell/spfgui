import QtQuick 2.15

Item {
    id: root

    width: 200
    Column {
        id: help
        property bool hidden: false

        spacing: 5

        Text {
            text: "Help (click me)"
            font.bold: true

            MouseArea {
                anchors.fill: parent
                cursorShape:
                    Qt.PointingHandCursor
                onClicked: help.hidden = !help.hidden
            }
        }

        Text {
            text: "- Click on empty place to create a vertex."
            visible: !help.hidden
        }

        Text {
            text: "- Double click on the vertex to remove it."
            visible: !help.hidden
        }

        Text {
            text: "- Click one vertex and then other vertex to set the edge between them.Set weight in the popup."
            visible: !help.hidden
        }

        Text {
            text: "- Double click on the weight label to remove the edge."
            visible: !help.hidden
        }

        Text {
            text: "- Click one vertex and then long press on other vertex to calculate the shortest path."
            visible: !help.hidden
        }
    }
}
