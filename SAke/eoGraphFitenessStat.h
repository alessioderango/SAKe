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
#include "Rain.h"
#include "update.h"
#include <QtConcurrent/QtConcurrent>



template <class EOT>
class eoGraphFitnessStat : public eoStat<EOT,  typename EOT::Fitness>
{

public:

    using eoStat<EOT, typename EOT::Fitness>::value;

    typedef typename EOT::Fitness Fitness;

    eoGraphFitnessStat(int _maxGen,QObject *_progressBar,CustomPlotItem *& _qCustomPlot,CustomPlotMobilityFunction*& plot,Rain*& rain,int& size,CustomPlotKernel * a,    QObject *_currentMaximumFitness,
    QObject *_absoluteMaximumFitness,
    QObject *_currentAverageFitness,
    QObject *_absoluteAverageFitness,
    QApplication*_appli,
    Update* _update,
    std::string _description = "Best ")
        : eoStat<EOT, Fitness>(Fitness(), _description)
    {
        qCustomPlot=_qCustomPlot;
        plotMobility=plot;
        plotKernel = a;
        progressBar = _progressBar;
        P=rain;
        rain_size=size;
        count=0;
        steps= 1;
        maxGen = _maxGen;
        currentMaximumFitness=_currentMaximumFitness;
        absoluteMaximumFitness=_absoluteMaximumFitness;
        currentAverageFitness= _currentAverageFitness;
        absoluteAverageFitness=_absoluteAverageFitness;
        appli=_appli;
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



       const EOT now= _pop.best_element();
       double * Y = new double[rain_size];
       for (int t = 0; t < rain_size; t++) {
           double ym = 0;
           Y[t] = 0;
           for (int r = 0; r < t; r++)
               if ((t - r) < now.getSizeConst()){
                   ym += now.getFiConst()[t - r] * P[r].getRainMm();
               }
           Y[t] = ym;
       }
//       auto p = QtConcurrent::run(plotMobility,plotMobility->updateGraph,Y,now.getYmMinConst(),now.getYmMin2Const(),now.getBestsConst());
//       p.waitForFinished();

       //plotMobility->updateGraph(Y,now.getYmMinConst(),now.getYmMin2Const(),now.getBestsConst());
       delete []Y;
      // currentMaximumFitness->children();

//       plotKernel->updateGraph(now.getFiConst(),now.getSizeConst());
//       p = QtConcurrent::run(plotKernel,plotKernel->updateGraph,now.getFiConst(),now.getSizeConst());
//       p.waitForFinished();
       //qCustomPlot->updateGraph0(x,yBest);
//       p= QtConcurrent::run(qCustomPlot,qCustomPlot->updateGraph0,x,yBest);
//       p.waitForFinished();
       //qCustomPlot->updateGraph1(x,yAverage);
//       p = QtConcurrent::run(qCustomPlot,qCustomPlot->updateGraph1,x,yAverage);
//       p.waitForFinished();

       QString genString= QString("Gen:    %1").arg(steps);
//       p=QtConcurrent::run(update,update->valueGen,genString);
//       p.waitForFinished();
       //Q_EMIT update->valueGen(genString);
       QString currentMaxiumFitness= QString("Current Maximum Fitness:    %1").arg(fitness );
       //Q_EMIT update->valueCurrentMaximumFitness(currentMaxiumFitness);
//       p=QtConcurrent::run(update,update->valueCurrentMaximumFitness,currentMaxiumFitness);
//       p.waitForFinished();

       QString currentAvarageFitness= QString("Current Average Fitness:    %1").arg( v / _pop.size() );
       //Q_EMIT update->valueCurrentAvarageFitness(currentAvarageFitness);
//       p=QtConcurrent::run(update,update->valueCurrentAvarageFitness,currentAvarageFitness);
//       p.waitForFinished();
       if(AbsoluteAvarageFitness < ( v / _pop.size())){
           QString tmpAvarage= QString("Absolute Average Fitness:       %1").arg( v / _pop.size() );
           //Q_EMIT update->valueAbsoluteAvarageFitness(tmpAvarage);
//           p=QtConcurrent::run(update,update->valueAbsoluteAvarageFitness,tmpAvarage);
//           p.waitForFinished();
           AbsoluteAvarageFitness=( v / _pop.size());
       }

       if(AbsoluteMaximumFitness < fitness){
           QString tmpAvarage= QString("Absolute Maximum Fitness:    %1").arg(fitness );
           //Q_EMIT update->valueAbsoluteMaximumFitness(tmpAvarage);
//           p=QtConcurrent::run(update,update->valueAbsoluteMaximumFitness,tmpAvarage);
//           p.waitForFinished();
           AbsoluteMaximumFitness=fitness;
       }
       QString tbString= QString("tb:    %1").arg(_pop.best_element().getSizeConst() );
       //qDebug() << tbString << endl;
       //Q_EMIT update->valueTb(tbString);
//       p=QtConcurrent::run(update,update->valueTb,tbString);
//       p.waitForFinished();

       QString deltaCriticoString= QString("Δcritico:    %1").arg((now.getYmMinConst().getValue()-now.getYmMin2Const().getValue())/now.getYmMinConst().getValue());
       //qDebug() << deltaCriticoString << endl;
       //Q_EMIT update->valueDeltaCritico(deltaCriticoString);
//       p=QtConcurrent::run(update,update->valueDeltaCritico,deltaCriticoString);
//       p.waitForFinished();

       QString momentoDelPrimoOrdineString= QString("Momento del primo ordine:    %1").arg(now.getMomentoDelPrimoOrdineConst());
       //qDebug() << momentoDelPrimoOrdineString << endl;
       //Q_EMIT update->valueMomentoDelPrimoOrdine(momentoDelPrimoOrdineString);
       //p=QtConcurrent::run(update,update->valueMomentoDelPrimoOrdine,momentoDelPrimoOrdineString);
       //p.waitForFinished();

       steps++;
//       cout << (steps*100)/maxGen << endl;
       //QString progBar =
       //progressBar->setProperty("value",((steps*100)/maxGen));
       //p=QtConcurrent::run(update,update->valueProgressBar,QString("%1").arg((steps*100)/maxGen));
       //p.waitForFinished();

    }
    int count;
    QVector<double> x;
    QVector<double> yBest;
    QVector<double> yAverage;
    CustomPlotItem * qCustomPlot;
    CustomPlotMobilityFunction *plotMobility;
    CustomPlotKernel *plotKernel;
    QObject *progressBar;
    QObject *currentMaximumFitness;
    QObject *absoluteMaximumFitness;
    QObject *currentAverageFitness;
    QObject *absoluteAverageFitness;
  //  SAKeController * sakecontroller;
    QApplication*appli;

    Rain * P;
    int rain_size;
    int steps ;
    int maxGen;

    Update* update;
    double AbsoluteMaximumFitness;
    double AbsoluteAvarageFitness;
};
#endif // EOGRAPHFITENESSSTAT_H
