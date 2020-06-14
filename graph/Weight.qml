import QtQuick 2.15
import QtQuick.Controls 2.15

WeightInput {
    id: root

    property alias maximum: slider.to
    property alias value: slider.value

    width: 200
    height: 50

    Rectangle {
        anchors.fill: parent
        border.color: "black"
        border.width: 1
        radius: height / 2
    }

    Slider {
        id: slider
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: button.left
        to: 50
        from: 1
        stepSize: 1
        value: 1
    }

    RoundButton {
        id: button
        text: slider.value
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right

        onClicked: root.ok(slider.value)
    }
}
