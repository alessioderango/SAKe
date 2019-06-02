#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->labelnumberElitists->hide();
    ui->lineEditNumberElitists->hide();
    ui->label_14->setText("Tr (tournament rate 0.55 <= Tr <= 1)");
    ui->label_15->hide();
    ui->lineEditPar2->hide();

    // check input
    ui->lineEditPopSize->setValidator(new QIntValidator(1, 1000000, this));
    QDoubleValidator *validator= new QDoubleValidator(this);
    validator->setRange(0,0,3);
    validator->setNotation(QDoubleValidator::StandardNotation);

    ui->lineEditPme->setValidator(new QIntValidator(0, 100, this));
    ui->lineEditPmb->setValidator(new QIntValidator(0, 100, this));
    ui->lineEditdHpMax->setValidator(new QIntValidator(0, 100, this));
    ui->lineEditPopSize->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEditTbMin->setValidator(new QIntValidator(1, 10000000000, this));
    ui->lineEditTbMax->setValidator(new QIntValidator(1, 10000000000, this));
    ui->lineEditNumberElitists->setValidator(new QIntValidator(1, 10000000000, this));
    ui->lineEditCrossoverP->setValidator(new QDoubleValidator(0, 1,2, this));
    ui->lineEditMutationP->setValidator(validator);
    ui->lineEditNumberOfLines->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEditNumProc->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEditSeed->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEditFrequKerSav->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEditNumBestKernelSaved->setValidator(new QIntValidator(0, 10000000000, this));
    ui->label_21->setVisible(false);
    ui->lineEditdHpMin->setVisible(false);
    ui->groupBox_7->setVisible(false);
    ui->pushButton_2->setAutoDefault(false);
    ui->pushButton_2->setDefault(false);
    ui->pushButton->setAutoDefault(false);
    ui->pushButton->setDefault(false);
    ui->pushButtonStart->setAutoDefault(false);
    ui->pushButtonStart->setDefault(false);

    //    QDoubleValidator* val = new QDoubleValidator(1.000, 2.000, 3, ui->lineEditPar1);
    //    val->setNotation(QDoubleValidator::StandardNotation);
    //    val->setLocale(QLocale::C);
    //    ui->lineEditPar1->setValidator(val);

    //ui->lineEditPar2->setValidator(val);

    //    QRegExp rx("^\d[0-9]*\.?[0-9]+");
    //    ui->lineEditPar1->setValidator(new QRegExpValidator(rx, this));
    ui->lineEditNumberOfLines->hide();
    ui->labelNumberOfLines->hide();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setParameters(QVariantList list)
{
    ui->checkBoxContinueFromLastGen->setEnabled(true);
    ui->label_25->setEnabled(true);
    ui->lineEditProjName->setText(list[0].toString());
    if(list[1]=="Stochastic Tournament (Tr)"){
        ui->comboBoxSelection->setCurrentIndex(0);
        ui->lineEditPar1->setText(list[2].toString());
        QDoubleValidator* val = new QDoubleValidator(0.55, 1.00, 2, ui->lineEditPar1);
        val->setNotation(QDoubleValidator::StandardNotation);
        val->setLocale(QLocale::C);
        ui->lineEditPar1->setValidator(val);
        ui->lineEditPar2->setText("-1");
    }else
        if(list[1]=="Deterministic Tournament (Ts)"){
            ui->comboBoxSelection->setCurrentIndex(1);
            ui->lineEditPar1->setText(list[2].toString());
            QIntValidator* val = new QIntValidator(2, ui->lineEditPopSize->text().toInt(), ui->lineEditPar1);
            val->setLocale(QLocale::C);
            ui->lineEditPar1->setValidator(val);
            ui->lineEditPar2->setText("-1");
        }else
            if(list[1]=="Ranking (s)"){
                ui->comboBoxSelection->setCurrentIndex(2);
                ui->lineEditPar1->setText(list[2].toString());
                QDoubleValidator* val = new QDoubleValidator(0.000, 2.000, 2, ui->lineEditPar1);
                val->setNotation(QDoubleValidator::StandardNotation);
                val->setLocale(QLocale::C);
                ui->lineEditPar1->setValidator(val);
                ui->lineEditPar2->setText("-1");
            }else
                if(list[1]=="Roulette"){
                    ui->comboBoxSelection->setCurrentIndex(3);
                    ui->lineEditPar1->setText("-1");
                    ui->lineEditPar2->setText("-1");
                }else
                    if(list[1]=="Ranking (p,e)"){
                        ui->comboBoxSelection->setCurrentIndex(2);
                        ui->lineEditPar1->setText(list[2].toString());
                        ui->lineEditPar1->setText(list[2].toString());
                        QDoubleValidator* val = new QDoubleValidator(1.000, 2.000, 2, ui->lineEditPar1);
                        val->setNotation(QDoubleValidator::StandardNotation);
                        val->setLocale(QLocale::C);
                        ui->lineEditPar1->setValidator(val);
                        ui->lineEditPar2->setText(list[3].toString());
                        //ui->lineEditPar2->setValidator(new QDoubleValidator(0,1,2));
                    }

    ui->lineEditNumProc->setText(list[4].toString());
    ui->lineEditPopSize->setText(list[5].toString());
    ui->lineEditMaxNumIte->setText(list[6].toString());
    ui->lineEditTbMax->setText(list[7].toString());
    ui->lineEditTbMin->setText(list[8].toString());
    ui->lineEditdHpMax->setText(list[9].toString());
    ui->lineEditdHpMin->setText(list[10].toString());
    ui->lineEditCrossoverP->setText(list[12].toString());
    ui->lineEditMutationP->setText(list[13].toString());
    ui->lineEditPme->setText(list[14].toString());
    ui->lineEditPmb->setText(list[15].toString());

    if(list[16] == "Rectangular")
        ui->comboBoxInitialPattern->setCurrentIndex(2);
    else
        if(list[16] == "Decreasing triangular")
            ui->comboBoxInitialPattern->setCurrentIndex(0);
        else
            if(list[16] == "Increasing triangular")
                ui->comboBoxInitialPattern->setCurrentIndex(1);


    ui->lineEditRain->setText(list[17].toString());
    ui->lineEditActivation->setText(list[18].toString());
    ui->comboBoxReplacement->setCurrentIndex(list[19].toInt());
    ui->lineEditNumberElitists->setText(list[20].toString());
    ui->lineEditSeed->setText(list[21].toString());
    ui->lineEditFrequKerSav->setText(list[22].toString());
    ui->lineEditNumBestKernelSaved->setText(list[23].toString());
    ui->selectOrder1->setCurrentText(list[25].toString());
    ui->selectOrder2->setCurrentText(list[26].toString());
    ui->comboBoxFitness->setCurrentIndex(list[28].toString().toInt());
    if(list[28] == "2"){
        ui->lineEditNumberOfLines->show();
        ui->labelNumberOfLines->show();
    }
    ui->lineEditNumberOfLines->setText(list[29].toString());
}

void Dialog::setReadOnlyProjName(bool a)
{
    ui->lineEditProjName->setReadOnly(a);
    ui->comboBoxReplacement->setCurrentIndex(1);
}

void Dialog::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr(""), "",
                                                    tr("All Files (*.csv)"));
    ui->lineEditRain->setText(fileName);

}

void Dialog::configComboBox3(int currentIndex){
    ui->selectOrder3->clear();
    if(currentIndex == 0)
    {
        ui->selectOrder3->addItem(ui->selectOrder2->itemText(1));
    }else
        if(currentIndex == 1)
        {
            ui->selectOrder3->addItem(ui->selectOrder2->itemText(0));
        }
    ui->selectOrder3->setMinimumContentsLength(18);
    ui->selectOrder3->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
}

void Dialog::configComboBox2(int currentIndex){
    ui->selectOrder2->clear();
    int i=0;
    if(currentIndex == 0)
    {
        for( i=1;i<3;i++ ){
            ui->selectOrder2->addItem(ui->selectOrder1->itemText(i%3));
        }
    }else
        if(currentIndex == 1)
        {
            for( i=2;i<4;i++ ){
                ui->selectOrder2->addItem(ui->selectOrder1->itemText(i%3));
            }
        }else
            if(currentIndex == 2)
            {
                for( i=3;i<5;i++ ){
                    ui->selectOrder2->addItem(ui->selectOrder1->itemText(i%3));
                }
            }
    configComboBox3(0);
}

void Dialog::on_selectOrder1_currentIndexChanged(int index)
{
    configComboBox2(index);
}

void Dialog::on_selectOrder2_currentIndexChanged(int index)
{
    configComboBox3(index);
}

void Dialog::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr(""), "",
                                                    tr("All Files (*.csv)"));
    ui->lineEditActivation->setText(fileName);
}
//
bool Dialog::checklineEdit(QString l, QString s){
    if(l.isEmpty()){
        QString error = QString(s);

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return true;
    }

    return false;
}


bool Dialog::checklineEditRangeDouble(QString l, double max, double min, QString s){
    if(l.toDouble() > max || l.toDouble() < min ){
        QString error = QString(s);

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return true;
    }
    if(l == "0." || l == "1." || l == "." ){
        QString error = QString(s);

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return true;
    }

    return false;
}
bool Dialog::checklineEditRangeInt(QString l, int max, int min, QString s){
    if(l.toInt() > max || l.toInt() < min ){
        QString error = QString(s);

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return true;
    }

    return false;
}

void Dialog::on_pushButtonStart_clicked()
{
    HandlerCSV * csv = new HandlerCSV();
    QString rainPath = ui->lineEditRain->text();
    Rain * rain;
    int rain_size=0;
    int rowError=0;
    QString e;
    QString actPath = ui->lineEditActivation->text();
    Activation * activation;
    int activation_size=0;


    if(ui->lineEditProjName->text().isEmpty())
    {
        QString error = QString("Projet name cannot be empty \n");

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }


    if(!ui->lineEditProjName->isReadOnly() && mainWindow->getXmlmanager()->findProjectName(ui->lineEditProjName->text(),"CalibrationProject"))
    {
        QString error = QString("Another Project with the same name already exists. \n");


        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );

        return;
    }

    if(!ui->lineEditProjName->isReadOnly()){
        QString tmp2 = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/workspace/calibration/"+ui->lineEditProjName->text();
        QDir dir3(tmp2);
        if(QDir(tmp2).exists()){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Warning", "A folder with the same name exists. Do you want to overwrite it?",
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {

            }else
            {
                if(reply == QMessageBox::No)
                    return;
            }
        }else
        {
            if (!dir3.exists()){
                dir3.mkdir(".");
            }
        }


    }


    if(!SAKeController::fileExists(rainPath)){
        //emit showAlertFileNotExist(rainPath);
        QString error = QString("File does not exist "+ rainPath+"\n");

        QMessageBox::information(
                    this,
                    tr(QString("File does not exist").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }

    if(!SAKeController::fileExists(actPath)){
        QString error = QString("File does not exist "+ actPath+"\n");

        QMessageBox::information(
                    this,
                    tr(QString("File does not exist").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }
    bool check = checklineEdit(ui->lineEditPopSize->text(), QString("Population size cannot be empty \n"));
    if(check) return;
    if(ui->lineEditPopSize->text().toInt() <= 0)
        check = checklineEdit("", QString("Population size myst be greater than 0\n"));
    if(check) return;


    // elitist
    if(ui->comboBoxReplacement->currentIndex() == 1){
        check = checklineEdit(ui->lineEditNumberElitists->text(), QString("number of elitists cannot be empty \n"));
        if(check) return;
        if(ui->lineEditPopSize->text().toInt() > ui->lineEditPopSize->text().toInt())
        {
            check = checklineEdit("", QString("number of elitists must be greater than the population size \n"));
            if(check) return;
        }
    }


    if(ui->comboBoxSelection->currentIndex() ==0 ){
        check = checklineEdit(ui->lineEditPar1->text(), QString("Tr cannot be empty \n"));
        if(check) return;
        check = checklineEditRangeDouble(ui->lineEditPar1->text(),1.0,0.55, QString("Tr must t be between 0.55 and 1. \n"));
        if(check) return;
    }else
        if(ui->comboBoxSelection->currentIndex() ==1 ){
            check = checklineEdit(ui->lineEditPar1->text(), QString("Ts cannot be empty \n"));
            if(check) return;
        }
        else
            if(ui->comboBoxSelection->currentIndex() ==2 ){
                check = checklineEdit(ui->lineEditPar1->text(), QString("selective pressure cannot be empty \n"));
                if(check) return;
                //                check = checklineEdit(ui->lineEditPar2->text(), QString("exponent cannot be empty \n"));
                //                if(check) return;
            }else
                if(ui->comboBoxSelection->currentIndex() ==4 ){//Ranking (p,e)
                    check = checklineEdit(ui->lineEditPar1->text(), QString("selective pressure cannot be empty \n"));
                    if(check) return;
                    check = checklineEdit(ui->lineEditPar2->text(), QString("exponent cannot be empty \n"));
                    if(check) return;
                }

    check = checklineEdit(ui->lineEditMutationP->text(), QString("Mutation probability cannot be empty \n"));
    if(check) return;
    check = checklineEditRangeDouble(ui->lineEditMutationP->text(),1.0,0.0, QString("Mutation probability must be between 0 and 1. \n"));
    if(check) return;

    check = checklineEdit(ui->lineEditCrossoverP->text(), QString("Crossover probability cannot be empty \n"));
    if(check) return;
    check = checklineEditRangeDouble(ui->lineEditCrossoverP->text(),1.0,0.0, QString("Crossover probability must be between 0 and 1. \n"));
    if(check) return;

    check = checklineEdit(ui->lineEditPme->text(), QString("Pme cannot be empty \n"));
    if(check) return;
    check = checklineEditRangeInt(ui->lineEditPme->text(), 100, 0, QString("Pme cannot be empty \n"));
    if(check) return;

    check = checklineEdit(ui->lineEditPmb->text(), QString("Pmb cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditTbMin->text(), QString("Tbmin cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditTbMax->text(), QString("Tbmax cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditdHpMax->text(), QString("dHpMax cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditdHpMin->text(), QString("dHpMin cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditMaxNumIte->text(), QString("Max number of iteration cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditNumProc->text(), QString("Number of processors cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditSeed->text(), QString("Seed cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditFrequKerSav->text(), QString("Frequency of kernel saving cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditNumBestKernelSaved->text(), QString("Number of best kernels to saved cannot be empty \n"));
    if(check) return;
    if(ui->comboBoxSelection->currentIndex()==2){
        check = checklineEdit(ui->lineEditNumberOfLines->text(), QString("Number of lines cannot be empty \n"));
        if(check) return;
    }

    check = checkValueSelectionParameter();
    if(check){
        return;
    }

    string rainMinDate, rainMaxDate;
    int result = csv->loadCSVRain(rainPath,rain,rain_size, rowError, e,rainMinDate, rainMaxDate);
    if(result == 0)
    {
        //emit showAlertInputCsv(rowError,rainPath, e);
        QString error = QString(e);

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }

    result = csv->loadCSVActivation(actPath,activation,activation_size, rowError, e,rainMinDate, rainMaxDate);
    if(result== 0)
    {
        //emit showAlertInputCsv(rowError,rainPath, e);
        QString error = QString(e);

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }




    vector<QString> ordersSelectionCriterion;
    ordersSelectionCriterion.push_back(ui->order1->text());
    ordersSelectionCriterion.push_back(ui->selectOrder1->currentText());
    ordersSelectionCriterion.push_back(ui->selectOrder2->currentText());
    ordersSelectionCriterion.push_back(ui->selectOrder3->currentText());
    int x = QString::compare(ui->comboBoxReplacement->currentText(), "generational", Qt::CaseInsensitive);
    if(x !=0){
        x=1;
    }
    //check input
    SAKeController * controller = new SAKeController(mainWindow,
                                                     ui->comboBoxSelection->currentText(),
                                                     ui->comboBoxReplacement->currentText(),
                                                     ui->comboBoxInitialPattern->currentText(),
                                                     rain,
                                                     rain_size,
                                                     activation,
                                                     activation_size,
                                                     ui->lineEditPopSize->text().toInt(),
                                                     ui->lineEditMaxNumIte->text().toInt(),//imaxGen,
                                                     ui->lineEditTbMax->text().toDouble(),//itbMax,
                                                     ui->lineEditTbMin->text().toDouble(),//itbMin,
                                                     ui->lineEditdHpMax->text().toDouble(),//idHpMax,
                                                     ui->lineEditdHpMin->text().toDouble(),//idHpMin,
                                                     ui->lineEditCrossoverP->text().toDouble(),//fpropCrossover,
                                                     ui->lineEditMutationP->text().toDouble(),//fpropMutation,
                                                     ui->lineEditPme->text().toDouble(),//fpme,
                                                     ui->lineEditPmb->text().toDouble(),//fpmb,
                                                     ui->lineEditNumProc->text().toInt(),//inumberProcessor,
                                                     ui->lineEditPar1->text().toDouble(),//ipara1,
                                                     ui->lineEditPar2->text().toDouble(),//ipara2,
                                                     ui->checkBoxContinueFromLastGen->isChecked(),//bLastGeneration,
                                                     ui->lineEditProjName->text(),//sprojectname,
                                                     ordersSelectionCriterion,//ordersSelectionCriterion
                                                     x,//itypeAlgorithm,
                                                     ui->lineEditNumberElitists->text().toInt(),//numberElitist.toInt(),
                                                     ui->lineEditSeed->text().toInt(),//seed.toInt(),
                                                     ui->lineEditFrequKerSav->text().toInt(),//saveKernels.toInt());
                                                     ui->lineEditNumBestKernelSaved->text().toInt(),
                                                     ui->lineEditNumberOfLines->text().toInt());//lineEditNumBestKernelSaved.toInt());

    controller->setFt(ui->comboBoxFitness->currentIndex());

    if(ui->lineEditProjName->isReadOnly() )
    {
        mainWindow->getXmlmanager()->SaveXMLFileAlreadyExistCalibrationProject(ui->lineEditProjName->text(),
                                                                               ui->comboBoxSelection->currentText(),
                                                                               ui->lineEditPar1->text(),//ipara1,
                                                                               ui->lineEditPar2->text(),//ipara2,
                                                                               ui->lineEditNumProc->text(),
                                                                               ui->lineEditPopSize->text(),//pop.toString(),
                                                                               ui->lineEditMaxNumIte->text(),//imaxGen,
                                                                               ui->lineEditTbMax->text(),//itbMax,
                                                                               ui->lineEditTbMin->text(),//itbMin,
                                                                               ui->lineEditdHpMax->text(),//idHpMax,
                                                                               ui->lineEditdHpMin->text(),//idHpMin,
                                                                               QString("%1").arg(1),
                                                                               ui->lineEditCrossoverP->text(),//fpropCrossover,
                                                                               ui->lineEditMutationP->text(),//fpropMutation,
                                                                               ui->lineEditPme->text(),//fpme,
                                                                               ui->lineEditPmb->text(),//fpmb,
                                                                               ui->comboBoxInitialPattern->currentText(),
                                                                               rainPath,
                                                                               actPath,
                                                                               QString("%1").arg(x),
                                                                               ui->lineEditNumberElitists->text(),
                                                                               ui->lineEditSeed->text(),
                                                                               ui->lineEditFrequKerSav->text(),
                                                                               ui->lineEditNumBestKernelSaved->text(),
                                                                               ordersSelectionCriterion,
                                                                               QString("%1").arg(ui->comboBoxFitness->currentIndex()),
                                                                               ui->lineEditNumberOfLines->text());
    }else{
        mainWindow->getXmlmanager()->SaveXMLFileCalibrationProject(ui->lineEditProjName->text(),
                                                                   ui->comboBoxSelection->currentText(),
                                                                   ui->lineEditPar1->text(),//ipara1,
                                                                   ui->lineEditPar2->text(),//ipara2,
                                                                   ui->lineEditNumProc->text(),
                                                                   ui->lineEditPopSize->text(),//pop.toString(),
                                                                   ui->lineEditMaxNumIte->text(),//imaxGen,
                                                                   ui->lineEditTbMax->text(),//itbMax,
                                                                   ui->lineEditTbMin->text(),//itbMin,
                                                                   ui->lineEditdHpMax->text(),//idHpMax,
                                                                   ui->lineEditdHpMin->text(),//idHpMin,
                                                                   QString("%1").arg(1),
                                                                   ui->lineEditCrossoverP->text(),//fpropCrossover,
                                                                   ui->lineEditMutationP->text(),//fpropMutation,
                                                                   ui->lineEditPme->text(),//fpme,
                                                                   ui->lineEditPmb->text(),//fpmb,
                                                                   ui->comboBoxInitialPattern->currentText(),
                                                                   rainPath,
                                                                   actPath,
                                                                   QString("%1").arg(x),
                                                                   ui->lineEditNumberElitists->text(),
                                                                   ui->lineEditSeed->text(),
                                                                   ui->lineEditFrequKerSav->text(),
                                                                   ui->lineEditNumBestKernelSaved->text(),
                                                                   ordersSelectionCriterion,
                                                                   QString("%1").arg(ui->comboBoxFitness->currentIndex()),
                                                                   ui->lineEditNumberOfLines->text());
    }



    //thread.insert();
    connect(controller, SIGNAL(finished(int)), mainWindow, SLOT(closeTab(int)));
    qRegisterMetaType<tm>("tm");
    qRegisterMetaType<std::vector<Ym>>("std::vector<Ym>");
    qRegisterMetaType<std::vector<QCPItemLine*>>("std::vector<QCPItemLine*>");
    qRegisterMetaType<std::vector<QCPItemText*>>("std::vector<QCPItemText*>");
    qRegisterMetaType<std::vector<double>>("std::vector<double>");
    qRegisterMetaType<QVector<double>>("QVector<double>");
    connect(controller, SIGNAL(updateMobPlot(int,Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
                                             std::vector<QCPItemLine*> )), mainWindow, SLOT(updateMobPlot(int,Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
                                                                                                          std::vector<QCPItemLine*> )));


    connect(controller, SIGNAL(updateFitnessPlot(int ,
                                                 QVector<double> ,
                                                 QVector<double> ,
                                                 QVector<double> ,
                                                 QVector<double> ,int, bool)), mainWindow, SLOT(updateFitnessPlot(int ,
                                                                                                                  QVector<double> ,
                                                                                                                  QVector<double> ,
                                                                                                                  QVector<double> ,
                                                                                                                  QVector<double> ,int ,bool)));


    connect(controller, SIGNAL(updateKernelPlot(int ,
                                                QVector<double> ,
                                                int  )), mainWindow, SLOT(updateKernelPlot(int ,
                                                                                           QVector<double> ,
                                                                                           int  )));

    connect(controller, SIGNAL(updateTexts(int ,
                                           QString,
                                           QString,
                                           QString ,
                                           QString ,
                                           QString ,
                                           QString ,
                                           QString ,
                                           QString ,
                                           int ,
                                           int,
                                           QString ,
                                           QString ,
                                           QString ,
                                           QString ,
                                           QString ,
                                           QString ,
                                           QString )), mainWindow, SLOT(updateTexts(int ,
                                                                                    QString,
                                                                                    QString,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    int,
                                                                                    int,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    QString ,
                                                                                    QString )));

    connect(controller, SIGNAL( updateTextsBestAbsolute(int ,
                                                        QString ,
                                                        QString ,
                                                        QString ,
                                                        QString ,
                                                        QString )), mainWindow, SLOT(updateTextsBestAbsolute(int ,
                                                                                                              QString ,
                                                                                                              QString ,
                                                                                                              QString ,
                                                                                                              QString ,
                                                                                                              QString )));
    connect(controller, SIGNAL(updateAbsMaxFit(int , QString )), mainWindow, SLOT(updateAbsMaxFit(int , QString )));

    connect(controller, SIGNAL(updateAbsAvFit(int , QString )), mainWindow, SLOT(updateAbsAvFit(int , QString )));

    connect(controller, SIGNAL(updateROCPlot(int ,
                                             QVector<double> ,
                                             QVector<double> ,
                                             double )), mainWindow, SLOT(updateROCPlot(int ,
                                                                                       QVector<double> ,
                                                                                       QVector<double> ,
                                                                                       double )));

    qRegisterMetaType<QVector<int>>("QVector<int>");

    connect(controller, SIGNAL(updateTableROCPlot(int ,
                                                            QVector<int> ,
                                                            QVector<int> ,
                                                            QVector<int> ,
                                                            QVector<int> )), mainWindow, SLOT( updateTableROCPlot(int ,
                                                                                                  QVector<int> ,
                                                                                                  QVector<int> ,
                                                                                                  QVector<int> ,
                                                                                                  QVector<int> )));

    mainWindow->mutex.lock();
    MainWindow::pushBackThread(controller);
    ptrdiff_t pos = distance(MainWindow::threads.begin(), std::find(MainWindow::threads.begin(), MainWindow::threads.end(), controller));


    //Fitness
    if(ui->comboBoxFitness->currentIndex() == FitnessAUCROC)
        mainWindow->addTabAUCROC(QString("Calibration AUC ROC - "+ui->lineEditProjName->text()),rain, rain_size, activation, activation_size,"AUC ROC");
    else
        if(ui->comboBoxFitness->currentIndex() == FitnessGMD)
            mainWindow->addTab(QString("Calibration GMD - "+ui->lineEditProjName->text()),rain, rain_size, activation, activation_size,"GMD");
        else
            if(ui->comboBoxFitness->currentIndex() == FitnessGMDn)
                mainWindow->addTab(QString("Calibration HW - "+ui->lineEditProjName->text()),rain, rain_size, activation, activation_size,"HW");
            else
                if(ui->comboBoxFitness->currentIndex() == FitnessEqualWeights)
                    mainWindow->addTab(QString("Calibration EW - "+ui->lineEditProjName->text()),rain, rain_size, activation, activation_size,"EW");



    QCustomPlot * m_CustomPlot = (QCustomPlot *) mainWindow->getPlotMobility(pos,"");
    for(int i = 0; i < activation_size;i++){
        QCPItemText *textLabel = new QCPItemText(m_CustomPlot);
        //m_CustomPlot->addItem(textLabel);
        textLabel->setPositionAlignment(Qt::AlignTop);
        //textLabel->position->setType(QCPItemPosition::ptPlotCoords);
        //textLabel->position->setCoords(15, 18); // place position at center/top of axis rect
        textLabel->setText("");
        //textLabel->setFont(QFont(font().family(), 16)); // make font a bit larger
        textLabel->setPen(QPen(Qt::black)); // show black border around text
        controller->widgetArray.push_back(textLabel);

        QCPItemLine *arrow = new QCPItemLine(m_CustomPlot);
        //m_CustomPlot->addItem(arrow);
        arrow->start->setParentAnchor(textLabel->bottom);
        arrow->end->setType(QCPItemPosition::ptPlotCoords);
        //arrow->end->setCoords(0.23, 1.6); // point to (4, 1.6) in x-y-plot coordinates
        arrow->setHead(QCPLineEnding::esSpikeArrow);
        controller->arrowArray.push_back(arrow);
    }
    mainWindow->mutex.unlock();

    controller->startThread();
    this->close();
}

Ui::Dialog *Dialog::getUi() const
{
    return ui;
}

void Dialog::on_comboBoxSelection_currentIndexChanged(int index)
{
    //ranking

    if(index ==0){
        //StockTour
        ui->label_14->show();
        QDoubleValidator* val = new QDoubleValidator(0.55, 1.00, 2, ui->lineEditPar1);
        val->setNotation(QDoubleValidator::StandardNotation);
        val->setLocale(QLocale::C);
        ui->lineEditPar1->setText("0.55");
        ui->lineEditPar1->setValidator(val);
        ui->lineEditPar1->show();

        ui->label_14->setText("Tr (tournament rate 0.55 <= Tr <= 1)");
        ui->label_15->hide();
        ui->lineEditPar2->hide();
    }else
        if(index == 1){
            //DetTour
            ui->label_14->show();
            ui->lineEditPar1->show();
            ui->lineEditPar1->setText("2");
            QIntValidator* val = new QIntValidator(2, ui->lineEditPopSize->text().toInt(), ui->lineEditPar1);
            val->setLocale(QLocale::C);
            ui->lineEditPar1->setValidator(val);
            ui->label_14->setText(" Ts (tournament size 2 <= Ts <=N))");
            ui->label_15->hide();
            ui->lineEditPar2->hide();
        }else
            if(index == 2)
            {
                ui->label_14->show();
                ui->label_14->setText("selective pressure 0 < s < 1   (exponential) \n \
                                      1 <= s <= 2 (linear)");
                                      ui->lineEditPar1->setText("2");
                        //ui->lineEditPar1->setValidator(new QDoubleValidator(0, 2,2, this));
                        QDoubleValidator* val = new QDoubleValidator(0.000, 2.000, 2, ui->lineEditPar1);
                val->setNotation(QDoubleValidator::StandardNotation);
                val->setLocale(QLocale::C);
                ui->lineEditPar1->setValidator(val);
                ui->lineEditPar1->setText("2");
                ui->lineEditPar1->show();
                //ui->label_15->show();
                //ui->label_15->setText("e (exponent 1=linear)");
                //ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
                //ui->lineEditPar2->setText("1");
                //ui->lineEditPar2->show();


                //                ui->label_14->setText("p (selective pressure 1 < p <= 2)");
                //                ui->lineEditPar1->setText("2");
                //                //ui->lineEditPar1->setValidator(new QDoubleValidator(1, 2,2, this));
                //                //ui->label_15->show();
                //                //ui->label_15->setText("e (exponent 1=linear)");
                //                //ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
                //                //ui->lineEditPar2->setText("1");
                //                //ui->lineEditPar2->show();
                //                ui->lineEditPar1->show();
                ui->label_15->hide();
                ui->lineEditPar2->hide();
            }else
                if(index == 3)
                {
                    ui->label_14->hide();
                    ui->lineEditPar1->hide();
                    ui->label_15->hide();
                    ui->lineEditPar2->hide();
                }else
                    if(index == 4)// Ranking (p,e)
                    {
                        ui->label_14->show();
                        ui->label_14->setText("p (selective pressure 1 < p <= 2)");
                        ui->lineEditPar1->setText("2");
                        //ui->lineEditPar1->setValidator(new QDoubleValidator(1, 2,2, this));
                        ui->label_15->show();
                        ui->label_15->setText("e (exponent 1=linear)");
                        //ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
                        ui->lineEditPar2->setText("1");
                        QDoubleValidator* val = new QDoubleValidator(1.000, 2.000, 2, ui->lineEditPar1);
                        val->setNotation(QDoubleValidator::StandardNotation);
                        val->setLocale(QLocale::C);
                        ui->lineEditPar1->setValidator(val);
                        ui->lineEditPar2->show();
                        ui->lineEditPar1->show();
                    }

    //Tr (tournament rate 0.55 <= Tr <= 1)
}

void Dialog::on_comboBoxReplacement_currentIndexChanged(int index)
{
    //generational
    if(index == 0){
        ui->labelnumberElitists->hide();
        ui->lineEditNumberElitists->hide();
    }
    else
        if(index == 1)
        {
            //elists
            ui->labelnumberElitists->show();
            ui->lineEditNumberElitists->show();
        }
}

MainWindow *Dialog::getMainWindow() const
{
    return mainWindow;
}

void Dialog::setMainWindow(MainWindow *value)
{
    mainWindow = value;

}

QTabWidget *Dialog::getTab() const
{
    return tab;
}

void Dialog::setTab(QTabWidget *value)
{
    tab = value;
}

QString Dialog::getProjectName()
{
    ui->lineEditProjName->text();
}

void Dialog::on_lineEditPopSize_textChanged(const QString &arg1)
{
    ui->lineEditNumberElitists->setValidator(new QIntValidator(1, ui->lineEditPopSize->text().toInt(), this));
    QString tmp = ui->lineEditPopSize->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditPopSize->setText(tmp);
    if(ui->lineEditNumberElitists->text().toInt() > ui->lineEditPopSize->text().toInt())
    {
        ui->lineEditNumberElitists->setText(QString::number(ui->lineEditPopSize->text().toInt()));
    }
    if(ui->comboBoxSelection->currentIndex()==1)
    {
        QIntValidator* val = new QIntValidator(2, ui->lineEditPopSize->text().toInt(), ui->lineEditPar1);
        val->setLocale(QLocale::C);
        ui->lineEditPar1->setValidator(val);
    }
}

void Dialog::on_comboBoxFitness_currentIndexChanged(int index)
{

    if(index == FitnessGMD || index == FitnessGMDn || index == FitnessEqualWeights){
        ui->labelNumberOfLines->hide();
        ui->lineEditNumberOfLines->hide();
    }
    else
        if(index == FitnessAUCROC)
        {
            ui->labelNumberOfLines->show();
            ui->lineEditNumberOfLines->show();
        }
}

void Dialog::setFieldEnabled(bool b){
    ui->lineEditRain->setEnabled(b);
    ui->lineEditActivation->setEnabled(b);
    ui->lineEditActivation->setEnabled(b);
    ui->pushButton->setEnabled(b);
    ui->pushButton_2->setEnabled(b);
    ui->lineEditPopSize->setEnabled(b);
    ui->comboBoxInitialPattern->setEnabled(b);
    ui->comboBoxReplacement->setEnabled(b);
    ui->lineEditNumberElitists->setEnabled(b);
    ui->comboBoxSelection->setEnabled(b);
    ui->lineEditPar1->setEnabled(b);
    ui->lineEditPar2->setEnabled(b);
    ui->lineEditCrossoverP->setEnabled(b);
    ui->lineEditMutationP->setEnabled(b);
    ui->lineEditPmb->setEnabled(b);
    ui->lineEditPme->setEnabled(b);
    ui->lineEditTbMin->setEnabled(b);
    ui->lineEditdHpMax->setEnabled(b);
    ui->lineEditTbMax->setEnabled(b);
    ui->comboBoxFitness->setEnabled(b);
    ui->lineEditNumberOfLines->setEnabled(b);
    ui->lineEditSeed->setEnabled(b);

}

void Dialog::setEnabledtoFalseCheckContinue()
{
    ui->checkBoxContinueFromLastGen->setEnabled(false);
    ui->label_25->setEnabled(false);
}


void Dialog::on_checkBoxContinueFromLastGen_clicked()
{
    if(ui->checkBoxContinueFromLastGen->isChecked())
    {
        QVariantList listParameter = mainWindow->getXmlmanager()->getAllElementsFromProjectName(idProject);
        setParameters(listParameter);
        setFieldEnabled(false);
    }else
    {
        setFieldEnabled(true);
    }
}

QString Dialog::getIdProject() const
{
    return idProject;
}

void Dialog::setIdProject(const QString &value)
{
    idProject = value;
}

void Dialog::on_lineEditNumberElitists_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditNumberElitists->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditNumberElitists->setText(tmp);
}

void Dialog::on_lineEditPmb_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditPmb->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditPmb->setText(tmp);
}

void Dialog::on_lineEditPme_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditPme->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditPme->setText(tmp);
}

void Dialog::on_lineEditTbMin_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditTbMin->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditTbMin->setText(tmp);
}

void Dialog::on_lineEditTbMax_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditTbMax->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditTbMax->setText(tmp);
    ui->lineEditTbMin->setValidator(new QIntValidator(0, ui->lineEditTbMax->text().toInt(), this));
    if(ui->lineEditTbMin->text().toInt() > ui->lineEditTbMax->text().toInt())
    {
        ui->lineEditTbMin->setText(QString::number(ui->lineEditTbMax->text().toInt()-1));
    }
}

void Dialog::on_lineEditdHpMax_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditdHpMax->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditdHpMax->setText(tmp);

}

void Dialog::on_lineEditNumberOfLines_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditNumberOfLines->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditNumberOfLines->setText(tmp);
}

void Dialog::on_lineEditMaxNumIte_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditMaxNumIte->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditMaxNumIte->setText(tmp);
    ui->lineEditFrequKerSav->setValidator(new QIntValidator(0, ui->lineEditMaxNumIte->text().toInt(), this));
    if(ui->lineEditFrequKerSav->text().toInt() > ui->lineEditMaxNumIte->text().toInt())
    {
        ui->lineEditFrequKerSav->setText(QString::number(ui->lineEditMaxNumIte->text().toInt()));
    }
}

void Dialog::on_lineEditNumProc_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditNumProc->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditNumProc->setText(tmp);
}

void Dialog::on_lineEditFrequKerSav_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditFrequKerSav->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditFrequKerSav->setText(tmp);
}

void Dialog::on_lineEditSeed_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditSeed->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditSeed->setText(tmp);
}

void Dialog::on_lineEditNumBestKernelSaved_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditNumBestKernelSaved->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditNumBestKernelSaved->setText(tmp);
}

void Dialog::on_lineEditCrossoverP_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditCrossoverP->text();
    QString tmp3 =  tmp.remove(',');
    tmp3 =  tmp.remove('e');
    ui->lineEditCrossoverP->setText(tmp3);
    if(tmp.toDouble() > 1)
    {
        ui->lineEditCrossoverP->setText("");
    }
    if(tmp.contains('.') || tmp.contains(',')){
        QString tmp1 = tmp.mid(0,2);
        QString tmp2 = tmp.mid(2);
//        cout << "QString tmp " << tmp.toStdString() << endl;
//        cout << "QString tmp1 " << tmp1.toStdString()  << endl;
//        cout << "QString tmp2 " << tmp2.toStdString()  << endl;
        tmp2.remove('.');tmp2.remove(',');
        ui->lineEditCrossoverP->setText(tmp1+tmp2);
    }
}

void Dialog::on_lineEditMutationP_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditMutationP->text();
    QString tmp3 =  tmp.remove(',');
    tmp3 =  tmp.remove('e');
    ui->lineEditMutationP->setText(tmp3);
    if(tmp.toDouble() > 1)
    {
        ui->lineEditMutationP->setText("1");
    }
    if(tmp.contains('.') || tmp.contains(',')){
        QString tmp1 = tmp.mid(0,2);
        QString tmp2 = tmp.mid(2);
//        cout << "QString tmp " << tmp.toStdString() << endl;
//        cout << "QString tmp1 " << tmp1.toStdString()  << endl;
//        cout << "QString tmp2 " << tmp2.toStdString()  << endl;
        tmp2.remove('.');tmp2.remove(',');
        ui->lineEditMutationP->setText(tmp1+tmp2);
    }
}

void Dialog::on_lineEditPar1_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditPar1->text();
//    cout << "tmp      --------------- >    " << tmp.toStdString() << endl;

    if(ui->comboBoxSelection->currentIndex() ==0 ){  // 0.55 - 1 Tr
        QString tmp3 =  tmp.remove(',');
        tmp3 =  tmp.remove('e');
        ui->lineEditPar1->setText(tmp3);
//        if(tmp.toDouble() > 1)
//        {
//           // ui->lineEditPar1->setText("");
//        }
        if(tmp.contains('.') && (tmp != "2." || tmp != "1.") ){
            QString tmp1 = tmp.mid(0,2);
            QString tmp2 = tmp.mid(2);
            tmp2.remove('.');tmp2.remove(',');
            ui->lineEditPar1->setText(tmp1+tmp2);
        }
    }else
        if(ui->comboBoxSelection->currentIndex() ==1 ){ // Det 2<= Ts <=N
            QString tmp3 =  tmp.remove(',');
            tmp3 =  tmp.remove('e');
            ui->lineEditPar1->setText(tmp3);
            if(tmp.toDouble() > ui->lineEditPopSize->text().toInt())
            {
                ui->lineEditPar1->setText("");
            }
            if(tmp.contains('.')){
                QString tmp1 = tmp.mid(0,2);
                QString tmp2 = tmp.mid(2);
                tmp2.remove('.');tmp2.remove(',');
                ui->lineEditPar1->setText(tmp1+tmp2);
            }
        }
        else
            if(ui->comboBoxSelection->currentIndex() ==2 ){// 0 < s <= 2
                QString tmp3 =  tmp.remove(',');
                tmp3 =  tmp.remove('e');
                ui->lineEditPar1->setText(tmp3);
                if(tmp.toDouble() > 2)
                {
                    ui->lineEditPar1->setText("");
                }
                if(tmp.contains('.')){
                    QString tmp1 = tmp.mid(0,2);
                    QString tmp2 = tmp.mid(2);
                    tmp2.remove('.');tmp2.remove(',');
                    ui->lineEditPar1->setText(tmp1+tmp2);
                }
            }else{
                if(ui->comboBoxSelection->currentIndex() ==4 ){// 1 < p <= 2
                    QString tmp3 =  tmp.remove(',');
                    tmp3 =  tmp.remove('e');
                    ui->lineEditPar1->setText(tmp3);
                    if(tmp.toDouble() > 2)
                    {
                        ui->lineEditPar1->setText("");
                    }
                    if(tmp.contains('.')){
                        QString tmp1 = tmp.mid(0,2);
                        QString tmp2 = tmp.mid(2);
                        tmp2.remove('.');tmp2.remove(',');
                        ui->lineEditPar1->setText(tmp1+tmp2);
                    }
                }
            }
}

bool Dialog::checkValueSelectionParameter(){

    QString tmp = ui->lineEditPar1->text();
    if(ui->comboBoxSelection->currentIndex() ==0 ){  // 0.55<= - <=1 Tr


        if(tmp.toDouble() < 0.55)
        {
            ui->lineEditPar1->setText("0.55");
            QString error = QString("The Tr value must be greater than 0.55. \n");

            QMessageBox::information(
                        this,
                        tr(QString("Warning").toStdString().c_str()),
                        tr(error.toStdString().c_str()) );
            return true;
        }


    }else
        if(ui->comboBoxSelection->currentIndex() == 1 ){ // Det 2<= - <=N
            if(tmp.toDouble() < 2)// || tmp.toDouble() > ui->lineEditPopSize->text().toInt())
            {
                ui->lineEditPar1->setText("2");
                QString error = QString("The Ts value must be greater than 2. \n");

                QMessageBox::information(
                            this,
                            tr(QString("Warning").toStdString().c_str()),
                            tr(error.toStdString().c_str()) );
                return true;
            }

        }
        else
            if(ui->comboBoxSelection->currentIndex() ==2 ){// 0 < s < 1
                if(tmp.toDouble() <= 0)// || tmp.toDouble() >= 1)
                {
                    ui->lineEditPar1->setText("0.1");
                    QString error = QString("The s value must be between 0 and 1. \n");

                    QMessageBox::information(
                                this,
                                tr(QString("Warning").toStdString().c_str()),
                                tr(error.toStdString().c_str()) );
                    return true;
                }

            }else
                if(ui->comboBoxSelection->currentIndex() ==4 ) //  1 < p <= 2
                    if(tmp.toDouble() <= 1)// || tmp.toDouble() > 2)
                    {
                        ui->lineEditPar1->setText("1.01");
                        QString error = QString("The p value must be between 1 and 2. \n");

                        QMessageBox::information(
                                    this,
                                    tr(QString("Warning").toStdString().c_str()),
                                    tr(error.toStdString().c_str()) );
                        return true;
                    }

    return false;
}


void Dialog::on_lineEditRain_editingFinished()
{
}
