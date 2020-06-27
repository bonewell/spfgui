import QtQuick 2.15

Rectangle {
    id: root

    signal couple()
    signal remove()

    property point center: Qt.point(0,0)
    property alias label: label.text

    x: center.x - width / 2
    y: center.y - height / 2
    border { width: 1 }
    radius: 25

    height: radius * 2
    width: radius * 2

    Text {
        id: label
        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: root.radius
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: root.couple()
        onDoubleClicked: root.remove()
    }

    states: [
        State {
            name: "new"
            PropertyChanges { target: label; color: "gray" }
            PropertyChanges { target: root; border.color: "gray" }
        },
        State {
            name: "ready"
            PropertyChanges { target: label; color: "black" }
            PropertyChanges { target: root; border.color: "black" }
        },
        State {
            name: "error"
            PropertyChanges { target: label; color: "red" }
            PropertyChanges { target: root; border.color: "red" }
        }
    ]
}
