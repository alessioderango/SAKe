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
using namespace std;

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

private:
    CustomPlotMobilityFunction * plotMobility;
    CustomPlotKernel * plotkernel;

    double* Fi;
    int size;
    Rain * rain;
    int rain_size;
    Activation * activations;
    int activations_size;
    double zCr;
};

#endif // VALIDATIONCONTROLLER_H
