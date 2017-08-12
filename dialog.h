#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <iostream>
#include <SAke/SAKeController.h>
#include "mainwindow.h"
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

private:
    Ui::Dialog *ui;
    QTabWidget * tab;
    MainWindow *mainWindow;
};

#endif // DIALOG_H
