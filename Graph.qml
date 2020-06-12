import QtQuick 2.15

Flickable {
    property alias vertexes: vertexes.children
    property alias edges: edges.children

    contentWidth: contentItem.childrenRect.x + contentItem.childrenRect.width
    contentHeight: contentItem.childrenRect.y + contentItem.childrenRect.height

    function add(x, y) {
    }

    Item {
        id: vertexes

        width: childrenRect.x + childrenRect.width
        height: childrenRect.y + childrenRect.height
    }

    Item {
        id: edges

        width: childrenRect.x + childrenRect.width
        height: childrenRect.y + childrenRect.height
    }
}
