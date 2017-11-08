#ifndef REGRESSION_H
#define REGRESSION_H

#include <QDialog>
#include <QMessageBox>
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

private:
    Ui::Regression *ui;
    MainWindow *w;
};

#endif // REGRESSION_H
