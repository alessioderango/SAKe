import QtQuick 2.0
import QtQuick.Window 2.0
import CustomPlot 1.0
import CustomPlotMobilityFunction 1.0
import CustomPlotKernel 1.0
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4
import QtQuick.Controls 1.4

ApplicationWindow {
    id: applicationWindow2
    visible: true
    Layout.fillWidth: true
    Layout.fillHeight: true
    title: qsTr("Sakè software")
    objectName: "mainwindow"
    
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }//MenuBar


    GridLayout {
        Layout.fillWidth: true
        id: columnLayout1
        rowSpacing: 0
        columnSpacing: 0
        columns: 1
        rows:3
        anchors.fill: parent
        Layout.maximumWidth:  1500
        Layout.maximumHeight:  1500


        CustomPlotItem {

            id: customPlotFitness
            height: 200
            Layout.fillWidth: true
             Layout.fillHeight: true
            Layout.minimumWidth:  700
            Layout.minimumHeight:  230
            Layout.maximumWidth:  1000000
            Layout.maximumHeight: 1000000


            objectName: "customPlotFitness"
            //antialiasing: true
            // Component.onCompleted: initCustomPlot()


        }

        CustomPlotKernel {

            id: customPlotKernel
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth:  700
            Layout.minimumHeight:  230
            Layout.maximumWidth:  1000000
            Layout.maximumHeight: 1000000
            objectName:  "customPlotKernel"
            //anchors.top: customPlot1.bottom
            // Component.onCompleted: initCustomPlotMobilityFunction()

        }

        CustomPlotMobilityFunction {

            id: customPlotMobilityFunction
            Layout.fillWidth: true
             Layout.fillHeight: true
            Layout.preferredWidth: 700
            Layout.preferredHeight: 230
            clip: false
            Layout.minimumWidth:  700
            Layout.minimumHeight:  230
            Layout.maximumWidth:  1000000
            Layout.maximumHeight: 1000000

            objectName:  "customPlotMobilityFunction"
            //anchors.top: customPlot1.bottom
            // Component.onCompleted: initCustomPlotMobilityFunction()

        }



    }//Rectangle
    
    
    
    
    //}
    
    
}//Application

