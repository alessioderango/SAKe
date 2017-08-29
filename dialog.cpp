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

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setParameters(QVariantList list)
{
    ui->lineEditProjName->setText(list[0].toString());
    if(list[1]=="StochTour(t)"){
        ui->comboBoxSelection->setCurrentIndex(0);
        ui->lineEditPar1->setText(list[2].toString());
    }else
        if(list[1]=="DetTour(T)"){
            ui->comboBoxSelection->setCurrentIndex(1);
            ui->lineEditPar1->setText(list[2].toString());
        }else
            if(list[1]=="Ranking(p,e)"){
                ui->comboBoxSelection->setCurrentIndex(2);
                ui->lineEditPar1->setText(list[2].toString());
                ui->lineEditPar2->setText(list[3].toString());
            }else
                if(list[1]=="Roulette"){
                    ui->comboBoxSelection->setCurrentIndex(3);
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
}

void Dialog::setReadOnlyProjName(bool a)
{
    ui->lineEditProjName->setReadOnly(a);
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


void Dialog::on_pushButtonStart_clicked()
{
    HandlerCSV * csv = new HandlerCSV();
    QString rainPath = ui->lineEditRain->text();
    Rain * rain;
    int rain_size=0;
    int rowError=0;
    QString e;

    if(!SAKeController::fileExists(rainPath)){
        //emit showAlertFileNotExist(rainPath);
        QString error = QString("File does not exist "+ rainPath+"\n");

        QMessageBox::information(
                    this,
                    tr(QString("File does not exist").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }


    int result = csv->loadCSVRain(rainPath,rain,rain_size, rowError, e);
    if(result == 0)
    {
        emit showAlertInputCsv(rowError,rainPath, e);
        return;
    }
    QString actPath = ui->lineEditActivation->text();
    Activation * activation;
    int activation_size=0;
    if(!SAKeController::fileExists(actPath)){
        QString error = QString("File does not exist "+ rainPath+"\n");

        QMessageBox::information(
                    this,
                    tr(QString("File does not exist").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }
    result = csv->loadCSVActivation(actPath,activation,activation_size, rowError, e);
    if(result== 0)
    {
        emit showAlertInputCsv(rowError,actPath, e);
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
                                                     ui->lineEditNumBestKernelSaved->text().toInt());//lineEditNumBestKernelSaved.toInt());
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
                                                              ui->lineEditFrequKerSav->text());
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
                                                  ui->lineEditFrequKerSav->text());
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
                                                 QVector<double> )), mainWindow, SLOT(updateFitnessPlot(int ,
                                                                                                        QVector<double> ,
                                                                                                        QVector<double> ,
                                                                                                        QVector<double> ,
                                                                                                        QVector<double> )));


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
                                           int ,
                                           int)), mainWindow, SLOT(updateTexts(int ,
                                                                               QString,
                                                                               QString,
                                                                               QString ,
                                                                               QString ,
                                                                               QString ,
                                                                               QString ,
                                                                               int,
                                                                               int)));
    connect(controller, SIGNAL(updateAbsMaxFit(int , QString )), mainWindow, SLOT(updateAbsMaxFit(int , QString )));

    connect(controller, SIGNAL(updateAbsAvFit(int , QString )), mainWindow, SLOT(updateAbsAvFit(int , QString )));

    mainWindow->mutex.lock();
    MainWindow::pushBackThread(controller);
    ptrdiff_t pos = distance(MainWindow::threads.begin(), std::find(MainWindow::threads.begin(), MainWindow::threads.end(), controller));

    mainWindow->addTab(QString("Calibration - "+ui->lineEditProjName->text()),rain, rain_size, activation, activation_size);
    QCustomPlot * m_CustomPlot = (QCustomPlot *) mainWindow->getPlotMobility(pos);
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
        ui->lineEditPar1->show();
        ui->label_14->setText("Tr (tournament rate 0.55 <= Tr <= 1)");
        ui->label_15->hide();
        ui->lineEditPar2->hide();
    }else
        if(index == 1){
            //DetTour
            ui->label_14->show();
            ui->lineEditPar1->show();
            ui->label_14->setText(" Ts (tournament size 2 <= Ts <=N))");
            ui->label_15->hide();
            ui->lineEditPar2->hide();
        }else
            if(index == 2)
            {
                ui->label_14->show();
                ui->label_14->setText("p (selective pressure 1 < p <= 2)");
                ui->label_15->show();
                ui->label_15->setText("e (exponent 1=linear)");
                ui->lineEditPar2->show();
                ui->lineEditPar1->show();
            }else
                if(index == 3)
                {
                    ui->label_14->hide();
                    ui->lineEditPar1->hide();
                    ui->label_15->hide();
                    ui->lineEditPar2->hide();
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
