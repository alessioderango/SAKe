#ifndef REGRESSIONCONTROLLER_H
#define REGRESSIONCONTROLLER_H
#include <iostream>
#include <QObject>
#include <QThread>
#include "parameters.h"
#include "CustomPlotRegression.h"
#include "CustomPlotItem.h"
using namespace std;


// eo general include
#include "eo"
// the real bounds (not yet in general eo include)
#include "utils/eoRealVectorBounds.h"

// include here whatever specific files for your representation
// Basically, this should include at least the following

/** definition of representation:
 * class eoOneMax MUST derive from EO<FitT> for some fitness
 */
#include "eoOneMax.h"

/** definition of initilizqtion:
 * class eoOneMaxInit MUST derive from eoInit<eoOneMax>
 */
#include "eoOneMaxInit.h"

/** definition of evaluation:
 * class eoOneMaxEvalFunc MUST derive from eoEvalFunc<eoOneMax>
 * and should test for validity before doing any computation
 * see tutorial/Templates/evalFunc.tmpl
 */
#include "eoOneMaxEvalFunc.h"

// GENOTYPE   eoOneMax ***MUST*** be templatized over the fitness

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// START fitness type: double or eoMaximizingFitness if you are maximizing
//                     eoMinimizingFitness if you are minimizing
//typedef eoMinimizingFitness MyFitT ;	// type of fitness
typedef eoMaximizingFitness MyFitT ;	// type of fitness
// END fitness type
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// Then define your EO objects using that fitness type
typedef eoOneMax<MyFitT> Individual;      // ***MUST*** derive from EO

// create an initializer
#include "make_genotype_OneMax.h"

// and the variation operaotrs
#include "make_op_OneMax.h"

// Use existing modules to define representation independent routines
// These are parser-based definitions of objects

// how to initialize the population
// it IS representation independent if an eoInit is given
#include <do/make_pop.h>

// the stopping criterion
#include <Regression/make_continue_my.h>

// outputs (stats, population dumps, ...)
#include <Regression/make_checkpoint_my.h>

#include <Regression/make_algo_scalar_my.h>

// simple call to the algo. stays there for consistency reasons
// no template for that one
#include <do/make_run.h>
// the instanciating fitnesses
#include <eoScalarFitness.h>

// checks for help demand, and writes the status file
// and make_help; in libutils
void make_help(eoParser & _parser);

class RegressionController: public QThread
{
    Q_OBJECT
public:
    RegressionController(    QString projectName,
                             double* percentualePeso,
                             double* percentualeLineareA,
                             double* percentualeLineareB,
                             double* percentualeGammaA,
                             double* percentualeGammaB,
                             double *weights,
                             int weightsSize,
                             int *functionTypes,
                             int functionTypesSize,
                             Parameters *parameters,
                             int parametersSize,
                             int sizeKernel,
                             double *kernel,
                             int iselectionElitist,
                             int ipopulationSize,
                             int imaxGeneration,
                             double dpercentageCrossover,
                             double dpercentageMutation,
                             int inumberProcessor,
                             double * percantageTranslation);
    RegressionController();
    CustomPlotItem *getQCustomPlotFitness() const;
    void setQCustomPlotFitness(CustomPlotItem *value);


    QObject *getProgressBar() const;
    void setProgressBar(QObject *value);

    QObject *getCurrentMaximumFitness() const;
    void setCurrentMaximumFitness(QObject *value);

    QObject *getAbsoluteMaximumFitness() const;
    void setAbsoluteMaximumFitness(QObject *value);

    QObject *getCurrentAverageFitness() const;
    void setCurrentAverageFitness(QObject *value);

    QObject *getAbsoluteAverageFitness() const;
    void setAbsoluteAverageFitness(QObject *value);

    int getNumberProcessor() const;
    void setNumberProcessor(int value);

    Update *getUpdate() const;
    void setUpdate(Update *value);

    CustomPlotRegression *getQCustomPlotRegression();
    void setQCustomPlotRegression(CustomPlotRegression *value);

    std::vector<double> getX();
    void setX(std::vector<double> &value);

    std::vector<double> getY();
    void setY(std::vector<double> &value);

public slots:
    void startThread();
    void startAlgorithm();
     void stopThread();
private:
    void run();
    bool start;
    bool finish;

    int numberProcessor;
    eoGenContinueMy<Individual> *stop;

    //Parameters Algorithm
    double* percentualePeso;
    int percentualePesoSize;
    double* percentualeLineareA;
    int percentualeLineareASize;
    double* percentualeLineareB;
    int percentualeLineareBSize;
    double* percentualeGammaA;
    int percentualeGammaASize;
    double* percentualeGammaB;
    int percentualeGammaBSize;

    double *weights;
    int weightsSize;
    int *functionTypes;
    int functionTypesSize;
    Parameters *parameters;
    int parametersSize;
    int sizeKernel;
    double *kernel;
    Update *update;
    CustomPlotItem *qCustomPlotFitness;
    CustomPlotRegression *qCustomPlotRegression;
    QObject *progressBar;
    QObject *currentMaximumFitness;
    QObject *absoluteMaximumFitness;
    QObject *currentAverageFitness;
    QObject *absoluteAverageFitness;

    int selectionElitist;
    int populationSize;
    int maxGeneration;
    double percentageCrossover;
    double percentageMutation;
    double* translation;
    std::vector< double> x;
    std::vector< double> y;

    QString savePath;

};

#endif // REGRESSIONCONTROLLER_H
