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
#include "Rain.h"
#include <QtConcurrent/QtConcurrent>
#include "mainwindow.h"
#include "SAke/SAKeController.h"
#include "HandlerCSV.h"



template <class EOT>
class eoGraphFitnessStat : public eoStat<EOT,  typename EOT::Fitness>
{

public:
    typedef typename EOT::Fitness Fitness;
    using eoStat<EOT, typename EOT::Fitness>::value;

    eoGraphFitnessStat();
    eoGraphFitnessStat(int _maxGen,
                       Rain*& rain,
                       int& size,
                       Activation *_activation,
                       int _activation_size,SAKeController* s,
                       std::string _description = "Best ")
        : eoStat<EOT, Fitness>(Fitness(), _description)
    {
        P=rain;
        rain_size=size;
        activation =_activation;
        activation_size = _activation_size;
        count=0;
        steps= 1;
        maxGen = _maxGen;
        AbsoluteMaximumFitness=0;
        AbsoluteAvarageFitness=0;
        controller =s;
        numGenerations = 0;
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
        count++;
        double fitness =_pop.best_element().fitness();

        if(steps == 1){ // first step
            QString stmp = controller->getSavePath()+"/fitnessGenerations.csv";
            HandlerCSV::loadCSVGenationsFromFile(stmp, x, yBest, yAverage);
            numGenerations = x.size();

        }

        yBest.push_back( _pop.best_element().fitness() );
        x.push_back(numGenerations+count);

        Fitness v = std::accumulate(_pop.begin(), _pop.end(), Fitness(0.0), eoGraphFitnessStat::sumFitness);

        yAverage.push_back( v / _pop.size());

        const EOT best_element= _pop.best_element();
        std::vector<double> Y;
        Y.resize(rain_size);

        for (int t = 0; t < rain_size; t++) {
            double ym = 0;
            Y[t] = 0;
            for (int r = 0; r < t; r++)
                if ((t - r) < best_element.getSizeConst()){
                    ym += best_element.getFiConstIndex(t - r) * P[r].getRainMm();
                }
            Y[t] = ym;
        }
        controller->getMainwindows()->mutex.lock();
        ptrdiff_t pos = distance(MainWindow::threads.begin(), find(MainWindow::threads.begin(), MainWindow::threads.end(), controller));

        cout << "aggiorno " << pos << endl;
        emit controller->updateMobPlot(pos,P,rain_size,activation, activation_size, Y,best_element.getYmMinConst().getValue(),best_element.getYmMinConst().getTime(), best_element.getYmMin2Const().getValue(), best_element.getYmMin2Const().getTime(),best_element.getBestsConst(),controller->widgetArray, controller->arrowArray);

        emit controller->updateKernelPlot(pos,QVector<double>::fromStdVector(best_element.getFiConst()),best_element.getSizeConst());

        emit controller->updateFitnessPlot(pos,x,yBest,x,yAverage, numGenerations, (steps == 1));

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
        if(AbsoluteAvarageFitness < ( v / _pop.size())){
            AbsoluteAvarageFitness=( v / _pop.size());
        }

        if(AbsoluteMaximumFitness < fitness){
            AbsoluteMaximumFitness=fitness;

        }

        if(best_element.getFPR().size() != 0)
            emit controller->updateROCPlot(pos, QVector<double>::fromStdVector(best_element.getFPR()),QVector<double>::fromStdVector(best_element.getTPR()),best_element.getAUC());

        QString genString= QString("%1").arg(steps+numGenerations);
        steps++;
        emit controller->updateTexts(pos,genString,QString("%1").arg(fitness),
                                     QString("%1").arg(v / _pop.size()),
                                     QString("%1").arg(_pop.best_element().getSizeConst()),
                                     QString("%1").arg((best_element.getYmMinConst().getValue()-best_element.getYmMin2Const().getValue())/best_element.getYmMinConst().getValue()),
                                     QString("%1").arg(best_element.getMomentoDelPrimoOrdineConst()),
                                     (steps*100)/maxGen,
                                     firstOccurance,
                                     QString("%1").arg(AbsoluteMaximumFitness),
                                     QString("%1").arg(AbsoluteAvarageFitness)
                                     );
        controller->getMainwindows()->mutex.unlock();

    }
    int count;
    QVector<double> x;
    QVector<double> yBest;
    QVector<double> yAverage;


    Rain * P;
    int rain_size;
    Activation *activation;
    int activation_size;
    int steps ;
    int maxGen;
    int firstOccurance;
    double bestfitness;

    int numGenerations;

    double AbsoluteMaximumFitness;
    double AbsoluteAvarageFitness;
    SAKeController* controller;
};
#endif // EOGRAPHFITENESSSTAT_H
