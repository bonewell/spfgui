import QtQuick 2.15
import QtTest 1.15

import "../graph"

Vertex {
    id: vertex

    anchors.fill: parent

    SignalSpy {
        id: remove
        target: vertex
        signalName: "remove"
    }

    TestCase {
        name: "vertex"
        when: windowShown

        function test_remove_vertex() {
            remove.clear();
            mouseDoubleClick(vertex, 25, 25);
            remove.wait()

            compare(remove.count, 1);
        }
    }
}
