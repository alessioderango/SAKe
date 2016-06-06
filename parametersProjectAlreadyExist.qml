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
    minimumHeight: 800
    minimumWidth: 700
    maximumHeight: minimumHeight
    maximumWidth: minimumWidth

    property  string pathrain;
    property  string pathactivation;

    function f(list){
        console.log("Ok funzia")
        labelProjectNameFromFile.text=list[0]
        if(list[1]=="Genarational"){
            comboSelection.currentIndex=5
            selectionParameterTournamentWithoutReplacement.text=list[2]
        }else
            if(list[1]=="Steady-State"){
                comboSelection.currentIndex=7
                selectionParameterTournamentWithoutReplacement.text=list[2]
            }else
                if(list[1]=="MultiObject Steady-State"){
                    comboSelection.currentIndex=8
                    selectionParameterTournamentWithoutReplacement.text=list[2]
                }else
                    if(list[1]=="MultiObject Genarational"){
                        comboSelection.currentIndex=6
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
        textFieldPopulation.text=list[5]
        textFieldMaxGen.text=list[6]
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
        width: 700
        height: 785
        color:"white"

        ColumnLayout {
            id: columnLayout2
            x: 31
            y: 8
            width: 655
            height: 777
            spacing: 20



            Label {
                id: label1
                y: 26
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("SAKe parameters")
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

                GridLayout {
                    id: gridLayout4

                    rows: 1
                    columns: 4
                    columnSpacing: 20
                    Label {
                        id: labelSelection
                        text: qsTr("Selection")
                        scale: 1
                        transformOrigin: Item.Center
                    }



                    ComboBox {
                        id: comboSelection
                        currentIndex: 3
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

                            if(currentIndex ===5 || currentIndex ===7 || currentIndex ===6 || currentIndex ===8){
                                selectionParameterTournamentWithoutReplacement.visible=true;
                            }else{
                                selectionParameterTournamentWithoutReplacement.visible=false;
                            }
                            if(currentIndex ===6 || currentIndex ===8){
                                gridLayout5.visible=true;
                            }else{
                                gridLayout5.visible=false;
                            }
                        }

                        model: ListModel {
                            id: selections
                            ListElement { text: "StochTour(t)";  }
                            ListElement { text: "DetTour(T)";  }
                            ListElement { text: "Ranking(p,e)";  }
                            ListElement { text: "Roulette"; }
                            ListElement { text: "Sequential(ordered/unordered)";  }
                            ListElement { text: "Generational"; }
                            ListElement { text: "MultiObjects Generational"; }
                            ListElement { text: "Steady-State"; }
                            ListElement { text: "MultiObjects Steady-State"; }
                        }
                        onCurrentIndexChanged: show(currentIndex)
                    }

                    TextField {
                        id: selectionParameterTournamentWithoutReplacement
                        visible: false
                        text: "0"
                    }
                    TextField {
                        id: selectionParameter
                        width: 39
                        height: 31
                        visible: false
                        text: "0"
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
                        visible: false
                        currentIndex: 1
                        model: ListModel {
                            id: comboSelectinParameterSequentialList
                            ListElement { text: "ordered"; }
                            ListElement { text: "unorder";  }
                        }

                    }

                }

                GridLayout {
                    id: gridLayout5
                    width: 100
                    height: 100
                    visible: false
                    rows: 1
                    columns: 2

                    Label {
                        id: label2
                        text: qsTr("Selection Order")
                    }

                    Label {
                        id: label12
                        text: qsTr(":")
                        visible: true
                    }

                    Label {
                        id: label13
                        text: qsTr("1")
                    }

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
                        id: comboBox1
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

                    Label {
                        id: label14
                        text: qsTr("2")
                    }


                    ComboBox {

                        id: comboBox2
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
                        id: label15
                        text: qsTr("3")
                    }

                    ComboBox {
                        id: comboBox3
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
                        id: label16
                        text: qsTr("4")
                    }

                    ComboBox {
                        id: comboBox4
                        currentIndex: 0
                        model:selectionsOrder3
                        visible: true
                    }


                }

            }
            RowLayout {
                id: rowLayout1
                y: 100
                width: 645
                height: 431
                spacing: 1

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
                    rows: 1
                    columns: 2

                    Layout.preferredWidth: 309
                    Layout.preferredHeight: 426

                    GridLayout{
                        rows: 4
                        columns: 2
                        rowSpacing: 2
                        columnSpacing: 2
                        Layout.preferredWidth: 309
                        Layout.preferredHeight: 426
                        width: 309
                        height: 426
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Label {
                            id: labelPopulatioonSize
                            y: 243
                            text: qsTr("Population Size")
                            transformOrigin: Item.Center
                        }

                        TextField {
                            id: textFieldPopulation
                            width: 63
                            //text: "30"
                            //inputMethodHints: Qt.ImhDigitsOnly
                            validator: RegExpValidator { regExp: /^[1-9]\d+/ }
                            placeholderText: "population Size"
                        }



                        Label {
                            id: labelMaxGen1
                            text: qsTr("Maximum number of generations")
                        }

                        TextField {
                            id: textFieldMaxGen
                            width: 63
                            text: "5000"
                            validator: RegExpValidator { regExp: /^[1-9]\d+/ }
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
                            validator: RegExpValidator { regExp: /^[1-9]\d+/ }
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
                            validator: RegExpValidator { regExp: /^[1-9]\d+/ }
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

                            validator: RegExpValidator { regExp: /^-?[0-9]\d+/ }
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
                            validator: RegExpValidator { regExp: /^-?[0-9]\d+/ }
                            placeholderText: qsTr("")
                        }

                        CheckBox {id:lastGeneration; text: qsTr("Start From Last Generation")   }
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
                            validator:  RegExpValidator { regExp: /0[.]\d{1,3}/ }
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
                            validator:  RegExpValidator { regExp: /0[.]\d{1,3}/ }
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
                            validator:  RegExpValidator { regExp: /0[.]\d{1,3}|^[1-9]\d+/ }
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
                            validator:  RegExpValidator { regExp: /0[.]\d{1,3}|^[1-9]\d+/ }
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
                            validator:  RegExpValidator { regExp: /[1-9][0-9]+/ }
                            placeholderText: "Number of Processor"
                        }

                        Label {
                            id: labelSeed
                            width: 120
                            text: qsTr("Seed")
                        }

                        TextField {
                            id: textSeed
                            width: 63
                            visible: true
                            text: ""
                            validator:  RegExpValidator { regExp: /\d+/ }
                            placeholderText: "Seed"
                        }


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
                    property  string para1;
                    property  string para2;
                    property  string order1;
                    property  string order2;
                    property  string order3;
                    property  string order4;
                    property  int typeAlgorithm;

                    onClicked: {
                        order1="";
                        order2="";
                        order3="";
                        order4="";
                        typeAlgorithm=4;
                        if(comboSelection.currentText == "StochTour(t)"
                                || comboSelection.currentText == "DetTour(T)"){
                            para1=selectionParameter.text;
                            para2=-1;
                        }else
                            if(comboSelection.currentText == "Ranking(p,e)"){
                                para1=selectParameterRanking1.text;
                                para2=selectParameterRanking2.text;
                            }else
                                if(comboSelection.currentText == "Roulette"){
                                    para1=-1;
                                    para2=-1;
                                }else
                                    if(comboSelection.currentText == "Sequential(ordered/unordered)")
                                    {
                                        para1=comboSelectinParameterSequentialList.get(comboSelectinParameterSequential.currentIndex).text;
                                        para2=-1;
                                    }else
                                        if(comboSelection.currentText == "Generational"){
                                            para1=selectionParameterTournamentWithoutReplacement.text;
                                            para2=-1;
                                            typeAlgorithm=2;
                                        }else
                                            if(comboSelection.currentText == "MultiObjects Generational"){
                                                para1=selectionParameterTournamentWithoutReplacement.text;
                                                para2=-1;
                                                typeAlgorithm=3;
                                                order1=selectionsOrder.get(selectionsOrder.currentIndex).text
                                                order2=selectionsOrder1.get(selectionsOrder1.currentIndex).text
                                                order3=selectionsOrder2.get(selectionsOrder2.currentIndex).text
                                                order4=selectionsOrder3.get(selectionsOrder3.currentIndex).text
                                            }else
                                                if(comboSelection.currentText == "Steady-State"){
                                                    para1=selectionParameterTournamentWithoutReplacement.text;
                                                    para2=-1;
                                                    typeAlgorithm=0;
                                                }else
                                                    if(comboSelection.currentText == "MultiObjects Steady-State"){
                                                        para1=selectionParameterTournamentWithoutReplacement.text;
                                                        para2=-1;
                                                        typeAlgorithm=1;
                                                        order1=selectionsOrder.get(selectionsOrder.currentIndex).text
                                                        order2=selectionsOrder1.get(selectionsOrder1.currentIndex).text
                                                        order3=selectionsOrder2.get(selectionsOrder2.currentIndex).text
                                                        order4=selectionsOrder3.get(selectionsOrder3.currentIndex).text
                                                    }
                        // if(textfileRain.text != "empty")

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
                                                       pathrain,
                                                       pathactivation,
                                                       labelProjectNameFromFile.text,
                                                       textNumberProcessor.text,
                                                       para1,
                                                       para2,
                                                       lastGeneration.checked,
                                                       1,
                                                       typeAlgorithm,
                                                       order1,
                                                       order2,
                                                       order3,
                                                       order4
                                                       )
                                    close()
                                }

                    }

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
    MessageDialog {
        id: messageError
        title: "Input error"
        text: " "
        onAccepted: close()
        Component.onCompleted: visible = false
        modality: "ApplicationModal"
    }

}
