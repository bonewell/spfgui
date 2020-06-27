import QtQuick 2.15
import QtQuick.Shapes 1.15

Item {
    id: root

    signal remove()

    property point from
    property point to

    property alias label: label.text

    x: Math.min(from.x, to.x)
    y: Math.min(from.y, to.y)

    width: Math.abs(to.x - from.x)
    height: Math.abs(to.y - from.y)

    property point begin: Qt.point(from.x - root.x, from.y - root.y)
    property point end: Qt.point(to.x - root.x, to.y - root.y)

    Shape {
        anchors.fill: parent
        ShapePath {
            id: line
            startX: root.begin.x
            startY: root.begin.y
            PathLine { x: root.end.x; y: root.end.y }
        }
    }

    Rectangle {
        anchors.centerIn: parent
        width: childrenRect.width
        height: childrenRect.height
        color: "white"

        Text {
            id: label
            font.pixelSize: 15
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onDoubleClicked: root.remove()
        }
    }

    states: [
        State {
            name: "new"
            PropertyChanges { target: label; color: "gray" }
            PropertyChanges { target: line; strokeColor: "gray" }
        },
        State {
            name: "ready"
            PropertyChanges { target: label; color: "black" }
            PropertyChanges { target: line; strokeColor: "black" }
        },
        State {
            name: "error"
            PropertyChanges { target: label; color: "red" }
            PropertyChanges { target: line; strokeColor: "red" }
        }
    ]
}
