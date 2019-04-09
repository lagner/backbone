import QtQuick 2.8
import QtQuick.Layouts 1.3
import Backbone 1.0 as Backbone
import App.Presenters 1.0


Backbone.Page {
    id: page

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Backbone.InjectorBlock {
            Layout.fillWidth: true
            height: 300

            Rectangle {
                property BranchPresenter $presenter
                property SchedulePresenter $schedule

                anchors.fill: parent
                color: "lightgreen"
            }
        }

        Backbone.InjectorBlock {
            Layout.fillWidth: true
            height: 100

            Rectangle {
                anchors.fill: parent
                color: "yellow"
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
