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
    connect(this, SIGNAL(showAlertInputCsv(int,QString,QString)), mainWindow, SLOT(showAlertInputCsv(int,QString,QString))) ;
    int errorRain = HandlerCSV::loadCSVRain(ui->lineEdit_rain->text(), rain, rain_size, rowError, e);
        if(errorRain==0){
            emit showAlertInputCsv(rowError,rainPath, e);
            return;
        }
        QString actPath = ui->lineEdit_activation->text();
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
                                                                              ""
                                                                              );
    }else{
        mainWindow->getXmlmanager()->SaveXMLFileValidationProject(ui->lineEditProjName->text(),
                                                                  ui->lineEdit_rain->text(),
                                                                  ui->lineEdit_activation->text(),
                                                                  ui->lineEdit_kernel->text(),
                                                                  "");
    }

    ValidationController * validationController=new ValidationController(&(mainWindow->mutex),
                rain,
                rain_size,
                activation,
                activation_size,
                Fi,
                size_Fi,
                zCr
                );
    qRegisterMetaType<tm>("tm");
    qRegisterMetaType<std::vector<Ym>>("std::vector<Ym>");
    qRegisterMetaType<std::vector<QCPItemLine*>>("std::vector<QCPItemLine*>");
    qRegisterMetaType<std::vector<QCPItemText*>>("std::vector<QCPItemText*>");
    qRegisterMetaType<std::vector<double>>("std::vector<double>");
    qRegisterMetaType<QVector<double>>("QVector<double>");
    connect(validationController, SIGNAL(updateMobPlot(int,Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
                                                       std::vector<QCPItemLine*> )), mainWindow, SLOT(updateMobPlot(int,Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
                                                                                                                    std::vector<QCPItemLine*> )));


    connect(validationController, SIGNAL(updateFitnessPlot(int ,
                                                           QVector<double> ,
                                                           QVector<double> ,
                                                           QVector<double> ,
                                                           QVector<double> )), mainWindow, SLOT(updateFitnessPlot(int ,
                                                                                                                  QVector<double> ,
                                                                                                                  QVector<double> ,
                                                                                                                  QVector<double> ,
                                                                                                                  QVector<double> )));


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
    mainWindow->mutex.lock();
    MainWindow::pushBackThread(validationController);
    ptrdiff_t pos = distance(MainWindow::threads.begin(), std::find(MainWindow::threads.begin(), MainWindow::threads.end(), validationController));
    mainWindow->addTabValidation(QString("Validation - " + ui->lineEditProjName->text()),rain, rain_size, activation, activation_size);

    QCustomPlot * m_CustomPlot = (QCustomPlot *) mainWindow->getPlotMobility(pos);
    for(int i = 0; i < activation_size;i++){
        QCPItemText *textLabel = new QCPItemText(m_CustomPlot);
        //m_CustomPlot->addItem(textLabel);
        textLabel->setPositionAlignment(Qt::AlignTop);
        textLabel->setText("");
        textLabel->setPen(QPen(Qt::black)); // show black border around text
        validationController->widgetArray.push_back(textLabel);

        QCPItemLine *arrow = new QCPItemLine(m_CustomPlot);
        arrow->start->setParentAnchor(textLabel->bottom);
        arrow->end->setType(QCPItemPosition::ptPlotCoords);
        arrow->setHead(QCPLineEnding::esSpikeArrow);
        validationController->arrowArray.push_back(arrow);
    }

    //.push_back(validationController);
    mainWindow->mutex.unlock();
    validationController->startThread();
    this->close();
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
}
