#include "ValidationController.h"

ValidationController::ValidationController(
                                           QString  filenameRainPath,
                                           QString  filenameActivationPath,
                                           QString  filenameKernelPath,
                                           QString  folderSave
                                           )
{
       //CARICO I CSV
       HandlerCSV::loadCSVRain(filenameRainPath,rain,rain_size);
       HandlerCSV::loadCSVActivation(filenameActivationPath,activations,activations_size);
       HandlerCSV::loadCSVKernel(filenameKernelPath,Fi,size,zCr);
}

void ValidationController::setPlotMobility(CustomPlotMobilityFunction *value)
{
    plotMobility = value;
    plotMobility->setActivation(this->activations,this->activations_size);
    plotMobility->setRain(this->rain,this->rain_size);
    plotMobility->initCustomPlotMobilityFunction();
}

void ValidationController::updatePlot(){
    //Calcolo Mobiliy Function
    double * Y = new double[rain_size];
    for (int t = 0; t < rain_size; t++) {
        double ym = 0;
        Y[t] = 0;
        for (int r = 0; r < t; r++)
            if ((t - r) < size){
                ym += Fi[t - r] * rain[r].getRainMm();
            }
        Y[t] = ym;
    }
    //AGGIORNO IL GRAFICO
    //TODO creare funzione
   plotMobility->updateGraph(Y,zCr);
}

void ValidationController::setKernelPlot(CustomPlotKernel *value){
    plotkernel = value;
    plotkernel->initCustomPlotFitness();

}

void ValidationController::updateKernelPlot(){

    plotkernel->updateGraph(Fi,size);
}
