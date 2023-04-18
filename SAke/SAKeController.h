#ifndef SAKECONTROLLER_H
#define SAKECONTROLLER_H

#include <utils/eoParallel.h>
#include "SAke/eoSAKeEvalFunc.h"
#include "SAke/eoSAKeEvalFuncEqualWeights.h"
#include "SAke/eoSAKeEvalFuncAUCROC.h"
#include "SAke/eoSAKeEvalFuncGMDn.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
//#include "db/DBmanager.h"
#include "eo"
#include "utils/eoRealVectorBounds.h"
#include "eoSAKe.h"
#include "eoSAKeInit.h"
//#include "SAke/eoParallelMy.h"
#include "handlercsv.h"

// GENOTYPE   eoSAKe ***MUST*** be templatized over the fitness

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// START fitness type: double or eoMaximizingFitness if you are maximizing
//                     eoMinimizingFitness if you are minimizing
typedef eoMaximizingFitness MyFitT ;	// type of fitness

typedef eoSAKe<MyFitT> Indi;      // ***MUST*** derive from EO

#include "SAke/make_genotype_SAKe.h"
#include "SAke/make_op_SAKe.h"
#include "make_pop_my.h"

#include "make_algo_scalar_my.h"
#include <do/make_run.h>
#include <eoScalarFitness.h>
#include "mainwindow.h"


void make_help(eoParser & _parser);

template< class EOT>
class eoGenContinueMy;


#include <QObject>
//


using namespace eo;

class SAKeController: public QThread
{
    Q_OBJECT

public:
    SAKeController(MainWindow *main,
                   QString  sselection,
                   QString  replacement,
                   QString  spattern,
                   Rain *rain,
                   int rain_size,
                   Activation * activation,
                   int activation_size,
                   int      ipop,
                   int      imaxGen,
                   int      itbMax,
                   int      itbMin,
                   int      idHpMax,
                   int      idHpMin,
                   float    fpropCrossover,
                   float    fpropMutation,
                   float    fpme,
                   float    fpmb,
                   int numberofProcessor,
                   float para1,
                   float para2,
                   bool _lastGeneration,
                   const QString& projectName,
                   vector<QString> orders,
                   int itypeAlgorithm,
                   int numberElitist,
                   int seed,
                   int saveKernels, int numberOfKernelToBeSaved, int numberOfLines);
    static bool fileExists(QString path);
    SAKeController();
    bool finish;
    void setProgressBar(QObject* progressBar);
    int getCsvHandlerstatusRain() const;
    void setCsvHandlerstatusRain(int value);
    vector<QCPItemText *> getWidgetArray() const;
    void setWidgetArray(const vector<QCPItemText *> &value);

    vector<QCPItemLine *> getArrowArray() const;
    void setArrowArray(const vector<QCPItemLine *> &value);
    vector<QCPItemText*> widgetArray;
    vector<QCPItemLine*> arrowArray;
    bool getClickCloseTab() const;
    void setClickCloseTab(bool value);

    MainWindow *getMainwindows() const;
    void setMainwindows(MainWindow *value);

    void setFt(int value);

    QString getSavePath() const;

    int getMaxGen() const;
    void setMaxGen(int value);

signals:
    void finished(int index);
    void updateMobPlot(int indexTab,
                       Rain * rain,
                       int rain_size,
                       Activation *activation,
                       int activation_size,
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
                           QVector<double> y1,
                           int numGenerations,
                           bool b);

    void updateKernelPlot(int indexTab,
                          QVector<double> Fi,
                          int tb);
    void updateROCPlot(int indexTab,
                            QVector<double> FPR,
                            QVector<double> TPR,
                            double AUCROC);
    void updateTextsBestAbsolute(int indexTab,
                                 QString tbBestAbsolute,
                                 QString safetyMarginBestAbsolute,
                                 QString momentumBestAbsolute,
                                 QString ZjminBestAbsolute,
                                 QString ZcrBestAbsolute);
    void updateTexts(int indexTab,
                     QString s,
                     QString fitness,
                     QString cuavfitness,
                     QString tb,
                     QString Zjmin,
                     QString Zcr,
                     QString safetyMargin,
                     QString momentum,
                     int barValur,
                     int firstOccurence,
                     QString abmaxfitness,
                     QString avmaxfitnes,
                     QString tbBest,
                     QString safetyMarginBest,
                     QString momentumBest,
                     QString ZjminBest,
                     QString ZcrBest);

    void updateAbsMaxFit(int indexTab, QString s);
    void updateAbsAvFit(int indexTab, QString s);
    void updateTableROCPlot(int indexTab,
                       QVector<int> TP,
                       QVector<int> FP,
                       QVector<int> TN,
                       QVector<int> FN);


protected:

public slots:
    void startThread();
    void restartThread();
    void stopThread();
    bool getStop();
private:
    void run();
    void startAlgorithm();
    bool start;
    //bool finish;

    //Plot temporary info


    //stop algorithm
    eoGenContinueMy<Indi> *stop;
    Rain * rain;
    int rain_size;
    //DBmanager db;
    Activation * activations;
    int activations_size;

    //Parameters Algorithm
    QString  selection;
    QString  replacement;
    QString  pattern;
    int      pop;
    int      maxGen;
    int      tbMax;
    int      tbMin;
    int      dHpMax;
    int      dHpMin;

    float    propCrossover;
    float    propMutation;
    float    pme;
    float    pmb;
    int maxNumberToConsider;
    int numberofProcessor;
    bool lastGeneration;
    QString  savePath;

    unsigned int typeAlgorithm;
    double parameter1;
    double parameter2;
    SelectionStrategy<Indi> ** selectionStrategy;
    int csvHandlerstatusRain;

    int seed;
    int saveKernels;
    int numberOfKernelToBeSaved;
    bool clickCloseTab;
    MainWindow *mainwindows;
    FitnessType ft;
    int numberOfLines;



};

#endif // SAKCONTROLLER_H
