import QtQuick 2.0
import QtQuick.Window 2.0
import CustomPlot 1.0
import CustomPlotMobilityFunction 1.0
import CustomPlotKernel 1.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtMultimedia 5.5
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    id: applicationWindow1
    visible: true
    width: 700
    height: 800
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
    }//MenuBar


    toolBar:ToolBar {
            RowLayout {
                anchors.fill: parent
                height: 80

                ToolButton{
                        iconSource: "qrc:/img/download.png"
                id:openFile
                width: parent.height
                onClicked: {
                        console.log("Action Calibration Project");
                        var component = Qt.createComponent("newProjectCalibration.qml")

                        var window    = component.createObject(applicationWindow1)

                  }

                }

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

            ListModel {
                objectName: "ListProjects"
                id: model
                 function addElementList(projectName){
                      console.log("Entrato!!!!!!!!!!!!!!!!  "+ projectName);

                   // model.clear()
                     for (var i=0; i<projectName.length; i++){
                         console.log("Entrato!!!!!!!!!!!!!!!!  "+ projectName[i]);
                         model.append({"name": projectName[i]})

                     }


                 }

            }
                Component {
                    id: contactDelegate
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

                                  var component = Qt.createComponent("ProjectCalibration.qml")

                                  var window    = component.createObject(applicationWindow1)
                                    console.log(window.f())
                              }

                       }

                    }
                }

                ListView {

                    id: listview1
                    anchors.fill: parent

                    model: model
                    delegate: contactDelegate
                    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                    focus: true
                    onCurrentItemChanged: console.log(model.get(listview1.currentIndex).name + ' selected')
                }

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
import QtMultimedia 5.5
import QtQuick.Controls.Styles 1.4
                        Tab {
                           title:   '"+msg+"'
                        active: true
                        GridLayout {
                        Layout.fillWidth: true
                        rowSpacing: 0
                        columnSpacing: 0
                        columns: 1
                        rows:5
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

                               ProgressBar {
                                    objectName:  'progressBar"+count+"'
                                    value: 0

                                    Layout.fillWidth: true
                                }

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
                        tabmain.activeFocusOnTab=count-1;
                         //   tabmain.addTab(component);

                    return "0"

                    }





                    TabView {
                        id: tabmain
                        anchors.fill: parent
                        Layout.fillWidth: true
                        Layout.fillHeight: true


                    }




        }



    }



//Column{
//        Rectangle{
//            id: parameter
//            width: 700
//            color:"#d1d6d7"
//            anchors.horizontalCenterOffset: 0
//            anchors.bottomMargin: 7
//            anchors.leftMargin: 0
//            anchors.topMargin: -7
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.left: parent.left
//            anchors.bottom: parent.bottom
//            anchors.top: parent.top

//            ComboBox {
//                id: comboSelection
//                x: 366
//                y: 137


//                function show( currentIndex){
//                    if(currentIndex === 0 ||
//                       currentIndex === 1  ){
//                        selectionParameter.visible=true;
//                    }else
//                        selectionParameter.visible=false;

//                    if(currentIndex ===2){
//                        selectParameterRanking1.visible=true;
//                        selectParameterRanking2.visible=true;
//                    }else
//                    {
//                        selectParameterRanking1.visible=false;
//                        selectParameterRanking2.visible=false;

//                    }
//                    if(currentIndex ===4){
//                        comboSelectinParameterSequential.visible=true;
//                    }else{
//                        comboSelectinParameterSequential.visible=false;
//                    }
//                }
//                width: 136
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 534
//                anchors.horizontalCenterOffset: -185
//                anchors.horizontalCenter: parent.horizontalCenter
//                currentIndex: 3
//                model: ListModel {
//                    id: selections
//                    ListElement { text: "StochTour(t)";  }
//                    ListElement { text: "DetTour(T)";  }
//                    ListElement { text: "Ranking(p,e)";  }
//                    ListElement { text: "Roulette"; }
//                    ListElement { text: "Sequential(ordered/unordered)";  }
//                    ListElement { text: "NoSelect"; }
//                }
//               onCurrentIndexChanged: show(currentIndex)
//            }

//            ComboBox {
//                id: comboReplacement
//                y: 183
//                width: 124
//                height: 29

//                function show( currentIndex){
//                    if(currentIndex === 2 ||
//                       currentIndex === 4 ||
//                       currentIndex === 5||
//                       currentIndex === 6  ){
//                        selectReplacement.visible=true;
//                    }else
//                        selectReplacement.visible=false;

//                }

//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 488
//                anchors.horizontalCenterOffset: -179
//                anchors.horizontalCenter: parent.horizontalCenter
//                currentIndex: 1
//                model: ListModel {
//                    id: replacemnets
//                    ListElement { text: "Comma"; }
//                    ListElement { text: "Plus";  }
//                    ListElement { text: "EPTour(T)";  }
//                    ListElement { text: "SSGAWorst"; }
//                    ListElement { text: "SSGADet(T)";  }
//                    ListElement { text: "SSGAStoch(T)"; }
//                    ListElement { text: "ElitistReplacement(T)";  }
//                }
//                 onCurrentIndexChanged: show(currentIndex)

//            }



//            ComboBox {
//                id: comboSelectinParameterSequential
//                y: 137
//                width: 124
//                height: 29

//                visible: false
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 534
//                anchors.horizontalCenterOffset: -52
//                anchors.horizontalCenter: parent.horizontalCenter
//                currentIndex: 1
//                model: ListModel {
//                    id: comboSelectinParameterSequentialList
//                    ListElement { text: "ordered"; }
//                    ListElement { text: "unorder";  }
//                }

//            }

//            ComboBox {
//                id: comboPattern
//                y: 488
//                width: 148
//                height: 29
//                activeFocusOnPress: true
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 183
//                anchors.horizontalCenterOffset: 247
//                anchors.horizontalCenter: parent.horizontalCenter
//                currentIndex: 2
//                model: ListModel {
//                    id: patterns
//                    ListElement { text: "Triangolare Disc";  }
//                    ListElement { text: "Triangolare Asc";  }
//                    ListElement { text: "Rettangolare";  }
//                }
//                //  onCurrentIndexChanged: console.debug(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
//            }

//            Button {
//                id: start
//                objectName: "namestart"



//                signal qmlSignal(var var1,var var1,var var2,var var3,var var4,var var5,
//                                 var var6,var var7,var var8,var var9,var var10,var var11,
//                                 var var12,var var13,var var14)
//                y: 597
//                text: qsTr("Start")
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 22
//                anchors.horizontalCenterOffset: -5
//                anchors.horizontalCenter: parent.horizontalCenter
//                checkable: false
//                onClicked: qmlSignal(comboSelection.currentText,comboReplacement.currentText, textFieldPopulation.text,
//                                     textFieldMaxGen.text,textFieldtbMax.text,textFieldtbMin.text,textFielddHpMax.text,
//                                     textFielddHpMin.text,textFieldRelRateCrossover.text,textFieldRelRateMutation.text,
//                                     textFieldPropCrossover.text,textFieldPropMutation.text,textFieldPme.text,
//                                     textFieldPmb.text,comboPattern.currentText)

//            }

//            Label {
//                id: labelSelection
//                x: 157
//                y: 141
//                text: qsTr("Selection")
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 538
//                anchors.horizontalCenterOffset: -299
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            Text {
//                id: title
//                x: 187
//                y: 23
//                text: qsTr("Parametri algoritmo genetico SAKè")
//                anchors.horizontalCenterOffset: 0
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 599
//                anchors.horizontalCenter: parent.horizontalCenter
//                font.bold: true
//                font.pixelSize: 20
//            }

//            Label {
//                id: labelReplacement
//                x: 145
//                y: 187
//                width: 84
//                text: qsTr("Replacement")
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 492
//                anchors.horizontalCenterOffset: -299
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            TextField {
//                id: textFieldPopulation
//                y: 238
//                width: 63
//                text: "20"
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 431
//                validator: IntValidator{}
//                placeholderText: ""
//                anchors.horizontalCenterOffset: -157
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            Label {
//                id: labelPopulatioonSize
//                x: 188
//                y: 243
//                text: qsTr("Population Size")
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 436
//                anchors.horizontalCenterOffset: -279
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            TextField {
//                id: textFieldMaxGen
//                x: 367
//                y: 286
//                width: 63
//                text: "30"
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 383
//                validator: IntValidator{}
//                anchors.horizontalCenterOffset: -157
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            Label {
//                id: labelMaxGen1
//                x: 124
//                y: 286
//                text: qsTr("Maximum number")
//                wrapMode: Text.NoWrap
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 393
//                anchors.horizontalCenterOffset: -270
//                anchors.horizontalCenter: parent.horizontalCenter
//                horizontalAlignment: Text.AlignHCenter
//            }
//            Label {
//                id: labelMaxGen2
//                x: 124
//                y: 302
//                text: qsTr("of generations")
//                wrapMode: Text.NoWrap
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 377
//                anchors.horizontalCenterOffset: -272
//                anchors.horizontalCenter: parent.horizontalCenter
//                horizontalAlignment: Text.AlignHCenter
//            }

//            TextField {
//                id: textFieldRelRateCrossover
//                x: 367
//                y: 136
//                width: 63
//                text: "0.8"
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 533
//                validator: IntValidator{}
//                anchors.horizontalCenterOffset: 253
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            TextField {
//                id: textFieldRelRateMutation
//                x: 367
//                y: 191
//                width: 63
//                text: "0.9"
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 478
//                validator: IntValidator{}
//                anchors.horizontalCenterOffset: 253
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            TextField {
//                id: textFieldPropCrossover
//                x: 367
//                y: 249
//                width: 63
//                text: "0.6"
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 420
//                validator: IntValidator{}
//                anchors.horizontalCenterOffset: 253
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            TextField {
//                id: textFieldPropMutation
//                x: 367
//                y: 310
//                width: 63
//                text: "0.6"
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 359
//                validator: IntValidator{}
//                anchors.horizontalCenterOffset: 253
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            Label {
//                id: label1
//                x: 161
//                y: 91

//                text: qsTr("Relative rate crossover")
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 538
//                anchors.horizontalCenterOffset: 115
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            Label {
//                id: label2
//                x: 167
//                y: 146
//                text: qsTr("Relative rate mutation")
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 483
//                anchors.horizontalCenterOffset: 114
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            Label {
//                id: label3
//                x: 167
//                y: 204
//                text: qsTr("Probability of Crossover")
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 425
//                anchors.horizontalCenterOffset: 106
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            Label {
//                id: label4
//                x: 175
//                y: 265

//                text: qsTr("Probability of Mutation")
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 364
//                anchors.horizontalCenterOffset: 115
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            Label {
//                id: label5
//                x: 92
//                y: 339
//                text: qsTr("tbMax")
//                anchors.horizontalCenterOffset: -270
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 340
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            TextField {
//                id: textFieldtbMax
//                x: 233
//                y: 334
//                width: 63
//                text: "180"
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 335
//                anchors.horizontalCenterOffset: -156
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            TextField {
//                id: textFieldtbMin
//                x: 233
//                y: 381
//                width: 63
//                text: "30"
//                anchors.horizontalCenterOffset: -157
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 288
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            Label {
//                id: label6
//                x: 90
//                y: 386
//                text: qsTr("tbMin")
//                anchors.horizontalCenterOffset: -272
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 293
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            TextField {
//                id: textFieldPmb
//                x: 581
//                y: 423
//                width: 63
//                text: "0.3"
//                anchors.horizontalCenterOffset: 253
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 246
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            Label {
//                id: label7
//                x: 446
//                y: 323
//                text: qsTr("Pme")
//                anchors.horizontalCenterOffset: 107
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 306
//            }

//            Label {
//                id: label8
//                x: 446
//                y: 378
//                text: qsTr("Pmb")
//                anchors.horizontalCenterOffset: 107
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 251
//            }

//            TextField {
//                id: textFieldPme
//                x: 581
//                y: 368
//                width: 63
//                text: "25"
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 301
//                anchors.horizontalCenterOffset: 253
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            TextField {
//                id: textFielddHpMax
//                x: 233
//                y: 428
//                width: 63
//                text: "10"
//                anchors.horizontalCenterOffset: -156
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 241
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            Label {
//                id: label9
//                x: 86
//                y: 478
//                text: qsTr("dHpMin")
//                anchors.horizontalCenterOffset: -272
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 201
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            TextField {
//                id: textFielddHpMin
//                x: 233
//                y: 473
//                width: 63
//                text: "0"
//                anchors.horizontalCenterOffset: -156
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 196
//                anchors.horizontalCenter: parent.horizontalCenter
//                placeholderText: qsTr("")
//            }

//            Label {
//                id: label10
//                x: 81
//                y: 433
//                text: qsTr("dHpMax")
//                anchors.horizontalCenterOffset: -273
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 246
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            Label {
//                id: label11
//                x: 443
//                y: 442
//                text: qsTr("Pattern")
//                anchors.horizontalCenterOffset: 107
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 187
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            TextField {
//                id: selectionParameter
//                x: 290
//                y: 136
//                width: 39
//                height: 31
//                visible: false
//                text: "0"
//                anchors.horizontalCenterOffset: -91
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 533
//                // placeholderText: qsTr("Text Field")
//            }

//            TextField {
//                id: selectParameterRanking2
//                x: 284
//                y: 136
//                width: 45
//                height: 31
//                text: "0"
//                anchors.horizontalCenterOffset: -43
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 533
//                visible: false
//                //placeholderText: qsTr("Text Field")
//            }

//            TextField {
//                id: selectParameterRanking1
//                x: 233
//                y: 136
//                width: 45
//                height: 31
//                text: "0"
//                anchors.horizontalCenterOffset: -91
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 533
//                visible: false
//                //placeholderText: qsTr("Text Field")
//            }

//            TextField {
//                id: selectReplacement
//                x: 239
//                y: 182
//                width: 45
//                visible: false
//                text: "0"
//                anchors.horizontalCenterOffset: -88
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.bottom: parent.bottom
//                anchors.bottomMargin: 487
//             //   placeholderText: qsTr("Text Field")
//            }

//            //Button

//        }
//    }





}//Application

