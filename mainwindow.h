#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TreeModel.h"
#include <QTreeWidget>
#include "xmlmanager.h"
#include "qcustomplot.h"
#include "Rain.h"
#include "HandlerCSV.h"
#include <QThread>
#include "SAke/Ym.h"
#include <QMutex>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QTabWidget* getTabbyPos(int pos);
    explicit MainWindow(QWidget *parent = 0);
    void makeFitnessPlot(QCustomPlot * customPlot);

    void makeAUCROCPlot(QCustomPlot * customPlot);
    void makeDETPlot(QCustomPlot * customPlot);

    void makeMobilityFunctionPlot(QCustomPlot * customPlot,Rain * rain, int rain_size, Activation *activation, int activation_size);

    static void makeKernelPlot(QCustomPlot * customPlot, MainWindow *w);
    void updateMobilityKernelPlot(QCustomPlot * customPlot);
    void updateKernelPlotRegression(QCustomPlot *m_CustomPlot, QVector<double> xKernel,QVector<double> yKernel,QVector<double> xControlpoints,QVector<double> yControlpoints );
    void updateKernelPlotRegressionWithControlPoints(QCustomPlot *m_CustomPlot,QVector<double> xControlpoints,QVector<double> yControlpoints );
    static void pushBackThread(QThread *thread);
    void addTab(QString name, Rain *rain, int rain_size, Activation *activation, int activation_size);
    void addTabRegression(QString name);
    void addTabAUCROC(QString name, Rain *rain, int rain_size, Activation *activation, int activation_size);
    void addTabValidation(QString name, Rain *rain, int rain_size, Activation *activation, int activation_size);
    void addTabValidationNewInterface(QString name, Rain *rain, int rain_size, Activation *activation, int activation_size);


    ~MainWindow();

    Ui::MainWindow *getUi() const;
    static std::vector<QThread *> threads;

    QCustomPlot *getPlotMobility(int indexTab, QString objName);
    QCustomPlot* getFitnessPlot(int indexTab);
    QCustomPlot *getKernelPlot(int indexTab);
    QCustomPlot* getAUCROCPlot(int indexTab);
    XMLManager *getXmlmanager() const;
    void setXmlmanager(XMLManager *value);
    void showLoadingWheel();


    QMutex mutex;

    void getGraphs(QString nameKerFunc, QString nameMobFunc, QString fitness,auto* mainL, Rain* rain, int rain_size, int activation_size, Activation *activation, QCustomPlot* mobFunc);
    
private slots:
    void on_newCalibrationProject_triggered();

    void myClick(QTreeWidgetItem * item, int column);

    void on_tabWidget_2_tabCloseRequested(int index);
    void closeTab(int index);
    void updateMobPlot(int indexTab,
                                    Rain * rain,
                                    int rain_size,
                                    Activation *,
                                    int,
                                    std::vector<double> Y,
                                    double,
                                    tm,
                                    double,
                                    tm,
                                    std::vector<Ym> bests,
                                    std::vector<QCPItemText*> widgetArray,
                                    std::vector<QCPItemLine*> arrowArray);
    void updateMobPlotAllInOne(int indexTab,
                       QString name,
                       Rain * rain,
                       int rain_size,
                       Activation *,
                       int,
                       std::vector<double> Y,
                       double,
                       tm,
                       double,
                       tm,
                       std::vector<Ym> bests,
                       std::vector<QCPItemText*> widgetArray,
                       std::vector<QCPItemLine*> arrowArray);
    void updateFitnessPlot(int indexTab,
                           QVector<double> x,
                           QVector<double> y,
                           QVector<double> x1,
                           QVector<double> y1);
    void updateKernelPlot(int indexTab,
                           QVector<double> Fi,
                           int tb);

    void updateROCPlot(int indexTab,
                            QVector<double> FPR,
                            QVector<double> TPR,
                            double AUCROC);

    void updateTexts(int indexTab,
                              QString s,
                              QString fitness,
                              QString cuavfitness,
                              QString tb,
                              QString safetyMargin,
                              QString momentum,
                              int barValur,
                              int firstOccurence, QString abmaxfitness, QString avmaxfitness);

    void updateTextsRegression(int indexTab,
                              QString s,
                              QString fitness,
                              QString cuavfitness,
                              int barValur,
                              int firstOccurence, QString abmaxfitness, QString avmaxfitness);

    void updateRegression(int indexTab,
                           QVector<double> x,
                           QVector<double> y,
                           QVector<double> xReal,
                           QVector<double> yReal,
                           int steps);


    void updateTextsValidation(int indexTab,
                              QString fitness,
                              QString tb,
                              QString safetyMargin,
                              QString momentum);
    void updateTextsValidationAllInOne(int indexTab,
                                      QString name,
                               QString fitness,
                               QString tb,
                               QString safetyMargin,
                               QString momentum);
    void updateAbsMaxFit(int indexTab, QString s);
    void updateAbsAvFit(int indexTab, QString s);

    void getMoreInfoROC();

    void on_stopButton_triggered();

    void on_actionNewValidationProject_triggered();
    void prepareMenu( const QPoint & pos );
    void deleteProject(int item);
    void expandTreeViewSlot();
    void resizeMobilityFunction();
    void savePngMobilityFunction();
    void savePdfMobilityFunction();

    void resizeKernel();
    void savePngKernel();
    void savePdfKernel();

    void resizeFitness();
    void savePngFitness();
    void savePdfFitness();

    void resizeAUCROC();
    void savePngAUCROC();
    void savePdfAUCROC();

    void contextMenuRequestMobilityFunction(QPoint pos);
    void contextMenuRequestKernel(QPoint pos);
    void contextMenuRequestFitness(QPoint pos);
    void contextMenuRequestAUCROC(QPoint pos);
    void openFolderProject();
    void showAlertInputCsv(int row, QString filename , QString e);


    void on_actionNew_Regression_Project_triggered();

signals:
     void expandTreeViewSignals();

private:
    Ui::MainWindow *ui;
    XMLManager * xmlmanager;
    QSignalMapper *signalMapper;
    QMenu menu;



};



#endif // MAINWINDOW_H
