import QtQuick 2.15

Item {
    id: root

    signal ok(int value)

    function show() { visible = true }
    function hide() { visible = false }
}
