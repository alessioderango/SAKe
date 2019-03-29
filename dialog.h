#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <iostream>
#include <SAke/SAKeController.h>
#include "mainwindow.h"
#include <myvalidatordouble.h>
using namespace std;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);

    ~Dialog();
    void setParameters(QVariantList a);
    void setReadOnlyProjName(bool a);

    Ui::Dialog *getUi() const;

    QTabWidget *getTab() const;
    void setTab(QTabWidget *value);
    QString getProjectName();

    MainWindow *getMainWindow() const;
    void setMainWindow(MainWindow *value);
    bool checklineEdit(QString l, QString s);
    bool checklineEditRangeDouble(QString l, double max, double min, QString s);
    bool checklineEditRangeInt(QString l, int max, int min, QString s);
    bool checkValueSelectionParameter();


    QString getIdProject() const;
    void setIdProject(const QString &value);
    void setFieldEnabled(bool);


private slots:

    void on_pushButton_clicked();

    void configComboBox2(int currentIndex);

    void configComboBox3(int currentIndex);
    void on_selectOrder1_currentIndexChanged(int index);

    void on_selectOrder2_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_pushButtonStart_clicked();

    void on_comboBoxSelection_currentIndexChanged(int index);

    void on_comboBoxReplacement_currentIndexChanged(int index);

    void on_lineEditPopSize_textChanged(const QString &arg1);


    void on_comboBoxFitness_currentIndexChanged(int index);

    void on_checkBoxContinueFromLastGen_clicked();

    void on_lineEditNumberElitists_textChanged(const QString &arg1);

    void on_lineEditPmb_textChanged(const QString &arg1);

    void on_lineEditPme_textChanged(const QString &arg1);

    void on_lineEditTbMin_textChanged(const QString &arg1);

    void on_lineEditTbMax_textChanged(const QString &arg1);

    void on_lineEditdHpMax_textChanged(const QString &arg1);

    void on_lineEditNumberOfLines_textChanged(const QString &arg1);

    void on_lineEditMaxNumIte_textChanged(const QString &arg1);

    void on_lineEditNumProc_textChanged(const QString &arg1);

    void on_lineEditFrequKerSav_textChanged(const QString &arg1);

    void on_lineEditSeed_textChanged(const QString &arg1);

    void on_lineEditNumBestKernelSaved_textChanged(const QString &arg1);

    void on_lineEditCrossoverP_textChanged(const QString &arg1);

    void on_lineEditMutationP_textChanged(const QString &arg1);

    void on_lineEditPar1_textChanged(const QString &arg1);


signals:
    void showAlertInputCsv(int row,QString a,  QString e);

private:



    Ui::Dialog *ui;
    QTabWidget * tab;
    MainWindow *mainWindow;
    QString idProject;
};

#endif // DIALOG_H
