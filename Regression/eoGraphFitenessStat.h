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
//#include "CustomPlotRegression.h"
#include <QtConcurrent/QtConcurrent>
#include "Regression/regressioncontroller.h"

template <class EOT>
class eoGraphFitnessStat : public eoStat<EOT,  typename EOT::Fitness>
{

public:

    using eoStat<EOT, typename EOT::Fitness>::value;

    typedef typename EOT::Fitness Fitness;

    eoGraphFitnessStat(int _maxGen,
                       std::vector< double> _xRegression,
                       std::vector< double> _y,
                       RegressionController *controller,
                       std::string _description = "Best ")
        : eoStat<EOT, Fitness>(Fitness(), _description)
    {
        xRegression = _xRegression;
//        progressBar = _progressBar;
        count=0;
        steps= 1;
        maxGen = _maxGen;
//        currentMaximumFitness=_currentMaximumFitness;
//        absoluteMaximumFitness=_absoluteMaximumFitness;
//        currentAverageFitness= _currentAverageFitness;
//        absoluteAverageFitness=_absoluteAverageFitness;
        AbsoluteMaximumFitness= - 1000000;
        AbsoluteAvarageFitness=-DBL_MIN;
        this->controller = controller;
        this->_y = _y;

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





        if(_pop.size() < 200 && steps%5 ==0){
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
        if(steps ==1){
            firstOccurance = 1;
            bestfitness = 0;
        }
        else{
             if(fitness > bestfitness){
                 bestfitness = fitness;
                 firstOccurance = steps;
             }
        }

        steps++;

        controller->getMainwindows()->mutex.lock();
        ptrdiff_t pos = distance(MainWindow::threads.begin(), find(MainWindow::threads.begin(), MainWindow::threads.end(), controller));
        if( steps%5 ==0)
        emit controller->updateRegression(pos,xRegretmp, yRegretmp, xRegretmp, QVector<double>::fromStdVector(_y),steps);

        emit controller->updateTextsRegression(pos,genString,
                                               QString("%1").arg(fitness),
                                               QString("%1").arg(v / _pop.size()),
                                               (steps*100)/maxGen,
                                               firstOccurance,
                                               QString("%1").arg(AbsoluteMaximumFitness),
                                               QString("%1").arg(AbsoluteAvarageFitness));
        controller->getMainwindows()->mutex.unlock();

        //       cout << (steps*100)/maxGen << endl;
        //progressBar->setProperty("value",((steps*100)/maxGen));
//        p=QtConcurrent::run(update,update->valueProgressBar,QString("%1").arg((steps*100)/maxGen));
//        p.waitForFinished();
    }
    int count;
    QVector<double> x;
     std::vector< double> _y;
    QVector<double> yBest;
    QVector<double> yAverage;

    QObject *progressBar;
    QObject *currentMaximumFitness;
    QObject *absoluteMaximumFitness;
    QObject *currentAverageFitness;
    QObject *absoluteAverageFitness;

    int firstOccurance;
    double bestfitness;

    int steps ;
    int maxGen;
    double AbsoluteMaximumFitness;
    double AbsoluteAvarageFitness;
    std::vector< double> xRegression;
    RegressionController *controller;
};
#endif // EOGRAPHFITENESSSTAT_H
