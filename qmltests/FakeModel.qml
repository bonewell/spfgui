import QtQuick 2.14

Item {
    property int vertexes: 1
    property int edges: 1
    property bool edgeExists: true

    function exists(from, to) {
        return edgeExists;
    }
}
