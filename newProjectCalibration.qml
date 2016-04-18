import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Dialog {
    visible: true
    title: "Sake Parameters"
    width: 695
    height: 750
    modality: Qt.ApplicationModal
    contentItem:

        Rectangle{
                id: parameter
                width: 700
                height: 750
                color:"white"


                ComboBox {
                    id: comboSelection
                    x: 366
                    y: 122


                    function show( currentIndex){
                        if(currentIndex === 0 ||
                           currentIndex === 1  ){
                            selectionParameter.visible=true;
                        }else
                            selectionParameter.visible=false;

                        if(currentIndex ===2){
                            selectParameterRanking1.visible=true;
                            selectParameterRanking2.visible=true;
                        }else
                        {
                            selectParameterRanking1.visible=false;
                            selectParameterRanking2.visible=false;

                        }
                        if(currentIndex ===4){
                            comboSelectinParameterSequential.visible=true;
                        }else{
                            comboSelectinParameterSequential.visible=false;
                        }
                        if(currentIndex ===5){
                            selectionParameterTournamentWithoutReplacement.visible=true;
                        }else{
                            selectionParameterTournamentWithoutReplacement.visible=false;
                        }
                    }
                    width: 136
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 606
                    anchors.horizontalCenterOffset: -154
                    anchors.horizontalCenter: parent.horizontalCenter
                    currentIndex: 3
                    model: ListModel {
                        id: selections
                        ListElement { text: "StochTour(t)";  }
                        ListElement { text: "DetTour(T)";  }
                        ListElement { text: "Ranking(p,e)";  }
                        ListElement { text: "Roulette"; }
                        ListElement { text: "Sequential(ordered/unordered)";  }
                        ListElement { text: "TournamentWithoutReplacement"; }
                    }
                   onCurrentIndexChanged: show(currentIndex)
                }





                ComboBox {
                    id: comboSelectinParameterSequential
                    y: 115
                    width: 124
                    height: 29

                    visible: false
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 606
                    anchors.horizontalCenterOffset: -21
                    anchors.horizontalCenter: parent.horizontalCenter
                    currentIndex: 1
                    model: ListModel {
                        id: comboSelectinParameterSequentialList
                        ListElement { text: "ordered"; }
                        ListElement { text: "unorder";  }
                    }

                }

                ComboBox {
                    id: comboPattern
                    y: 411
                    width: 148
                    height: 29
                    activeFocusOnPress: true
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 310
                    anchors.horizontalCenterOffset: 249
                    anchors.horizontalCenter: parent.horizontalCenter
                    currentIndex: 2
                    model: ListModel {
                        id: patterns
                        ListElement { text: "Triangolare Disc";  }
                        ListElement { text: "Triangolare Asc";  }
                        ListElement { text: "Rettangolare";  }
                    }
                    //  onCurrentIndexChanged: console.debug(   cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
                }

                Button {
                    id: start
                        objectName: "namestart"



        //            signal qmlSignal(var var1,var var1,var var2,var var3,var var4,var var5,
        //                             var var6,var var7,var var8,var var9,var var10,var var11,
        //                             var var12,var var13,var var14)
                    y: 688
                    text: qsTr("Start")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 34
                    anchors.horizontalCenterOffset: -50
                    anchors.horizontalCenter: parent.horizontalCenter
                    checkable: false
                    onClicked: {

                            console.log("You chose: " + textProjectName.text);
                            console.log("You chose: " + sakeStart.existProjectName(textProjectName.text));

                        if(textProjectName.length ===0){
                             messageDialogProjectNameEmpty.open()
                        }else

                        if( sakeStart.existProjectName(textProjectName.text) === 1 ){
                            messageDialogProjectName.open()
                        }
                           else
                             if(textfileRain.text == "Empty"){
                                  messageDialogRain.open()
                             }else
                                 if(textfileActivation.text == "Empty"){
                                      messageDialogActivation.open()
                                 }else{
                                         sakeStart.InitAlgo(comboSelection.currentText,
                                                            textFieldPopulation.text,
                                                            textFieldMaxGen.text,
                                                            textFieldtbMax.text,
                                                            textFieldtbMin.text,
                                                            textFielddHpMax.text,
                                                            textFielddHpMin.text,
                                                            textFieldPropCrossover.text,
                                                            textFieldPropMutation.text,
                                                            textFieldPme.text,
                                                            textFieldPmb.text,
                                                            comboPattern.currentText,
                                                            fileDialogRain.fileUrl,
                                                            fileDialogActivation.fileUrl,
                                                            textProjectName.text,
                                                            textNumberProcessor.text,
                                                            selectionParameterTournamentWithoutReplacement.text,
                                                            textFieldSoglia.text,
                                                            0
                                                            )
                                         close()
                                     }



                    }

                }
                Button {
                    id: cancel
                    objectName: "namecancel"



                    y: 688
                    text: qsTr("Cancel")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 34
                    anchors.horizontalCenterOffset: 100
                    anchors.horizontalCenter: parent.horizontalCenter
                    checkable: false
                    onClicked: close()

                }


                Label {
                    id: labelSelection
                    x: 157
                    y: 129
                    text: qsTr("Selection")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 605
                    anchors.horizontalCenterOffset: -297
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Label {
                    id: labelProjectName
                    x: 157
                    y: 74
                    text: qsTr("Project Name")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 660
                    anchors.horizontalCenterOffset: -284
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    id: title
                    x: 187
                    y: 20
                    text: qsTr("SAke Parameters")
                    anchors.horizontalCenterOffset: 5
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 706
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.bold: true
                    font.pixelSize: 20
                }

                Label {
                    id: labelNumberProcessor
                    x: 145
                    y: 182
                    width: 120
                    text: qsTr("Number Processor")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 552
                    anchors.horizontalCenterOffset: -273
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField {
                    id: textFieldPopulation
                    y: 228
                    width: 63
                    text: "20"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 502

                    placeholderText: ""
                    anchors.horizontalCenterOffset: -135
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Label {
                    id: labelPopulatioonSize
                    x: 188
                    y: 230
                    text: qsTr("Population Size")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 504
                    anchors.horizontalCenterOffset: -282
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField {
                    id: textFieldMaxGen
                    x: 367
                    y: 285
                    width: 63
                    text: "5000"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 445

                    anchors.horizontalCenterOffset: -134
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                Label {
                    id: labelMaxGen1
                    x: 124
                    y: 280
                    text: qsTr("Maximum number")
                    wrapMode: Text.NoWrap
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 454
                    anchors.horizontalCenterOffset: -273
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Label {
                    id: labelMaxGen2
                    x: 124
                    y: 296
                    text: qsTr("of generations")
                    wrapMode: Text.NoWrap
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 438
                    anchors.horizontalCenterOffset: -275
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                TextField {
                    id: textFieldPropCrossover
                    x: 367
                    y: 183
                    width: 63
                    text: "0.75"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 547

                    anchors.horizontalCenterOffset: 255
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                TextField {
                    id: textFieldPropMutation
                    x: 367
                    y: 244
                    width: 63
                    text: "0.25"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 486

                    anchors.horizontalCenterOffset: 255
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                Label {
                    id: label3
                    x: 167
                    y: 182
                    text: qsTr("Probability of Crossover")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 552
                    anchors.horizontalCenterOffset: 108
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Label {
                    id: label4
                    x: 175
                    y: 243

                    text: qsTr("Probability of Mutation")
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 491
                    anchors.horizontalCenterOffset: 117
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Label {
                    id: label5
                    x: 92
                    y: 333
                    text: qsTr("tbMax")
                    anchors.horizontalCenterOffset: -273
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 401
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField {
                    id: textFieldtbMax
                    x: 233
                    y: 331
                    width: 63
                    text: "180"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 399
                    anchors.horizontalCenterOffset: -134
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                TextField {
                    id: textFieldtbMin
                    x: 233
                    y: 378
                    width: 63
                    text: "30"
                    anchors.horizontalCenterOffset: -134
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 352
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                Label {
                    id: label6
                    x: 90
                    y: 380
                    text: qsTr("tbMin")
                    anchors.horizontalCenterOffset: -275
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 354
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField {
                    id: textFieldPmb
                    x: 581
                    y: 357
                    width: 63
                    text: "0.5"
                    anchors.horizontalCenterOffset: 255
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 373
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                Label {
                    id: label7
                    x: 446
                    y: 301
                    text: qsTr("Pme")
                    anchors.horizontalCenterOffset: 109
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 433
                }

                Label {
                    id: label8
                    x: 446
                    y: 356
                    text: qsTr("Pmb")
                    anchors.horizontalCenterOffset: 109
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 378
                }

                Label {
                    id: labeSoglia
                    x: 446
                    text: qsTr("minimum kernel saving threshold")
                    anchors.horizontalCenterOffset: 109
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 348
                }

                TextField {
                    id: textFieldSoglia
                    x: 581
                    width: 63
                    text: "0.5"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 348
                    anchors.horizontalCenterOffset: 255
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                TextField {
                    id: textFieldPme
                    x: 581
                    y: 302
                    width: 63
                    text: "25"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 428
                    anchors.horizontalCenterOffset: 255
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                TextField {
                    id: textFielddHpMax
                    x: 233
                    y: 427
                    width: 63
                    text: "50"
                    anchors.horizontalCenterOffset: -134
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 303
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                Label {
                    id: label9
                    x: 86
                    y: 472
                    text: qsTr("dHpMin")
                    anchors.horizontalCenterOffset: -275
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 262
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField {
                    id: textFielddHpMin
                    x: 233
                    y: 472
                    width: 63
                    text: "-50"
                    anchors.horizontalCenterOffset: -134
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 258
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("")
                }

                Label {
                    id: label10
                    x: 81
                    y: 427
                    text: qsTr("dHpMax")
                    anchors.horizontalCenterOffset: -276
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 307
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Label {
                    id: label11
                    x: 443
                    y: 420
                    text: qsTr("Pattern")
                    anchors.horizontalCenterOffset: 109
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 314
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField {
                    id: selectionParameter
                    x: 290
                    y: 114
                    width: 39
                    height: 31
                    visible: false
                    text: "0"
                    anchors.horizontalCenterOffset: -60
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 605
                    // placeholderText: qsTr("Text Field")
                }
                TextField {
                    id: selectionParameterTournamentWithoutReplacement
                    x: 290
                    y: 114
                    width: 39
                    height: 31
                    visible: false
                    text: "0"
                    anchors.horizontalCenterOffset: -60
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 605
                    // placeholderText: qsTr("Text Field")
                }

                TextField {
                    id: selectParameterRanking2
                    x: 284
                    y: 114
                    width: 45
                    height: 31
                    text: "0"
                    anchors.horizontalCenterOffset: -12
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 605
                    visible: false
                    //placeholderText: qsTr("Text Field")
                }

                TextField {
                    id: selectParameterRanking1
                    x: 233
                    y: 114
                    width: 45
                    height: 31
                    text: "0"
                    anchors.horizontalCenterOffset: -60
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 605
                    visible: false
                    //placeholderText: qsTr("Text Field")
                }

                TextField {
                    id: textNumberProcessor
                    x: 239
                    y: 180
                    width: 63
                    visible: true
                    text: "1"
                    placeholderText: "Number of Processor"
                    anchors.horizontalCenterOffset: -135
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 550
                 //   placeholderText: qsTr("Text Field")
                }


                FileDialog {
                    id: fileDialogRain
                    title: "Please choose a file"
                    folder: shortcuts.home
                    property string  tmp
                    property variant split
                    onAccepted: {
                        //console.log("You chose: " + fileDialogRain.fileUrls)
                        tmp = fileDialogRain.fileUrl
                        split = tmp.split("/")
                        console.log("You chose: " + split[0])
                        console.log("You chose: " + split.length)
                        textfileRain.text = "../"+split[split.length-1]
                    }
                    onRejected: {
                        console.log("Canceled")
                        //Qt.quit()
                    }
                    nameFilters: [ "files (*.csv)" ]
                    Component.onCompleted: visible = false
                    modality: "ApplicationModal"
                }


                FileDialog {
                    property var path: shortcuts.home
                    id: fileDialogActivation
                    title: "Please choose a file"
                    folder: shortcuts.home
                    property string  tmp
                    property variant split
                    onAccepted: {
                        tmp = fileDialogActivation.fileUrl
                        split = tmp.split("/")
                        console.log("You chose: " + split[0])
                        console.log("You chose: " + split.length)
                        textfileActivation.text = "../"+split[split.length-1]
                        //Qt.quit()
                    }
                    onRejected: {
                        console.log("Canceled")
                        //Qt.quit()
                    }
                    nameFilters: [ "files (*.csv)" ]
                    Component.onCompleted: visible = false
                    modality: "ApplicationModal"
                }

                Button {
                    id: button1
                    x: 49
                    y: 533
                    text: qsTr("Load Rains")
                    onClicked: {
                        fileDialogRain.open()
                    }
                }

                Text {
                    id: textfileRain
                    x: 260
                    y: 533
                    width: 147
                    height: 31
                    text: qsTr("Empty")
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 12
                }


                Button {
                    id: button2
                    x: 49
                    y: 573
                    text: qsTr("Load Activations")
                    onClicked: {
                        fileDialogActivation.open()
                    }
                }

                Text {
                    id: textfileActivation
                    x: 260
                    y: 573
                    width: 79
                    height: 31
                    text: qsTr("Empty")
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 12
                }

               TextField {
                    id: textProjectName
                    x: 145
                    y: 74
                    width: 102
                    height: 20
                    placeholderText: qsTr("Project Name")
                }

                Label {
                    id: label1
                    x: 396
                    y: 472
                    text: qsTr("Tempo (giorni/ora/mesi)")
                }

                MessageDialog {
                    id: messageDialogRain
                    title: "Input error"
                    text: "Please enter rain csv path."
                    onAccepted: close()
                    Component.onCompleted: visible = false
                    modality: "ApplicationModal"
                }

                MessageDialog {
                    id: messageDialogActivation
                    title: "Input error"
                    text: "Please enter Activation csv path."
                    onAccepted: close()
                    Component.onCompleted: visible = false
                    modality: "ApplicationModal"
                }

                MessageDialog {
                    id: messageDialogProjectName
                    title: "Input error"
                    text: "The project name already exists."
                    onAccepted: close()
                    Component.onCompleted: visible = false
                    modality: "ApplicationModal"
                }
                MessageDialog {
                    id: messageDialogProjectNameEmpty
                    title: "Input error"
                    text: "The project name is empty."
                    onAccepted: close()
                    Component.onCompleted: visible = false
                    modality: "ApplicationModal"
                }

        }
}

