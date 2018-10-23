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
#include "CustomPlotRegression.h"
#include <QtConcurrent/QtConcurrent>


template <class EOT>
class eoGraphFitnessStat : public eoStat<EOT,  typename EOT::Fitness>
{

public:

    using eoStat<EOT, typename EOT::Fitness>::value;

    typedef typename EOT::Fitness Fitness;

    eoGraphFitnessStat(int _maxGen,
                       QObject *_progressBar,
                       QObject *_currentMaximumFitness,
                       QObject *_absoluteMaximumFitness,
                       QObject *_currentAverageFitness,
                       QObject *_absoluteAverageFitness,
                       std::vector< double> _xRegression,
                       std::string _description = "Best ")
        : eoStat<EOT, Fitness>(Fitness(), _description)
    {
        xRegression = _xRegression;
        progressBar = _progressBar;
        count=0;
        steps= 1;
        maxGen = _maxGen;
        currentMaximumFitness=_currentMaximumFitness;
        absoluteMaximumFitness=_absoluteMaximumFitness;
        currentAverageFitness= _currentAverageFitness;
        absoluteAverageFitness=_absoluteAverageFitness;
        AbsoluteMaximumFitness= - 1000000;
        AbsoluteAvarageFitness=-DBL_MIN;
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
        //Sleep(uint(1000));
        count++;
        double fitness =_pop.best_element().fitness();

        yBest.push_back( _pop.best_element().fitness());
        x.push_back(count);

        Fitness v = std::accumulate(_pop.begin(), _pop.end(), Fitness(0.0), eoGraphFitnessStat::sumFitness);

        yAverage.push_back( v / _pop.size());
        //       qCustomPlot->updateGraph0(x,yBest);
        //       qCustomPlot->updateGraph1(x,yAverage);
        QVector<double> xRegretmp(xRegression.size());
        QVector<double> yRegretmp(xRegression.size());
        QVector<Parameters> parameter(_pop.best_element().getFunctionTypeConst().size());
        QVector<int> functiontype(_pop.best_element().getFunctionTypeConst().size());

        for (int i = 0; i < xRegression.size(); i++) {
            xRegretmp[i]=xRegression[i];
            yRegretmp[i]= _pop.best_element().getYCombinataConst()[i];

        }

        for (int i = 0; i < functiontype.size(); ++i) {
            parameter[i]= _pop.best_element().getParConst(i);
            functiontype[i]= _pop.best_element().getFunctionTypeConst(i);
        }



        if(_pop.size() < 200 && steps%50 ==0){
//            p.waitForFinished();
            //qCustomPlotRegression->drawGammaFunctions(xRegretmp,functiontype,parameter);
//            p = QtConcurrent::run(qCustomPlotRegression,qCustomPlotRegression->updateGraph1,xRegretmp,yRegretmp);
//            p.waitForFinished();
            //qCustomPlotRegression->updateGraph1(xRegretmp,yRegretmp);
//            auto p = QtConcurrent::run(xRegretmp,yRegretmp);
//            p.waitForFinished();
//            p = QtConcurrent::run(xRegretmp,functiontype,parameter);
//            p.waitForFinished();
        }
        else
            if(_pop.size() >200){
//                 p = QtConcurrent::run(qCustomPlotRegression,qCustomPlotRegression->updateGraph1,xRegretmp,yRegretmp);
//                 p.waitForFinished();
                //qCustomPlotRegression->updateGraph1(xRegretmp,yRegretmp);
            }



        //       std::cout << "WEIGHT" << std::endl;
        //       for (int i = 0; i < _pop.best_element().getWConst().size(); ++i) {
        //           std::cout << _pop.best_element().getWConst()[i] << std::endl;
        //       }

        //       std::cout << "PARAMETER" << std::endl;
        //       for (int i = 0; i < _pop.best_element().getParConst().size(); ++i) {
        //           std::cout << _pop.best_element().getParConst()[i].getParameters(0) << std::endl;
        //           std::cout << _pop.best_element().getParConst()[i].getParameters(1) << std::endl;
        //       }

        QString genString= QString("Gen:    %1").arg(steps);
//        auto p =QtConcurrent::run(update,update->valueGenRegression,genString);
//        p.waitForFinished();
        //Q_EMIT update->valueGenRegression(genString);
        QString currentMaxiumFitness= QString("Current Maximum Fitness:    %1").arg(fitness );
//        p=QtConcurrent::run(update,update->valueCurrentMaximumFitnessRegression,currentMaxiumFitness);
//        p.waitForFinished();
        //Q_EMIT update->valueCurrentMaximumFitnessRegression(currentMaxiumFitness);
        QString currentAvarageFitness= QString("Current Average Fitness:    %1").arg( v / _pop.size() );
//        p=QtConcurrent::run(update,update->valueCurrentAvarageFitnessRegression,currentAvarageFitness);
//        p.waitForFinished();
        //Q_EMIT update->valueCurrentAvarageFitnessRegression(currentAvarageFitness);
        if(AbsoluteAvarageFitness < ( v / _pop.size())){
            QString tmpAvarage= QString("Absolute Average Fitness:       %1").arg( v / _pop.size() );
//            p=QtConcurrent::run(update,update->valueAbsoluteAvarageFitnessRegression,tmpAvarage);
//            p.waitForFinished();
            //Q_EMIT update->valueAbsoluteAvarageFitnessRegression(tmpAvarage);
            AbsoluteAvarageFitness=( v / _pop.size());
        }

        if(AbsoluteMaximumFitness < fitness){
            QString tmpAvarage= QString("Absolute Maximum Fitness:    %1").arg(fitness );
//            p=QtConcurrent::run(update,update->valueAbsoluteMaximumFitnessRegression,tmpAvarage);
//            p.waitForFinished();
            //Q_EMIT update->valueAbsoluteMaximumFitnessRegression(tmpAvarage);
            AbsoluteMaximumFitness=fitness;
        }

        steps++;
        //       cout << (steps*100)/maxGen << endl;
        //progressBar->setProperty("value",((steps*100)/maxGen));
//        p=QtConcurrent::run(update,update->valueProgressBar,QString("%1").arg((steps*100)/maxGen));
//        p.waitForFinished();
    }
    int count;
    QVector<double> x;
    QVector<double> yBest;
    QVector<double> yAverage;

    QObject *progressBar;
    QObject *currentMaximumFitness;
    QObject *absoluteMaximumFitness;
    QObject *currentAverageFitness;
    QObject *absoluteAverageFitness;

    int steps ;
    int maxGen;
    double AbsoluteMaximumFitness;
    double AbsoluteAvarageFitness;
    std::vector< double> xRegression;
};
#endif // EOGRAPHFITENESSSTAT_H
