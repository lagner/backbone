import QtQuick 2.0
import App.Presenters 1.0


Rectangle {
    property BranchPresenter $branchPresenter
    property SchedulePresenter $schedulePresenter

    width: parent.width
    height: 100
    color: "lightblue"

    Component.onCompleted: {
        console.log(model.index, " injected: ", $branchPresenter, $schedulePresenter);
    }
}
