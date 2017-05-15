import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2

ApplicationWindow {
    visible: true
    width: 350
    height: 450
    property alias chooseKernel: chooseKernel
    property alias loadRains: loadRains
    property alias textfileRain: textfileRain
    property alias loadActivation: loadActivation
    property alias textfileActivation: textfileActivation
    property alias chooseSave: chooseSave
    property alias textfileSavePath: textfileSavePath
    property alias textfileKernel: textfileKernel
    //title: qsTr("Sake software")
    Rectangle{
        id: parameter
        x: 0
        y: 0
        anchors.fill: parent
        color:"white"

        ColumnLayout {
            id: columnLayout2
            x: 4
            y: 127
            width: 342
            height: 210
            spacing: 0.1



            GridLayout {
                id: gridLayout3
                y: 548
                width: 309
                height: 134
                columns: 2
                rows: 5
                FileDialog {
                    id: fileDialogRain
                    title: "Please choose a file"
                    property string  tmp
                    property variant split
                    folder: shortcuts.home
                    onAccepted: {
                        console.log("You chose: " + fileDialogRain.fileUrls)
                        //textfileRain.text = fileDialogRain.fileUrl
                        //handlerCSV.loadCSV(fileDialogRain.fileUrl)
                        tmp = fileDialogRain.fileUrl
                        split = tmp.split("/")
                        textfileRain.text  = "../"+split[split.length-1]
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
                    property string  tmp
                    property variant split
                    folder: shortcuts.home
                    onAccepted: {
                        console.log("You chose: " + fileDialogActivation.fileUrls)
                        //textfileActivation.text = fileDialogActivation.fileUrl
                        //handlerCSV.loadCSV(fileDialogActivation.fileUrl)
                        tmp = fileDialogActivation.fileUrl
                        split = tmp.split("/")
                        textfileActivation.text  = "../"+split[split.length-1]
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
                    property string  tmp
                    property variant split
                    selectFolder: true
                    onAccepted: {
                        console.log("You chose: " + fileDialogPathSave.folder)
                        //textfileSavePath.text = fileDialogPathSave.folder
                        //handlerCSV.loadCSV(fileDialogPathSave.fileUrl)
                        tmp = fileDialogPathSave.fileUrl
                        split = tmp.split("/")
                        textfileSavePath.text  = "../"+split[split.length-1]
                        //Qt.quit()
                    }
                    onRejected: {
                        console.log("Canceled")
                        //Qt.quit()
                    }
                    nameFilters: [ "All files (*)" ]

                    Component.onCompleted: visible = false
                }

                FileDialog {
                    id: fileDialogKernelPath
                    title: "Please choose a file"
                    property string  tmp
                    property variant split
                    onAccepted: {
                        console.log("You chose: " + fileDialogPathSave.folder)
                        //textfileKernel.text = fileDialogKernelPath.fileUrl
                        tmp = fileDialogKernelPath.fileUrl
                        split = tmp.split("/")
                        textfileKernel.text  = "../"+split[split.length-1]
                        //CHECK CSV
                        //handlerCSV.loadCSV(fileDialogPathSave.fileUrl)
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
                    id: loadRains
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
                    id: loadActivation
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
                    id: chooseKernel
                    text: qsTr("Choose Kernel Path")
                    onClicked: {
                        fileDialogKernelPath.open()
                    }
                }

                Text {
                    id: textfileKernel
                    width: 79
                    height: 31
                    text: qsTr("Empty")
                    font.pixelSize: 12
                }

                Button {
                    id: chooseSave
                    text: qsTr("Choose where save kernels")
                    onClicked: {
                        fileDialogPathSave.open()
                    }
                    visible: false;
                }

                Text {
                    id: textfileSavePath
                    width: 79
                    height: 31
                    text: qsTr("Empty")
                    font.pixelSize: 12
                    visible: false;
                }





            }


            RowLayout {
                id: columnLayout1
                spacing: 4.8

                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: 328
                Layout.preferredHeight: 100

                Button {
                    id: start
                    objectName: "namestart"



                    signal qmlSignal(var var1,var var2,var var3,var var4)
                    y: 597
                    text: qsTr("Start")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    checkable: false
                    onClicked: {
                        // if(textfileRain.text != "empty")
                                            sakeStart.startValidation("Prova",fileDialogRain.fileUrl,fileDialogActivation.fileUrl,fileDialogKernelPath.fileUrl,
                                                               fileDialogPathSave.folder)
                        close()


                    }

                }

                Button {
                    id: cancel
                    objectName: "namecancel"
                    text: qsTr("Cancel")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    checkable: false
                    onClicked: close()

                }
            }

        }

        Label {
            id: label1
            x: 14
            y: 21
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Validation parameters")
            font.bold: true
            font.pointSize: 22

        }

    }

}
