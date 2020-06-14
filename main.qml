import QtQuick 2.15
import QtQuick.Window 2.15

import "graph"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("SpfGui")

    GraphModel {
        id: graph
    }

    GraphView {
        id: view
        anchors.fill: parent
        canvas: Qt.size(width * 2, height * 2)

        model: graph
        vertex: Vertex {
            x: model.x - width / 2
            y: model.y - height / 2
            label: model.id
            color: model.color
            onCouple: view.couple(model.index)
            onRemove: graph.removeVertex(model.index)
        }
        edge: Edge {
            label: model.weight
            color: model.color
            from: Qt.point(model.from.x, model.from.y)
            to: Qt.point(model.to.x, model.to.y)
            onRemove: graph.removeEdge(model.index)
        }

        onAddVertex: graph.addVertex(p)
        onSetEdge: graph.setEdge(from, to, weight)
    }
}
