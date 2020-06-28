import QtQuick 2.14

Flickable {
    id: root

    signal addVertex(point p)
    signal setEdge(int from, int to, int weight)
    signal getPath(int from, int to)

    property size canvas: Qt.size(width, height)

    property var model
    property alias vertex: vertexes.delegate
    property alias edge: edges.delegate

    property WeightEditor editor: Weight{ anchors.centerIn: parent; visible: false }

    QtObject {
        id: internal
        property int from: -1
        property int to: -1
    }

    contentWidth: canvas.width
    contentHeight: canvas.height
    contentX: contentWidth / 4
    contentY: contentHeight / 4

    function couple(id) {
        if (internal.from === -1) {
            internal.from = id;
        } else if (id !== internal.from &&
                   !root.model.exists(internal.from, id)) {
            internal.to = id;
            editor.show();
        }
    }

    function path(id) {
        if (internal.from !== -1 && id !== internal.from) {
            root.getPath(internal.from, id);
            internal.from = -1;
        }
    }

    MouseArea {
        width: root.contentWidth
        height: root.contentHeight
        onClicked: root.addVertex(Qt.point(mouseX, mouseY))
    }

    Repeater {
        id: edges
        model: root.model.edges
    }

    Repeater {
        id: vertexes
        model: root.model.vertexes
    }

    Connections {
        target: editor
        function onOk(value) {
            root.setEdge(internal.from, internal.to, value);
            internal.from = internal.to = -1;
            editor.hide();
        }
    }

    Component.onCompleted: children.push(editor)
}
