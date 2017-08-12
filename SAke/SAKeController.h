#ifndef SAKECONTROLLER_H
#define SAKECONTROLLER_H

#include <utils/eoParallel.h>
#include "SAke/eoSAKeEvalFunc.h"
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
#include "updateprojects.h"
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
#include "SAke/make_continue_my.h"
//#include <do/make_checkpoint.h>
#include "make_algo_scalar_my.h"
#include <do/make_run.h>
#include <eoScalarFitness.h>
void make_help(eoParser & _parser);



#include <QObject>
#include <QtQuick>
#include "CustomPlotItem.h"
#include "CustomPlotMobilityFunction.h"
#include "CustomPlotKernel.h"
#include "make_checkpoint_my.h"
#include "SAke/eoGenContinueMy.h"
#include "update.h"

using namespace eo;

class SAKeController: public QThread
{
       Q_OBJECT

public:
    SAKeController(
                   QString  sselection,
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
                   QObject *_currentMaximumFitness,
                   QObject *_absoluteMaximumFitness,
                   QObject *_currentAverageFitness,
                   QObject *_absoluteAverageFitness,
                   int numberofProcessor,
                   int para1,
                   int para2,
                   QString spara1,
                   bool _lastGeneration,
                   Update* update,
                   const QString& projectName,
                   vector<QString> orders,
                   int itypeAlgorithm,
                   int numberElitist,
                   int seed,
                   int saveKernels);

    SAKeController();


    void setPlotMobility(CustomPlotMobilityFunction *value);

    void setApplication(QApplication * _a);
    CustomPlotKernel *getPlotkernel() const;
    void setPlotkernel(CustomPlotKernel *value);
     void setPlotGenerations(CustomPlotItem *value);
    void setProgressBar(QObject* progressBar);
    int getCsvHandlerstatusRain() const;
    void setCsvHandlerstatusRain(int value);

    float getPropSelection() const;
    void setPropSelection(float value);

protected:

public slots:
    void startThread();
    void stopThread();
private:
    void run();
    void startAlgorithm();
    bool start;
    bool finish;
    //Graphs
    CustomPlotItem *qCustomPlot;
    CustomPlotMobilityFunction * plotMobility;
    CustomPlotKernel * plotkernel;
    QObject *progressBar;
    QObject *currentMaximumFitness;
    QObject *absoluteMaximumFitness;
    QObject *currentAverageFitness;
    QObject *absoluteAverageFitness;


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
    float    relRateCrossover;
    float    relRateMutation;
    float    propSelection;
    float    propCrossover;
    float    propMutation;
    float    pme;
    float    pmb;
    int maxNumberToConsider;
    int numberofProcessor;
    bool lastGeneration;
    QString  savePath;
    QApplication * a;
    Update* update;

    unsigned int typeAlgorithm;
    double parameter1;
    double parameter2;
    SelectionStrategy<Indi> ** selectionStrategy;
    int csvHandlerstatusRain;

    int seed;
    int saveKernels;
};

#endif // SAKCONTROLLER_H
