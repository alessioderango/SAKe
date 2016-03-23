import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2

ApplicationWindow {
    id: applicationWindow1
    visible: true
    width: 700
    height: 800
    title: qsTr("Sake software")
Rectangle{
    id: parameter
    x: 0
    y: 0
    width: 700
    height: 785
    color:"white"

    ColumnLayout {
        id: columnLayout2
        x: 31
        y: 8
        width: 655
        height: 777
        spacing: 1



        Label {
            id: label1
            y: 26
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("SAKe parameters")
            font.bold: true
            font.pointSize: 22

        }
        RowLayout {
            id: rowLayout
            spacing: 2

             Label {
                id: projectName
                y: 26
                text: qsTr("Project Name")
                Layout.alignment: Qt.AlignHCenter
            }

             TextField {
                 id: textProjectName
                 width: 63
                 text: "20"

                 placeholderText: ""
             }
        }
        RowLayout {
            id: rowLayout1
            y: 100
            width: 645
            height: 431
            spacing: 0

            GridLayout {
                id: gridLayout1
                x: 0
                y: 0
                width: 309
                height: 426
                rowSpacing: 2
                columnSpacing: 2
                scale: 1
                transformOrigin: Item.Center
                rows: 3
                columns: 2

                Layout.preferredWidth: 309
                Layout.preferredHeight: 426


                Label {
                    id: labelSelection
                    text: qsTr("Selection")
                    scale: 1
                    transformOrigin: Item.Center
                }



                ComboBox {
                    id: comboSelection



                    currentIndex: 3
                    model: ListModel {
                        id: selections
                        ListElement { text: "StochTour(t)";  }
                        ListElement { text: "DetTour(T)";  }
                        ListElement { text: "Ranking(p,e)";  }
                        ListElement { text: "Roulette"; }
                        ListElement { text: "Sequential(ordered/unordered)";  }
                        ListElement { text: "NoSelect"; }
                    }
                }


                Label {
                    id: labelPopulatioonSize
                    y: 243
                    text: qsTr("Population Size")
                    transformOrigin: Item.Center
                }

                TextField {
                    id: textFieldPopulation
                    width: 63
                    text: "20"

                    placeholderText: ""
                }



                Label {
                    id: labelMaxGen1
                    text: qsTr("Maximum number of generations")
                }

                TextField {
                    id: textFieldMaxGen
                    width: 63
                    text: "5000"
                    placeholderText: qsTr("")
                }



                Label {
                    id: label5
                    text: qsTr("tbMax")
                }

                TextField {
                    id: textFieldtbMax
                    width: 63
                    text: "180"
                    placeholderText: qsTr("")
                }

                Label {
                    id: label6
                    text: qsTr("tbMin")
                }

                TextField {
                    id: textFieldtbMin
                    width: 63
                    text: "30"
                    placeholderText: qsTr("")
                }

                Label {
                    id: label9
                    text: qsTr("dHpMin")
                }

                TextField {
                    id: textFielddHpMax
                    width: 63
                    text: "50"
                    placeholderText: qsTr("")
                }



                Label {
                    id: label10
                    text: qsTr("dHpMax")
                }

                TextField {
                    id: textFielddHpMin
                    width: 63
                    text: "-50"
                    placeholderText: qsTr("")
                }






            }

            ColumnLayout{
                y: 100
                TextField {
                    id: selectionParameterTournamentWithoutReplacement
                    visible: true
                    text: "0"
                }
            }


            GridLayout {
                id: gridLayout2
                x: 297
                y: 0
                width: 309
                height: 426
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                columns: 2
                rows: 4

                Layout.preferredWidth: 309
                Layout.preferredHeight: 426


                Label {
                    id: label3
                    text: qsTr("Probability of Crossover")
                }
                TextField {
                    id: textFieldPropCrossover
                    width: 63
                    text: "0.75"
                    placeholderText: qsTr("")
                }

                Label {
                    id: label4

                    text: qsTr("Probability of Mutation")
                }




                TextField {
                    id: textFieldPropMutation
                    width: 63
                    text: "0.25"
                    placeholderText: qsTr("")
                }




                Label {
                    id: label7
                    text: qsTr("Pme")
                }

                TextField {
                    id: textFieldPme
                    width: 63
                    text: "25"
                    placeholderText: qsTr("")
                }


                Label {
                    id: label8
                    text: qsTr("Pmb")
                }

                TextField {
                    id: textFieldPmb
                    width: 63
                    text: "0.5"
                    placeholderText: qsTr("")
                }

                Label {
                    id: label11
                    text: qsTr("Pattern")
                }

                ComboBox {
                    id: comboPattern
                    activeFocusOnPress: true
                    currentIndex: 2
                    model: ListModel {
                        id: patterns
                        ListElement { text: "Triangolare Disc";  }
                        ListElement { text: "Triangolare Asc";  }
                        ListElement { text: "Rettangolare";  }
                    }
                }

                Label {
                    id: labelNumberProcessor
                    width: 120
                    text: qsTr("Number Processor")
                }

                TextField {
                    id: textNumberProcessor
                    width: 63
                    visible: true
                    text: "1"
                    placeholderText: "Number of Processor"
                }


            }
        }

        GridLayout {
            id: gridLayout3
            y: 548
            width: 309
            height: 134
            columns: 2
            rows: 3

            Layout.preferredWidth: 309
            Layout.preferredHeight: 134



            FileDialog {
                id: fileDialogRain
                title: "Please choose a file"
                folder: shortcuts.home
                onAccepted: {
                    console.log("You chose: " + fileDialogRain.fileUrls)
                    textfileRain.text = fileDialogRain.fileUrl
                    handlerCSV.loadCSV(fileDialogRain.fileUrl)
                    //Qt.quit()
                }
                onRejected: {
                    console.log("Canceled")
                    //Qt.quit()
                }
                nameFilters: [ "files (*.csv)" ]
                Component.onCompleted: visible = false
            }


            FileDialog {
                id: fileDialogActivation
                title: "Please choose a file"
                folder: shortcuts.home
                onAccepted: {
                    console.log("You chose: " + fileDialogActivation.fileUrls)
                    textfileActivation.text = fileDialogActivation.fileUrl
                    handlerCSV.loadCSV(fileDialogActivation.fileUrl)
                    //Qt.quit()
                }
                onRejected: {
                    console.log("Canceled")
                    //Qt.quit()
                }
                nameFilters: [ "files (*.csv)" ]
                Component.onCompleted: visible = false
            }

            FileDialog {
                id: fileDialogPathSave
                title: "Please choose a file"
                selectFolder: true
                onAccepted: {
                    console.log("You chose: " + fileDialogPathSave.folder)
                    textfileSave.text = fileDialogPathSave.folder
                    handlerCSV.loadCSV(fileDialogPathSave.fileUrl)
                    //Qt.quit()
                }
                onRejected: {
                    console.log("Canceled")
                    //Qt.quit()
                }
                nameFilters: [ "All files (*)" ]

                Component.onCompleted: visible = false
            }

            Button {
                id: button1
                text: qsTr("Load Rains")
                onClicked: {
                    fileDialogRain.open()
                }
            }

            Text {
                id: textfileRain
                width: 147
                height: 31
                text: qsTr("Empty")
                font.pixelSize: 12
            }


            Button {
                id: button2
                x: 49
                y: 607
                text: qsTr("Load Activations")
                onClicked: {
                    fileDialogActivation.open()
                }
            }

            Text {
                id: textfileActivation
                width: 79
                height: 31
                text: qsTr("Empty")
                font.pixelSize: 12
            }

            Button {
                id: button3
                text: qsTr("Choose where save kernels")
                onClicked: {
                    fileDialogPathSave.open()
                }
            }

            Text {
                id: textfileSave
                width: 79
                height: 31
                text: qsTr("Empty")
                font.pixelSize: 12
            }



        }


        RowLayout {
            id: columnLayout1
            y: 709
            width: 328
            height: 100
            spacing: 4.8

            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 328
            Layout.preferredHeight: 100

            Button {
                id: start
                objectName: "namestart"



                signal qmlSignal(var var1,var var1,var var2,var var3,var var4,var var5,
                                 var var6,var var7,var var8,var var9,var var10,var var11,
                                 var var12,var var13,var var14)
                y: 597
                text: qsTr("Start")
                checkable: false
//                            onClicked: {
//                                       // if(textfileRain.text != "empty")
//                                        sakeStart.InitAlgo(comboSelection.currentText,
//                                                           textFieldPopulation.text,
//                                                           textFieldMaxGen.text,
//                                                           textFieldtbMax.text,
//                                                           textFieldtbMin.text,
//                                                           textFielddHpMax.text,
//                                                           textFielddHpMin.text,
//                                                           textFieldPropCrossover.text,
//                                                           textFieldPropMutation.text,
//                                                           textFieldPme.text,
//                                                           textFieldPmb.text,
//                                                           comboPattern.currentText,
//                                                           fileDialogRain.fileUrl,
//                                                           fileDialogActivation.fileUrl,
//                                                           fileDialogPathSave.folder,
//                                                           textProjectName.text,
//                                                           textNumberProcessor.text,
//                                                           selectionParameterTournamentWithoutReplacement.text,
//                                                           textFieldSoglia.text,
//                                                           0)
//                                       close()


//                            }

            }

            Button {
                id: cancel
                objectName: "namecancel"
                text: qsTr("Cancel")
                checkable: false
                onClicked: close()

            }
        }



    }

}

}
