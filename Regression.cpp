#include "Regression.h"
#include "ui_regression.h"

void addRow(QTableWidget * tw, int row,
            QString aMins,
            QString aMaxs,
            QString bMins,
            QString bMaxs,
            QString wMins,
            QString wMaxs,
            QString percAs,
            QString percBs,
            QString percWs){

    QString s= QString("%1").arg(row+1);
    tw->setItem(row, 0, new QTableWidgetItem(s));
    QLineEdit* aMin = new QLineEdit();
    aMin->setText(aMins);
    tw->setCellWidget(row, 1, aMin);
    QLineEdit* aMax = new QLineEdit();
    aMax->setText(aMaxs);
    //aMax->setSizePolicy(QSizePolicy::Preferred);
    tw->setCellWidget(row, 2, aMax);

    QLineEdit* bMin = new QLineEdit();
    bMin->setText(bMins);
    tw->setCellWidget(row, 3, bMin);
    QLineEdit* bMax = new QLineEdit();
    bMax->setText(bMaxs);
    tw->setCellWidget(row, 4, bMax);

    QLineEdit* wMin = new QLineEdit();
    wMin->setText(wMins);
    tw->setCellWidget(row, 5, wMin);
    QLineEdit* wMax = new QLineEdit();
    wMax->setText(wMaxs);
    tw->setCellWidget(row, 6, wMax);

    QLineEdit* percA = new QLineEdit();
    percA->setText(percAs);
    tw->setCellWidget(row, 7, percA);
    QLineEdit* percB = new QLineEdit();
    percB->setText(percBs);
    tw->setCellWidget(row, 8, percB);
    QLineEdit* percW = new QLineEdit();
    percW->setText(percWs);
    tw->setCellWidget(row, 9, percW);
    tw->resizeColumnsToContents();
}

Regression::Regression(MainWindow * _w,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Regression)
{
    ui->setupUi(this);
    w=_w;
    //ui->tableWidgetMin1->setRowCount(10);
    ui->tableWidgetMin1->setColumnCount(10);
    QStringList m_TableHeader;
    m_TableHeader<<"N."<<"a min"<<"a max"<< "B min" << "B max" << "W min"<< "W max" << "Perc a" << "Perc b" << "Perc w";
    ui->tableWidgetMin1->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidgetMin1->verticalHeader()->setVisible(false);
    ui->tableWidgetMin1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetMin1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetMin1->setSelectionMode(QAbstractItemView::SingleSelection);


       ui->tableWidgetMin1->setRowCount(1);
       addRow(ui->tableWidgetMin1,
              0,
              "0.2",
              "0.8",
              "5",
              "50",
              "0.02",
              "2",
              "0.03",
              "0.03",
              "0.03");
       //ui->tableWidget1->resizeColumnsToContents();

       //QTableWidget::horizontalHeader().setStretchLastSection(true);
       ui->tableWidgetMin1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->tableWidget1->setColumnCount(10);
    m_TableHeader<<"N."<<"a min"<<"a max"<< "B min" << "B max" << "Weight min"<< "Weight max" << "Perc a" << "Perc b" << "Perc weight";
    ui->tableWidget1->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget1->verticalHeader()->setVisible(false);
    ui->tableWidget1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget1->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget1->setShowGrid(false);
    //ui->tableWidget1->setStyleSheet("QTableView {selection-background-color: red;}");
    //ui->tableWidget1->setGeometry(QApplication::desktop()->screenGeometry());
    //ui->tableWidget1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->tableWidget1->setRowCount(3);
    addRow(ui->tableWidget1,
           0,
           "1",
           "8",
           "20",
           "200",
           "0.02",
           "2",
           "0.03",
           "0.03",
           "0.03");
    addRow(ui->tableWidget1,
           1,
           "20",
           "80",
           "2",
           "30",
           "0.02",
           "2",
           "0.03",
           "0.03",
           "0.03");
    addRow(ui->tableWidget1,
           2,
           "150",
           "350",
           "2",
           "7",
           "0.02",
           "2",
           "0.03",
           "0.03",
           "0.03");

    ui->tableWidget1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->tableWidgetLin->setColumnCount(10);
    m_TableHeader<<"N."<<"a min"<<"a max"<< "B min" << "B max" << "Weight min"<< "Weight max" << "Perc a" << "Perc b" << "Perc weight";
    ui->tableWidgetLin->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidgetLin->verticalHeader()->setVisible(false);
    ui->tableWidgetLin->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetLin->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetLin->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetLin->setRowCount(1);
    addRow(ui->tableWidgetLin,
           0,
           "-0.0005",
           "0.0005",
           "0.003",
           "0.1",
           "0.2",
           "2",
           "0.03",
           "0.03",
           "0.03");

    ui->tableWidgetLin->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    MainWindow::makeKernelPlot(ui->kernelPlot,w);
    //ui->kernelPlot->setSizePolicy(spUp);
    ui->kernelPlot->setObjectName("kerFunc");

    controlPoints = new ControlPoints();

    ui->label_14->hide();
    ui->lineEditNumberElitists->hide();
    ui->label_15->show();
    ui->lineEditPar1->setValidator(new QDoubleValidator(0.55, 1,2, this));
    ui->lineEditPar1->show();

    ui->label_15->setText("Tr (tournament rate 0.55 <= Tr <= 1)");
    ui->label_16->hide();
    ui->lineEditPar2->hide();

}

Regression::~Regression()
{
    delete ui;
}

void Regression::cellSelected(int nRow, int nCol)
{
 QMessageBox::information(this, "","Cell at row "+QString::number(nRow)+" column "+QString::number(nCol)+" was double clicked.");
}

MainWindow *Regression::getW() const
{
    return w;
}

void Regression::setW(MainWindow *value)
{
    w = value;
}

void Regression::on_lineEdit_8_textChanged(const QString &arg1)
{
    if(arg1.toInt() >=0 ){
        //delete
        if(ui->tableWidgetMin1->rowCount() > arg1.toInt() ){
            for (int row = ui->tableWidgetMin1->rowCount(); row >= arg1.toInt(); row--) {
                ui->tableWidgetMin1->removeRow(row);
            }

        }else{
            //add
            if(ui->tableWidgetMin1->rowCount() < arg1.toInt() ){
                for (int i = ui->tableWidgetMin1->rowCount()+1; i <= arg1.toInt(); ++i) {
                    ui->tableWidgetMin1->insertRow(i-1);
                    addRow(ui->tableWidgetMin1,
                           i-1,
                           "1",
                           "8",
                           "20",
                           "200",
                           "0.02",
                           "2",
                           "0.03",
                           "0.03",
                           "0.03");
//                    ui->tableWidgetMin1->insertRow(i-1);
//                    QString s= QString("%1").arg(i);
//                   ui->tableWidgetMin1->setItem(i-1, 0, new QTableWidgetItem(s));
//                   for (int j = 1; j < 10; ++j) {
//                     ui->tableWidgetMin1->setCellWidget(i-1, j, new QLineEdit);
//                   }
                }
            }
        }

    }
}

void Regression::on_lineEdit_10_textChanged(const QString &arg1)
{
    if(arg1.toInt() >= 0){
        //delete
        if(ui->tableWidget1->rowCount() > arg1.toInt() ){
            for (int row = ui->tableWidget1->rowCount(); row >= arg1.toInt(); row--) {
                ui->tableWidget1->removeRow(row);
            }

        }else{
            //add
            if(ui->tableWidget1->rowCount() < arg1.toInt() ){
                for (int i = ui->tableWidget1->rowCount()+1; i <= arg1.toInt(); ++i) {
                    ui->tableWidget1->insertRow(i-1);
                    addRow(ui->tableWidget1,
                           i-1,
                           "1",
                           "8",
                           "20",
                           "200",
                           "0.02",
                           "2",
                           "0.03",
                           "0.03",
                           "0.03");
                }
            }
        }

    }
}

void Regression::on_lineEdit_9_textChanged(const QString &arg1)
{
    if(arg1.toInt() >= 0){
        //delete
        if(ui->tableWidgetLin->rowCount() > arg1.toInt() ){
            for (int row = ui->tableWidgetLin->rowCount(); row >= arg1.toInt(); row--) {
                ui->tableWidgetLin->removeRow(row);
            }

        }else{
            //add
            if(ui->tableWidgetLin->rowCount() < arg1.toInt() ){
                for (int i = ui->tableWidgetLin->rowCount()+1; i <= arg1.toInt(); ++i) {
                    ui->tableWidgetLin->insertRow(i-1);
                    addRow(ui->tableWidgetLin,
                           i-1,
                           "1",
                           "8",
                           "20",
                           "200",
                           "0.02",
                           "2",
                           "0.03",
                           "0.03",
                           "0.03");
                }
            }
        }

    }
}

void Regression::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr(""), "",
                                                    tr("All Files (*.csv)"));
    ui->lineEditLoadKernel->setText(fileName);

    QString filename = ui->lineEditLoadKernel->text();


    HandlerCSV::loadCSVKernel(filename,this->kernel,this->size_kernel,this->Delta_cr);

    //MainWindow::updateKernelPlot();


        QVector<double> xKernel;
        QVector<double> yKernel;
        for (int i = 0; i < size_kernel; i++) {
            xKernel.push_back(i+1);
            yKernel.push_back(kernel[i]);
        }




    //updateGraph(kernel,size_kernel);


    controlPoints->calculateControlPoints(&(kernel[0]),size_kernel);
    xControlpoints = controlPoints->getX();
    yControlpoints = controlPoints->getY();

    QCustomPlot *m_CustomPlot = ui->kernelPlot;
    w->updateKernelPlotRegression(m_CustomPlot,xKernel,
                                               yKernel,
                                               QVector<double>::fromStdVector(xControlpoints),
                                               QVector<double>::fromStdVector(yControlpoints));

}

void Regression::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        ui->checkBox_2->setChecked(false);
        ui->checkBox_4->setChecked(false);
    }

}

void Regression::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        ui->checkBox_3->setChecked(false);
        ui->checkBox_4->setChecked(false);
    }

}

void Regression::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        ui->checkBox_3->setChecked(false);
        ui->checkBox_2->setChecked(false);
    }
}

void Regression::on_comboBox_currentIndexChanged(int index)
{
    //genrational
    if(index == 0){
        ui->label_14->hide();
        ui->lineEditNumberElitists->hide();
    }
    else
        if(index == 1)
        {
            //elists
            ui->label_14->show();
            ui->lineEditNumberElitists->show();
        }
}


void Regression::on_lineEdit_7_textChanged(const QString &n)
{
    if(!n.isEmpty()){

       std::vector< double> x;
       std::vector< double> y;
       int nInt =  n.toInt();

       if(ui->checkBox->isChecked()){
           controlPoints->getSubdividePointsFromControlPoints(xControlpoints, yControlpoints, nInt, x, y);
       }else{
           controlPoints->getSubdividePointsFromKernel(&(kernel[0]), size_kernel, nInt, x, y);
       }

       w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(x), QVector<double>::fromStdVector(y) );

    }



}

void Regression::on_checkBox_clicked()
{
    if(!ui->lineEditN->text().isEmpty()){

       std::vector< double> x;
       std::vector< double> y;
       int nInt =  ui->lineEditN->text().toInt();

       if(ui->checkBox->isChecked()){
           controlPoints->getSubdividePointsFromControlPoints(xControlpoints, yControlpoints, nInt, x, y);
       }else{
           controlPoints->getSubdividePointsFromKernel(&(kernel[0]), size_kernel, nInt, x, y);
       }

       w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(x), QVector<double>::fromStdVector(y) );

    }
}

void Regression::on_comboBox_2_currentIndexChanged(int index)
{
    if(index == 0){
        //StockTour
        ui->label_15->show();
        ui->lineEditPar1->setValidator(new QDoubleValidator(0.55, 1,2, this));
        ui->lineEditPar1->show();

        ui->label_15->setText("Tr (tournament rate 0.55 <= Tr <= 1)");
        ui->label_16->hide();
        ui->lineEditPar2->hide();
    }else
        if(index == 1){
            //DetTour
            ui->label_15->show();
            ui->lineEditPar1->show();
            ui->lineEditPar1->setText("2");
            ui->lineEditPar1->setValidator(new QIntValidator(2, ui->lineEditPopSize->text().toInt(), this));
            ui->label_15->setText(" Ts (tournament size 2 <= Ts <=N))");
            ui->label_16->hide();
            ui->lineEditPar2->hide();
        }else
            if(index == 2)
            {
                ui->label_15->show();
                ui->label_15->setText("p (selective pressure 1 < p <= 2)");
                ui->lineEditPar1->setText("2");
                //ui->lineEditPar1->setValidator(new QDoubleValidator(1, 2,2, this));
                ui->label_16->show();
                ui->label_16->setText("e (exponent 1=linear)");
                //ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
                ui->lineEditPar2->setText("1");
                ui->lineEditPar2->show();
                ui->lineEditPar2->show();
            }else
                if(index == 3)
                {
                    ui->label_15->hide();
                    ui->lineEditPar1->hide();
                    ui->label_16->hide();
                    ui->lineEditPar2->hide();
                }
}

void Regression::on_pushButton_2_clicked()
{
    this->close();
}


bool Regression::checklineEdit(QString l, QString s){
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

void Regression::on_pushButton_clicked()
{
    QString e;


    if(ui->lineEditProjName->text().isEmpty())
    {
        QString error = QString("Projet name cannot be empty \n");

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }

    bool check = checklineEdit(ui->lineEditPopSize->text(), QString("Population size cannot be empty \n"));
    if(check) return;


    // elitist
    if(ui->comboBoxReplacement->currentIndex() == 1){
        check = checklineEdit(ui->lineEditNumberElitists->text(), QString("number of elitists cannot be empty \n"));
        if(check) return;
    }

    if(ui->comboBoxSelection->currentIndex() ==0 ){
        check = checklineEdit(ui->lineEditPar1->text(), QString("Tr cannot be empty \n"));
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
                check = checklineEdit(ui->lineEditPar2->text(), QString("exponent cannot be empty \n"));
                if(check) return;
            }

    check = checklineEdit(ui->lineEditMutationP->text(), QString("Mutation probability cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditCrossoverP->text(), QString("Crossover probability cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditMaxNumIte->text(), QString("Max number of iteration cannot be empty \n"));
    if(check) return;
    check = checklineEdit(ui->lineEditNumProc->text(), QString("Number of processors cannot be empty \n"));
    if(check) return;
//    check = checklineEdit(ui->lineEditSeed->text(), QString("Seed cannot be empty \n"));
//    if(check) return;
//    check = checklineEdit(ui->lineEditFrequKerSav->text(), QString("Frequency of kernel saving cannot be empty \n"));
//    if(check) return;
//    check = checklineEdit(ui->lineEditNumBestKernelSaved->text(), QString("Number of best kernels to saved cannot be empty \n"));
//    if(check) return;

    std::vector<std::vector<double> > matrixGamma1;
    std::vector<double> tmp;
    //min a
    tmp.push_back(0.2);
    //max a
    tmp.push_back(0.8);
    //min b
    tmp.push_back(5);
    //max b
    tmp.push_back(50);
    //min w
    tmp.push_back(0.02);
    //max w
    tmp.push_back(2);
    //perc a
    tmp.push_back(0.03);
    //perc b
    tmp.push_back(0.03);
    //perc w
    tmp.push_back(0.03);

    matrixGamma1.push_back(tmp);

    std::vector<std::vector<double> > matrixGamma2;
    std::vector<double> tmp2;
    //min a
    tmp2.push_back(1);
    //max a
    tmp2.push_back(8);
    //min b
    tmp2.push_back(20);
    //max b
    tmp2.push_back(200);
    //min w
    tmp2.push_back(0.02);
    //max w
    tmp2.push_back(2);
    //perc a
    tmp2.push_back(0.03);
    //perc b
    tmp2.push_back(0.03);
    //perc w
    tmp2.push_back(0.03);
    matrixGamma2.push_back(tmp2);

    tmp2[0] = 20;
    tmp2[1] = 80;
    tmp2[2] = 2;
    tmp2[3] = 30;
    matrixGamma2.push_back(tmp2);

    tmp2[0] = 150;
    tmp2[1] = 300;
    tmp2[2] = 2;
    tmp2[3] = 7;
     matrixGamma2.push_back(tmp2);
    std::vector<std::vector<double> > matrixLinear;
     std::vector<double> tmp3;
     //min a
     tmp3.push_back(-0.0005);
     //max a
     tmp3.push_back(0.0005);
     //min b
     tmp3.push_back(0.003);
     //max b
     tmp3.push_back(0.1);
     //min w
     tmp3.push_back(0.2);
     //max w
     tmp3.push_back(2);
     //perc a
     tmp3.push_back(0.03);
     //perc b
     tmp3.push_back(0.03);
     //perc w
     tmp3.push_back(0.03);

     matrixLinear.push_back(tmp3);
//    RegressionController * controller = RegressionController(ui->lineEditProjName,
//                                                             );
     int x = QString::compare(ui->comboBoxReplacement->currentText(), "generational", Qt::CaseInsensitive);
     if(x !=0){
         x=1;
     }
     if(ui->lineEditProjName->isReadOnly())
     {
         w->getXmlmanager()->SaveXMLFileAlreadyExistRegressionProject(ui->lineEditProjName->text(),
                                                                      ui->comboBoxSelection->currentText(),
                                                                      ui->lineEditPar1->text(),//ipara1,
                                                                      ui->lineEditPar2->text(),//ipara2,
                                                                      ui->lineEditPopSize->text(),
                                                                      ui->lineEditCrossoverP->text(),//fpropCrossover,
                                                                      ui->lineEditMutationP->text(),//fpropMutation,
                                                                      ui->lineEditNumProc->text(),
                                                                      ui->lineEditMaxNumIte->text(),//imaxGen,
                                                                      ui->lineEditLoadKernel->text(),
                                                                      matrixGamma1,
                                                                      matrixGamma2,
                                                                      matrixLinear,
                                                                      ui->checkBox->text(),
                                                                      ui->lineEditN->text(),
                                                                      QString("%1").arg(1),
                                                                      ui->comboBoxReplacement->currentText(),
                                                                      ui->lineEditNumberElitists->text());


     }else{
         w->getXmlmanager()->SaveXMLFileRegressionProject(ui->lineEditProjName->text(),
                                                          ui->comboBoxSelection->currentText(),
                                                          ui->lineEditPar1->text(),//ipara1,
                                                          ui->lineEditPar2->text(),//ipara2,
                                                          ui->lineEditPopSize->text(),
                                                          ui->lineEditCrossoverP->text(),//fpropCrossover,
                                                          ui->lineEditMutationP->text(),//fpropMutation,
                                                          ui->lineEditNumProc->text(),
                                                          ui->lineEditMaxNumIte->text(),//imaxGen,
                                                          ui->lineEditLoadKernel->text(),
                                                          matrixGamma1,
                                                          matrixGamma2,
                                                          matrixLinear,
                                                          ui->checkBox->text(),
                                                          ui->lineEditN->text(),
                                                          QString("%1").arg(0),
                                                          ui->comboBoxReplacement->currentText(),
                                                          ui->lineEditNumberElitists->text());
     }


//     RegressionController

    //check input
//    SAKeController * controller = new SAKeController(mainWindow,
//                                                     ui->comboBoxSelection->currentText(),
//                                                     ui->comboBoxReplacement->currentText(),
//                                                     ui->comboBoxInitialPattern->currentText(),
//                                                     rain,
//                                                     rain_size,
//                                                     activation,
//                                                     activation_size,
//                                                     ui->lineEditPopSize->text().toInt(),
//                                                     ui->lineEditMaxNumIte->text().toInt(),//imaxGen,
//                                                     ui->lineEditTbMax->text().toDouble(),//itbMax,
//                                                     ui->lineEditTbMin->text().toDouble(),//itbMin,
//                                                     ui->lineEditdHpMax->text().toDouble(),//idHpMax,
//                                                     ui->lineEditdHpMin->text().toDouble(),//idHpMin,
//                                                     ui->lineEditCrossoverP->text().toDouble(),//fpropCrossover,
//                                                     ui->lineEditMutationP->text().toDouble(),//fpropMutation,
//                                                     ui->lineEditPme->text().toDouble(),//fpme,
//                                                     ui->lineEditPmb->text().toDouble(),//fpmb,
//                                                     ui->lineEditNumProc->text().toInt(),//inumberProcessor,
//                                                     ui->lineEditPar1->text().toDouble(),//ipara1,
//                                                     ui->lineEditPar2->text().toDouble(),//ipara2,
//                                                     ui->checkBoxContinueFromLastGen->isChecked(),//bLastGeneration,
//                                                     ui->lineEditProjName->text(),//sprojectname,
//                                                     ordersSelectionCriterion,//ordersSelectionCriterion
//                                                     x,//itypeAlgorithm,
//                                                     ui->lineEditNumberElitists->text().toInt(),//numberElitist.toInt(),
//                                                     ui->lineEditSeed->text().toInt(),//seed.toInt(),
//                                                     ui->lineEditFrequKerSav->text().toInt(),//saveKernels.toInt());
//                                                     ui->lineEditNumBestKernelSaved->text().toInt(),
//                                                     ui->lineEditNumberOfLines->text().toInt());//lineEditNumBestKernelSaved.toInt());

//    controller->setFt(ui->comboBoxFitness->currentIndex());

//    if(ui->lineEditProjName->isReadOnly() )
//    {
//        mainWindow->getXmlmanager()->SaveXMLFileAlreadyExistCalibrationProject(ui->lineEditProjName->text(),
//                                                                               ui->comboBoxSelection->currentText(),
//                                                                               ui->lineEditPar1->text(),//ipara1,
//                                                                               ui->lineEditPar2->text(),//ipara2,
//                                                                               ui->lineEditNumProc->text(),
//                                                                               ui->lineEditPopSize->text(),//pop.toString(),
//                                                                               ui->lineEditMaxNumIte->text(),//imaxGen,
//                                                                               ui->lineEditTbMax->text(),//itbMax,
//                                                                               ui->lineEditTbMin->text(),//itbMin,
//                                                                               ui->lineEditdHpMax->text(),//idHpMax,
//                                                                               ui->lineEditdHpMin->text(),//idHpMin,
//                                                                               QString("%1").arg(1),
//                                                                               ui->lineEditCrossoverP->text(),//fpropCrossover,
//                                                                               ui->lineEditMutationP->text(),//fpropMutation,
//                                                                               ui->lineEditPme->text(),//fpme,
//                                                                               ui->lineEditPmb->text(),//fpmb,
//                                                                               ui->comboBoxInitialPattern->currentText(),
//                                                                               rainPath,
//                                                                               actPath,
//                                                                               QString("%1").arg(x),
//                                                                               ui->lineEditNumberElitists->text(),
//                                                                               ui->lineEditSeed->text(),
//                                                                               ui->lineEditFrequKerSav->text(),
//                                                                               ui->lineEditNumBestKernelSaved->text(),
//                                                                               ordersSelectionCriterion,
//                                                                               QString("%1").arg(ui->comboBoxFitness->currentIndex()),
//                                                                               ui->lineEditNumberOfLines->text());
//    }else{
//        mainWindow->getXmlmanager()->SaveXMLFileCalibrationProject(ui->lineEditProjName->text(),
//                                                                   ui->comboBoxSelection->currentText(),
//                                                                   ui->lineEditPar1->text(),//ipara1,
//                                                                   ui->lineEditPar2->text(),//ipara2,
//                                                                   ui->lineEditNumProc->text(),
//                                                                   ui->lineEditPopSize->text(),//pop.toString(),
//                                                                   ui->lineEditMaxNumIte->text(),//imaxGen,
//                                                                   ui->lineEditTbMax->text(),//itbMax,
//                                                                   ui->lineEditTbMin->text(),//itbMin,
//                                                                   ui->lineEditdHpMax->text(),//idHpMax,
//                                                                   ui->lineEditdHpMin->text(),//idHpMin,
//                                                                   QString("%1").arg(1),
//                                                                   ui->lineEditCrossoverP->text(),//fpropCrossover,
//                                                                   ui->lineEditMutationP->text(),//fpropMutation,
//                                                                   ui->lineEditPme->text(),//fpme,
//                                                                   ui->lineEditPmb->text(),//fpmb,
//                                                                   ui->comboBoxInitialPattern->currentText(),
//                                                                   rainPath,
//                                                                   actPath,
//                                                                   QString("%1").arg(x),
//                                                                   ui->lineEditNumberElitists->text(),
//                                                                   ui->lineEditSeed->text(),
//                                                                   ui->lineEditFrequKerSav->text(),
//                                                                   ui->lineEditNumBestKernelSaved->text(),
//                                                                   ordersSelectionCriterion,
//                                                                   QString("%1").arg(ui->comboBoxFitness->currentIndex()),
//                                                                   ui->lineEditNumberOfLines->text());
//    }



//    //thread.insert();
//    connect(controller, SIGNAL(finished(int)), mainWindow, SLOT(closeTab(int)));
//    qRegisterMetaType<tm>("tm");
//    qRegisterMetaType<std::vector<Ym>>("std::vector<Ym>");
//    qRegisterMetaType<std::vector<QCPItemLine*>>("std::vector<QCPItemLine*>");
//    qRegisterMetaType<std::vector<QCPItemText*>>("std::vector<QCPItemText*>");
//    qRegisterMetaType<std::vector<double>>("std::vector<double>");
//    qRegisterMetaType<QVector<double>>("QVector<double>");
//    connect(controller, SIGNAL(updateMobPlot(int,Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
//                                             std::vector<QCPItemLine*> )), mainWindow, SLOT(updateMobPlot(int,Rain * , int ,Activation *,int, std::vector<double>,double,tm,double ,tm,std::vector<Ym> , std::vector<QCPItemText*> ,
//                                                                                                          std::vector<QCPItemLine*> )));


//    connect(controller, SIGNAL(updateFitnessPlot(int ,
//                                                 QVector<double> ,
//                                                 QVector<double> ,
//                                                 QVector<double> ,
//                                                 QVector<double> )), mainWindow, SLOT(updateFitnessPlot(int ,
//                                                                                                        QVector<double> ,
//                                                                                                        QVector<double> ,
//                                                                                                        QVector<double> ,
//                                                                                                        QVector<double> )));


//    connect(controller, SIGNAL(updateKernelPlot(int ,
//                                                QVector<double> ,
//                                                int  )), mainWindow, SLOT(updateKernelPlot(int ,
//                                                                                           QVector<double> ,
//                                                                                           int  )));

//    connect(controller, SIGNAL(updateTexts(int ,
//                                           QString,
//                                           QString,
//                                           QString ,
//                                           QString ,
//                                           QString ,
//                                           QString ,
//                                           int ,
//                                           int,
//                                           QString ,
//                                           QString )), mainWindow, SLOT(updateTexts(int ,
//                                                                                    QString,
//                                                                                    QString,
//                                                                                    QString ,
//                                                                                    QString ,
//                                                                                    QString ,
//                                                                                    QString ,
//                                                                                    int,
//                                                                                    int,
//                                                                                    QString ,
//                                                                                    QString )));
//    connect(controller, SIGNAL(updateAbsMaxFit(int , QString )), mainWindow, SLOT(updateAbsMaxFit(int , QString )));

//    connect(controller, SIGNAL(updateAbsAvFit(int , QString )), mainWindow, SLOT(updateAbsAvFit(int , QString )));

//    connect(controller, SIGNAL(updateROCPlot(int ,
//                                             QVector<double> ,
//                                             QVector<double> ,
//                                             double )), mainWindow, SLOT(updateROCPlot(int ,
//                                                                                       QVector<double> ,
//                                                                                       QVector<double> ,
//                                                                                       double )));



//    mainWindow->mutex.lock();
//    MainWindow::pushBackThread(controller);
//    ptrdiff_t pos = distance(MainWindow::threads.begin(), std::find(MainWindow::threads.begin(), MainWindow::threads.end(), controller));

//    //Fitness
//    if(ui->comboBoxFitness->currentIndex() == 3)
//        mainWindow->addTabAUCROC(QString("Calibration AUC ROC - "+ui->lineEditProjName->text()),rain, rain_size, activation, activation_size);
//    else
//        if(ui->comboBoxFitness->currentIndex() == 0)
//            mainWindow->addTab(QString("Calibration - GMD "+ui->lineEditProjName->text()),rain, rain_size, activation, activation_size);
//        else
//            if(ui->comboBoxFitness->currentIndex() == 1)
//                mainWindow->addTab(QString("Calibration - GMDn "+ui->lineEditProjName->text()),rain, rain_size, activation, activation_size);
//            else
//                if(ui->comboBoxFitness->currentIndex() == 2)
//                    mainWindow->addTab(QString("Calibration - EW "+ui->lineEditProjName->text()),rain, rain_size, activation, activation_size);



//    QCustomPlot * m_CustomPlot = (QCustomPlot *) mainWindow->getPlotMobility(pos,"");
//    for(int i = 0; i < activation_size;i++){
//        QCPItemText *textLabel = new QCPItemText(m_CustomPlot);
//        //m_CustomPlot->addItem(textLabel);
//        textLabel->setPositionAlignment(Qt::AlignTop);
//        //textLabel->position->setType(QCPItemPosition::ptPlotCoords);
//        //textLabel->position->setCoords(15, 18); // place position at center/top of axis rect
//        textLabel->setText("");
//        //textLabel->setFont(QFont(font().family(), 16)); // make font a bit larger
//        textLabel->setPen(QPen(Qt::black)); // show black border around text
//        controller->widgetArray.push_back(textLabel);

//        QCPItemLine *arrow = new QCPItemLine(m_CustomPlot);
//        //m_CustomPlot->addItem(arrow);
//        arrow->start->setParentAnchor(textLabel->bottom);
//        arrow->end->setType(QCPItemPosition::ptPlotCoords);
//        //arrow->end->setCoords(0.23, 1.6); // point to (4, 1.6) in x-y-plot coordinates
//        arrow->setHead(QCPLineEnding::esSpikeArrow);
//        controller->arrowArray.push_back(arrow);
//    }
//    mainWindow->mutex.unlock();

//    controller->startThread();
    this->close();

}

