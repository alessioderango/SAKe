#ifndef VALIDATIONCONTROLLER_H
#define VALIDATIONCONTROLLER_H
#include <QObject>
#include "SAke/Rain.h"
#include "SAke/Activation.h"
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <QThread>
#include "handlercsv.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/local_time_adjustor.hpp"
#include "boost/date_time/c_local_time_adjustor.hpp"
#include <SAke/Ym.h>
#include "qcustomplot.h"
#include <mainwindow.h>

using namespace std;
using boost::posix_time::ptime;
using namespace boost::gregorian;
using namespace boost::posix_time;



class ValidationController : public QThread
{
    Q_OBJECT
public:
    ValidationController(Rain *  rain,
            int  rain_size,
            Activation *  activations,
            int  activations_size,
            std::vector<double> &Fi,
            int size,
            double zCr
            );

    void startThread();
    Rain *getRain() const;
    void setRain(Rain *value);

    Activation *getActivations() const;
    void setActivations(Activation *value);

    int getRain_size() const;
    void setRain_size(int value);

    int getActivations_size() const;
    void setActivations_size(int value);

    QObject *getTb() const;
    void setTb(QObject *value);

    QObject *getDeltaCritico() const;
    void setDeltaCritico(QObject *value);


    QObject *getMomentoDelPrimoOrdine() const;
    void setMomentoDelPrimoOrdine(QObject *value);

    QObject *getFitness() const;
    void setFitness(QObject *value);

    void startValidation();
    void startValidationAllinOne(QString namePlot);


    void startValidationAUCROC(QString AUCROC);

    vector<vector<QCPItemText*>> widgetArray;
    vector<vector<QCPItemLine*>> arrowArray;

    MainWindow *getMainwindows() const;
    void setMainwindows(MainWindow *value);

    void setFt(const FitnessType &value);

    void getMobilityFunction(std::vector<double>&  Y, std::vector<Ym> &ym);
    
signals:
    void updateMobPlot(int indexTab,
                       Rain * rain,
                       int rain_size,
                       Activation * a,
                       int act_size,
                       std::vector<double> Y,
                       double,
                       tm,
                       double,
                       tm,
                       std::vector<Ym> bests,
                       std::vector<QCPItemText*> widgetArray,
                       std::vector<QCPItemLine*> arrowArray);
    void updateMobPlotAllInOne(int indexTab,
                       QString namePlot,
                       Rain * rain,
                       int rain_size,
                       Activation * a,
                       int act_size,
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
    void updateROCPlot(int indexTab,
                            QVector<double> FPR,
                            QVector<double> TPR,
                            double AUCROC);

private:
    void run();

    QObject *tb;
    QObject *deltaCritico;
    QObject *momentoDelPrimoOrdine;
    QObject *fitness;

    std::vector<double> Fi;
    int size;
    Rain * rain;
    int rain_size;
    Activation * activations;
    int activations_size;
    double zCr;
MainWindow *mainwindows;
    FitnessType ft;


};

#endif // VALIDATIONCONTROLLER_H
