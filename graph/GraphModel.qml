import QtQuick 2.0

Item {
    id: root

    property int uid: 0
    property alias vertexes: vertexes
    property alias edges: edges

    function addVertex(v) {
        vertexes.append({x: v.x, y: v.y, id: ++uid, color: "grey"})
    }

    function removeVertex(index) {
        vertexes.remove(index)
    }

    function setEdge(from, to, weight) {
        let b = root.vertexes.get(from);
        let e = root.vertexes.get(to);
        edges.append({from: {x: b.x, y: b.y}, to: {x: e.x, y: e.y},
                      weight: weight, color: "grey"})
    }

    function removeEdge(index) {
        edges.remove(index)
    }

    ListModel {
        id: vertexes
    }

    ListModel {
        id: edges
    }
}
