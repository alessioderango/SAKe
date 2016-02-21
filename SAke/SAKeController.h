#ifndef SAKECONTROLLER_H
#define SAKECONTROLLER_H
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

// GENOTYPE   eoSAKe ***MUST*** be templatized over the fitness

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// START fitness type: double or eoMaximizingFitness if you are maximizing
//                     eoMinimizingFitness if you are minimizing
typedef eoMaximizingFitness MyFitT ;	// type of fitness

typedef eoSAKe<MyFitT> Indi;      // ***MUST*** derive from EO

#include "SAke/make_genotype_SAKe.h"
#include "SAke/make_op_SAKe.h"
#include <do/make_pop.h>
#include "SAke/make_continue_my.h"
//#include <do/make_checkpoint.h>
#include "make_algo_scalar_my.h"
#include <do/make_run.h>
#include <eoScalarFitness.h>
void make_help(eoParser & _parser);


//#include <utils/eoParallel.h>
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
    SAKeController(CustomPlotItem *& qCustomPlot,
                   QString  sselection,
                   QString  spattern,
                   QString  filename,
				   QString  filenameActivaion,
				   QString  filenameSavePath,
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
                   int maxNumberToConsider,
                   Update* update);




    void setPlotMobility(CustomPlotMobilityFunction *value);

    void setApplication(QApplication * _a);
    CustomPlotKernel *getPlotkernel() const;
    void setPlotkernel(CustomPlotKernel *value);
    void setProgressBar(QObject* progressBar);
protected:

public slots:
    void startThread();
    void stopThread(QQuickCloseEvent * selection);
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
    float    propCrossover;
    float    propMutation;
    float    pme;
    float    pmb;
    int maxNumberToConsider;
    int numberofProcessor;
    QString  savePath;
    QApplication * a;
    Update* update;

};

#endif // SAKCONTROLLER_H
