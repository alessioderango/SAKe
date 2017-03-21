#ifndef VALIDATIONCONTROLLER_H
#define VALIDATIONCONTROLLER_H
#include <QObject>
#include "CustomPlotMobilityFunction.h"
#include "CustomPlotKernel.h"
#include "SAke/Rain.h"
#include "SAke/Activation.h"
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include "handlercsv.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/local_time_adjustor.hpp"
#include "boost/date_time/c_local_time_adjustor.hpp"
using namespace std;
using boost::posix_time::ptime;
using namespace boost::gregorian;
using namespace boost::posix_time;

class ValidationController
{
public:
    ValidationController(
            Rain *  rain,
            int  rain_size,
            Activation *  activations,
            int  activations_size,
            double * Fi,
            int size,
            double zCr
            );
    void setPlotMobility(CustomPlotMobilityFunction *value);
    void setKernelPlot(CustomPlotKernel *value);
    void updateKernelPlot();
    void updatePlot();
    Rain *getRain() const;
    void setRain(Rain *value);

    Activation *getActivations() const;
    void setActivations(Activation *value);

    int getRain_size() const;
    void setRain_size(int value);

    int getActivations_size() const;
    void setActivations_size(int value);

    QObject *getTb() const;
    void setTb(QObject *value);

    QObject *getDeltaCritico() const;
    void setDeltaCritico(QObject *value);


    QObject *getMomentoDelPrimoOrdine() const;
    void setMomentoDelPrimoOrdine(QObject *value);

    QObject *getFitness() const;
    void setFitness(QObject *value);

private:
    CustomPlotMobilityFunction * plotMobility;
    CustomPlotKernel * plotkernel;
    QObject *tb;
    QObject *deltaCritico;
    QObject *momentoDelPrimoOrdine;
    QObject *fitness;

    double* Fi;
    int size;
    Rain * rain;
    int rain_size;
    Activation * activations;
    int activations_size;
    double zCr;
};

#endif // VALIDATIONCONTROLLER_H
