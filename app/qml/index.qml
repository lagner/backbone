import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Backbone 1.0 as Backbone
import App.Presenters 1.0


Backbone.Page { // view
    id: view

    property IndexPagePresenter presenter

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 30
        spacing: 30

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 48

            Row {
                Button {
                    text: "collect"
                    onClicked: presenter.collect()
                }
            }
        }

        TextField {
            Layout.fillWidth: true
            Layout.minimumHeight: 64
            Layout.preferredHeight: 64
            Layout.maximumHeight: 96
            onAccepted: presenter.searchByText(text)
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true


            Backbone.Block {
                property DetailPagePresenter presenter;

                property Component delegate: Item {

                    Rectangle {
                    }
                }

                width: parent.width
                height: 100
                anchors.bottom: parent.bottom

                Rectangle {
                    anchors.fill: parent
                    color: "lightblue"
                }
            }
        }
    }
}
