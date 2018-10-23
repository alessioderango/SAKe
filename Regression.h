#ifndef REGRESSION_H
#define REGRESSION_H

#include <QDialog>
#include <QMessageBox>
#include <controlpoints.h>
#include <Regression/regressioncontroller.h>
#include "mainwindow.h"

namespace Ui {
class Regression;
}

class Regression : public QDialog
{
    Q_OBJECT

public:
    explicit Regression(MainWindow * _w,QWidget *parent = 0);
    ~Regression();
    MainWindow *getW() const;
    void setW(MainWindow *value);

private slots:

    void cellSelected(int nRow, int nCol);

    void on_lineEdit_8_textChanged(const QString &arg1);

    void on_lineEdit_10_textChanged(const QString &arg1);

    void on_lineEdit_9_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_checkBox_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    bool checklineEdit(QString l, QString s);
private:
    Ui::Regression *ui;
    MainWindow *w;

    std::vector<double> kernel;
    int size_kernel;
    double Delta_cr;

    ControlPoints * controlPoints;
    std::vector< double> xControlpoints;
    std::vector< double> yControlpoints;

};

#endif // REGRESSION_H
