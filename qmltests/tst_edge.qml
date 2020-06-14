import QtQuick 2.15
import QtTest 1.15

import "../graph"

Edge {
    id: edge

    SignalSpy {
        id: remove
        target: edge
        signalName: "remove"
    }

    TestCase {
        name: "edge"
        when: windowShown

        function test_point_of_item() {
            edge.from = Qt.point(10, 40);
            edge.to = Qt.point(30, 20);

            compare(edge.x, 10);
            compare(edge.y, 20);
        }

        function test_size_of_item() {
            edge.from = Qt.point(100, 400);
            edge.to = Qt.point(150, 200);

            compare(edge.width, 50);
            compare(edge.height, 200);
        }

        function test_line_from_left_to_right() {
            edge.from = Qt.point(10, 20);
            edge.to = Qt.point(20, 40);

            compare(edge.begin, Qt.point(0, 0));
            compare(edge.end, Qt.point(10, 20));
        }

        function test_line_from_right_to_left() {
            edge.from = Qt.point(50, 10);
            edge.to = Qt.point(20, 20);

            compare(edge.begin, Qt.point(30, 0));
            compare(edge.end, Qt.point(0, 10));
        }

        function test_remove_edge() {
            edge.from = Qt.point(0, 0);
            edge.to = Qt.point(10, 10);

            remove.clear();
            mouseDoubleClick(edge, 5, 5);
            remove.wait()

            compare(remove.count, 1);
        }
    }
}
