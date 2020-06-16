import QtQuick 2.15

Rectangle {
    id: root

    signal couple()
    signal remove()

    property point center: Qt.point(0,0)
    property alias label: label.text
    property color color: "black"

    x: center.x - width / 2
    y: center.y - height / 2
    border { color: root.color; width: 1 }
    radius: 25

    height: radius * 2
    width: radius * 2

    Text {
        id: label
        anchors.fill: parent

        color: root.color
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
}
