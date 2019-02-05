import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import Backbone 1.0 as Backbone


Window {
    readonly property alias stackView: stack

    visible: true
    width: 640
    height: 480
    title: qsTr("DI Application")

    StackView {
        id: stack
        anchors.fill: parent

        Component.onCompleted: stack.openPage(Qt.resolvedUrl("index.qml"))

        function openPage(pageUrl) {
            var stackView = stack;
            router.createPage(pageUrl, function (page) {
                if (!page) {
                    console.error("page ", pageUrl, " was not created");
                    return;
                }
                if (stackView) {
                    stackView.push(page);
                } else {
                    console.error("stackView is not available any more");
                }
            });
        }
    }
}
