import QtQuick 2.15
import QtTest 1.15

import "../graph"

GraphView {
    id: graph
    anchors.fill: parent

    model: FakeModel{}
    editor: FakeWeight{}

    SignalSpy {
        id: addVertex
        target: graph
        signalName: "addVertex"
    }

    SignalSpy {
        id: setEdge
        target: graph
        signalName: "setEdge"
    }

    TestCase {
        name: "graph"
        when: windowShown

        function test_add_vertex() {
            addVertex.clear();
            mouseClick(graph, 50, 100);
            addVertex.wait();

            compare(addVertex.count, 1);
            compare(addVertex.signalArguments[0][0], Qt.point(50, 100));
        }

        function test_set_edge() {
            model.edgeExists = false;
            editor.value = 3;
            setEdge.clear();
            graph.couple(1);
            graph.couple(2);
            setEdge.wait();

            compare(setEdge.count, 1);
            compare(setEdge.signalArguments[0][0], 1);
            compare(setEdge.signalArguments[0][1], 2);
            compare(setEdge.signalArguments[0][2], 3);
        }
    }
}
