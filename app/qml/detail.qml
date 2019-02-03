import QtQuick 2.5
import QtQuick.Layouts 1.3
import Backbone 1.0 as Backbone
import App.Presenters 1.0


Rectangle { // view
    property DetailPagePresenter presenter;

    color: "silver"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        Rectangle {
            width: 100
            height: 100

            // TODO: color from item
            color: !!presenter.model ? presenter.model.color : "green"
        }


        Text {
            id: description
            Layout.fillHeight: true

            // TODO: get from model item
            text: {
                if (presenter.model) {
                    return presenter.model.id + " - " + presenter.model.color;
                }
                return "";
            }
        }

        // TODO: add blocks

        // TODO: add one mannually loading block
    }
}
