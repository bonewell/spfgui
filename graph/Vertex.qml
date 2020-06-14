import QtQuick 2.15

Rectangle {
    id: root

    signal couple()
    signal remove()

    property alias label: label.text
    property color color: "black"

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
