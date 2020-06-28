import QtQuick 2.14
import QtTest 1.14

import "../graph"

Weight {
    id: weight

    width: 200
    height: 50

    SignalSpy {
        id: ok
        target: weight
        signalName: "ok"
    }

    TestCase {
        name: "weight"
        when: windowShown

        function test_ok() {
            ok.clear();
            mouseClick(weight, 175, 25);
            ok.wait()

            compare(ok.count, 1);
        }

        function test_change_value() {
            mouseClick(weight, 100, 25);

            compare(weight.value, 35);
        }
    }
}
