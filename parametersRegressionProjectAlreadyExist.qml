import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2

ApplicationWindow {
    id: applicationWindow1
    visible: true
    width: 417
    height: 620
    title: qsTr("Sake software")
    minimumHeight: 620
    minimumWidth: 417
    maximumHeight: minimumHeight
    maximumWidth: minimumWidth

    property  string pathrain;
    property  string pathactivation;

    function f(list){
        console.log("Ok funzia")
        labelProjectNameFromFile.text=list[0]
        if(list[1]=="TournamentWithoutReplacement"){
            comboSelection.currentIndex=5
            selectionParameterTournamentWithoutReplacement.text=list[2]
        }else
            if(list[1]=="StochTour(t)"){
                comboSelection.currentIndex=0
                selectionParameter.text=list[2]
            }else
                if(list[1]=="DetTour(T)"){
                    comboSelection.currentIndex=1
                    selectionParameter.text=list[2]
                }else
                    if(list[1]=="Ranking(p,e)"){
                        comboSelection.currentIndex=2
                        selectParameterRanking1.text=list[2]
                        selectParameterRanking2.text=list[3]
                    }else
                        if(list[1]=="Sequential(ordered/unordered)"){
                            comboSelection.currentIndex=4
                            if(list[2]=="ordered")
                            {
                                comboSelectinParameterSequential.currentIndex=0;
                            }else
                                comboSelectinParameterSequential.currentIndex=1;

                            //comboSelectinParameterSequentialList.text=list[2]
                        }else
                            if(list[1]=="Roulette"){
                                comboSelection.currentIndex=3
                            }


        textNumberProcessor.text=list[4]
        textPercentageWeight.text=list[5]
        textFieldNumberProcessor.text=list[6]
        textFieldtbMax.text=list[7]
        textFieldtbMin.text=list[8]
        textFielddHpMax.text=list[9]
        textFielddHpMin.text=list[10]
        textFieldPropCrossover.text=list[11]
        textFieldPropMutation.text=list[12]
        textFieldPme.text=list[13]
        textFieldPmb.text=list[14]
        if(list[15]=="Rettangolare")
            comboPattern.currentIndex=2
        else
            if(list[15]=="Triangolare Disc")
                comboPattern.currentIndex=0
            else
                if(list[15]=="Triangolare Asc")
                    comboPattern.currentIndex=1

        var split = list[16].split("/")
        console.log("AAAAAAAAAAAAAAAAAAAAAAAAA ../"+split[split.length-1]);
        textfileRain.text = "../"+split[split.length-1]
        pathrain=list[16]

        var split2 = list[17].split("/")
        console.log("AAAAAAAAAAAAAAAAAAAAAAAA ../"+split2[split2.length-1]);
        textfileActivation.text = "../"+split2[split2.length-1]
        pathactivation=list[17]

    }


    Rectangle{
        id: parameter
        x: 0
        y: 0
        width: 417
        height: 620
        color:"#f2f2f2"

        ColumnLayout {
            id: columnLayout2
            x: 19
            y: 8
            width: 386
            height: 604
            spacing: 2



            Label {
                id: label1
                y: 26
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Regression Parameters")
                font.bold: true
                font.pointSize: 22

            }
            ColumnLayout{
                spacing: 20
                RowLayout {
                    id: rowLayout
                    spacing: 20

                    Label {
                        id: projectName
                        y: 26
                        text: qsTr("Project Name")
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Label {
                        id: labelProjectNameFromFile
                        width: 63
                        text: ""
                    }
                }

            }
            RowLayout {
                id: rowLayout1
                y: 100
                width: 630
                height: 300
                spacing: 1

                GridLayout {
                    id: gridLayout1
                    x: 0
                    y: 0
                    width: 63
                    height: 350
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    rowSpacing: 19
                    columnSpacing: 2
                    scale: 1
                    transformOrigin: Item.Center
                    rows: 2
                    columns: 1

                    Layout.preferredWidth: 309
                    Layout.preferredHeight: 250

                    ColumnLayout {
                        id: columnLayout4
                        width: 100
                        height: 100

                        GridLayout {
                            id: gridLayout5
                            Label {
                                id: labelSelection
                                text: qsTr("Selection")
                                scale: 1
                                transformOrigin: Item.Center
                            }

                            ComboBox {
                                id: comboSelection
                                currentIndex: 0
                                function show( currentIndex){
                                    //                                    if(currentIndex === 0 ||
                                    //                                       currentIndex === 1  ){
                                    //                                        selectionParameter.visible=true;
                                    //                                    }else
                                    //                                        selectionParameter.visible=false;

                                    //                                    if(currentIndex ===2){
                                    //                                        selectParameterRanking1.visible=true;
                                    //                                        selectParameterRanking2.visible=true;
                                    //                                    }else
                                    //                                    {
                                    //                                        selectParameterRanking1.visible=false;
                                    //                                        selectParameterRanking2.visible=false;

                                    //                                    }
                                    //                                    if(currentIndex ===4){
                                    //                                        comboSelectinParameterSequential.visible=true;
                                    //                                    }else{
                                    //                                        comboSelectinParameterSequential.visible=false;
                                    //                                    }

                                    if(currentIndex ===0 || currentIndex ===7 || currentIndex ===6 || currentIndex ===8){
                                        selectionParameterTournamentWithoutReplacement.visible=true;
                                    }else{
                                        selectionParameterTournamentWithoutReplacement.visible=false;
                                    }
                                    //                                    if(currentIndex ===6 || currentIndex ===8){
                                    //                                        gridLayout5.visible=true;
                                    //                                    }else{
                                    //                                        gridLayout5.visible=false;
                                    //                                    }
                                }
                                model: ListModel {
                                    id: selections
                                    ListElement {
                                        text: "Generational"
                                    }
                                }
                                onCurrentIndexChanged: show(currentIndex)
                            }

                            TextField {
                                id: selectionParameterTournamentWithoutReplacement
                                text: "8"
                                validator: RegExpValidator {
                                    regExp: /^[1-9]\d+/
                                }
                                visible: true
                            }

                            TextField {
                                id: selectionParameter
                                width: 39
                                height: 31
                                text: "0"
                                visible: false
                            }

                            TextField {
                                id: selectParameterRanking2
                                width: 45
                                height: 31
                                text: "0"
                                visible: false
                            }

                            TextField {
                                id: selectParameterRanking1
                                width: 45
                                height: 31
                                text: "0"
                                visible: false
                            }

                            ComboBox {
                                id: comboSelectinParameterSequential
                                model: ListModel {
                                    id: comboSelectinParameterSequentialList
                                    ListElement {
                                        text: "ordered"
                                    }

                                    ListElement {
                                        text: "unorder"
                                    }
                                }
                                visible: false
                                currentIndex: 1
                            }
                            columns: 4
                            rows: 1
                            columnSpacing: 20
                        }
                    }

                    GridLayout{
                        rows: 4
                        columns: 2
                        rowSpacing: 8
                        columnSpacing: 3
                        Layout.preferredWidth: 309
                        Layout.preferredHeight: 50
                        width: 630
                        height: 150







                        Label {
                            id: labelPopulationSize
                            text: qsTr("Population Size")
                        }

                        TextField {
                            id: textFieldPopulationSize
                            width: 63
                            text: "20"
                            placeholderText: qsTr("Population Size")
                            validator: RegExpValidator {
                                regExp: /^[1-9]\d+/
                            }
                        }

                        Label {
                            id: labelProbabiltyCrossOver
                            text: qsTr("Probabilty CrossOver")
                        }

                        TextField {
                            id: textFieldProbabiltyCrossOver
                            width: 63
                            text: "0.65"
                            placeholderText: qsTr("Probabilty CrossOver")
                            validator:  RegExpValidator { regExp: /0[.]\d{1,3}/ }
                        }

                        Label {
                            id: labelProbabiltyMutation
                            text: qsTr("Probabilty Mutation")
                        }

                        TextField {
                            id: textFieldProbabiltyMutation
                            width: 63
                            text: "0.35"
                            placeholderText: qsTr("Probabilty Mutation")
                            validator:  RegExpValidator { regExp: /0[.]\d{1,3}/ }
                        }




                        Label {
                            id: labelNumberProcessor
                            text: qsTr("Number of processor")
                        }
                        TextField {
                            id: textFieldNumberProcessor
                            width: 63
                            text: "4"
                            validator: RegExpValidator { regExp: /^[1-9]\d+/ }
                            placeholderText: qsTr("")
                        }
                        Label {
                            id: labelPercentageWeight
                            y: 243
                            text: qsTr("Percentage Weight")
                            transformOrigin: Item.Center
                        }
                        TextField {
                            id: textPercentageWeight
                            width: 63
                            text: "0.03"
                            //text: "30"
                            //inputMethodHints: Qt.ImhDigitsOnly
                             validator:  RegExpValidator { regExp: /0[.]\d{1,3}|^[1-9]\d+/ }
                            placeholderText: "Population Size"
                        }

                        Label {
                            id: labelMaxGeneration
                            y: 243
                            text: qsTr("Max Number of Generation")
                            transformOrigin: Item.Center
                        }

                        TextField {
                            id: textFieldMaxGeneration
                            width: 63
                            text: "50000"
                            placeholderText: "Max Number of Generation"
                            validator: RegExpValidator {
                                regExp: /^[1-9]\d+/
                            }
                        }



                    }


                }



            }
            ColumnLayout {
                id: columnLayout3
                width: 100
                height: 100
                visible: true
                spacing: 2

                RowLayout {
                    id: rowLayout2
                    width: 100
                    height: 100
                    visible: true
                    spacing: 15

                    Label {
                        id: labelGammaFunctions
                        text: qsTr("Number of gamma functions")
                        transformOrigin: Item.Center


                    }

                    TextField {
                        id: textFieldGammaFunctions

                        function showLabel(text){
                            if(text > 0){
                                labelPercentualeGammaA.visible=true;
                                labelPercentualeGammaB.visible=true;
                                textFieldGammaA.visible = true;
                                textFieldGammaB.visible = true;
                            }else
                            {
                                labelPercentualeGammaA.visible=false;
                                labelPercentualeGammaB.visible=false;
                                textFieldGammaA.visible = false;
                                textFieldGammaB.visible = false;

                            }
                        }

                        width: 63
                        text: "0"
                        placeholderText: "Number of gamma functions"
                        validator: RegExpValidator {
                            regExp: /^[0-9]\d+/
                        }
                        //                                editingFinished: console.log("CIAO")
                        onTextChanged: showLabel(text)
                    }


                }

                RowLayout {
                    id: rowLayout4
                    width: 100
                    height: 50
                    visible: true
                    spacing: 1

                    GridLayout {
                        id: gridLayout2
                        width: 100
                        height: 100
                        columnSpacing: 4
                        rowSpacing: 4
                        visible: true
                        rows: 4
                        columns: 2

                        Label {
                            id: labelPercentualeGammaA
                            text: qsTr("Percentage Gamma A")
                            visible: false
                        }

                        TextField {
                            id: textFieldGammaA
                            text: "0.03"
                            visible: false
                            placeholderText: qsTr("Text Field")
                             validator:  RegExpValidator { regExp: /0[.]\d{1,3}|^[1-9]\d+/ }
                        }

                        Label {
                            id: labelPercentualeGammaB
                            text: qsTr("Percentage Gamma B")
                            visible: false
                        }

                        TextField {
                            id: textFieldGammaB
                            text: "0.03"
                            visible: false
                            placeholderText: qsTr("Text Field")
                             validator:  RegExpValidator { regExp: /0[.]\d{1,3}|^[1-9]\d+/ }
                        }
                    }
                }

                RowLayout {
                    id: rowLayout3
                    width: 100
                    height: 100
                    spacing: 23

                    Label {
                        id: labelGammaFunctions1
                        text: qsTr("Number of linear functions")
                        transformOrigin: Item.Center
                    }

                    TextField {
                        id: textFieldLinearFunction

                        function showLabel(text){
                            if(text > 0){
                                labelPercentualeLineareA1.visible=true;
                                labelPercentualeLineareB1.visible=true;
                                textFieldLinearA.visible = true;
                                textFieldLinearB.visible = true;
                            }else
                            {
                                labelPercentualeLineareA1.visible=false;
                                labelPercentualeLineareB1.visible=false;
                                textFieldLinearA.visible = false;
                                textFieldLinearB.visible = false;

                            }
                        }
                        width: 63
                        text: "0"
                        placeholderText: "Number of linear functions"
                        validator: RegExpValidator {
                            regExp: /^[0-9]\d+/
                        }
                        onTextChanged: showLabel(text)
                    }


                }

                RowLayout {
                    id: rowLayout5
                    width: 100
                    height: 100

                    GridLayout {
                        id: gridLayoutLinearB
                        width: 100
                        height: 100
                        columnSpacing: 25
                        visible: true
                        Label {
                            id: labelPercentualeLineareA1
                            text: qsTr("Percentage Lineare A")
                            visible: false
                        }

                        TextField {
                            id: textFieldLinearA
                            text: "0.03"
                            visible: false
                            placeholderText: qsTr("Text Field")
                             validator:  RegExpValidator { regExp: /0[.]\d{1,3}|^[1-9]\d+/ }
                        }

                        Label {
                            id: labelPercentualeLineareB1
                            text: qsTr("Percentage Lineare B")
                            visible: false
                        }

                        TextField {
                            id: textFieldLinearB
                            text: "0.03"
                            visible: false
                            placeholderText: qsTr("Text Field")
                             validator:  RegExpValidator { regExp: /0[.]\d{1,3}|^[1-9]\d+/ }
                        }
                        columns: 2
                        rows: 4
                    }
                }

            }

            GridLayout {
                id: gridLayout3
                y: 548
                width: 309
                height: 50
                columnSpacing: 2
                rowSpacing: 1
                columns: 2
                rows: 1

                Layout.preferredWidth: 309
                Layout.preferredHeight: 50



                FileDialog {
                    id: fileDialogRain
                    title: "Please choose a file"
                    folder: shortcuts.home
                    property string  tmp
                    property variant split
                    onAccepted: {
                        pathrain=fileDialogRain.fileUrl
                        tmp = fileDialogRain.fileUrl
                        split = tmp.split("/")
                        console.log("You chose: " + split[0])
                        console.log("You chose: " + split.length)
                        textfileRain.text = "../"+split[split.length-1]
                        //handlerCSV.loadCSV(fileDialogRain.fileUrl)
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
                    property string  tmp
                    property variant split
                    onAccepted: {
                        pathactivation=fileDialogActivation.fileUrl
                        tmp = fileDialogActivation.fileUrl
                        split = tmp.split("/")
                        console.log("You chose: " + split[0])
                        console.log("You chose: " + split.length)
                        textfileActivation.text = "../"+split[split.length-1]
                        //handlerCSV.loadCSV(fileDialogActivation.fileUrl)
                        //Qt.quit()
                    }
                    onRejected: {
                        console.log("Canceled")
                        //Qt.quit()
                    }
                    nameFilters: [ "files (*.csv)" ]
                    Component.onCompleted: visible = false
                }

                Button {
                    id: button1
                    text: qsTr("Load Kernel")
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

            }


            RowLayout {
                id: columnLayout1
                y: 709
                width: 328
                height: 100
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 2

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
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    checkable: false
                    property  string selection;
                    property  string selectionElitist;
                    property  string populationSize;
                    property  string percentageCrossover;
                    property  string percentageMutation;
                    property  string percentageWeight;
                    property  string numberProcessor;
                    property  string numberGamma;
                    property  string percentageGammaA;
                    property  string percentageGammaB;
                    property  string numberLinear;
                    property  string percentageLinearA;
                    property  string percentageLinearB;
                    property  string maxGeneration;
                    property  string fileUrl;

                    property  int typeAlgorithm;

                    onClicked: {
                        populationSize = textFieldPopulationSize.text;
                        percentageCrossover = textFieldProbabiltyCrossOver.text;
                        percentageMutation = textFieldProbabiltyMutation.text;
                        percentageWeight = textPercentageWeight.text;
                        numberProcessor = textFieldNumberProcessor.text;
                        numberGamma = textFieldGammaFunctions.text;
                        percentageGammaA = textFieldGammaA.text;
                        percentageGammaB = textFieldGammaB.text;
                        numberLinear = textFieldLinearFunction.text;
                        percentageLinearA = textFieldLinearA.text;
                        percentageLinearB = textFieldLinearB.text;
                        maxGeneration = textFieldMaxGeneration.text;
                        selection =  selections.get(selections.currentIndex).text;
                        selectionElitist =  selectionParameterTournamentWithoutReplacement.text;
                        typeAlgorithm = 4;
                        fileUrl = fileDialogRain.fileUrl;

                        console.log("populationSize : "+populationSize +
                                    "\n percentageCrossover : "+percentageCrossover+
                                    "\n percentageMutation : "+percentageMutation+
                                    "\n percentageWeight : "+percentageWeight+
                                    "\n numberProcessor : "+numberProcessor+
                                    "\n numberGamma : "+numberGamma+
                                    "\n percentageGammaA : "+percentageGammaA+
                                    "\n percentageGammaB : "+percentageGammaB+
                                    "\n numberLinear : "+numberLinear+
                                    "\n percentageLinearA : "+percentageLinearA+
                                    "\n percentageLinearB : "+percentageLinearB+
                                    "\n maxGeneration : "+maxGeneration+
                                    "\n selection : "+selection+
                                    "\n selectionElitist : "+selectionElitist+
                                    "\n fileUrl : "+fileUrl
                                    )


                                    sakeStart.startRegression(
                                          selection  ,
                                          selectionElitist  ,
                                          populationSize  ,
                                          percentageCrossover  ,
                                          percentageMutation  ,
                                          percentageWeight  ,
                                          numberProcessor  ,
                                          numberGamma  ,
                                          percentageGammaA  ,
                                          percentageGammaB  ,
                                          numberLinear  ,
                                          percentageLinearA  ,
                                          percentageLinearB  ,
                                          maxGeneration,
                                          fileUrl
                                        )
//                                                            sakeStart.startRegression()
                                        close();
                        //                        if(comboSelection.currentText == "StochTour(t)"
                        //                                || comboSelection.currentText == "DetTour(T)"){
                        //                            para1=selectionParameter.text;
                        //                            para2=-1;
                        //                        }else
                        //                            if(comboSelection.currentText == "Ranking(p,e)"){
                        //                                para1=selectParameterRanking1.text;
                        //                                para2=selectParameterRanking2.text;
                        //                            }else
                        //                                if(comboSelection.currentText == "Roulette"){
                        //                                    para1=-1;
                        //                                    para2=-1;
                        //                                }else
                        //                                    if(comboSelection.currentText == "Sequential(ordered/unordered)")
                        //                                    {
                        //                                        para1=comboSelectinParameterSequentialList.get(comboSelectinParameterSequential.currentIndex).text;
                        //                                        para2=-1;
                        //                                    }else
                        //                                        if(comboSelection.currentText == "Generational"){
                        //                                            para1=selectionParameterTournamentWithoutReplacement.text;
                        //                                            para2=-1;
                        //                                            typeAlgorithm=2;
                        //                                        }else
                        //                                            if(comboSelection.currentText == "MultiObjects Generational"){
                        //                                                para1=selectionParameterTournamentWithoutReplacement.text;
                        //                                                para2=-1;
                        //                                                typeAlgorithm=3;
                        //                                                order1=selectionsOrder.get(selectionsOrder.currentIndex).text
                        //                                                order2=selectionsOrder1.get(selectionsOrder1.currentIndex).text
                        //                                                order3=selectionsOrder2.get(selectionsOrder2.currentIndex).text
                        //                                                order4=selectionsOrder3.get(selectionsOrder3.currentIndex).text
                        //                                            }else
                        //                                                if(comboSelection.currentText == "Steady-State"){
                        //                                                    para1=selectionParameterTournamentWithoutReplacement.text;
                        //                                                    para2=-1;
                        //                                                    typeAlgorithm=0;
                        //                                                }else
                        //                                                    if(comboSelection.currentText == "MultiObjects Steady-State"){
                        //                                                        para1=selectionParameterTournamentWithoutReplacement.text;
                        //                                                        para2=-1;
                        //                                                        typeAlgorithm=1;
                        //                                                        order1=selectionsOrder.get(selectionsOrder.currentIndex).text
                        //                                                        order2=selectionsOrder1.get(selectionsOrder1.currentIndex).text
                        //                                                        order3=selectionsOrder2.get(selectionsOrder2.currentIndex).text
                        //                                                        order4=selectionsOrder3.get(selectionsOrder3.currentIndex).text
                        //                                                    }



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

    }
    //    MessageDialog {
    //        id: messageDialogRain
    //        title: "Input error"
    //        text: "Please enter rain csv path."
    //        onAccepted: close()
    //        Component.onCompleted: visible = false
    //        modality: "ApplicationModal"
    //    }

    //    MessageDialog {
    //        id: messageDialogActivation
    //        title: "Input error"
    //        text: "Please enter Activation csv path."
    //        onAccepted: close()
    //        Component.onCompleted: visible = false
    //        modality: "ApplicationModal"
    //    }

    //    MessageDialog {
    //        id: messageDialogProjectName
    //        title: "Input error"
    //        text: "The project name already exists."
    //        onAccepted: close()
    //        Component.onCompleted: visible = false
    //        modality: "ApplicationModal"
    //    }
    //    MessageDialog {
    //        id: messageDialogProjectNameEmpty
    //        title: "Input error"
    //        text: "The project name is empty."
    //        onAccepted: close()
    //        Component.onCompleted: visible = false
    //        modality: "ApplicationModal"
    //    }

}
