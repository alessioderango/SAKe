#include "Regression.h"
#include "ui_regression.h"
#include <Regression/regressioncontroller.h>


void addRow(QTableWidget * tw, int row,
            QString aMaxs,
            QString aMins,
            QString bMaxs,
            QString bMins,
            QString wMaxs,
            QString wMins,
            QString percAs,
            QString percBs,
            QString percWs,
            QString transMaxs,
            QString transMins,
            QString percTranss){

    QString s= QString("%1").arg(row+1);
    QLineEdit* nrow = new QLineEdit();
    nrow->setText(s);
    tw->setCellWidget(row, 0, nrow);
    QLineEdit* aMax = new QLineEdit();
    aMax->setText(aMaxs);
    //aMax->setSizePolicy(QSizePolicy::Preferred);
    tw->setCellWidget(row, 1, aMax);
    QLineEdit* aMin = new QLineEdit();
    aMin->setText(aMins);
    tw->setCellWidget(row, 2, aMin);

    QLineEdit* bMax = new QLineEdit();
    bMax->setText(bMaxs);
    tw->setCellWidget(row, 3, bMax);
    QLineEdit* bMin = new QLineEdit();
    bMin->setText(bMins);
    tw->setCellWidget(row, 4, bMin);


    QLineEdit* wMax = new QLineEdit();
    wMax->setText(wMaxs);
    tw->setCellWidget(row, 5, wMax);
    QLineEdit* wMin = new QLineEdit();
    wMin->setText(wMins);
    tw->setCellWidget(row, 6, wMin);

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


    QLineEdit* transMax = new QLineEdit();
    transMax->setText(transMaxs);
    tw->setCellWidget(row, 10, transMax);
    QLineEdit* transMin = new QLineEdit();
    transMin->setText(transMins);
    tw->setCellWidget(row, 11, transMin);
    QLineEdit* percTrans = new QLineEdit();
    percTrans->setText(percTranss);
    tw->setCellWidget(row, 12, percTrans);
    tw->resizeColumnsToContents();


}

Regression::Regression(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Regression)
{
    ui->setupUi(this);
}

Regression::Regression(MainWindow * _w,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Regression)
{

    ui->setupUi(this);
    w=_w;
    //ui->tableWidgetMin1->setRowCount(10);
    ui->tableWidgetMin1->setColumnCount(13);
    QStringList m_TableHeader;
    m_TableHeader<<"N."<<"a max"<<"a min"<< "B max" << "B min" << "W max"<< "W min" << "Perc a" << "Perc b" << "Perc w"<< "trans max" << "trans min"<< "Perc trans";
    ui->tableWidgetMin1->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidgetMin1->verticalHeader()->setVisible(false);
    ui->tableWidgetMin1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetMin1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetMin1->setSelectionMode(QAbstractItemView::SingleSelection);


    //Validator
    ui->lineEditPopSize->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEditNumberElitists->setValidator(new QIntValidator(0, 10000000000, this));

//    ui->tableWidgetMin1->setRowCount(1);
//    addRow(ui->tableWidgetMin1,
//           0,
//           "0.8",
//           "0.2",
//           "50",
//           "5",
//           "2",
//           "0.02",
//           "0.03",
//           "0.03",
//           "0.03",
//           "0.03",
//           "0.03",
//           "0.03");
    //ui->tableWidget1->resizeColumnsToContents();

    //QTableWidget::horizontalHeader().setStretchLastSection(true);
    ui->tableWidgetMin1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->tableWidget1->setColumnCount(13);
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


    ui->tableWidget1->setRowCount(1);
    addRow(ui->tableWidget1,
           0,
           "8",
           "1",
           "100",
           "20",
           "2",
           "0.02",
           "0.03",
           "0.03",
           "0.03",
           "10",
           "1",
           "1.5");
//    addRow(ui->tableWidget1,
//           1,
//           "80",
//           "20",
//           "30",
//           "2",
//           "2",
//           "0.02",
//           "0.03",
//           "0.03",
//           "0.03",
//           "0.03",
//           "0.03",
//           "0.03");
//    addRow(ui->tableWidget1,
//           2,
//           "350",
//           "150",
//           "7",
//           "2",
//           "2",
//           "0.02",
//           "0.03",
//           "0.03",
//           "0.03",
//           "0.03",
//           "0.03",
//           "0.03");

    ui->tableWidget1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->tableWidgetLin->setColumnCount(13);
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
           "0.03",
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
    size_kernel=0;


    ui->lineEditPopSize->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEditNumberElitists->setValidator(new QIntValidator(1, 10000000000, this));

    QDoubleValidator* val = new QDoubleValidator(0.0, 1.0, 2, ui->lineEditCrossoverP);
    val->setNotation(QDoubleValidator::StandardNotation);
    val->setLocale(QLocale::C);

    ui->lineEditCrossoverP->setValidator(val);
    QDoubleValidator* val2 = new QDoubleValidator(0.0, 1.0, 2, ui->lineEditMutationP);
    val2->setNotation(QDoubleValidator::StandardNotation);
    val2->setLocale(QLocale::C);
    ui->lineEditMutationP->setValidator(val2);

    ui->lineEditNumProc->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEdit_seed->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEdit_frequencyPop->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEditNumProc->setValidator(new QIntValidator(0, 10000000000, this));


    ui->label_9->hide();
    ui->checkBox->hide();
    ui->lineEditN->hide();
    ui->groupBox_7->hide();
    ui->checkBox_kernel->hide();
    ui->checkBox_controlpoints->hide();
    ui->checkBox_N->hide();
    //hide first matrix
    ui->label_10->hide();
    ui->lineEdit_8->hide();
    ui->tableWidgetMin1->hide();

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

void Regression::hideTableFirstGamma(){
    ui->label_10->hide();
    ui->lineEdit_8->hide();
    ui->tableWidgetMin1->hide();
}

void Regression::setParameters(QVariantList list)
{

    size_kernel=0;
    QVector<QVariant> qvlist = list.toVector();
    int first = qvlist.indexOf("-");
    //Setting GA paramenters
    ui->lineEditProjName->setText(qvlist[0].toString());
    if(qvlist[1]=="Stochastic Tournament (Tr)"){
        ui->comboBox_2->setCurrentIndex(0);
        ui->lineEditPar1->setText(qvlist[2].toString());

        ui->label_15->show();
        QDoubleValidator* val = new QDoubleValidator(0.55, 1.00, 2, ui->lineEditPar1);
        val->setNotation(QDoubleValidator::StandardNotation);
        val->setLocale(QLocale::C);
        ui->lineEditPar1->setValidator(val);
        ui->lineEditPar1->show();

        ui->label_15->setText("Tr (tournament rate 0.55 <= Tr <= 1)");
        ui->label_16->hide();
        ui->lineEditPar2->hide();
    }else
        if(qvlist[1]=="Deterministic Tournament (Ts)"){
            ui->comboBox_2->setCurrentIndex(1);
            ui->lineEditPar1->setText(qvlist[2].toString());
            ui->label_15->show();
            ui->lineEditPar1->show();
            //ui->lineEditPar1->setText("2");
            QIntValidator* val = new QIntValidator(2, ui->lineEditPopSize->text().toInt(), ui->lineEditPar1);
            val->setLocale(QLocale::C);
            ui->lineEditPar1->setValidator(val);
            ui->label_15->setText(" Ts (tournament size 2 <= Ts <=N))");
            ui->label_16->hide();
            ui->lineEditPar2->hide();
        }else
            if(qvlist[1]=="Ranking (s)"){
                ui->comboBox_2->setCurrentIndex(2);
                ui->lineEditPar1->setText(qvlist[2].toString());
                //ui->lineEditPar2->setText(qvlist[3].toString());
                ui->label_15->show();
                ui->label_15->setText("selective pressure 0 < s < 1   (exponential) \n \
                                      1 <= s <= 2 (linear)");
                //ui->lineEditPar1->setText("2");
                QDoubleValidator* val = new QDoubleValidator(0.000, 2.000, 2, ui->lineEditPar1);
                val->setNotation(QDoubleValidator::StandardNotation);
                val->setLocale(QLocale::C);
                ui->lineEditPar1->setValidator(val);
                ui->label_16->show();
                ui->label_16->setText("e (exponent 1=linear)");
                //ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
                ui->lineEditPar2->setText("-1");
                ui->lineEditPar2->show();
                ui->label_16->hide();
                ui->lineEditPar2->hide();
            }else
                if(qvlist[1]=="Roulette"){
                    ui->comboBox_2->setCurrentIndex(3);
                    ui->label_15->hide();
                    ui->lineEditPar1->hide();
                    ui->label_16->hide();
                    ui->lineEditPar2->hide();
                }else
                    if(qvlist[1]=="Ranking (p,e)"){
                        ui->comboBox_2->setCurrentIndex(4);
                        ui->lineEditPar1->setText(qvlist[2].toString());
                        ui->lineEditPar2->setText(qvlist[3].toString());
                        ui->label_15->show();
                        ui->label_15->setText("p (selective pressure 1 < p <= 2)");
                        //ui->lineEditPar1->setText("2");
                        QDoubleValidator* val = new QDoubleValidator(1.000, 2.000, 2, ui->lineEditPar1);
                        val->setNotation(QDoubleValidator::StandardNotation);
                        val->setLocale(QLocale::C);
                        ui->lineEditPar1->setValidator(val);
                        ui->label_16->show();
                        ui->label_16->setText("e (exponent 1=linear)");
                       // ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
                        //ui->lineEditPar2->setText("1");
                        ui->lineEditPar2->show();
                    }
    ui->lineEditPopSize->setText(qvlist[4].toString());
    ui->lineEditNumProc->setText(qvlist[5].toString());
    ui->lineEditCrossoverP->setText(qvlist[6].toString());
    ui->lineEditMutationP->setText(qvlist[7].toString());
    ui->lineEditMaxNumIte->setText(qvlist[8].toString());
    QString filename = qvlist[9].toString();
    //9  file kernel
    ui->lineEditLoadKernel->setText(filename);
    //10 control points
    bool UseControlPointsChecked = qvlist[10].toInt();
    ui->checkBox->setChecked(UseControlPointsChecked);
    //11 number control points

    ui->lineEditN->setText(qvlist[11].toString());
    //12 typeexecution means kernel / controls points / N
    int typekernel = qvlist[12].toInt();
    switch (typekernel) {
    case 0:
        ui->checkBox_kernel->setChecked(true);
        break;
    case 1:
        ui->checkBox_controlpoints->setChecked(true);
        break;
    case 2:
        ui->checkBox_N->setChecked(true);
        break;
    default:
        break;
    }
    ui->checkBox_kernel->hide();
    ui->checkBox_controlpoints->hide();
    ui->checkBox_N->hide();
    //hide first matrix
    ui->label_10->hide();
    ui->lineEdit_8->hide();
    ui->tableWidgetMin1->hide();


    ui->comboBox->setCurrentIndex(qvlist[13].toInt());
    if(qvlist[13].toInt() == 0)
    {
      ui->label_14->hide();
      ui->lineEditNumberElitists->hide();
    }
    ui->lineEditNumberElitists->setText(QString("%1").arg(qvlist[14].toInt()));
    ui->lineEdit_seed->setText(QString("%1").arg(qvlist[15].toInt()));
   // bool lastgen = qvlist[16].toInt();
   // ui->checkBox_lastgeneration->setChecked(lastgen);
    ui->lineEdit_frequencyPop->setText(QString("%1").arg(qvlist[17].toInt()));

    int second = qvlist.indexOf("-",first+1);


    int third = qvlist.indexOf("-",second+1);


    int fourth = qvlist.indexOf("-", third+1);

    int dim = (second - (first+1))/12;
    ui->tableWidgetMin1->setColumnCount(13);
    QStringList m_TableHeader;
    m_TableHeader<<"N."<<"a max"<<"a min"<< "B max" << "B min" << "W max"<< "W min" << "Perc a" << "Perc b" << "Perc w"<< "trans max" << "trans min"<< "Perc trans";
    ui->tableWidgetMin1->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidgetMin1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetMin1->verticalHeader()->setVisible(false);
    ui->tableWidgetMin1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetMin1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetMin1->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidgetMin1->setRowCount(dim);
    int row=0;
    for (int i = first+1; i < second; i+=12) {

        addRow(ui->tableWidgetMin1,
               row,
               qvlist[i].toString(),
               qvlist[i+1].toString(),
               qvlist[i+2].toString(),
               qvlist[i+3].toString(),
               qvlist[i+4].toString(),
               qvlist[i+5].toString(),
               qvlist[i+6].toString(),
               qvlist[i+7].toString(),
               qvlist[i+8].toString(),
               qvlist[i+9].toString(),
               qvlist[i+10].toString(),
               qvlist[i+11].toString());
        row++;
    }
    ui->tableWidgetMin1->resizeColumnsToContents();

    row=0;
    int dim2 = (third - (second+1))/12;
    ui->tableWidget1->setColumnCount(13);
    ui->tableWidget1->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget1->verticalHeader()->setVisible(false);
    ui->tableWidget1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget1->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidget1->setRowCount(dim2);
    for (int i = second+1; i < third; i+=12) {

        addRow(ui->tableWidget1,
               row,
               qvlist[i].toString(),
               qvlist[i+1].toString(),
               qvlist[i+2].toString(),
               qvlist[i+3].toString(),
               qvlist[i+4].toString(),
               qvlist[i+5].toString(),
               qvlist[i+6].toString(),
               qvlist[i+7].toString(),
               qvlist[i+8].toString(),
               qvlist[i+9].toString(),
               qvlist[i+10].toString(),
               qvlist[i+11].toString());
        row++;
    }
    ui->tableWidget1->setVisible(false);
     ui->tableWidget1->resizeColumnsToContents();
     ui->tableWidget1->setVisible(true);

    row=0;
    int dim3 = (fourth - (third+1))/12;
    ui->tableWidgetLin->setColumnCount(13);
    ui->tableWidgetLin->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidgetLin->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetLin->verticalHeader()->setVisible(false);
    ui->tableWidgetLin->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetLin->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetLin->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidgetLin->setRowCount(dim3);
    for (int i = third+1; i < fourth; i+=12) {

        addRow(ui->tableWidgetLin,
               row,
               qvlist[i].toString(),
               qvlist[i+1].toString(),
               qvlist[i+2].toString(),
               qvlist[i+3].toString(),
               qvlist[i+4].toString(),
               qvlist[i+5].toString(),
               qvlist[i+6].toString(),
               qvlist[i+7].toString(),
               qvlist[i+8].toString(),
               qvlist[i+9].toString(),
               qvlist[i+10].toString(),
               qvlist[i+11].toString());
        row++;
    }

     ui->tableWidgetLin->resizeColumnsToContents();
//     ui->kernelPlot = new QCustomPlot();
     MainWindow::makeKernelPlot(ui->kernelPlot,w);
     //ui->kernelPlot->setSizePolicy(spUp);
     ui->kernelPlot->setObjectName("kerFunc");
     controlPoints = new ControlPoints();
     HandlerCSV::loadCSVKernel(ui->lineEditLoadKernel->text(),this->kernel,this->size_kernel,this->Delta_cr);

     //MainWindow::updateKernelPlot();

     std::vector<double> x;
     std::vector<double> y;

//     controlPoints->calculateControlPoints(&(this->kernel[0]),this->size_kernel);
//     xControlpoints = controlPoints->getX();
//     yControlpoints = controlPoints->getY();

     QVector<double> xKernel;
     QVector<double> yKernel;
     for (int i = 0; i < size_kernel; i++) {
         xKernel.push_back(i+1);
         yKernel.push_back(kernel[i]);
     }

//     //updateGraph(kernel,size_kernel);
//     xControlpointsbyN.clear();
//     yControlpointsbyN.clear();

//     if(ui->checkBox->isChecked()){
//         controlPoints->getSubdividePointsFromControlPoints(xControlpoints, yControlpoints, ui->lineEditN->text().toInt(), xControlpointsbyN, yControlpointsbyN);

//     }else{
//         controlPoints->getSubdividePointsFromKernel(&(kernel[0]), size_kernel, ui->lineEditN->text().toInt(), xControlpointsbyN, yControlpointsbyN);
//     }
//      w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(xControlpointsbyN), QVector<double>::fromStdVector(yControlpointsbyN) );


     QCustomPlot *m_CustomPlot = ui->kernelPlot;
     w->updateKernelPlotRegression(m_CustomPlot,xKernel,
                                   yKernel,
                                   QVector<double>::fromStdVector(xControlpoints),
                                   QVector<double>::fromStdVector(yControlpoints));
     ui->label_9->hide();
     ui->checkBox->hide();
     ui->lineEditN->hide();
     ui->groupBox_7->hide();
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
                           "8",
                           "1",
                           "100",
                           "20",
                           "2",
                           "0.02",
                           "0.03",
                           "0.03",
                           "0.03",
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
                           "8",
                           "1",
                           "100",
                           "20",
                           "2",
                           "0.02",
                           "0.03",
                           "0.03",
                           "0.03",
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
                           "8",
                           "1",
                           "100",
                           "20",
                           "2",
                           "0.02",
                           "0.03",
                           "0.03",
                           "0.03",
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
    if(!fileName.isEmpty()){
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


//    controlPoints->calculateControlPoints(&(this->kernel[0]),this->size_kernel);
//    xControlpoints = controlPoints->getX();
//    yControlpoints = controlPoints->getY();


    QCustomPlot *m_CustomPlot = ui->kernelPlot;
    w->updateKernelPlotRegression(m_CustomPlot,xKernel,
                                  yKernel,
                                  QVector<double>::fromStdVector(xControlpoints),
                                  QVector<double>::fromStdVector(yControlpoints));
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


//void Regression::on_lineEdit_7_textChanged(const QString &n)
//{
//    if(!n.isEmpty()){

//        std::vector< double> x;
//        std::vector< double> y;
//        int nInt =  n.toInt();

////        if(ui->checkBox->isChecked()){
////            xControlpointsbyN.clear();
////            yControlpointsbyN.clear();
////            controlPoints->getSubdividePointsFromControlPoints(xControlpoints, yControlpoints, nInt, xControlpointsbyN, yControlpointsbyN);
////            w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(xControlpointsbyN), QVector<double>::fromStdVector(yControlpointsbyN) );
////        }else{
////            controlPoints->getSubdividePointsFromKernel(&(kernel[0]), size_kernel, nInt,x, y);
////            w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(x), QVector<double>::fromStdVector(y));

////        }

//        xControlpointsbyN.clear();
//        yControlpointsbyN.clear();

//        if(ui->checkBox->isChecked()){
//            controlPoints->getSubdividePointsFromControlPoints(xControlpoints, yControlpoints, ui->lineEditN->text().toInt(), xControlpointsbyN, yControlpointsbyN);

//        }else{
//            controlPoints->getSubdividePointsFromKernel(&(kernel[0]), size_kernel, ui->lineEditN->text().toInt(), xControlpointsbyN, yControlpointsbyN);
//        }
//         w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(xControlpointsbyN), QVector<double>::fromStdVector(yControlpointsbyN) );



//    }



//}

void Regression::on_checkBox_clicked()
{
    if(!ui->lineEditN->text().isEmpty()){

        std::vector< double> x;
        std::vector< double> y;
        int nInt =  ui->lineEditN->text().toInt();
//        if(ui->checkBox->isChecked()){
//            xControlpointsbyN.clear();
//            yControlpointsbyN.clear();
//            controlPoints->getSubdividePointsFromControlPoints(xControlpoints, yControlpoints, nInt, xControlpointsbyN, yControlpointsbyN);
//            w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(xControlpointsbyN), QVector<double>::fromStdVector(yControlpointsbyN) );
//        }else{
//            controlPoints->getSubdividePointsFromKernel(&(kernel[0]), size_kernel, nInt,x, y);
//            w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(x), QVector<double>::fromStdVector(y));

//        }
        xControlpointsbyN.clear();
        yControlpointsbyN.clear();

        if(ui->checkBox->isChecked()){
            if(xControlpoints.size() !=0)
                controlPoints->getSubdividePointsFromControlPoints(xControlpoints, yControlpoints, ui->lineEditN->text().toInt(), xControlpointsbyN, yControlpointsbyN);

        }else{
            if(size_kernel !=0)
               controlPoints->getSubdividePointsFromKernel(&(kernel[0]), size_kernel, ui->lineEditN->text().toInt(), xControlpointsbyN, yControlpointsbyN);
        }
         if(xControlpointsbyN.size() !=0)
         w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(xControlpointsbyN), QVector<double>::fromStdVector(yControlpointsbyN) );


    }
}

//void Regression::on_comboBox_2_currentIndexChanged(int index)
//{
//    if(index == 0){
//        //StockTour
//        ui->label_15->show();
//        ui->lineEditPar1->setValidator(new QDoubleValidator(0.55, 1,2, this));
//        ui->lineEditPar1->show();

//        ui->label_15->setText("Tr (tournament rate 0.55 <= Tr <= 1)");
//        ui->label_16->hide();
//        ui->lineEditPar2->hide();
//    }else
//        if(index == 1){
//            //DetTour
//            ui->label_15->show();
//            ui->lineEditPar1->show();
//            ui->lineEditPar1->setText("2");
//            ui->lineEditPar1->setValidator(new QIntValidator(2, ui->lineEditPopSize->text().toInt(), this));
//            ui->label_15->setText(" Ts (tournament size 2 <= Ts <=N))");
//            ui->label_16->hide();
//            ui->lineEditPar2->hide();
//        }else
//            if(index == 2)
//            {
//                ui->label_15->show();
//                ui->label_15->setText("p (selective pressure 1 < p <= 2)");
//                ui->lineEditPar1->setText("2");
//                //ui->lineEditPar1->setValidator(new QDoubleValidator(1, 2,2, this));
//                ui->label_16->show();
//                ui->label_16->setText("e (exponent 1=linear)");
//                //ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
//                ui->lineEditPar2->setText("1");
//                ui->lineEditPar2->show();
//                ui->lineEditPar2->show();
//            }else
//                if(index == 3)
//                {
//                    ui->label_15->hide();
//                    ui->lineEditPar1->hide();
//                    ui->label_16->hide();
//                    ui->lineEditPar2->hide();
//                }else
//                    if(index == 4)// Ranking (p,e)
//                    {
//                        ui->label_15->show();
//                        ui->label_15->setText("p (selective pressure 1 < p <= 2)");
//                        ui->lineEditPar1->setText("2");
//                        ui->lineEditPar1->setValidator(new QDoubleValidator(1, 2,2, this));
//                        ui->label_16->show();
//                        ui->label_16->setText("e (exponent 1=linear)");
//                        ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
//                        ui->lineEditPar2->setText("1");
//                        ui->lineEditPar2->show();
//                        ui->lineEditPar1->show();
//                    }
//}

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

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / (double)RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void Regression::on_pushButton_clicked()
{
    QString e;


    if(ui->lineEditProjName->text().isEmpty())
    {
        QString error = QString("Project name cannot be empty \n");

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }

    if(!ui->lineEditProjName->isReadOnly() && w->getXmlmanager()->findProjectName(ui->lineEditProjName->text(), "RegressionProject"))
    {
        QString error = QString("Anotehr Project with the same name already exists \n");

        QMessageBox::information(
                    this,
                    tr(QString("Warning").toStdString().c_str()),
                    tr(error.toStdString().c_str()) );
        return;
    }



    bool check = checklineEdit(ui->lineEditPopSize->text(), QString("Population size cannot be empty \n"));
    if(check) return;
    if(ui->lineEditPopSize->text().toInt() <= 0)
    check = checklineEdit("", QString("Population size myst be greater than 0\n"));
    if(check) return;

    // elitist
    if(ui->comboBox->currentIndex() == 1){
        check = checklineEdit(ui->lineEditNumberElitists->text(), QString("number of elitists cannot be empty \n"));
        if(check) return;
    }

    if(ui->comboBox_2->currentIndex() ==0 ){
        check = checklineEdit(ui->lineEditPar1->text(), QString("Tr cannot be empty \n"));
        if(check) return;
    }else
        if(ui->comboBox_2->currentIndex() ==1 ){
            check = checklineEdit(ui->lineEditPar1->text(), QString("Ts cannot be empty \n"));
            if(check) return;
        }
        else
            if(ui->comboBox_2->currentIndex() ==2 ){
                check = checklineEdit(ui->lineEditPar1->text(), QString("selective pressure cannot be empty \n"));
                if(check) return;
                check = checklineEdit(ui->lineEditPar2->text(), QString("exponent cannot be empty \n"));
                if(check) return;
            }else
                if(ui->comboBox_2->currentIndex() ==4 ){//Ranking (p,e)
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
    check = checkValueSelectionParameter();
    if(check){
        return;
    }
    //    check = checklineEdit(ui->lineEditSeed->text(), QString("Seed cannot be empty \n"));
    //    if(check) return;
    //    check = checklineEdit(ui->lineEditFrequKerSav->text(), QString("Frequency of kernel saving cannot be empty \n"));
    //    if(check) return;
    //    check = checklineEdit(ui->lineEditNumBestKernelSaved->text(), QString("Number of best kernels to saved cannot be empty \n"));
    //    if(check) return;

    //reading Gamma1 table
    std::vector<std::vector<double> > matrixGamma1;
//    cout << ui->tableWidgetMin1->rowCount() << endl;
//    cout << ui->tableWidgetMin1->columnCount() << endl;
    for(int row = 0;row <ui->tableWidgetMin1->rowCount(); row++)
    {
        std::vector<double> tmp;
        for(int column = 1;column< ui->tableWidgetMin1->columnCount() ;column++)
        {
            QLineEdit* t= (QLineEdit*)ui->tableWidgetMin1->cellWidget(row,column);
            //cout << t->text().toStdString() << endl;
            check = checklineEdit(t->text(), QString("Values inside gamma table cannot be empty \n"));
            if(check) return;
            if(t->text().toDouble() < 0)
            {
                checklineEdit("", QString("Values inside gamma table must be > 0 \n"));
                return;
            }

            tmp.push_back(t->text().toDouble());
        }
        matrixGamma1.push_back(tmp);
    }



    double maxBeta = 100;
    double maxAlpha = 100;

    //reading Gamma2 table
    std::vector<std::vector<double> > matrixGamma2;
    for(int row = 0;row <ui->tableWidget1->rowCount(); row++)
    {
        std::vector<double> tmp;
        for(int column = 1;column< ui->tableWidget1->columnCount() ;column++)
        {
            QLineEdit* t= (QLineEdit*)ui->tableWidget1->cellWidget(row,column);
            //cout << t->text().toStdString() << endl;
            check = checklineEdit(t->text(), QString("Values inside gamma table cannot be empty \n"));
            if(check) return;
            if(t->text().toDouble() <= 0)
            {
                checklineEdit("", QString("Values inside gamma table must be > 0 \n"));
                return;
            }
            if((column == 1) && t->text().toDouble() > maxAlpha ){
                checklineEdit("", QString("Max alpha value must be less than "+QString::number(maxAlpha)+" \n"));
                return;
            }

            if((column == 3) && t->text().toDouble() > maxBeta ){
                checklineEdit("", QString("Max beta value must be less than "+QString::number(maxBeta)+" \n"));
                return;
            }
            tmp.push_back(t->text().toDouble());
        }
        matrixGamma2.push_back(tmp);
    }

    //reading Linear table
    std::vector<std::vector<double> > matrixLinear;
    for(int row = 0;row <ui->tableWidgetLin->rowCount(); row++)
    {
        std::vector<double> tmp;
        for(int column = 1;column< ui->tableWidgetLin->columnCount() ;column++)
        {
            QLineEdit* t= (QLineEdit*)ui->tableWidgetLin->cellWidget(row,column);
            //cout << t->text().toStdString() << endl;
            check = checklineEdit(t->text(), QString("Values inside linear table cannot be empty \n"));
            if(check) return;
//            if(t->text().toDouble() <= 0)
//            {
//                checklineEdit("", QString("Values inside gamma table must be > 0 \n"));
//                return;
//            }
            tmp.push_back(t->text().toDouble());
        }
        matrixLinear.push_back(tmp);
    }

    //    RegressionController * controller = RegressionController(ui->lineEditProjName,
    //                                                             );
    int typeReplacement = QString::compare(ui->comboBox->currentText(), "generational", Qt::CaseInsensitive);
    if(typeReplacement !=0){
        typeReplacement=1;
    }


    std::vector<double>  ykerneltmp;
    std::vector<double>  xkerneltmp;
    std::vector<double> x1;
    for (int i = 0; i < size_kernel; i++) {
        x1.push_back(i+1);
    }
    int size;
    int checked;

//    ui->checkBox_kernel->setCheckable(true);

//    if(ui->checkBox_kernel->isChecked())
//    {   //use kernel
        ykerneltmp = kernel;
        xkerneltmp = x1;
        size = kernel.size();
        checked = 0;
//    }else
//    if(ui->checkBox_controlpoints->isChecked())
//    {
//        //use control points
//        ykerneltmp = yControlpoints;
//        xkerneltmp = xControlpoints;
//        size = yControlpoints.size();
//        checked = 1;
//    }else
//    if(ui->checkBox_N->isChecked())
//    {
//        //use N
//        ykerneltmp = yControlpointsbyN;
//        xkerneltmp = xControlpointsbyN;
//        size = yControlpointsbyN.size();
//        checked = 2;
//    }

    if(ui->lineEditProjName->isReadOnly())
    {
        w->getXmlmanager()->SaveXMLFileAlreadyExistRegressionProject(ui->lineEditProjName->text(),
                                                                     ui->comboBox_2->currentText(),
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
                                                                     QString::number(ui->checkBox->isChecked()),
                                                                     ui->lineEditN->text(),
                                                                     QString("%1").arg(checked),
                                                                     QString("%1").arg(ui->comboBox->currentIndex()),
                                                                     ui->lineEditNumberElitists->text(),
                                                                     ui->lineEdit_seed->text(),
                                                                     QString::number(ui->checkBox_lastgeneration->isChecked()),
                                                                     ui->lineEdit_frequencyPop->text());


    }else{
        w->getXmlmanager()->SaveXMLFileRegressionProject(ui->lineEditProjName->text(),
                                                         ui->comboBox_2->currentText(),
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
                                                         QString::number(ui->checkBox->isChecked()),
                                                         ui->lineEditN->text(),
                                                         QString("%1").arg(checked),
                                                         QString("%1").arg(ui->comboBox->currentIndex()),
                                                         ui->lineEditNumberElitists->text(),
                                                         ui->lineEdit_seed->text(),
                                                         QString::number(ui->checkBox_lastgeneration->isChecked()),
                                                         ui->lineEdit_frequencyPop->text());
    }

    int dimension=matrixGamma1.size()+matrixGamma2.size()+matrixLinear.size();
    double * weight = new double[dimension];
    int count =0;
    for (int i = 0; i < matrixLinear.size(); ++i) {
        double tmp1=fRand(matrixLinear[i][4],matrixLinear[i][5]);
        weight[count] = tmp1;
        count++;
    }
    for (int i = 0; i < matrixGamma1.size(); ++i) {
        double tmp1=fRand(matrixGamma1[i][4],matrixGamma1[i][5]);
        weight[count] = tmp1;
        count++;
    }
    for (int i = 0; i <  matrixGamma2.size(); ++i) {
        double tmp1=fRand(matrixGamma2[i][4],matrixGamma2[i][5]);
        weight[count] = tmp1;
        count++;
    }

    int * functionType = new int[dimension];

    double * percantageGammaA;
    percantageGammaA= new double[dimension];
    double * percantageGammaB;
    percantageGammaB= new double[dimension];
    double * percantageLinearA;
    percantageLinearA= new double[dimension];
    double * percantageLinearB;
    percantageLinearB= new double[dimension];
    double * percantageW;
    percantageW= new double[dimension];
    double* translation= new double[dimension];

    count = 0;
    for (int i = 0; i < matrixLinear.size(); ++i) {
        functionType[count]=0;
        percantageLinearA[count]=matrixLinear[i][6];
        percantageLinearB[count]=matrixLinear[i][7];
        percantageW[count]=matrixLinear[i][8];
        translation[count] = matrixLinear[i][11];
        count++;
    }
//new
    for (int i = matrixLinear.size(); i <  matrixGamma1.size()+matrixGamma2.size(); ++i) {
        percantageLinearA[i]=0;
        percantageLinearB[i]=0;
        percantageW[i]=0;
        translation[i]=0;
    }

    for (int i = 0; i < matrixGamma1.size(); ++i) {
        functionType[count]=1;
        percantageGammaA[count]=(matrixGamma1[i][6]);
        percantageGammaB[count]=(matrixGamma1[i][7]);
        percantageW[count]=(matrixGamma1[i][8]);
        translation[count] =matrixGamma1[i][11];
        count++;
    }


    for (int i =  0; i <  matrixGamma2.size(); ++i) {
        functionType[count]=2;
        percantageGammaA[count]=(matrixGamma2[i][6]);
        percantageGammaB[count]=(matrixGamma2[i][7]);
        percantageW[count]=matrixGamma2[i][8];
        translation[count] =matrixGamma2[i][11];
        count++;
    }

    //new
    for (int i = 0; i < matrixLinear.size(); ++i) {
        percantageGammaA[i]=0;
        percantageGammaB[i]=0;
        percantageW[i]=0;
        translation[i]=0;
    }


//    for (int i =  0; i <  matrixLinear.size(); ++i) {
//        cout << functionType[i] << endl;
//        cout <<percantageLinearA[i]<< endl;
//        cout <<percantageLinearB[i]<< endl;
//        cout <<percantageW[i]<< endl;
//        cout <<translation[i] << endl;
//    }

//    for (int i =  matrixLinear.size(); i <  matrixGamma1.size()+matrixGamma2.size(); ++i) {
//        cout << functionType[i] << endl;
//        cout <<percantageGammaA[i]<< endl;
//        cout <<percantageGammaA[i]<< endl;
//        cout <<percantageW[i]<< endl;
//        cout <<translation[i] << endl;
//    }

    Parameters *parameters = new Parameters[dimension];

    count = 0;
    for (int i = 0; i < matrixLinear.size(); ++i) {
        Parameters tmp;
        double tmp1=fRand(matrixLinear[i][0],matrixLinear[i][1]);
//        std::cout <<tmp1<< std::endl;
        tmp.addParameters(tmp1);
        double tmp2=fRand(matrixLinear[i][2],matrixLinear[i][3]);
//        std::cout <<tmp2<< std::endl;
        tmp.addParameters(tmp2);
        double tmp3=fRand(matrixLinear[i][9],matrixLinear[i][10]);
//        std::cout <<tmp3<< std::endl;
        tmp.addParameters(tmp3);
        parameters[count]=tmp;
        count++;
    }

    for (int i = 0; i < matrixGamma1.size(); ++i) {
        Parameters tmp;
        double tmp1=fRand(matrixGamma1[i][0],matrixGamma1[i][1]);
        //std::cout <<tmp1<< std::endl;
        tmp.addParameters(tmp1);
        double tmp2=fRand(matrixGamma1[i][2],matrixGamma1[i][3]);
        //std::cout <<tmp2<< std::endl;
        tmp.addParameters(tmp2);
        double tmp3=fRand(matrixGamma1[i][9],matrixGamma1[i][10]);
        //std::cout <<tmp3<< std::endl;
        tmp.addParameters(tmp3);
        parameters[count]=tmp;
        count++;

    }
    for (int i = 0; i < matrixGamma2.size(); ++i) {
        Parameters tmp;
        double tmp1=fRand(matrixGamma2[i][0],matrixGamma2[i][1]);
        //std::cout <<tmp1<< std::endl;
        tmp.addParameters(tmp1);
        double tmp2=fRand(matrixGamma2[i][2],matrixGamma2[i][3]);
        //std::cout <<tmp2<< std::endl;
        tmp.addParameters(tmp2);
        double tmp3=fRand(matrixGamma2[i][9],matrixGamma2[i][10]);
        //std::cout <<tmp3<< std::endl;
        tmp.addParameters(tmp3);
        parameters[count]=tmp;
        count++;

    }

//    double *kernel;
//    int size_kernel;
//    double Delta_cr;
    //QObject *errorHandler = rootObject->findChild<QObject*>("errorcsvHandler");
    //int errorRain = HandlerCSV::loadCSVKernel(ui->lineEditLoadKernel->text(),kernel,size_kernel,Delta_cr);

    QString tmp2 = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/workspace/regression/"+ui->lineEditProjName->text();
    QDir dir3(tmp2);
    if (!dir3.exists()){
        dir3.mkdir(".");


    }

    std::vector<Genotype> loadedPopulation;
    if(ui->checkBox_lastgeneration->isChecked()){
        HandlerCSV::loadCSVPopFromFileRegression(tmp2+"/population.csv",
                                             loadedPopulation,
                                             dimension
                                             );


    }
    RegressionController * controller = new RegressionController(w,
                                                                 ui->lineEditProjName->text(),
                                                                 percantageW,
                                                                 percantageLinearA,
                                                                 percantageLinearB,
                                                                 percantageGammaA,
                                                                 percantageGammaB,
                                                                 weight,
                                                                 dimension,
                                                                 functionType,
                                                                 dimension,
                                                                 parameters,
                                                                 dimension,
                                                                 xkerneltmp,
                                                                 ykerneltmp,
                                                                 ui->lineEditNumberElitists->text().toInt(),
                                                                 ui->lineEditPopSize->text().toInt(),
                                                                 ui->lineEditMaxNumIte->text().toInt(),
                                                                 ui->lineEditCrossoverP->text().toDouble(),//fpropCrossover,
                                                                 ui->lineEditMutationP->text().toDouble(),//fpropMutation,
                                                                 ui->lineEditNumProc->text().toInt(),
                                                                 translation,
                                                                 ui->lineEditPar1->text().toDouble(),//ipara1,
                                                                 ui->lineEditPar2->text().toDouble(),//ipara2,
                                                                 typeReplacement,
                                                                 ui->comboBox_2->currentText(),
                                                                 ui->lineEdit_seed->text().toInt(),
                                                                 loadedPopulation,
                                                                 ui->checkBox_lastgeneration->isChecked(),
                                                                 ui->lineEdit_frequencyPop->text().toInt()
                                                                 );

//    controller->setX(x1);
//    controller->setY(kernel);


    connect(controller, SIGNAL(finished(int)), w, SLOT(closeTab(int)));
    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<std::vector<QCPItemLine*>>("std::vector<QCPItemLine*>");
    qRegisterMetaType<std::vector<QCPItemText*>>("std::vector<QCPItemText*>");

    connect(controller, SIGNAL(updateTextsRegression(int ,
                                                QString,
                                                QString,
                                                QString,
                                                int,
                                                int,
                                                QString,
                                                QString )), w, SLOT(updateTextsRegression(int ,
                                                                                     QString,
                                                                                     QString,
                                                                                     QString,
                                                                                     int,
                                                                                     int,
                                                                                     QString,
                                                                                     QString )));
    qRegisterMetaType< std::vector< std::vector<double> >>(" std::vector< std::vector<double> >");
    connect(controller, SIGNAL(updateRegression(int ,
                               QVector<double> ,
                               QVector<double> ,
                               QVector<double> ,
                               QVector<double> ,
                               int ,
                               std::vector< std::vector<double> > ,
                               int ,
                               std::vector<QCPItemText*> ,
                               std::vector<QCPItemLine*> ,
                               std::vector< std::vector<double> >  )), w, SLOT(updateRegression(int ,
                                                                               QVector<double> ,
                                                                               QVector<double> ,
                                                                               QVector<double> ,
                                                                               QVector<double> ,
                                                                               int ,
                                                                               std::vector< std::vector<double> > ,
                                                                               int ,
                                                                               std::vector<QCPItemText*> ,
                                                                               std::vector<QCPItemLine*> ,
                                                                               std::vector< std::vector<double> >  )));




    w->mutex.lock();
    MainWindow::pushBackThread(controller);
    //ptrdiff_t pos = distance(MainWindow::threads.begin(), std::find(MainWindow::threads.begin(), MainWindow::threads.end(), controller));

    w->addTabRegression("Regression - " + ui->lineEditProjName->text(),dimension );

    ptrdiff_t pos = distance(MainWindow::threads.begin(), std::find(MainWindow::threads.begin(), MainWindow::threads.end(), controller));

    QCustomPlot * m_CustomPlot = (QCustomPlot *) w->getKernelPlotRegression(pos);

    for(int i = 0; i < dimension;i++){
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
    w->mutex.unlock();

    controller->startThread();
    this->close();

}


void Regression::on_comboBoxReplacement_currentIndexChanged(int index)
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

void Regression::on_lineEditN_textChanged(const QString &n)
{
    if(!n.isEmpty()){

        std::vector< double> x;
        std::vector< double> y;
        int nInt =  n.toInt();

        xControlpointsbyN.clear();
        yControlpointsbyN.clear();

        if(ui->checkBox->isChecked()){
            if(xControlpoints.size() != 0 )
            controlPoints->getSubdividePointsFromControlPoints(xControlpoints, yControlpoints, nInt, xControlpointsbyN, yControlpointsbyN);

        }else{
            if(size_kernel !=0)
                controlPoints->getSubdividePointsFromKernel(&(kernel[0]), size_kernel, nInt,xControlpointsbyN, yControlpointsbyN);

        }
         if(xControlpointsbyN.size() != 0 )
         w->updateKernelPlotRegressionWithControlPoints(ui->kernelPlot, QVector<double>::fromStdVector(xControlpointsbyN), QVector<double>::fromStdVector(yControlpointsbyN) );


    }
}


void Regression::on_checkBox_kernel_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        ui->checkBox_controlpoints->setChecked(false);
        ui->checkBox_N->setChecked(false);
    }
}

void Regression::on_checkBox_controlpoints_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        ui->checkBox_kernel->setChecked(false);
        ui->checkBox_N->setChecked(false);
    }
}

void Regression::on_checkBox_N_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        ui->checkBox_controlpoints->setChecked(false);
        ui->checkBox_kernel->setChecked(false);
    }
}

void Regression::setReadOnlyProjName(bool a)
{
    ui->lineEditProjName->setReadOnly(a);
}

void Regression::on_comboBox_2_currentIndexChanged(int index)
{
    if(index == 0){
        //StockTour
        ui->label_15->show();
        QDoubleValidator* val = new QDoubleValidator(0.55, 1.00, 2, ui->lineEditPar1);
        val->setNotation(QDoubleValidator::StandardNotation);
        val->setLocale(QLocale::C);
        ui->lineEditPar1->setValidator(val);

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
            QIntValidator* val = new QIntValidator(2, ui->lineEditPopSize->text().toInt(), ui->lineEditPar1);
            val->setLocale(QLocale::C);
            ui->lineEditPar1->setValidator(val);
            ui->label_15->setText(" Ts (tournament size 2 <= Ts <=N))");
            ui->label_16->hide();
            ui->lineEditPar2->hide();
        }else
            if(index == 2)
            {
                ui->label_15->show();
                ui->label_15->setText("selective pressure 0 < s < 1   (exponential) \n \
                                      1 <= s <= 2 (linear)");
                ui->lineEditPar1->setText("2");
                QDoubleValidator* val = new QDoubleValidator(0.000, 2.000, 2, ui->lineEditPar1);
                val->setNotation(QDoubleValidator::StandardNotation);
                val->setLocale(QLocale::C);
                ui->lineEditPar1->setValidator(val);
                //ui->lineEditPar1->setValidator(new QDoubleValidator(1, 2,2, this));
//                ui->label_16->show();
                ui->label_16->setText("e (exponent 1=linear)");
                //ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
                ui->lineEditPar2->setText("-1");
                ui->label_16->hide();
                ui->lineEditPar2->hide();
            }else
                if(index == 3)
                {
                    ui->label_15->hide();
                    ui->lineEditPar1->hide();
                    ui->label_16->hide();
                    ui->lineEditPar2->hide();
                }else
                    if(index == 4)// Ranking (p,e)
                    {
                        ui->label_15->show();
                        ui->label_15->setText("p (selective pressure 1 < p <= 2)");
                        ui->lineEditPar1->setText("2");
                        QDoubleValidator* val = new QDoubleValidator(1.000, 2.000, 2, ui->lineEditPar1);
                        val->setNotation(QDoubleValidator::StandardNotation);
                        val->setLocale(QLocale::C);
                        ui->lineEditPar1->setValidator(val);                        ui->label_16->show();
                        ui->label_16->setText("e (exponent 1=linear)");
                        //ui->lineEditPar1->setValidator(new QDoubleValidator(0, 1,2, this));
                        ui->lineEditPar2->setText("1");
                        ui->lineEditPar2->show();
                        ui->lineEditPar1->show();
                    }
}

QString Regression::getIdProject() const
{
    return idProject;
}

void Regression::setIdProject(const QString &value)
{
    idProject = value;
}

void Regression::setFieldEnabled(bool b){
    ui->pushButton_3->setEnabled(b);
    ui->lineEditPopSize->setEnabled(b);
    ui->lineEditLoadKernel->setEnabled(b);
    ui->comboBox->setEnabled(b);
    ui->lineEditNumberElitists->setEnabled(b);
    ui->comboBox_2->setEnabled(b);
    ui->lineEditPar1->setEnabled(b);
    ui->lineEditPar2->setEnabled(b);
    ui->lineEditCrossoverP->setEnabled(b);
    ui->lineEditMutationP->setEnabled(b);
    ui->lineEdit_seed->setEnabled(b);
    ui->tableWidgetMin1->setEnabled(b);
    ui->tableWidget1->setEnabled(b);
    ui->tableWidgetLin->setEnabled(b);



}

void Regression::disableCheckBoxLastGeneration(){
    ui->checkBox_lastgeneration->setEnabled(false);
}


void Regression::on_checkBox_lastgeneration_clicked()
{
    if(ui->checkBox_lastgeneration->isChecked())
    {
        QVariantList listParameter = w->getXmlmanager()->getAllElementsFromProjectName(idProject);
        setParameters(listParameter);
        setFieldEnabled(false);
    }else{
         setFieldEnabled(true);
    }
}

void Regression::on_lineEditPopSize_textChanged(const QString &arg1)
{
    ui->lineEditNumberElitists->setValidator(new QIntValidator(1, ui->lineEditPopSize->text().toInt(), this));
    QString tmp = ui->lineEditPopSize->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditPopSize->setText(tmp);
    if(ui->lineEditNumberElitists->text().toInt() > ui->lineEditPopSize->text().toInt())
    {
        ui->lineEditNumberElitists->setText(QString::number(ui->lineEditPopSize->text().toInt()));
    }
}

void Regression::on_lineEditNumberElitists_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditNumberElitists->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditNumberElitists->setText(tmp);
}

void Regression::on_lineEditCrossoverP_textChanged(const QString &arg1)
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

void Regression::on_lineEditMutationP_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditMutationP->text();
    QString tmp3 =  tmp.remove(',');
    tmp3 =  tmp.remove('e');
    ui->lineEditMutationP->setText(tmp3);

    if(tmp.toDouble() > 1)
    {
        ui->lineEditMutationP->setText("");
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

void Regression::on_lineEditNumProc_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditNumProc->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditNumProc->setText(tmp);
}

void Regression::on_lineEdit_seed_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEdit_seed->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEdit_seed->setText(tmp);
}

void Regression::on_lineEdit_frequencyPop_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEdit_frequencyPop->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEdit_frequencyPop->setText(tmp);
}

void Regression::on_lineEditMaxNumIte_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditMaxNumIte->text();
    tmp.remove('.');tmp.remove(',');
    ui->lineEditMaxNumIte->setText(tmp);
    ui->lineEdit_frequencyPop->setValidator(new QIntValidator(0, ui->lineEditMaxNumIte->text().toInt(), this));
    if(ui->lineEdit_frequencyPop->text().toInt() > ui->lineEditMaxNumIte->text().toInt())
    {
        ui->lineEdit_frequencyPop->setText(QString::number(ui->lineEditMaxNumIte->text().toInt()-1));
    }
}

void Regression::on_lineEditPar1_textChanged(const QString &arg1)
{
    QString tmp = ui->lineEditPar1->text();
    cout << "tmp      --------------- >    " << tmp.toStdString() << endl;

    if(ui->comboBox_2->currentIndex() ==0 ){  // 0.55 - 1 Tr
        QString tmp3 =  tmp.remove(',');
        tmp3 =  tmp.remove('e');
        ui->lineEditPar1->setText(tmp3);
        if(tmp.toDouble() > 1)
        {
            ui->lineEditPar1->setText("");
        }
        if(tmp.contains('.') && (tmp != "2." || tmp != "1.") ){
            QString tmp1 = tmp.mid(0,2);
            QString tmp2 = tmp.mid(2);
            tmp2.remove('.');tmp2.remove(',');
            ui->lineEditPar1->setText(tmp1+tmp2);
        }
    }else
        if(ui->comboBox_2->currentIndex() ==1 ){ // Det 2<= Ts <=N
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
            if(ui->comboBox_2->currentIndex() ==2 ){// 0 < s <= 2
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
                if(ui->comboBox_2->currentIndex() ==4 ){// 1 < p <= 2
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

bool Regression::checkValueSelectionParameter(){

    QString tmp = ui->lineEditPar1->text();
    if(ui->comboBox_2->currentIndex() ==0 ){  // 0.55<= - <=1 Tr


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
        if(ui->comboBox_2->currentIndex() == 1 ){ // Det 2<= - <=N
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
            if(ui->comboBox_2->currentIndex() ==2 ){// 0 < s < 1
                if(tmp == "2." || tmp == "1."){
                    ui->lineEditPar1->setText("1.01");
                    QString error = QString("The s invalid value. \n");

                    QMessageBox::information(
                                this,
                                tr(QString("Warning").toStdString().c_str()),
                                tr(error.toStdString().c_str()) );
                     return true;
                }

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
                if(ui->comboBox_2->currentIndex() ==4 ){ //  1 < p <= 2
                    if(tmp == "2." || tmp == "1."){
                        ui->lineEditPar1->setText("1.01");
                        QString error = QString("The p invalid value. \n");

                        QMessageBox::information(
                                    this,
                                    tr(QString("Warning").toStdString().c_str()),
                                    tr(error.toStdString().c_str()) );
                         return true;
                    }

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

                }

     return false;
}
