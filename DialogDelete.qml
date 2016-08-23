import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

MessageDialog {
    title: "Warning"
    icon: StandardIcon.Information
    text: "Do you want to delete permanently the project?"
    standardButtons: StandardButton.Yes | StandardButton.No
    Component.onCompleted: visible = true
    onYes: sakeStart.deleteProject(description_role)
    onNo: console.log("didn't copy")
}
