import QtQuick 2.14
import QtQuick.Controls 2.14

WeightEditor {
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
        focus: true
    }

    RoundButton {
        id: button
        text: slider.value
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        onClicked: ok(slider.value)
    }
}
