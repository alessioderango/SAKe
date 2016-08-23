import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    //    color: "#e7e1e1"
    title: qsTr("Options2")


    Rectangle
    {
        id: parameter
        color:"white"
        width: parent.width
        height: parent.height

        anchors.fill: parent

        ColumnLayout {
            id: columnLayout1
            x: 0
            y: 56
            width: 180
            height: 107
            spacing: 0

            Row {
                id: rowLayout1
                width: 100
                height: 100
                spacing: 6

                Image{ source: "qrc:/img/project.png"
                    width: 20
                    height: 20

                }
                Label {
                    id: label2
                    text: qsTr("Projects")
                    anchors.top: parent.top
                    anchors.topMargin: 4
                    verticalAlignment: Text.AlignVCenter
                }
            }


        }

        Rectangle{
            id: rectangle1
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 56
            anchors.left: parent.left
            anchors.leftMargin: 180

            TabView {
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0

                Tab {
                    title: "Options"
                    Rectangle { color: "red" }
                }
                Tab {
                    title: "Blue"
                    Rectangle { color: "blue" }
                }
                Tab {
                    title: "Green"
                    Rectangle { color: "green" }
                }
            }

        }

        Label {
            id: label1
            x: 186
            width: 88
            height: 23
            text: qsTr("Projects")
            anchors.top: parent.top
            anchors.topMargin: 19
            font.pointSize: 13
            font.bold: true
        }


    }
}
