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
    m_TableHeader<<"N."<<"a min"<<"a max"<< "B min" << "B max" << "Weight min"<< "Weight max" << "Perc a" << "Perc b" << "Perc weight";
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

    MainWindow::makeKernelPlot(ui->kernelPlot,w);
    //ui->kernelPlot->setSizePolicy(spUp);
    ui->kernelPlot->setObjectName("kerFunc");


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
