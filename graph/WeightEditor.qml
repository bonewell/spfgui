import QtQuick 2.14

Item {
    id: root

    signal ok(int value)

    function show() { visible = true }
    function hide() { visible = false }
}
