import QtQuick 2.0
import QtQuick.Window 2.0
import CustomPlot 1.0
import CustomPlotMobilityFunction 1.0
import CustomPlotKernel 1.0
import CustomPlotRegression 1.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQml.Models 2.2

ApplicationWindow {
    id: applicationWindow1
    visible: true
    width: 800
    height: 800
    title: qsTr("Sake software")

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
            Menu {
                title: qsTr("&New Project");

                MenuItem {
                    text: qsTr("&New Calibration Project");
                    onTriggered:{
                        console.log("Open action triggered Calibration Project");
                    }
                }
                MenuItem {
                    text: qsTr("&New Validation Project");
                    onTriggered:{
                        console.log("Open action triggered Validation Project");

                    }

                }



                // var component = Qt.createComponent("newProjectCalibration.qml");



            }




            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: qsTr("Help")


            MenuItem {
                text: qsTr("&About");
                onTriggered:{
                    console.log("Open action triggered Calibration Project");
                }
            }
            MenuItem {
                text: qsTr("&License");
                onTriggered:{
                    console.log("Open action triggered Validation Project");

                }

            }


        }

    }//MenuBar


    toolBar:ToolBar {
        Layout.fillHeight: true
        Layout.minimumHeight: 77
        Layout.minimumWidth:  80

        style: ToolBarStyle {
            padding {
                left: 8
                right: 8
                top: 3
                bottom: 3
            }
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 40
                border.color: "#d4d4d4"
                gradient: Gradient {
                    GradientStop { position: 0 ; color: "#fff" }
                    GradientStop { position: 1 ; color: "#d4d4d4" }
                }
            }
        }
        RowLayout {
            //            anchors.fill: parent



            ToolButton{
                //                iconSource: "qrc:/img/check.png"
                id:calibration
                width: parent.height
                onClicked: {
                    console.log("Action Validation Project");
                    var component = Qt.createComponent("parameters.qml")

                    var window    = component.createObject(applicationWindow1)

                }

                Layout.minimumHeight: 77
                Layout.minimumWidth:  70
                Image {
                    id: myToolButtonIconCalibration
                    source: "qrc:/img/download.png"
                    width: 24
                    height:  24
                    y: calibration.y + 5
                    anchors.horizontalCenter: calibration.horizontalCenter
                }

                Text {
                    text: qsTr("New\nCalibration\nProject")
                    y: myToolButtonIconCalibration.y + myToolButtonIconCalibration.height + 3
                    anchors.horizontalCenter: myToolButtonIconCalibration.horizontalCenter
                    horizontalAlignment: Text.AlignJustify | Text.AlignHCenter | Text.AlignVCenter
                }

            }

            ToolButton{
                //                iconSource: "qrc:/img/check.png"
                width: parent.height
                id: validation
                onClicked: {
                    console.log("Action Validation Project2");
                    var component = Qt.createComponent("parametersValidationLayout.qml")

                    var window    = component.createObject(applicationWindow1)

                }

                Layout.minimumHeight: 77
                Layout.minimumWidth:  70
                Image {
                    id: myToolButtonIconValidation
                    width: 24
                    height:  24
                    source: "qrc:/img/check.png"
                    y: validation.y + 5
                    anchors.horizontalCenter: validation.horizontalCenter
                }

                Text {
                    text: qsTr("New\nValidation\nProject")
                    y: myToolButtonIconValidation.y + myToolButtonIconValidation.height + 3
                    anchors.horizontalCenter: myToolButtonIconValidation.horizontalCenter
                    horizontalAlignment: Text.AlignJustify | Text.AlignHCenter | Text.AlignVCenter

                }

            }

            ToolButton {
                id :myToolButton
                onClicked: {
                    console.log("Action Calibration Project");
                    var component = Qt.createComponent("parametersRegression.qml")

                    var window    = component.createObject(applicationWindow1)

                }

                Layout.minimumHeight: 77
                Layout.minimumWidth:  70
                Image {
                    id: myToolButtonIcon
                    width: 24
                    height:  24
                    source: "qrc:/img/regression.png"
                    y: myToolButton.y + 5
                    anchors.horizontalCenter: myToolButton.horizontalCenter
                }

                Text {
                    text: qsTr("New\nRegression\nProject")
                    y: myToolButtonIcon.y + myToolButtonIcon.height + 3
                    anchors.horizontalCenter: myToolButtonIcon.horizontalCenter
                    horizontalAlignment: Text.AlignJustify | Text.AlignHCenter | Text.AlignVCenter
                }


            }

            ToolBarSeparator{}

            //            ToolButton{
            //                iconSource: "qrc:/img/check.png"
            //                width: parent.height
            //                onClicked: {
            //                    console.log("Regression Validation Project2");
            ////                    var component = Qt.createComponent("parametersValidationLayout.qml")

            ////                    var window    = component.createObject(applicationWindow1)
            ////                      sakeStart.startRegression();
            //                }

            //            }

            Item { Layout.fillWidth: true }

        }
    }

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        Rectangle {
            width: 180
            Layout.minimumWidth: 180
            Layout.maximumWidth: 180
            color: "white"

            //height: 200



//            MyTreeModel {
//                id: theModel

//            }
            //@disable-check M300
            TreeView {
                anchors.fill: parent
                model: theModel
                id: treeViewId
                //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                //color: "white"
                alternatingRowColors : false
                itemDelegate: Rectangle {
                    property color frameColor: "white"
                    property color fillColor: "blue"
                    //                    color: { if(styleData.selected) {
                    //                             console.log("fillColor "+styleData.value);
                    //                            fillColor
                    //                            }
                    //                            else{
                    //                             console.log("frameColor "+styleData.value);
                    //                            frameColor
                    //                        }
                    //                    }
                    height: 20


                    Text {
                        id:textItem
                        //color: styleData.selected ? "white" : "black"
                        //anchors.verticalCenter: parent.verticalCenter
                        text: styleData.value === undefined ? "" : styleData.value // The branches don't have a description_role so styleData.value will be undefined
                        //anchors.left: parent ;
                        color: "black"
                    }

                    Button {
                        anchors.fill: parent
                        style: ButtonStyle {
                            background: Rectangle {
                                implicitWidth: 16
                                implicitHeight: 16
                                radius: width/2
                                color: control.hovered ? "lightsteelblue": "white"
                                border.color: "white"
                                //Text {text: styleData.value ; anchors.left: parent ; color: "black"}

                            }}

                        Row {

                            Image{ source: "qrc:/img/project.png"
                                width: 17
                                height: 17

                            }
                            //                            Image{ source: "qrc:/img/download.png"
                            //                                width: 17
                            //                                height: 17}
                            Text { text: ' ' +  styleData.value }

                        }
                        onClicked: {
                            console.log("onClicked "+styleData.value
                                        +" "+model.description_role );
                            // parent.color =fillColor
//                              var list = sakeStart.getAllElementsFromProjectName(model.description_role)
                              var list = sakeStart.getAllElementsFromProjectName(model.description_role)
                            console.log("tipo Progetto = "+list[list.length -1])
                            var component;
                             var window  ;
                            if(list[list.length -1] === "CalibrationProject"){
                                component = Qt.createComponent("parametersProjectAlreadyExist.qml")
                                window= component.createObject(applicationWindow1)
                                console.log(window.f(list))
                            }else
                                if(list[list.length -1] === "RegressionProject"){
                                    component = Qt.createComponent("parametersRegressionProjectAlreadyExist.qml")
                                     window = component.createObject(applicationWindow1)
                                    console.log(window.f(list))
                                }
//                                else
//                                    if(list[list.length -1] === "ValidationProject"){
//                                        component = Qt.createComponent("parametersProjectAlreadyExist.qml")
//                                        console.log("listview1.model.get(listview1.currentIndex).name")
//                                    }

//                            console.log("ciao"+list.length )
//                            for(var i = 0; i < list.length-1 ; i++){
//                                console.log(list[i])
//                            }


//                            insert();

                        }
                        //                        onDoubleClicked: {


                        //                            console.log(styleData.selected)
                        //                        }

                    }
                }

                TableViewColumn {
                    role: "name_role"
                    title: "Projects"
                }
                //                TableViewColumn {
                //                    role: "description_role"
                //                    title: "Description"
                //                }

//                function insert(){
//                    component = Qt.createComponent("TableColumnTreeView.qml");
//                        sprite = component.createObject(treeViewId, {"x": 100, "y": 100});
//                       treeViewId.insertColumn(0,sprite);
//                }


            }



            //            ListModel {
            //                objectName: "ListProjects"
            //                id: model
            //                function addElementList(projectName){

            //                    console.log("Entrato!!!!!!!!!!!!!!!!  "+ projectName);

            //                    model.clear()
            //                    for (var i=0; i<projectName.length; i++){
            //                        console.log("Entrato!!!!!!!!!!!!!!!!  "+ projectName[i]);
            //                        model.append({"name": projectName[i]})

            //                    }


            //                }

            //            }
            //            Text {
            //                id: text1
            //                width: 180
            //                text: qsTr("Projects")
            //                horizontalAlignment: Text.AlignHCenter
            //                font.pixelSize: 12
            //            }

            Component {
                id: contactDelegate
                Column {
                    Item {

                        width: 180; height: 20
                        Row {
                            Image{ source: "qrc:/img/project.png"
                                width: 17
                                height: 17}
                            Text { text: ' ' + name }

                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {

                                listview1.currentIndex = index


                            }
                            onDoubleClicked: {

                                var component = Qt.createComponent("parametersProjectAlreadyExist.qml")
                                console.log(listview1.model.get(listview1.currentIndex).name)
                                var list = sakeStart.getAllElementsFromProjectName(listview1.model.get(listview1.currentIndex).name)
                                console.log("ciao"+list.length )
                                for(var i = 0; i < list.length ; i++){
                                    console.log(list[i])
                                }

                                var window    = component.createObject(applicationWindow1)
                                console.log(window.f(list))
                            }

                        }


                    }
                }
            }
            //            ScrollView {
            //                y: 20
            //                width: 180
            //                height: 700
            //                ListView {

            //                    id: listview1
            //                    anchors.fill: parent

            //                    model: model
            //                    delegate: contactDelegate
            //                    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            //                    focus: true
            //                    onCurrentItemChanged: console.log(model.get(listview1.currentIndex).name + ' selected')
            //                }
            //            }


        }


        Rectangle{
            id: parameter
            width: 700
            color:"white"
            Layout.minimumWidth: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
            objectName: "Rectanglemain"





            function addTab(msg,count){
                console.log("Entrato in Add Tab");
                console.log("Entrato in Add Tab"+ count);
                var tmp = "customPlotFitness"+count;
                console.log(tmp);
                var qml = "
import QtQuick 2.0
import QtQuick.Window 2.0
import CustomPlot 1.0
import CustomPlotMobilityFunction 1.0
import CustomPlotKernel 1.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
                        Tab {
                           title:   '"+msg+"'
                        active: true
                        property int threadId: "+count+"
                        function stopExecution(){
                                  console.log('clicco STOPPPPP');
                                  sakeStart.stopSAKeController(threadId);
                        }

                        GridLayout {
                        Layout.fillWidth: true
                        rowSpacing: 0
                        columnSpacing: 0
                        columns: 1
                        rows:7
                        anchors.fill: parent
                        Layout.preferredWidth: 700
                        Layout.preferredHeight: 200
                        Layout.maximumWidth:  1500
                        Layout.maximumHeight:  1500


                        CustomPlotItem {


                            Layout.fillWidth: true
                             Layout.fillHeight: true
                            Layout.preferredWidth: 700
                            Layout.preferredHeight: 200
                            Layout.maximumWidth:  1000000
                            Layout.maximumHeight: 1000000


                            objectName: '"+tmp+"'
                            //antialiasing: true
                            // Component.onCompleted: initCustomPlot()


                        }

                        CustomPlotKernel {

                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Layout.preferredWidth: 700
                            Layout.preferredHeight: 200
                            Layout.maximumWidth:  1000000
                            Layout.maximumHeight: 1000000
                            objectName:  'customPlotKernel"+count+"'
                            //anchors.top: customPlot1.bottom
                            // Component.onCompleted: initCustomPlotMobilityFunction()

                        }

                        CustomPlotMobilityFunction {


                            Layout.fillWidth: true
                             Layout.fillHeight: true
                            Layout.preferredWidth: 700
                            Layout.preferredHeight: 200
                            clip: false
                            Layout.maximumWidth:  1000000
                            Layout.maximumHeight: 1000000

                            objectName:  'customPlotMobilityFunction"+count+"'
                            //anchors.top: customPlot1.bottom
                            // Component.onCompleted: initCustomPlotMobilityFunction()

                        }



                    Rectangle{
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.preferredWidth: 700
                            Layout.preferredHeight: 100
                            clip: false
                            Layout.maximumWidth:  1000000
                            Layout.maximumHeight: 1000000
                              GridLayout {
                                   Layout.fillWidth: true
                                   rowSpacing: 0
                                   columnSpacing: 0
                                   columns: 1
                                   rows:4
                                   anchors.fill: parent
                                   Layout.preferredWidth: 700
                                   Layout.preferredHeight: 200
                                   Layout.maximumWidth:  1000000
                                   Layout.maximumHeight:  1000000

                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 150

                                    Label {
                                        id: gen
                                        objectName:  'gen"+count+"'
                                        text: 'Gen:     1'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                }

                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 150
                                    objectName:  'RowLayoutFitness"+count+"'
                                    //property alias text1Text: currentMaximumFitness.text


                                    Label {

                                        objectName:  'currentMaximumFitness"+count+"'
                                        text: 'Current Maximum Fitness:    0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                    Label {
                                        objectName:  'absoluteMaximumFitness"+count+"'
                                        text: 'Absolute Maximum Fitness:    0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                }

                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 150
                                    Label {
                                        objectName:  'currentAverageFitness"+count+"'
                                        text: 'Current Average Fitness:       0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                    Label {
                                        objectName:  'absoluteAverageFitness"+count+"'
                                        text: 'Absolute Average Fitness:       0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }


                                }



                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 150
                                    Label {
                                        objectName:  'tb"+count+"'
                                        text: 'tb:       0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                    Label {
                                        objectName:  'deltaCritico"+count+"'
                                        text: 'Δcritico:       0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                    Label {
                                        objectName:  'momentoDelPrimoOrdine"+count+"'
                                        text: 'Momento del primo ordine:       0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }


                                }

                               ProgressBar {
                                    objectName:  'progressBar"+count+"'
                                    value: 0

                                    Layout.fillWidth: true
                                }

//                               RowLayout {
                                        Button {
                                            id: stop
                                            objectName: 'stop"+count+"'
                                            text: qsTr('Stop')

                                        }
//                                        Button {
//                                            id: closeWindows
//                                            objectName: 'closeWindows"+count+"'
//                                            text: qsTr('close Tab')
//                                            //onClicked:
//                                                    //tabmain.removeTab("+count+")

//                                       }
//                               }

                            }




                        }
                    }
                    }";



                //                            var c_tab=tabmain.currentIndex
                //                                var t=tabmain.addTab("x",viewComp)
                //                                tabmain.currentIndex=count-1
                //                                tabmain.currentIndex=c_tab
                // var component=Qt.createComponent("Tab.qml");
                // var window    = component.createObject(applicationWindow1);
                var component=  Qt.createQmlObject(qml,tabmain);
                tabmain.activeFocusOnTab=count;

                //   tabmain.addTab(component);

                return "0"

            }

            function addTabRegression(msg,count){
                console.log("Entrato in Add Tab");
                console.log("Entrato in Add Tab"+ count);
                var tmp = "customPlotFitness"+count;
                var tmp2 = "customPlotRegression"+count;
                console.log(tmp);
                console.log(tmp2);
                var qml = "
import QtQuick 2.0
import QtQuick.Window 2.0
import CustomPlot 1.0
import CustomPlotRegression 1.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
                        Tab {
                           title:   '"+msg+"'
                        active: true
                        property int threadId: "+count+"
                        function stopExecution(){
                                  console.log('clicco STOPPPPP threadId');
                                  sakeStart.stopRegressionController(threadId);
                        }

                        GridLayout {
                        Layout.fillWidth: true
                        rowSpacing: 0
                        columnSpacing: 0
                        columns: 1
                        rows:6
                        anchors.fill: parent
                        Layout.preferredWidth: 700
                        Layout.preferredHeight: 200
                        Layout.maximumWidth:  1500
                        Layout.maximumHeight:  1500


//                        CustomPlotItem {


//                            Layout.fillWidth: true
//                             Layout.fillHeight: true
//                            Layout.preferredWidth: 700
//                            Layout.preferredHeight: 200
//                            Layout.maximumWidth:  1000000
//                            Layout.maximumHeight: 1000000


//                            objectName: '"+tmp+"'


//                        }

                        CustomPlotRegression {


                            Layout.fillWidth: true
                             Layout.fillHeight: true
                            Layout.preferredWidth: 700
                            Layout.preferredHeight: 400

                            Layout.maximumWidth:  1000000
                            Layout.maximumHeight: 1000000

                            objectName:  'customPlotRegression"+count+"'

                        }



                    Rectangle{
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.preferredWidth: 700
                            Layout.preferredHeight: 100
                            clip: false
                            Layout.maximumWidth:  1000000
                            Layout.maximumHeight: 1000000
                              GridLayout {
                                   Layout.fillWidth: true
                                   rowSpacing: 0
                                   columnSpacing: 0
                                   columns: 1
                                   rows:4
                                   anchors.fill: parent
                                   Layout.preferredWidth: 700
                                   Layout.preferredHeight: 200
                                   Layout.maximumWidth:  1000000
                                   Layout.maximumHeight:  1000000

                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 150

                                    Label {
                                        id: gen
                                        objectName:  'gen"+count+"'
                                        text: 'Gen:     1'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                }

                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 150
                                    objectName:  'RowLayoutFitness"+count+"'
                                    //property alias text1Text: currentMaximumFitness.text


                                    Label {

                                        objectName:  'currentMaximumFitness"+count+"'
                                        text: 'Current Maximum Fitness:    0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                    Label {
                                        objectName:  'absoluteMaximumFitness"+count+"'
                                        text: 'Absolute Maximum Fitness:    0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                }

                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 150
                                    Label {
                                        objectName:  'currentAverageFitness"+count+"'
                                        text: 'Current Average Fitness:       0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }

                                    Label {
                                        objectName:  'absoluteAverageFitness"+count+"'
                                        text: 'Absolute Average Fitness:       0'
                                        font.pixelSize: 16
                                        color: '#000000'
                                    }


                                }




                               ProgressBar {
                                    objectName:  'progressBar"+count+"'
                                    value: 0

                                    Layout.fillWidth: true
                                }

//                               RowLayout {
                                        Button {
                                            id: stop
                                            objectName: 'stop"+count+"'
                                            text: qsTr('Stop')

                                        }
//                                        Button {
//                                            id: closeWindows
//                                            objectName: 'closeWindows"+count+"'
//                                            text: qsTr('close Tab')
//                                            //onClicked:
//                                                    //tabmain.removeTab("+count+")

//                                       }
//                               }

                            }




                        }
                    }
                    }";



                //                            var c_tab=tabmain.currentIndex
                //                                var t=tabmain.addTab("x",viewComp)
                //                                tabmain.currentIndex=count-1
                //                                tabmain.currentIndex=c_tab
                // var component=Qt.createComponent("Tab.qml");
                // var window    = component.createObject(applicationWindow1);

                var component=  Qt.createQmlObject(qml,tabmain);
                tabmain.activeFocusOnTab=count;
                //   tabmain.addTab(component);

                return "0"

            }

            function addTabValidation(msg,count){
                console.log("Entrato in Add Tab");
                console.log("Entrato in Add Tab"+ count);
                var tmp = "customPlotFitness"+count;
                console.log(tmp);
                var qml = "
import QtQuick 2.0
import QtQuick.Window 2.0
import CustomPlot 1.0
import CustomPlotMobilityFunction 1.0
import CustomPlotKernel 1.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
                        Tab {
                           title:   '"+msg+"'
                        active: true


                        GridLayout {
                        Layout.fillWidth: true
                        rowSpacing: 0
                        columnSpacing: 0
                        columns: 1
                        rows:1
                        anchors.fill: parent
                        Layout.preferredWidth: 700
                        Layout.preferredHeight: 200
                        Layout.maximumWidth:  1500
                        Layout.maximumHeight:  1500

                        CustomPlotMobilityFunction {


                            Layout.fillWidth: true
                             Layout.fillHeight: true
                            Layout.preferredWidth: 700
                            Layout.preferredHeight: 200
                            clip: false
                            Layout.maximumWidth:  1000000
                            Layout.maximumHeight: 1000000

                            objectName:  'customPlotMobilityFunction"+count+"'
                            //anchors.top: customPlot1.bottom
                            // Component.onCompleted: initCustomPlotMobilityFunction()

                        }

                        CustomPlotKernel {

                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Layout.preferredWidth: 700
                            Layout.preferredHeight: 200
                            Layout.maximumWidth:  1000000
                            Layout.maximumHeight: 1000000
                            objectName:  'customPlotKernel"+count+"'
                            //anchors.top: customPlot1.bottom
                            // Component.onCompleted: initCustomPlotMobilityFunction()

                        }
                      }
                    }";



                //                            var c_tab=tabmain.currentIndex
                //                                var t=tabmain.addTab("x",viewComp)
                //                                tabmain.currentIndex=count-1
                //                                tabmain.currentIndex=c_tab
                // var component=Qt.createComponent("Tab.qml");
                // var window    = component.createObject(applicationWindow1);
                var component=  Qt.createQmlObject(qml,tabmain);
                tabmain.activeFocusOnTab=count;
                //   tabmain.addTab(component);

                return "0"

            }







            TabView {
                id: tabmain
                objectName: "Tabmain"
                anchors.fill: parent
                Layout.fillWidth: true
                Layout.fillHeight: true

                signal stopExecution()

                style: TabViewStyle {
                    property color frameColor: "#d5d0d3"
                    property color fillColor: "#eee"
                    frameOverlap: 1
                    frame: Rectangle {
                        color: "#eee"
                        border.color: frameColor
                    }
                    tab: Rectangle {
                        color: styleData.selected ? fillColor : frameColor
                        implicitWidth: Math.max(text.width + 40, 80)
                        implicitHeight: 20
                        Rectangle { height: 1 ; width: parent.width ; color: frameColor}
                        Rectangle { height: parent.height ; width: 1; color: frameColor}
                        Rectangle { x: parent.width -1; height: parent.height ; width: 1; color: frameColor}
                        border.width: 1
                        Text {
                            id: text
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin: 6
                            text: styleData.title
                            color: styleData.selected ? "black" : "black"
                        }
                        Button {

                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.rightMargin: 4
                            height: 16
                            style: ButtonStyle {
                                background: Rectangle {
                                    implicitWidth: 16
                                    implicitHeight: 16
                                    radius: width/2
                                    color: control.hovered ? "#eee": "#ccc"
                                    border.color: "gray"
                                    Text {text: "X" ; anchors.centerIn: parent ; color: "gray"}
                                }}
                            onClicked: {
                                //tabmain.stopExecution();
                                var patt = new RegExp("Calibration ");
                                var patt2 = new RegExp("Regression ");
                                console.log(patt.test(tabmain.getTab(styleData.index).title));
                                console.log(tabmain.getTab(styleData.index).title);
                                if(patt.test(tabmain.getTab(styleData.index).title) || patt2.test(tabmain.getTab(styleData.index).title)){
                                    console.log("STOPPO ALGO")

                                    tabmain.getTab(styleData.index).stopExecution();
                                }
                                tabmain.removeTab(styleData.index)
                            }
                        }
                    }
                }

//                Tab {
//                   title:   "Welcome"
//                    active: true

//                    Text {
//                        text: qsTr("Welcome to SAKe.")
//                        horizontalAlignment   :Text.AlignHCenter
//                        verticalAlignment    :Text.AlignVCenter
//                        font.family: "Helvetica"
//                        font.pointSize: 56
//                    }

//                }

            }




        }




    }
    //    MessageDialog {
    //        id: errorcsvRain
    //        objectName: "errorcsvRain"
    //        function errorcsvFunction( filename, row, err){
    //            errorcsvRain.text=" the file "+ filename +" at row "+row+"\n Error : "+ err+"\n";
    //            errorcsvRain.open();
    //        }

    //        title: "Input error"
    //        onAccepted: close()
    //        Component.onCompleted: visible = false
    //        modality: "ApplicationModal"
    //    }
    //    MessageDialog {
    //        id: errorcsvActivation
    //        objectName: "errorcsvActivation"
    //        function errorcsvFunction( filename, row, err){
    //            errorcsvActivation.text=" the file "+ filename +" at row "+row+"\n Error : "+ err+"\n";
    //            errorcsvActivation.open();
    //        }

    //        title: "Input error"
    //        onAccepted: close()
    //        Component.onCompleted: visible = false
    //        modality: "ApplicationModal"
    //    }





}//Application

