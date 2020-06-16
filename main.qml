import QtQuick 2.15
import QtQuick.Window 2.15

import "graph"
import Spf 1.0

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
            center: model.center
            label: model.id
            color: model.color
            onCouple: view.couple(model.id)
            onRemove: graph.removeVertex(model.id)
        }
        edge: Edge {
            label: model.weight
            color: model.color
            from: model.from.center
            to: model.to.center
            onRemove: graph.removeEdge(model.from.id, model.to.id)
        }

        onAddVertex: graph.addVertex(p)
        onSetEdge: graph.addEdge(from, to, weight)
    }

    Help {}
}
