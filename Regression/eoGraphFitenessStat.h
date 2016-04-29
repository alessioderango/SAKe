#ifndef EOGRAPHFITENESSSTAT_H
#define EOGRAPHFITENESSSTAT_H

#include <numeric> // accumulate

#include <eoFunctor.h>
#include <utils/eoParam.h>
#include <eoPop.h>
#include <utils/eoMonitor.h>
//#include <utils/eoCheckPoint.h>
#include <utils/eoLogger.h>
#include <utils/eoStat.h>
#include "CustomPlotItem.h"
#include "CustomPlotMobilityFunction.h"
#include "CustomPlotKernel.h"
#include "CustomPlotRegression.h"
#include "update.h"



template <class EOT>
class eoGraphFitnessStat : public eoStat<EOT,  typename EOT::Fitness>
{

public:

    using eoStat<EOT, typename EOT::Fitness>::value;

    typedef typename EOT::Fitness Fitness;

    eoGraphFitnessStat(int _maxGen,
                       QObject *_progressBar,
                       CustomPlotItem *& _qCustomPlot,
                       CustomPlotRegression *& _qCustomPlotRegression,
                       QObject *_currentMaximumFitness,
                       QObject *_absoluteMaximumFitness,
                       QObject *_currentAverageFitness,
                       QObject *_absoluteAverageFitness,
                       Update* _update,
                       std::vector< double> _xRegression,
                       std::string _description = "Best ")
                       : eoStat<EOT, Fitness>(Fitness(), _description)
    {
        qCustomPlot=_qCustomPlot;
        qCustomPlotRegression=_qCustomPlotRegression;
        xRegression = _xRegression;
        progressBar = _progressBar;
        count=0;
        steps= 1;
        maxGen = _maxGen;
        currentMaximumFitness=_currentMaximumFitness;
        absoluteMaximumFitness=_absoluteMaximumFitness;
        currentAverageFitness= _currentAverageFitness;
        absoluteAverageFitness=_absoluteAverageFitness;
        AbsoluteMaximumFitness=0;
        AbsoluteAvarageFitness=0;
        update=_update;
        //dsakecontroller =_sakecontroller;
    }

    void operator()(const eoPop<EOT>& _pop) {
        doit(_pop, Fitness() ); // specializations for scalar and std::vector
    }

    static Fitness sumFitness(double _sum, const EOT& _eot){
        _sum += _eot.fitness();
        return _sum;
    }


    virtual std::string className(void) const { return ""; }


private :
    // default
    template<class T>
    void doit(const eoPop<EOT>& _pop, T)
    { // find the largest elements
      //value() = _pop.best_element().fitness();

       count++;
       double fitness =_pop.best_element().fitness();

       yBest.push_back( _pop.best_element().fitness());
       x.push_back(count);

       Fitness v = std::accumulate(_pop.begin(), _pop.end(), Fitness(0.0), eoGraphFitnessStat::sumFitness);

       yAverage.push_back( v / _pop.size());
       qCustomPlot->updateGraph0(x,yBest);
       qCustomPlot->updateGraph1(x,yAverage);

       qCustomPlotRegression->updateGraph1(QVector<double>::fromStdVector(xRegression),QVector<double>::fromStdVector(_pop.best_element().getYCombinataConst()));

       QString genString= QString("Gen:    %1").arg(steps);
       Q_EMIT update->valueGenRegression(genString);
       QString currentMaxiumFitness= QString("Current Maximum Fitness:    %1").arg(fitness );
       Q_EMIT update->valueCurrentMaximumFitnessRegression(currentMaxiumFitness);
       QString currentAvarageFitness= QString("Current Average Fitness:    %1").arg( v / _pop.size() );
       Q_EMIT update->valueCurrentAvarageFitnessRegression(currentAvarageFitness);
       if(AbsoluteAvarageFitness < ( v / _pop.size())){
           QString tmpAvarage= QString("Absolute Average Fitness:       %1").arg( v / _pop.size() );
           Q_EMIT update->valueAbsoluteAvarageFitnessRegression(tmpAvarage);
           AbsoluteAvarageFitness=( v / _pop.size());
       }

       if(AbsoluteMaximumFitness < fitness){
           QString tmpAvarage= QString("Absolute Maximum Fitness:    %1").arg(fitness );
           Q_EMIT update->valueAbsoluteMaximumFitnessRegression(tmpAvarage);
           AbsoluteMaximumFitness=fitness;
       }

       steps++;
//       cout << (steps*100)/maxGen << endl;
       progressBar->setProperty("value",((steps*100)/maxGen));

    }
    int count;
    QVector<double> x;
    QVector<double> yBest;
    QVector<double> yAverage;
    CustomPlotItem * qCustomPlot;
    CustomPlotRegression * qCustomPlotRegression;

    QObject *progressBar;
    QObject *currentMaximumFitness;
    QObject *absoluteMaximumFitness;
    QObject *currentAverageFitness;
    QObject *absoluteAverageFitness;

    int steps ;
    int maxGen;

    Update* update;
    double AbsoluteMaximumFitness;
    double AbsoluteAvarageFitness;
    std::vector< double> xRegression;
};
#endif // EOGRAPHFITENESSSTAT_H
