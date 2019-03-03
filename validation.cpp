#include "validation.h"
#include "ui_validation.h"

Validation::Validation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Validation)
{
    ui->setupUi(this);
}

Validation::~Validation()
{
    delete ui;
}

void Validation::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr(""), "",
                                                    tr("All Files (*.csv)"));
    ui->lineEdit_rain->setText(fileName);
}

void Validation::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr(""), "",
                                                    tr("All Files (*.csv)"));
    ui->lineEdit_activation->setText(fileName);
}

void Validation::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr(""), "",
                                                    tr("All Files (*.csv)"));
    ui->lineEdit_kernel->setText(fileName);
}



void Validation::on_buttonBox_accepted()
{

}

void Validation::on_buttonBox_rejected()
{
    close();
}

MainWindow *Validation::getMainWindow() const
{
    return mainWindow;
}

void Validation::setMainWindow(MainWindow *value)
{
    mainWindow = value;
}

void Validation::setReadOnlyProjName(bool a)
{
    ui->lineEditProjName->setReadOnly(a);
}
void Validation::setParameters(QVariantList list)
{
    ui->lineEditProjName->setText(list[0].toString());
    ui->lineEdit_rain->setText(list[1].toString());
    ui->lineEdit_activation->setText(list[2].toString());
    ui->lineEdit_kernel->setText(list[3].toString());
    ui->lineEditNumberOfLines->setText(list[5].toString());
}

void Validation::accept()
{
    Rain * rain;
    int rain_size;
    Activation * activation;
    int activation_size;
    std::vector<double> Fi;
    int size_Fi;
    double zCr;
    int rowError=0;
    QString e;
    QString rainPath = ui->lineEdit_rain->text();
    QString actPath = ui->lineEdit_activation->text();

    if(ui->lineEditProjName->text().isEmpty())
    {
        QString error = QString("Projet name cannot be empty \n");

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }

    if(!ui->lineEditProjName->isReadOnly() && mainWindow->getXmlmanager()->findProjectName(ui->lineEditProjName->text()))
    {
        QString error = QString("Anotehr Project with the same name already exists \n");

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }

    if(!SAKeController::fileExists(rainPath)){
        QString error = QString("Rain File does not exist "+ rainPath+"\n");

        QMessageBox::information(
                    this,
                    tr(QString("File does not exist").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }

    if(!SAKeController::fileExists(actPath)){
        QString error = QString("Activation file does not exist "+ actPath+"\n");

        QMessageBox::information(
                    this,
                    tr(QString("File does not exist").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }

    if(!SAKeController::fileExists(ui->lineEdit_kernel->text())){
        QString error = QString("Kernel file does not exist "+ ui->lineEdit_kernel->text()+"\n");

        QMessageBox::information(
                    this,
                    tr(QString("File does not exist").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }

    connect(this, SIGNAL(showAlertInputCsv(int,QString,QString)), mainWindow, SLOT(showAlertInputCsv(int,QString,QString))) ;
    int errorRain = HandlerCSV::loadCSVRain(ui->lineEdit_rain->text(), rain, rain_size, rowError, e);
    if(errorRain==0){
        emit showAlertInputCsv(rowError,rainPath, e);
        return;
    }

    int errorActivation = HandlerCSV::loadCSVActivation(actPath, activation, activation_size, rowError, e);
    if(errorActivation ==0){
        emit showAlertInputCsv(rowError,actPath, e);
        return;
    }
    int errorKernel = HandlerCSV::loadCSVKernel(ui->lineEdit_kernel->text(), Fi, size_Fi,zCr);
    //            if(errorKernel){
    if(ui->lineEditProjName->isReadOnly() )
    {
        mainWindow->getXmlmanager()->SaveXMLFileAlreadyExistValidationProject(ui->lineEditProjName->text(),
                                                                              ui->lineEdit_rain->text(),
                                                                              ui->lineEdit_activation->text(),
                                                                              ui->lineEdit_kernel->text(),
                                                                              "",
                                                                              ui->lineEditNumberOfLines->text());
    }else{
        mainWindow->getXmlmanager()->SaveXMLFileValidationProject(ui->lineEditProjName->text(),
                                                                  ui->lineEdit_rain->text(),
                                                                  ui->lineEdit_activation->text(),
                                                                  ui->lineEdit_kernel->text(),
                                                                  "",
                                                                  ui->lineEditNumberOfLines->text());
    }

    ValidationController * validationController=new ValidationController(rain,
                                                                         rain_size,
                                                                         activation,
                                                                         activation_size,
                                                                         Fi,
                                                                         size_Fi,
                                                                         zCr
                                                                         );
        validationController->setNumberOfLines( ui->lineEditNumberOfLines->text().toInt());
//    if(ui->comboBoxFitness->currentIndex() == 0)
//        validationController->setFt(FitnessGMD);
//    else
//        if(ui->comboBoxFitness->currentIndex() == 1){
//            validationController->setFt(FitnessEqualWeights);
//        }else
//            if(ui->comboBoxFitness->currentIndex() ==2){
//                validationController->setFt(FitnessAUCROC);
//            }
    validationController->setMainwindows(mainWindow);
    qRegisterMetaType<tm>("tm");
    qRegisterMetaType<std::vector<Ym>>("std::vector<Ym>");
    qRegisterMetaType<std::vector<QCPItemLine*>>("std::vector<QCPItemLine*>");
    qRegisterMetaType<std::vector<QCPItemText*>>("std::vector<QCPItemText*>");
    qRegisterMetaType<std::vector<double>>("std::vector<double>");
    qRegisterMetaType<QVector<double>>("QVector<double>");
    connect(validationController, SIGNAL(updateMobPlot(int,Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
                                                       std::vector<QCPItemLine*> )), mainWindow, SLOT(updateMobPlot(int,Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
                                                                                                                    std::vector<QCPItemLine*> )));
    connect(validationController, SIGNAL(updateMobPlotAllInOne(int,QString, Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
                                                       std::vector<QCPItemLine*> )), mainWindow, SLOT(updateMobPlotAllInOne(int,QString,Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
                                                                                                                    std::vector<QCPItemLine*> )));



    connect(validationController, SIGNAL(updateFitnessPlot(int ,
                                                           QVector<double> ,
                                                           QVector<double> ,
                                                           QVector<double> ,
                                                           QVector<double> ,int,
                                                           bool )), mainWindow, SLOT(updateFitnessPlot(int ,
                                                                                                                  QVector<double> ,
                                                                                                                  QVector<double> ,
                                                                                                                  QVector<double> ,
                                                                                                                  QVector<double> ,int,
                                                                                                        bool )));


    connect(validationController, SIGNAL(updateKernelPlot(int ,
                                                          QVector<double> ,
                                                          int  )), mainWindow, SLOT(updateKernelPlot(int ,
                                                                                                     QVector<double> ,
                                                                                                     int  )));

    connect(validationController, SIGNAL(updateTextsValidation(int ,
                                                               QString,
                                                               QString,
                                                               QString ,
                                                               QString)), mainWindow, SLOT(updateTextsValidation(int ,
                                                                                                                 QString,
                                                                                                                 QString,
                                                                                                                 QString ,
                                                                                                                 QString)));

    connect(validationController, SIGNAL(updateTextsValidationAllInOne(int ,
                                                               QString,
                                                               QString,
                                                               QString,
                                                               QString ,
                                                               QString)), mainWindow, SLOT(updateTextsValidationAllInOne(int ,
                                                                                                                 QString,
                                                                                                                 QString,
                                                                                                                 QString,
                                                                                                                 QString ,
                                                                                                                 QString)));

    connect(validationController,
            SIGNAL(updateTextsValidationAllInOneFitness(int ,QString , QString )),
            mainWindow,
            SLOT(updateTextsValidationAllInOneFitness(int ,QString , QString )));


    connect(validationController, SIGNAL(updateROCPlot(int ,
                                             QVector<double> ,
                                             QVector<double> ,
                                             double )), mainWindow, SLOT(updateROCPlot(int ,
                                                                                       QVector<double> ,
                                                                                       QVector<double> ,
                                                                                       double )));
    validationController->setProjectName(ui->lineEditProjName->text());
    mainWindow->mutex.lock();
    MainWindow::pushBackThread(validationController);
    ptrdiff_t pos = distance(MainWindow::threads.begin(), std::find(MainWindow::threads.begin(), MainWindow::threads.end(), validationController));
    //    mainWindow->addTabValidation(QString("Validation - " + ui->lineEditProjName->text()),rain, rain_size, activation, activation_size);
    mainWindow->addTabValidationNewInterface(QString("Validation - " + ui->lineEditProjName->text()),rain, rain_size, activation, activation_size);


    int number_of_mobPlots = 1;
    for(int i = 0; i < number_of_mobPlots;i++){

        QCustomPlot * m_CustomPlot = getRightPlotFromIndex(i,pos);

        std::vector<QCPItemText *> vectorTmpWidgetArray;
        std::vector<QCPItemLine *> vectorTmpArrow;
        for(int i = 0; i < activation_size;i++){
            QCPItemText *textLabel = new QCPItemText(m_CustomPlot);
            //m_CustomPlot->addItem(textLabel);
            textLabel->setPositionAlignment(Qt::AlignTop);
            textLabel->setText("");
            textLabel->setPen(QPen(Qt::black)); // show black border around text
            vectorTmpWidgetArray.push_back(textLabel);

            QCPItemLine *arrow = new QCPItemLine(m_CustomPlot);
            arrow->start->setParentAnchor(textLabel->bottom);
            arrow->end->setType(QCPItemPosition::ptPlotCoords);
            arrow->setHead(QCPLineEnding::esSpikeArrow);
            vectorTmpArrow.push_back(arrow);
        }
        validationController->widgetArray.push_back(vectorTmpWidgetArray);
        validationController->arrowArray.push_back(vectorTmpArrow);
    }

    //.push_back(validationController);
    mainWindow->mutex.unlock();
    validationController->startThread();
    this->close();
}

int Validation::getRightPlotFromName(QString name)
{

    if(name == "mobFuncGMD")
        return 0;
    else
        if(name =="mobFuncGMDn")
            return 1;
        else
            if(name =="mobFuncEW")
                return 2;
            else
                if(name =="mobFuncAUCROC")
                    return 3;

}

QCustomPlot * Validation::getRightPlotFromIndex(int index, int pos){
    QString name;
    switch (index) {
    case 0:
        name = "AUCROC";//"GMD";
        break;
    case 1:
        name = "GMDn";
        break;
    case 2:
        name = "EW";
        break;
    case 3:
        name = "GMD";
        break;
    }

    return (QCustomPlot *) mainWindow->getPlotMobility(pos,name);

}


void Validation::on_buttonBox_clicked(QAbstractButton *button)
{

}
