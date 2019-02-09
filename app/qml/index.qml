import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Backbone 1.0 as Backbone
import App.Presenters 1.0


Backbone.Page { // view
    id: page

    property QtObject stackView
    property IndexPagePresenter presenter

    ColumnLayout {
        anchors {
            fill: parent
            margins: 10
        }
        spacing: 16

        TextField {
            width: parent.width
            Layout.fillWidth: true
            Layout.minimumHeight: 64
            Layout.preferredHeight: 64
            Layout.maximumHeight: 96
            onAccepted: presenter.searchByText(text)

            placeholderText: "search smth"
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 8
            clip: true

            model: ListModel {
                ListElement { }
                ListElement { }
                ListElement { }
                ListElement { }
                ListElement { }
                ListElement { }
                ListElement { }
            }

            delegate: Rectangle {
                width: ListView.view.width
                height: 36
                color: !!(model.index % 2)
                    ? "lightgreen"
                    : "lightblue"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stackView.openPage(Qt.resolvedUrl("search.qml"))
                    }
                }
            }
        }
    }
}
