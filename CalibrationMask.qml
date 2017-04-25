import QtQuick 2.0
import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Controls 2.1
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4

Window {

    id: calibrationMask
    visible: true
    width: 600
    height: 1000
    title: qsTr("SAKe")
    Layout.maximumHeight: height
    Layout.maximumWidth: width

    property  int typeProject : 0;
    property  string projectName : "";

    function f(list){
        typeProject=1;
        projectName = list[0];
        textFieldProjectName.visible = false;
        textProjectName.visible = false;
        console.log( " CIAOOOO " )
        for(var i = 0; i< list.length ; i++){
            console.log(i + "  " +list[i])
        }
        console.log( " CIAOOOO " )
        calibrationMask.title = "Project name               "  + list[0]
        //labelProjectNameFromFile.text=list[0]
                if(list[1]==="StochTour(t)"){
                            comboSelection.currentIndex=0
                            parameter1.text=list[2]
                        }else
                            if(list[1]==="DetTour(T)"){
                                comboSelection.currentIndex=1
                                parameter1.text=list[2]
                            }else
                                if(list[1]==="Ranking(p,e)"){
                                    comboSelection.currentIndex=2
                                    parameter1.text=list[2]
                                    parameter2.text=list[3]
                                }else
                                    if(list[1]==="Roulette"){
                                            comboSelection.currentIndex=3
                                        }


        textNumberProcessor.text=list[4]
        textFieldPopulation.text=list[5]
        textFieldMaxGen.text=list[6]
        textFieldtbMax.text=list[7]
        textFieldtbMin.text=list[8]
        textFielddHpMax.text=list[9]
        textFielddHpMin.text=list[10]
        //textFieldPropSelection.text=list[11]
        textFieldPropCrossover.text=list[12]
        textFieldPropMutation.text=list[13]
        textFieldPme.text=list[14]
        textFieldPmb.text=list[15]
        if(list[16]==="Rettangolare")
            comboPattern.currentIndex=2
        else
            if(list[16]==="Triangolare Disc")
                comboPattern.currentIndex=0
            else
                if(list[16]==="Triangolare Asc")
                    comboPattern.currentIndex=1

        //var split = list[17].split("/")
        //textFieldRain.text = "../"+split[split.length-1]
        textFieldRain.text=list[17]
        //var split2 = list[18].split("/")
        //textFieldActivation.text = "../"+split2[split2.length-1]
        textFieldActivation.text=list[18]
        comboReplacament.currentIndex = list[19]
        replacementParameter.text = list[20]
    }



    ScrollView {
        width: parent.width
        height: parent.height
        Layout.maximumHeight: parent.height
        Layout.maximumWidth: parent.width
        verticalScrollBarPolicy :Qt.ScrollBarAlwaysOn
        Grid {
            id: grid1
            x: 0
            y: 0
            width: 600
            height: 1000
            rows: 7

            Rectangle {
                id: rectangle1
                width: 353
                height: 151
                color: "#ffffff"
                border.width: 0
                border.color: "#000000"

                Text {
                    id: text1
                    x: 25
                    y: 8
                    text: qsTr("1 - Input")
                    font.pixelSize: 23
                }

                Rectangle {
                    id: rectangle2
                    x: 25
                    y: 42
                    width: 455
                    height: 96
                    color: "#ffffff"
                    border.width: 1
                    border.color: "#110000"

                    FileDialog {
                        id: fileDialogRain
                        title: "Please choose a file"
                        folder: shortcuts.home
                        onAccepted: {
                            console.log("You chose: " + fileDialogRain.fileUrls)
                            textFieldRain.text = fileDialogRain.fileUrl
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
                        onAccepted: {
                            console.log("You chose: " + fileDialogActivation.fileUrls)
                            textFieldActivation.text = fileDialogActivation.fileUrl
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

                    Text {
                        id: textfileRain
                        x: 8
                        y: 38
                        width: 82
                        height: 20
                        text: qsTr("Rain")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 12
                    }

                    Button {
                        id: button1
                        x: 300
                        y: 38
                        width: 80
                        height: 20
                        text: qsTr("Load")
                        onClicked: {
                            fileDialogRain.open()
                        }
                    }





                    Text {
                        id: textfileActivation
                        x: 8
                        y: 68
                        width: 82
                        height: 20
                        text: qsTr("Activations")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 12

                    }

                    Button {
                        id: button2
                        x: 300
                        y: 68
                        width: 80
                        height: 20
                        text: qsTr("Load")
                        onClicked: {
                            fileDialogActivation.open()
                        }
                    }

                    TextField {
                        id: textFieldRain
                        x: 126
                        y: 38
                        width: 147
                        height: 20
                        text: qsTr("")
                    }

                    TextField {
                        id: textFieldActivation
                        x: 126
                        y: 68
                        width: 147
                        height: 20
                        text: qsTr("")
                    }

                    Text {
                        id: textFieldProjectName
                        x: 8
                        y: 8
                        width: 82
                        height: 20
                        text: qsTr("Project name")
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 12
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField {
                        id: textProjectName
                        x: 126
                        y: 8
                        width: 147
                        height: 20
                        text: qsTr("")
                    }
                }


            }

            Rectangle {
                id: rectangle3
                width: 353
                height: 151
                color: "#ffffff"
                border.color: "#000000"
                border.width: 0
                Text {
                    id: text2
                    x: 25
                    y: -7
                    text: qsTr("2- Tournament Selection Additional Criteria")
                    font.pixelSize: 23
                }

                Rectangle {
                    id: rectangle4
                    x: 25
                    y: 27
                    width: 455
                    height: 71
                    color: "#ffffff"
                    border.color: "#110000"
                    border.width: 1

                    ListModel {
                        id: selectionsOrder1
                        ListElement {
                            text: "Delta critico"
                        }
                    }
                    ListModel {
                        id: selectionsOrder2
                        ListElement {
                            text: "Momento del primo ordine"
                        }
                    }

                    ListModel {
                        id: selectionsOrder3
                        ListElement {
                            text: "tempo base"
                        }


                    }









                    ComboBox {
                        id: comboBox4
                        x: 198
                        y: 38
                        currentIndex: 0
                        model:selectionsOrder3
                        visible: true
                    }
                    Label {
                        id: label16
                        x: 186
                        y: 40
                        text: qsTr("4")
                    }
                    ComboBox {
                        id: comboBox3
                        x: 29
                        y: 38
                        function configComboBox3(currentIndex){
                            selectionsOrder3.clear();
                            console.log("comboBox3 currentIndex = " +currentIndex+"\n")
                            if(currentIndex === 0)
                            {
                                selectionsOrder3.append(selectionsOrder2.get(1))
                            }else
                                if(currentIndex === 1)
                                {
                                    selectionsOrder3.append(selectionsOrder2.get(0))
                                }
                        }
                        currentIndex: 0
                        model:selectionsOrder2
                        visible: true
                        onCurrentIndexChanged: configComboBox3(currentIndex)
                    }
                    Label {
                        id: label15
                        x: 17
                        y: 41
                        text: qsTr("3")
                    }
                    Label {
                        id: label13
                        x: 17
                        y: 8
                        text: qsTr("1")
                    }
                    ComboBox {

                        id: comboBox2
                        x: 198
                        y: 5
                        function configComboBox2(currentIndex){
                            selectionsOrder2.clear();
                            var i=0;
                            if(currentIndex === 0)
                            {
                                for( i=1;i<3;i++ ){
                                    console.log(" comboBox2 0 index i = "+i%3+"\n");
                                    selectionsOrder2.append(selectionsOrder1.get(i%3))
                                }
                            }else
                                if(currentIndex === 1)
                                {
                                    for( i=2;i<4;i++ ){
                                        console.log(" comboBox2 1 index i = "+i%3+"\n");
                                        selectionsOrder2.append(selectionsOrder1.get(i%3))
                                    }
                                }else
                                    if(currentIndex === 2)
                                    {
                                        for( i=3;i<5;i++ ){
                                            console.log(" comboBox2 2 index i = "+i%3+"\n");
                                            selectionsOrder2.append(selectionsOrder1.get(i%3))
                                        }
                                    }
                            comboBox3.currentIndex=i%2;
                            comboBox3.configComboBox3((i%2));
                        }
                        currentIndex: 0
                        model: selectionsOrder1
                        visible: true
                        onCurrentIndexChanged: configComboBox2(currentIndex)
                    }
                    Label {
                        id: label14
                        x: 186
                        y: 7
                        text: qsTr("2")
                    }
                    ComboBox {
                        id: comboBox1
                        x: 29
                        y: 5
                        currentIndex: 0
                        visible: true
                        function configComboBox1(currentIndex){
                            selectionsOrder1.clear();
                            var i=0;
                            if(currentIndex === 0)
                            {
                                for( i=1;i<4;i++ ){
                                    console.log("0 index i = "+i+"\n");
                                    selectionsOrder1.append(selectionsOrder.get(i))
                                }
                            }else
                                if(currentIndex === 1)
                                {
                                    for( i=2;i<5;i++ ){
                                        console.log("1 index i = "+i%4+"\n");
                                        selectionsOrder1.append(selectionsOrder.get(i%4))
                                    }
                                }else
                                    if(currentIndex === 2)
                                    {
                                        for( i=3;i<6;i++ ){
                                            console.log("2 index i = "+i%4+"\n");
                                            selectionsOrder1.append(selectionsOrder.get(i%4))
                                        }
                                    }else
                                        if(currentIndex === 3)
                                        {
                                            for( i=4;i<7;i++ ){
                                                console.log("3 index i = "+i%4+"\n");
                                                selectionsOrder1.append(selectionsOrder.get(i%4))
                                            }
                                        }
                            comboBox2.currentIndex=i%3;
                            comboBox2.configComboBox2((i%3));
                            //comboBox3.configComboBox3(0);
                        }

                        model: ListModel {
                            id: selectionsOrder
                            ListElement { text: "Fitness";  }
                            ListElement { text: "Delta critico";  }
                            ListElement { text: "Momento del primo ordine";  }
                            ListElement { text: "tempo base"; }
                        }
                        onCurrentIndexChanged: configComboBox1(currentIndex)
                    }
                }
            }

            Rectangle {
                id: rectangle5
                width: 353
                height: 151
                color: "#ffffff"
                border.color: "#000000"
                border.width: 0

                Text {
                    id: text3
                    x: 26
                    y: -42
                    text: qsTr("3 - Population, Pattern & Replacement")
                    font.pixelSize: 23
                }

                Rectangle {
                    id: rectangle6
                    x: 26
                    y: 0
                    width: 455
                    height: 109
                    color: "#ffffff"
                    border.color: "#110000"
                    border.width: 1

                    Label {
                        id: labelPopulatioonSize
                        x: 14
                        y: 8
                        text: qsTr("Population size (N)")
                        transformOrigin: Item.Center


                    }

                    TextField {
                        id: textFieldPopulation
                        x: 131
                        y: 8
                        width: 63
                        text: "20"

                        placeholderText: "20"
                    }


                    Label {
                        id: label11
                        x: 14
                        y: 40
                        text: qsTr("Initial pattern")
                    }

                    Label {
                        id: labelselectionParameterTournamentWithoutReplacement
                        x: 280
                        y: 70
                        visible: false
                        text: "number of elitists"
                    }
                    TextField {
                        id: replacementParameter
                        x: 376
                        y: 68
                        width: 39
                        height: 16
                        visible: false
                        text: "0"
                    }

                    ComboBox {
                        id: comboPattern
                        x: 130
                        y: 37
                        activeFocusOnPress: true
                        currentIndex: 2


                        model: ListModel {
                            id: patterns
                            ListElement { text: "Triangolare Disc";  }
                            ListElement { text: "Triangolare Asc";  }
                            ListElement { text: "Rettangolare";  }
                        }
                    }

                    ComboBox {
                        id: comboReplacament

                        x: 130
                        y: 68
                        width: 138
                        height: 18
                        activeFocusOnPress: true

                        function show( currentIndex){

                            if(currentIndex === 1 ){
                                replacementParameter.visible=true;
                                labelselectionParameterTournamentWithoutReplacement.visible=true;
                            }else{
                                replacementParameter.visible=false;
                                labelselectionParameterTournamentWithoutReplacement.visible=false;
                            }

                        }

                        model: ListModel {
                            id: patterns1
                            ListElement {
                                text: "generational"
                            }

                            ListElement {
                                text: "elitist/steady state"
                            }
                        }
                        currentIndex: 0
                        onCurrentIndexChanged:show(currentIndex)
                    }

                    Label {
                        id: label12
                        x: 15
                        y: 72
                        text: qsTr("Replacement")
                    }




                }
            }

            Rectangle {
                id: rectangle7
                width: 353
                height: 151
                color: "#ffffff"
                border.width: 0
                Text {
                    id: text4
                    x: 28
                    y: -34
                    text: qsTr("4 - Selection")
                    font.pixelSize: 23
                }

                Rectangle {
                    id: rectangle8
                    x: 28
                    y: 0
                    width: 455
                    height: 109
                    color: "#ffffff"
                    border.width: 1

                    Label {
                        id: labelSelection
                        x: 16
                        y: 15
                        text: qsTr("Selection")
                        scale: 1
                        transformOrigin: Item.Center
                    }



                    ComboBox {
                        id: comboSelection
                        x: 94
                        y: 12
                        currentIndex: 3
                        function show( currentIndex){

                            if(currentIndex === 0  ){
                                labelstochpar1.visible = true;
                            }else
                            {
                                labelstochpar1.visible = false;
                            }

                            if(currentIndex === 1  ){
                                labeldetpar1.visible = true;
                            }else
                            {
                                labeldetpar1.visible = false;
                            }


                            if(currentIndex ===2){
                                labelrankpar1.visible = true;
                                labelrankpar2.visible = true;
                            }else
                            {
                                labelrankpar1.visible = false;
                                labelrankpar2.visible = false;
                            }

                            if(currentIndex === 0  || currentIndex === 1){
                                parameter1.visible = true;
                                parameter2.visible = false;
                            }else{
                                if(currentIndex === 2){
                                    parameter1.visible = true;
                                    parameter2.visible = true;
                                }else
                                    if(currentIndex === 3)
                                    {
                                        parameter1.visible = false;
                                        parameter2.visible = false;
                                    }
                            }


                        }

                        model: ListModel {
                            id: selections
                            ListElement { text: "StochTour(t)";  }
                            ListElement { text: "DetTour(T)";  }
                            ListElement { text: "Ranking(p,e)";  }
                            ListElement { text: "Roulette"; }
                        }
                        onCurrentIndexChanged: show(currentIndex)
                    }


                    Label {
                        id: labelrankpar1
                        x: 242
                        y: 15
                        visible: false
                        text: "p (selective pressure 1 < p <= 2)"
                    }
                    Label {
                        id: labelrankpar2
                        x: 242
                        y: 60
                        visible: false
                        text: "e (exponent 1=linear)"
                    }

                    Label {
                        id: labelstochpar1
                        x: 242
                        y: 15
                        visible: false
                        text: "Tr (tournament rate 0.55 <= Tr <= 1)"
                    }

                    Label {
                        id: labeldetpar1
                        x: 242
                        y: 18
                        visible: false
                        text: "Ts (tournament size 2 <= Ts <=N)"
                    }

                    TextField {
                        id: parameter1
                        x: 244
                        y: 38
                        width: 125
                        height: 16
                        visible: false
                        text: "0"
                    }
                    TextField {
                        id: parameter2
                        x: 244
                        y: 82
                        width: 125
                        height: 15
                        visible: false
                        text: "0"
                    }
                    //                TextField {
                    //                    id: selectParameterRanking2
                    //                    width: 31
                    //                    height: 31
                    //                    text: "0"
                    //                    visible: false
                    //                }

                    //                TextField {
                    //                    id: selectParameterRanking1
                    //                    width: 31
                    //                    height: 31
                    //                    text: "0"
                    //                    visible: false
                    //                }



                    border.color: "#110000"
                }
                border.color: "#000000"
            }

            Rectangle {
                id: rectangle9
                width: 353
                height: 151
                color: "#ffffff"
                border.width: 0
                Text {
                    id: text5
                    x: 29
                    y: -34
                    text: qsTr("5 - Genetic operators")
                    font.pixelSize: 23
                }

                Rectangle {
                    id: rectangle10
                    x: 29
                    y: 0
                    width: 455
                    height: 120
                    color: "#ffffff"
                    border.width: 1

                    Label {
                        id: label3
                        x: 14
                        y: 8
                        text: qsTr("Crossover probability")
                    }

                    TextField {
                        id: textFieldPropCrossover
                        x: 139
                        y: 8
                        width: 63
                        height: 16
                        text: "0.75"
                        placeholderText: qsTr("0.75")
                    }

                    Label {
                        id: label4
                        x: 17
                        y: 35

                        text: qsTr("Mutation probability")
                    }

                    TextField {
                        id: textFieldPropMutation
                        x: 139
                        y: 35
                        width: 63
                        height: 16
                        text: "0.25"
                        placeholderText: qsTr("0.25")
                    }

                    Label {
                        id: label7
                        x: 54
                        y: 63
                        text: qsTr("Pme")
                    }

                    TextField {
                        id: textFieldPme
                        x: 139
                        y: 61
                        width: 63
                        height: 16
                        text: "25"
                        placeholderText: qsTr("25")
                    }

                    Label {
                        id: label8
                        x: 55
                        y: 88
                        width: 21
                        height: 13
                        text: qsTr("Pmb")
                    }

                    TextField {
                        id: textFieldPmb
                        x: 139
                        y: 88
                        width: 63
                        height: 16
                        text: "0.5"
                        placeholderText: qsTr("0.5")
                    }

                    Label {
                        id: label5
                        x: 281
                        y: 10
                        text: qsTr("tbMax")
                    }

                    TextField {
                        id: textFieldtbMax
                        x: 337
                        y: 8
                        width: 63
                        height: 16
                        text: "180"
                        placeholderText: qsTr("180")
                    }

                    Label {
                        id: label6
                        x: 283
                        y: 35
                        text: qsTr("tbMin")
                    }

                    TextField {
                        id: textFieldtbMin
                        x: 337
                        y: 35
                        width: 63
                        height: 16
                        text: "30"
                        placeholderText: qsTr("30")
                    }

                    Label {
                        id: label9
                        x: 276
                        y: 88
                        text: qsTr("dHpMax")
                    }

                    TextField {
                        id: textFielddHpMax
                        x: 337
                        y: 85
                        width: 63
                        text: "50"
                        placeholderText: qsTr("50")
                    }

                    Label {
                        id: label10
                        x: 277
                        y: 63
                        text: qsTr("dHpMin")
                    }

                    TextField {
                        id: textFielddHpMin
                        x: 337
                        y: 60
                        width: 63
                        text: "-50"
                        placeholderText: qsTr("-50")
                    }

                    border.color: "#110000"
                }
                border.color: "#000000"
            }

            Rectangle {
                id: rectangle11
                width: 353
                height: 151
                color: "#ffffff"
                Text {
                    id: text6
                    x: 30
                    y: -26
                    text: qsTr("6 - Stopping criteria")
                    font.pixelSize: 23
                }

                Rectangle {
                    id: rectangle12
                    x: 30
                    y: 8
                    width: 455
                    height: 34
                    color: "#ffffff"
                    border.width: 1
                    border.color: "#110000"

                    Label {
                        id: labelMaxGen1
                        x: 8
                        y: 8
                        text: qsTr("Maximum number of iterations")
                    }

                    TextField {
                        id: textFieldMaxGen
                        x: 213
                        y: 6
                        width: 63
                        text: "5000"
                        placeholderText: qsTr("5000")
                    }
                }
                border.width: 0
                border.color: "#000000"
            }

            Rectangle {
                id: rectangle13
                width: 353
                height: 151
                color: "#ffffff"
                Text {
                    id: text7
                    x: 31
                    y: -102
                    text: qsTr("7 - Run")
                    font.pixelSize: 23
                }

                Rectangle {
                    id: rectangle14
                    x: 31
                    y: -65
                    width: 455
                    height: 100
                    color: "#ffffff"
                    border.width: 1
                    border.color: "#110000"

                    Label {
                        id: labelNumberProcessor
                        x: 8
                        y: 14
                        width: 120
                        text: qsTr("Number Processor")
                    }

                    TextField {
                        id: textNumberProcessor
                        x: 165
                        y: 12
                        width: 63
                        visible: true
                        text: "1"
                        placeholderText: "1"
                    }

                    Label {
                        id: labellastGeneration
                        x: 8
                        y: 40
                        width: 120
                        text: qsTr("Continue from last generation")
                    }

                    CheckBox {
                        id:lastGeneration
                        activeFocusOnPress: false
                        checked: false
                        x: 165
                        y: 38
                        //text: qsTr("Start From Last Generation")

                    }

                    Button {
                        id: start
                        objectName: "namestart"



                        signal qmlSignal(var var1,var var1,var var2,var var3,var var4,var var5,
                                         var var6,var var7,var var8,var var9,var var10,var var11,
                                         var var12,var var13,var var14)
                        y: 58
                        text: qsTr("Start GA")
                        checkable: false
                        property  string para1;
                        property  string para2;
                        property  string order1;
                        property  string order2;
                        property  string order3;
                        property  string order4;
                        property  int typeReplacement;
                        x: 283

                        onClicked: {
                            order1="";
                            order2="";
                            order3="";
                            order4="";

                            if(typeProject===0)
                            {
                                projectName = textProjectName.text;
                            }

                            typeReplacement=4;
                            if(comboSelection.currentText == "StochTour(t)"
                                    || comboSelection.currentText == "DetTour(T)"){
                                para1=parameter1.text;
                                para2=-1;
                            }else
                                if(comboSelection.currentText == "Ranking(p,e)"){
                                    para1=parameter1.text;
                                    para2=parameter2.text;
                                }else
                                    if(comboSelection.currentText == "Roulette"){
                                        para1=-1;
                                        para2=-1;
                                    }

                            if(comboReplacament.currentText == "generational"){
                                typeReplacement=0;
                                order1=selectionsOrder.get(comboBox1.currentIndex).text
                                order2=selectionsOrder1.get(comboBox2.currentIndex).text
                                order3=selectionsOrder2.get(comboBox3.currentIndex).text
                                order4=selectionsOrder3.get(comboBox4.currentIndex).text
                            }else
                                if(comboReplacament.currentText == "elitist/steady state"){
                                    typeReplacement=1;
                                    order1=selectionsOrder.get(comboBox1.currentIndex).text
                                    order2=selectionsOrder1.get(comboBox2.currentIndex).text
                                    order3=selectionsOrder2.get(comboBox3.currentIndex).text
                                    order4=selectionsOrder3.get(comboBox4.currentIndex).text
                                }
                                                    if(textProjectName.length ===0 && typeProject===0){
                                                        messageDialogProjectNameEmpty.open()
                                                    }else

                                                        if( sakeStart.existProjectName(textProjectName.text) === 1 && typeProject===1){
                                                            messageDialogProjectName.open()
                                                        }
                                                        else
                            if(textfileRain.text == "Empty"){
                                messageDialogRain.open()
                            }else
                                if(textfileActivation.text == "Empty"){
                                    messageDialogActivation.open()
                                }else
                                    if(textFieldPopulation.text == ""){
                                        messageError.text = "Field Population can not be empty"
                                        messageError.open()
                                    }else if(textFieldMaxGen.text == ""){
                                        messageError.text = "Field max generations can not be empty"
                                        messageError.open()
                                    }else if(textFieldtbMax.text == ""){
                                        messageError.text = "Field tb Max can not be empty"
                                        messageError.open()
                                    }else if(textFieldtbMin.text == ""){
                                        messageError.text = "Field tb Min can not be empty"
                                        messageError.open()
                                    }else if(textFielddHpMax.text == ""){
                                        messageError.text = "Field dHpMax can not be empty"
                                        messageError.open()
                                    }else if(textFielddHpMin.text == ""){
                                        messageError.text = "Field dHpMin can not be empty"
                                        messageError.open()
                                    }else if(textFieldPropCrossover.text == ""){
                                        messageError.text = "Field Probability Crossover can not be empty"
                                        messageError.open()
                                    }else if(textFieldPropMutation.text == ""){
                                        messageError.text = "Field Probability Mutation can not be empty"
                                        messageError.open()
                                    }else if(textFieldPme.text == ""){
                                        messageError.text = "Field Pme can not be empty"
                                        messageError.open()
                                    }else if(textFieldPmb.text == ""){
                                        messageError.text = "Field Pmb can not be empty"
                                        messageError.open()
                                    }else if(textNumberProcessor.text == ""){
                                        messageError.text = "Field Number of Processor can not be empty"
                                        messageError.open()
                                    }else {

//                                        console.log("order1 = "+selectionsOrder.get(comboBox1.currentIndex).text)
//                                        console.log("order2 = "+selectionsOrder1.get(comboBox2.currentIndex).text)
//                                        console.log("order3 = "+selectionsOrder2.get(comboBox3.currentIndex).text)
//                                        console.log("order4 = "+selectionsOrder3.get(comboBox4.currentIndex).text)


//                                        console.log("order1 = "+selectionsOrder.currentIndex)
//                                        console.log("order2 = "+selectionsOrder1.currentIndex)
//                                        console.log("order3 = "+selectionsOrder2.currentIndex)
//                                        console.log("order4 = "+selectionsOrder3.currentIndex)

//                                        console.log("order1 = "+selectionsOrder.get(selectionsOrder.currentIndex).text)
//                                        console.log("order2 = "+selectionsOrder1.get(selectionsOrder1.currentIndex).text)
//                                        console.log("order3 = "+selectionsOrder2.get(selectionsOrder2.currentIndex).text)
//                                        console.log("order4 = "+selectionsOrder3.get(selectionsOrder3.currentIndex).text)

                                                                                    sakeStart.InitAlgo(comboSelection.currentText,
                                                                                                       textFieldPopulation.text,
                                                                                                       textFieldMaxGen.text,
                                                                                                        textFieldtbMax.text,
                                                                                                       textFieldtbMin.text,
                                                                                                       textFielddHpMax.text,
                                                                                                       textFielddHpMin.text,
                                                                                                       textProjectName.text,
                                                                                                       textFieldPropCrossover.text,
                                                                                                       textFieldPropMutation.text,
                                                                                                       textFieldPme.text,
                                                                                                       textFieldPmb.text,
                                                                                                       comboPattern.currentText,
                                                                                                       textFieldRain.text,
                                                                                                       textFieldActivation.text,
                                                                                                       projectName,
                                                                                                       textNumberProcessor.text,
                                                                                                       para1,
                                                                                                       para2,
                                                                                                       false,
                                                                                                       typeProject,
                                                                                                       typeReplacement,
                                                                                                       order1,
                                                                                                       order2,
                                                                                                       order3,
                                                                                                       order4,
                                                                                                       replacementParameter.text
                                                                                                       )

                                        close()
                                    }

                        }

                    }
                }
                border.width: 0
                border.color: "#000000"
            }
        }

    }

}
