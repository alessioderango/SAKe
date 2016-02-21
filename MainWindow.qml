import QtQuick.Controls 1.3
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4
import QtMultimedia 5.5
import QtTest 1.1

ApplicationWindow {
    id: applicationWindow3
    visible: true
    width: 700
    height: 700
    title: qsTr("Sakè software")

    function createSpriteObjects() {
        component = Qt.createComponent("Sprite.qml");
        sprite = component.createObject(appWindow, {"x": 100, "y": 100});

        if (sprite == null) {
            // Error Handling
            console.log("Error creating object");
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open");
                onTriggered:{
                        console.log("Open action triggered");
                        createSpriteObjects();
                }
               // var component = Qt.createComponent("newProjectCalibration.qml");



            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }


    toolBar:ToolBar {
            RowLayout {
                anchors.fill: parent
                ToolButton {
                    iconSource: "qrc:/img/download.png"
                }

                Item { Layout.fillWidth: true }

            }
        }

    SplitView {
        id: splitView1
        //anchors.fill: parent
    }//MenuBar

}
