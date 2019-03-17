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
                ListElement { text: "wow" ; type: "branch" }
                ListElement { text: "wow" ; type: "branch" }
                ListElement { text: "wow" ; type: "branch" }
                ListElement { text: "wow" ; type: "branch" }
                ListElement { text: "wow" ; type: "branch" }
                ListElement { text: "wow" ; type: "branch" }
            }

            delegate: Backbone.DelegateBuilder {

                width: parent.width
                height: childrenRect.height

                context: model.type

                delegate: Rectangle {
                    property BranchPresenter $branchPresenter;
                    property SchedulePresenter $schedulePresenter;

                    width: parent.width
                    height: 100
                    color: "lightblue"

                    Component.onCompleted: {
                        console.log(model.index, " injected: ", $branchPresenter, $schedulePresenter);
                    }
                }
            }
        }
    }

    Component {
        id: branchMiniCard
        Item {}
    }

    Component {
        id: buildingMiniCard
        Item {}
    }

    Component {
        id: settlementMiniCard
        Item {}
    }
}
