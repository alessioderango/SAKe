#ifndef REGRESSION_H
#define REGRESSION_H

#include <QDialog>
#include <QMessageBox>
#include <controlpoints.h>
#include "mainwindow.h"


namespace Ui {
class Regression;
}

class Regression : public QDialog
{
    Q_OBJECT

public:
    explicit Regression(MainWindow * _w,QWidget *parent = 0);
    Regression(QWidget *parent =0);
    ~Regression();
    MainWindow *getW() const;
    void setW(MainWindow *value);
    void setParameters(QVariantList );
    void setReadOnlyProjName(bool );



    QString getIdProject() const;
    void setIdProject(const QString &value);
    void setFieldEnabled(bool);
    void disableCheckBoxLastGeneration();
    void hideTableFirstGamma();



private slots:

    void cellSelected(int nRow, int nCol);

    void on_lineEdit_8_textChanged(const QString &arg1);

    void on_lineEdit_10_textChanged(const QString &arg1);

    void on_lineEdit_9_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_checkBox_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    bool checklineEdit(QString l, QString s);
    void on_comboBoxReplacement_currentIndexChanged(int index);

    void on_lineEditN_textChanged(const QString &arg1);

    void on_checkBox_kernel_stateChanged(int arg1);

    void on_checkBox_controlpoints_stateChanged(int arg1);

    void on_checkBox_N_stateChanged(int arg1);

    void on_comboBoxSelection_currentIndexChanged(int index);

    void on_checkBox_lastgeneration_clicked();

private:
    Ui::Regression *ui;
    MainWindow *w;

    std::vector<double> kernel;
    int size_kernel;
    double Delta_cr;

    ControlPoints * controlPoints;
    std::vector<double> xControlpoints;
    std::vector<double> yControlpoints;

    std::vector< double> xControlpointsbyN;
    std::vector< double> yControlpointsbyN;

    QString idProject;



};

#endif // REGRESSION_H
