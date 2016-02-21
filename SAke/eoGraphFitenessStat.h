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
       //const double *Fi=now.getFi();
       //   const int tb=now.getSize();
       //  typename eoPop<EOT>::iterator it = std::max_element(_pop.begin(), _pop.end());
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
       plotMobility->updateGraph(Y,now.getYsMinConst(),now.getYsMin2Const());
       delete []Y;
      // currentMaximumFitness->children();

       plotKernel->updateGraph(now.getFiConst(),now.getSizeConst());
       qCustomPlot->updateGraph0(x,yBest);
       qCustomPlot->updateGraph1(x,yAverage);

//       QString tmp= QString("Current Maximum Fitness:    %1").arg(fitness );
//       currentMaximumFitness->setProperty("text",tmp);
//       QString tmpAvarage= QString("Current Maximum Fitness:    %1").arg( v / _pop.size() );
//       currentAverageFitness->setProperty("text",tmpAvarage);

       QString genString= QString("Gen:    %1").arg(steps);
       Q_EMIT update->valueGen(genString);
       QString currentMaxiumFitness= QString("Current Maximum Fitness:    %1").arg(fitness );
       Q_EMIT update->valueCurrentMaximumFitness(currentMaxiumFitness);
       QString currentAvarageFitness= QString("Current Average Fitness:    %1").arg( v / _pop.size() );
       Q_EMIT update->valueCurrentAvarageFitness(currentAvarageFitness);
       if(AbsoluteAvarageFitness < ( v / _pop.size())){
           QString tmpAvarage= QString("Absolute Average Fitness:       %1").arg( v / _pop.size() );
           Q_EMIT update->valueAbsoluteAvarageFitness(tmpAvarage);
           AbsoluteAvarageFitness=( v / _pop.size());
       }

       if(AbsoluteMaximumFitness < fitness){
           QString tmpAvarage= QString("Absolute Maximum Fitness:    %1").arg(fitness );
           Q_EMIT update->valueAbsoluteMaximumFitness(tmpAvarage);
           AbsoluteMaximumFitness=fitness;
       }
       //QQmlProperty(currentMaximumFitness, "text").write(tmp);
       //cout << "aaaaaaaaaaaaaa " <<currentMaximumFitness->setProperty("text",tmp)<< endl;
   //    QWidget* tmp2 = qobject_cast<QWidget*>(currentMaximumFitness );

       //appli->processEvents();
//       ((QLabel*)currentMaximumFitness)->repaint();
//       if(currentMaximumFitness->property("text").toDouble() > absoluteMaximumFitness->property("text").toDouble()){
//                QString tmp2= QString("Absolute Maximum Fitness:    %1").arg( _pop.best_element().fitness());
//                absoluteMaximumFitness->setProperty("text",QVariant(tmp2));
//       }
       steps++;
//       cout << (steps*100)/maxGen << endl;
       progressBar->setProperty("value",((steps*100)/maxGen));

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
