#include "ValidationController.h"

ValidationController::ValidationController(
                                           Rain *  rain,
                                           int  rain_size,
                                           Activation *  activations,
                                           int  activations_size,
                                           double * Fi,
                                           int size,
                                           double zCr
                                           )
{
       //CARICO I CSV
//       HandlerCSV::loadCSVRain(filenameRainPath,rain,rain_size);
//       HandlerCSV::loadCSVActivation(filenameActivationPath,activations,activations_size);
//       HandlerCSV::loadCSVKernel(filenameKernelPath,Fi,size,zCr);
    this->rain = rain;
    this->rain_size = rain_size;
    this->activations = activations;
    this->activations_size = activations_size;
    this->Fi = Fi;
    this->size = size;
    this->zCr = zCr;



}

void ValidationController::setPlotMobility(CustomPlotMobilityFunction *value)
{
    plotMobility = value;
    plotMobility->setActivation(this->activations,this->activations_size);
    plotMobility->setRain(this->rain,this->rain_size);
    plotMobility->initCustomPlotMobilityFunction();
}

static int  compareDouble (const void * a, const void * b)
{
    // - perche decrescente
  if( (double)(((Ym*)a)->getValue()) > (double)(((Ym*)b)->getValue()) ){
      return -1;
  }
  if( (double)(((Ym*)a)->getValue()) < (double)(((Ym*)b)->getValue()) ){
      return 1;
  }
  if( (double)(((Ym*)a)->getValue()) == (double)(((Ym*)b)->getValue()) ){
      return 0;
  }
}
int getDifferenceTime(tm temp1,tm temp2){
    ptime rain0 = ptime_from_tm(temp1);
    ptime rainLast = ptime_from_tm(temp2);
    boost::posix_time::time_duration diff1 =(rain0-ptime(date(1970, Jan, 1)));
    boost::posix_time::time_duration diff2 =(rainLast-ptime(date(1970, Jan, 1)));
    std::time_t x = diff1.total_seconds();
    std::time_t y = diff2.total_seconds();
    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
    {
        //TODO [differenza in minuti] [differenza in ore] [ differenza in giorni ]
        int difference = std::difftime(y, x) / (60*60*24);
//	        std::cout << std::ctime(&x);
//	        std::cout << std::ctime(&y);
//	        std::cout << "difference = " << difference << " days" << std::endl;
        return difference;
    }
    return -1;
}

void getYmDecr(Ym*&ym,int &size){
    qsort (ym, size, sizeof(Ym),compareDouble);

}

void ValidationController::updatePlot(){

//    printf("rain_size %d \n",rain_size);
    //printf("tb %d \n",size);


//    for (int i = 0; i < size; i++) {
//           printf("Fi[%d] %f \n",i, Fi[i]);
//     myfile <<< "Fi[ " << i<<"] = " << Fi[i] << "\n";
//    }
//    printf("tb %d \n",size);
//    ofstream myfile;
//    myfile.open ("C:\\Users\\Alessio\\Documents\\workspace\\calibration\\seed1\\validation.csv",ios::out);
//        for (int i = 0; i < size; i++) {
//    //           printf("Fi[%d] %f \n",i, Fi[i]);
//         myfile << "Fi[ " << i<<"] = " << Fi[i] << "\n";
//        }
    //Calcolo Mobiliy Function
    double * Y = new double[rain_size];
    for (int t = 0; t < rain_size; t++) {
        double ym = 0;
        Y[t] = 0;
        for (int r = 0; r < t; r++)
            if ((t - r) < size){
                ym += Fi[t - r] * rain[r].getRainMm();
               // myfile << "Fi[t - r] = " << Fi[t - r] << ", rain[r].getRainMm() " << rain[r].getRainMm() << "\n";
            }
//        myfile << "Y[" << t << "] " << ym << "\n";
        Y[t] = ym;


    }
//    myfile.close();

    double f=0;
    Ym * ym= new Ym[rain_size];
    int countYm=0;

    for (int t = 1; t < rain_size-1; t++) {
        bool cross = (((Y[t] - Y[t - 1]) * (Y[t + 1] - Y[t])) < 0) && (Y[t] > Y[t - 1]);
        if(cross){
            // trovato un picco deve essere considerato
            ym[countYm].setValue(Y[t]);
            ym[countYm].setTime(rain[t].getTime());
            countYm++;
        }
    }

    getYmDecr(ym,countYm);

//        for (int i = 0; i < countYm; i++) {
//               printf("ym[%d] %f \n",i, ym[i].getValue());
//        }
//        printf("countYm %d \n",countYm);


    double YsMin = 999999999;
    int iMin =-1;
    std::vector<Ym> bests;
//    printf("activations_size %d \n",activations_size);
    for (int s = 0; s < activations_size; s++) {
        for (int i = 0; i < countYm; i++) {
            //TODO inserire variabili intervallo giorni
            int result1 = getDifferenceTime(activations[s].getStart(),ym[i].getTime());
            int result2 = getDifferenceTime(ym[i].getTime(),activations[s].getEnd());
            if(result1>=-2 && result2>=-1){
                //if(i<countYm)
                //if(i<(activations_size)){
//                    printf("i %d \n",i);

                    f += 1 / (double)(i + 1);
//                    printf("f %f \n",f);
                    //fflush( stdout );
                    bests.push_back(ym[i]);
//                        int year = ym[i].getTime().tm_year +1900;
//                        int mon = ym[i].getTime().tm_mon +1;
//                        int day = ym[i].getTime().tm_mday ;
//                        std::cout << "year " << year << " mon " << mon << " day " << day << std::endl;
//                        std::cout << "ym[i] value " << ym[i].getValue() << std::endl;
                    //printf("+  %f \n",(1 / (double)(i + 1)));
                    if(ym[i].getValue() < YsMin){
                        YsMin =ym[i].getValue();
                        iMin=i;
                    }//if
                    break;
                //}
                // calcolo valori per calcolare dYcr per risparmiare calcoli

            }//if
        }//for
    }//for
    if(iMin < 0)  iMin = 0;
    if(iMin > countYm-1)  iMin = countYm-1;
    int index=(iMin+1);

    double dYcr = (YsMin-ym[index].getValue())/YsMin;
//    printf("dYcr %f \n",dYcr);
//    printf("YsMin %f \n",YsMin);
//    printf("YsMin2 %f \n",ym[index].getValue());
    Ym ymMin= ym[iMin];
    Ym ymMin2 = ym[iMin+1];

    // tb = this->size
    double momentoDelPrimoOrdine = 0;
    for (int i = 0; i < size; i++) {
        momentoDelPrimoOrdine += Fi[i]*((i+1)-0.5);
    }

    double fMax=0;
//    printf("activations_size %d \n",activations_size);
    for (int i = 1; i <= activations_size; i++) {
        fMax +=(double)(1/(double)i);
    }
//    printf("f %f fMax %f fitness = %f \n",f,fMax,(double) (f/fMax));

    QString fitnessString= QString("Fitness :    %1").arg((double) (f/fMax));
    this->fitness->setProperty("text",fitnessString);


    QString momentoDelPrimoOrdineString= QString("Momento del primo ordine:    %1").arg(momentoDelPrimoOrdine);
    this->momentoDelPrimoOrdine->setProperty("text",momentoDelPrimoOrdineString);

    QString deltaCriticoString= QString("Δcritico:    %1").arg(dYcr);
    this->deltaCritico->setProperty("text",deltaCriticoString);

    QString tbString= QString("tb:    %1").arg(this->size );
    this->tb->setProperty("text",tbString);


    plotMobility->updateGraph(Y,ymMin,ymMin2,bests);
}

Rain *ValidationController::getRain() const
{
    return rain;
}

void ValidationController::setRain(Rain *value)
{
    rain = value;
}

Activation *ValidationController::getActivations() const
{
    return activations;
}

void ValidationController::setActivations(Activation *value)
{
    activations = value;
}

int ValidationController::getRain_size() const
{
    return rain_size;
}

void ValidationController::setRain_size(int value)
{
    rain_size = value;
}

int ValidationController::getActivations_size() const
{
    return activations_size;
}

void ValidationController::setActivations_size(int value)
{
    activations_size = value;
}

QObject *ValidationController::getTb() const
{
    return tb;
}

void ValidationController::setTb(QObject *value)
{
    tb = value;
}

QObject *ValidationController::getDeltaCritico() const
{
    return deltaCritico;
}

void ValidationController::setDeltaCritico(QObject *value)
{
    deltaCritico = value;
}

QObject *ValidationController::getMomentoDelPrimoOrdine() const
{
    return momentoDelPrimoOrdine;
}

void ValidationController::setMomentoDelPrimoOrdine(QObject *value)
{
    momentoDelPrimoOrdine = value;
}

QObject *ValidationController::getFitness() const
{
    return fitness;
}

void ValidationController::setFitness(QObject *value)
{
    fitness = value;
}

void ValidationController::setKernelPlot(CustomPlotKernel *value){
    plotkernel = value;
    plotkernel->initCustomPlotFitness();

}

void ValidationController::updateKernelPlot(){

    plotkernel->updateGraph(Fi,size);
}

