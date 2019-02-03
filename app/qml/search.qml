import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Backbone 1.0 as Backbone
import App.Presenters 1.0


Rectangle { // view
    property SearchPagePresenter presenter;

    color: "gray"

    ListView {
        anchors.fill: parent
        anchors.margins: 30
        model: presenter.model
        spacing: 8

        delegate: Rectangle {
            width: parent.width
            height: 36
            color: modelData.color

            Text {
                anchors.centerIn: parent
                text: modelData.id + ""
            }

            MouseArea {
                anchors.fill: parent
                onClicked: presenter.selectItem(model.index)
            }
        }
    }
}
