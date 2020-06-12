import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("SpfGui")

    Graph {
        id: graph
        anchors.fill: parent
        anchors.margins: 10

        vertexes: [
            Vertex{ x: 10; y: 10 },
            Vertex{ x: 100; y: 100 }
        ]
    }

    MouseArea {
        anchors.fill: parent
        onClicked: graph.add(mouseX, mouseY)
    }
}
