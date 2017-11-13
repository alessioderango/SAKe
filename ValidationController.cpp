#include "ValidationController.h"

ValidationController::ValidationController(
        Rain *  rain,
        int  rain_size,
        Activation *  activations,
        int  activations_size,
        std::vector<double> &Fi,
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
    try {
        ptime rain0 = ptime_from_tm(temp1);
        ptime rainLast = ptime_from_tm(temp2);
        boost::posix_time::time_duration diff1 =(rain0-ptime(date(1970, Jan, 1)));
        boost::posix_time::time_duration diff2 =(rainLast-ptime(date(1970, Jan, 1)));
        std::time_t x = diff1.total_seconds();
        std::time_t y = diff2.total_seconds();
        if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
        {
            //TODO [differenza in minuti] [differenza in ore] [ differenza in giorni ]
            int difference = 0;

            difference = std::difftime(y, x) / (60*60*24);


            //	        std::cout << std::ctime(&x);
            //	        std::cout << std::ctime(&y);
            //	        std::cout << "difference = " << difference << " days" << std::endl;
            return difference;
        }

        return -1;
    } catch (std::exception& e){
        std::cout << "  Exception: " <<  e.what() << std::endl;
    }
}

void getYmDecr(Ym*&ym,int &size){
    qsort (ym, size, sizeof(Ym),compareDouble);

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


//void ValidationController::updateKernelPlot(){

////    plotkernel->updateGraph(Fi,size);
//}

void ValidationController::run(){
    if(ft == FitnessGMD || ft == FitnessEqualWeights)
        startValidation();
    else
        if(ft == FitnessAUCROC)
            startValidationAUCROC();
}

void ValidationController::setFt(const FitnessType &value)
{
    ft = value;
}

MainWindow *ValidationController::getMainwindows() const
{
    return mainwindows;
}

void ValidationController::setMainwindows(MainWindow *value)
{
    mainwindows = value;
}

void ValidationController::getMobilityFunction(std::vector<double>&  Y, std::vector<Ym>& ym)
{
    Y.resize(rain_size);
    for (int t = 0; t < rain_size; t++) {
        double ym = 0;
        Y[t] = 0;
        for (int r = 0; r < t; r++)
            if ((t - r) < size){
                ym += Fi[t - r] * rain[r].getRainMm();
            }
        Y[t] = ym;


    }

    double f=0;
    int countYm=0;

    for (int t = 1; t < rain_size-1; t++) {
        bool cross = (((Y[t] - Y[t - 1]) * (Y[t + 1] - Y[t])) < 0) && (Y[t] > Y[t - 1]);
        if(cross){
            // trovato un picco deve essere considerato

            Ym p;
            p.setValue(Y[t]);
            p.setTime(rain[t].getTime());
            ym.push_back(p);
            countYm++;
        }
    }
}

void ValidationController::startValidationAUCROC(){

    std::vector<Ym> ym;
    std::vector<double>  Y;
    std::vector<Ym> ymSorted;
    std::vector<Ym> bests;
    //calcolo mobility function
    getMobilityFunction(Y,ym);
    getMobilityFunction(Y, ymSorted);

    qsort (&ymSorted[0], ymSorted.size(), sizeof(Ym),compareDouble);


    Ym ymMax = ymSorted[0];

    double line = ymMax.getValue()/10;

    cout << ymMax.getValue() << endl;
    cout << line << endl;

    vector<double> lines;
    for (int i = 10; i >= 1; i--) {
        lines.push_back(line*i);
    }

    for (int i = 0; i < activations_size; ++i) {
        bests.push_back(ym[i]);
    }

    //inside the activation range
    vector<int> TP(10,0);// true positive
    vector<int> FN(10,0);// false negative

    //outside the activation range
    vector<int> FP(10,0);// false positive
    vector<int> TN(10,0);// true negative


    for (int i = 0; i < lines.size(); ++i) {

        for(int t = 0; t < rain_size; t++) {

            //controllo TP e FN
            for (int s = 0; s < activations_size; s++) {
                //TODO inserire variabili intervallo giorni
                int result1 = getDifferenceTime(activations[s].getStart(),rain[t].getTime());
                int result2 = getDifferenceTime(rain[t].getTime(),activations[s].getEnd());

                if(result1>=-2 && result2>=-1){
                    break;
                }
            }


            //controllo FP e TN
            if(Y[t] < lines[i])
               TN[i]++;
            else
               FP[i]++;
        }
    }

    for (int i = 0; i < lines.size(); ++i) {
        FN[i] = activations_size;
        for (int s = 0; s < activations_size; s++) {

            //controllo TP e FN

            for(int t = 0; t < rain_size; t++) {
                //TODO inserire variabili intervallo giorni
                int result1 = getDifferenceTime(activations[s].getStart(),rain[t].getTime());
                int result2 = getDifferenceTime(rain[t].getTime(),activations[s].getEnd());

                if(result1>=-2 && result2>=-1){
                    if(Y[t] >= lines[i]){
                        TP[i]++;
                        FN[i]--;
                        break;
                    }
                    //                    else
                    //                      FN[i]++;
                    //                    break;
                }
            }


            //controllo FP e TN
            //            if(lines[i] >= Y[t])
            //              FP[i]++;
            //            else
            //              TN[i]++;
        }
    }




    vector<double> TPR(10,0);// true positive rate
    vector<double> FPR(10,0);// False positive rate


    for (int i = 0; i < 10; ++i) {
        TPR[i] = (double) (TP[i]/((double) (TP[i]+FN[i])));
        double TNR =  (double)TN[i] / (double)(TN[i]+FP[i]);
        FPR[i] = (double) (1-((double) TNR));

        cout << TPR[i] << ";" << FPR[i] << ";"<< endl;
    }

    double AUC=0; // Area under the curve
    // primo trapezio
    AUC += FPR[0]*TPR[0]*((double)(0.5));
    for (int i = 0; i < 9; ++i) {
        double h = FPR[i+1]-FPR[i];
        double base = TPR[i]+TPR[i+1];
        double tmp = (((double)(0.5))*(h))*(base);
        cout << "area trapezio "<<i<< " base --> " << base  <<" h --> " << h  <<"  = " << tmp <<endl;
        AUC += tmp;
    }
    AUC += (1-FPR[9])*((double)(0.5))*(1+TPR[9]);

    cout << "AUC "<<AUC<<endl;

    ptrdiff_t pos = distance(MainWindow::threads.begin(), find(MainWindow::threads.begin(), MainWindow::threads.end(), this));

    emit this->updateMobPlot(pos,rain,rain_size,activations, activations_size, Y,ymMax.getValue(),ymMax.getTime(), ymMax.getValue(),ymMax.getTime(),bests,widgetArray,arrowArray);

    emit this->updateKernelPlot(pos,QVector<double>::fromStdVector(Fi),size);



}
bool diffTimeInterval(tm actStart, tm actEnd, tm pichTime){
    int result1 = getDifferenceTime(actStart,pichTime);
    int result2 = getDifferenceTime(pichTime,actEnd);
     if(result1>=-2 && result2>=-1){
         return true;
     }
     else
         return false;
}

void ValidationController::startValidation(){

    //Calcolo Mobiliy Function
    //double * Y = new double[rain_size];
    std::vector<double> Y;
    Y.resize(rain_size);
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
    //Ym * ym= new Ym[rain_size];
    std::vector<Ym> ym;
    //ym.resize(rain_size);
    int countYm=0;

    for (int t = 1; t < rain_size-1; t++) {
        bool cross = (((Y[t] - Y[t - 1]) * (Y[t + 1] - Y[t])) < 0) && (Y[t] > Y[t - 1]);

        bool jump = false;

        if(cross){
            // trovato un picco deve essere considerato
            //                ym[countYm].setValue(Y[t]);
            //                ym[countYm].setTime(rain[t].getTime());

            //------------------ GMDn --------------------------------------------
            if(ft == FitnessGMDn)
            for (int a = 0; a < activations_size; a++) {
                 if(diffTimeInterval(activations[a].getStart(), activations[a].getEnd(),rain[t].getTime())){
                     cout << "salto un pico all'interno di un intervallo " << endl;
                     jump = true;
                 }
            }
            //------------------ GMDn --------------------------------------------

            if(jump)
                continue;

            Ym p;
            p.setValue(Y[t]);
            p.setTime(rain[t].getTime());
            ym.push_back(p);
            countYm++;
        }
    }

    //------------------ GMDn --------------------------------------------
    //trovo il picco massimo nell'intervallo
    if(ft == FitnessGMDn)
    for (int s = 0; s < activations_size; s++) {
        double maxPich = 0;
        int tMax =0;
        for (int t = 1; t < rain_size-1; t++) {

            if(diffTimeInterval(activations[s].getStart(), activations[s].getEnd(),rain[t].getTime())){
                if(Y[t] > maxPich)
                {
                    maxPich = Y[t];
                    tMax = t;
                }
            }
        }
        Ym p;
        p.setValue(Y[tMax]);
        p.setTime(rain[tMax].getTime());
        ym.push_back(p);

    }
    //------------------ GMDn --------------------------------------------



    //getYmDecr(ym,countYm);
    qsort (&ym[0], ym.size(), sizeof(Ym),compareDouble);


    //            for (int i = 0; i < countYm; i++) {
    //                int year = ym[i].getTime().tm_year +1900;
    //                int mon = ym[i].getTime().tm_mon +1;
    //                int day = ym[i].getTime().tm_mday ;
    //                std::cout << "ym countYm  year " << year << " mon " << mon << " day " << day << "   ym["<< i <<"] = " <<  ym[i].getValue() << std::endl;
    //                   //printf("ym[%d] %f \n",i, ym[i].getValue());
    //            }
    //            printf("countYm %d \n",countYm);


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
                if(ft == FitnessGMD)
                    f += 1 / (double)(i + 1);

                if(ft == FitnessEqualWeights)
                {
                    if(i < activations_size )
                        f += 1 / (double)activations_size;
                    else
                        f += 1 / (double)(i + 1);
                }

                ym[i].setI(i+1);
                bests.push_back(ym[i]);

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

    Ym ymMin= ym[iMin];
    Ym ymMin2 = ym[iMin+1];

    double momentoDelPrimoOrdine = 0;
    for (int i = 0; i < size; i++) {
        momentoDelPrimoOrdine += Fi[i]*((i+1)-0.5);
    }

    double fMax=0;

    for (int i = 1; i <= activations_size; i++) {
        fMax +=(double)(1/(double)i);
    }
    //mutex->lock();
    mainwindows->mutex.lock();
    ptrdiff_t pos = distance(MainWindow::threads.begin(), find(MainWindow::threads.begin(), MainWindow::threads.end(), this));

    emit this->updateMobPlot(pos,rain,rain_size,activations, activations_size, Y,ymMin.getValue(),ymMin.getTime(), ymMin2.getValue(), ymMin2.getTime(),bests,widgetArray,arrowArray);

    emit this->updateKernelPlot(pos,QVector<double>::fromStdVector(Fi),size);

    QString finalFitness;
    if(ft == FitnessGMD)
        finalFitness = QString("%1").arg((double) (f/fMax));
    if(ft == FitnessEqualWeights)
        finalFitness = QString("%1").arg((double) (f));

    emit this->updateTextsValidation(pos,finalFitness,
                                     QString("%1").arg(this->size),
                                     QString("%1").arg(dYcr),
                                     QString("%1").arg(momentoDelPrimoOrdine)
                                     );
    mainwindows->mutex.unlock();
    // mutex->unlock();
    //delete ym;

}

void ValidationController::startThread(){
    QThread::start();
}

