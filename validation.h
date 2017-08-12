#ifndef VALIDATION_H
#define VALIDATION_H

#include <QDialog>
#include <QFileDialog>
#include <SAke/Ym.h>
#include <SAke/Activation.h>
#include <SAke/Rain.h>
#include <ValidationController.h>
#include <HandlerCSV.h>
#include <mainwindow.h>

namespace Ui {
class Validation;
}

class Validation : public QDialog
{
    Q_OBJECT

public:
    explicit Validation(QWidget *parent = 0);
    ~Validation();

    MainWindow *getMainWindow() const;
    void setMainWindow(MainWindow *value);
    void setReadOnlyProjName(bool a);
    void setParameters(QVariantList list);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Validation *ui;
    MainWindow *mainWindow;
};

#endif // VALIDATION_H
