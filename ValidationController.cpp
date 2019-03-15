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
int getRightPlotFromName(QString name)
{

    if(name == "AUCROC")
        return 0;
    else
        if(name =="GMDn")
            return 1;
        else
            if(name =="EW")
                return 2;
            else
                if(name =="GMD")
                    return 3;

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
    //    if(ft == FitnessGMD || ft == FitnessEqualWeights)
    //        startValidation();
    //    else
    //        if(ft == FitnessAUCROC)
    //            startValidationAUCROC();
//    ft = FitnessGMD;
//    startValidationAllinOne("GMD");
    ft = FitnessGMDn;
    startValidationAllinOne("GMDn");
    ft=FitnessEqualWeights;
    startValidationAllinOne("EW");

    startValidationAUCROC("AUCROC");


}

int ValidationController::getNumberOfLines() const
{
    return numberOfLines;
}

void ValidationController::setNumberOfLines(int value)
{
    numberOfLines = value;
}

QString ValidationController::getProjectName() const
{
    return projectName;
}

void ValidationController::setProjectName(const QString &value)
{
    projectName = value;
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

bool diffTimeInterval(tm actStart, tm actEnd, tm pichTime){
    int result1 = getDifferenceTime(actStart,pichTime);
    int result2 = getDifferenceTime(pichTime,actEnd);
    if(result1>=-2 && result2>=-1){
        return true;
    }
    else
        return false;
}

double ValidationController::getAUCROC(std::vector<double>&  Y,
                                    std::vector<Ym>& ymSorted,
                                    std::vector<double> Fi,
                                    Rain *& rain,
                                    int rain_size,
                                    Activation * activations,
                                    int activations_size,
                                    int tb,
                                    double &dYcr,
                                    Ym &ymMin,
                                    Ym &ymMin2,
                                    std::vector<int>& TP,
                                    std::vector<int>& FN,
                                    std::vector<int>& FP,
                                    std::vector<int>& TN,
                                    std::vector<double>& TPR,
                                    std::vector<double>& FPR,
                                    double& momentoDelPrimoOrdine,
                                    std::vector<Ym>& bests,
                                    vector<double>& lines,
                                    int numberOfLines)
{
    double YsMin = 999999999;
    double YsAbsMinInsideTheActivationInterval = 999999999;
    int iMin =-1;
    double Maxtmp = -999999999;
    Ym zMax;
    for (int s = 0; s < activations_size; s++) {
        for (int i = 0; i < ymSorted.size(); i++) {
            //TODO inserire variabili intervallo giorni
            int result1 = getDifferenceTime(activations[s].getStart(),ymSorted[i].getTime());
            int result2 = getDifferenceTime(ymSorted[i].getTime(),activations[s].getEnd());
            if(result1>=-2 && result2>=-1){
                cout << "considero intervallo con ymSorted" << endl;
                ymSorted[i].setI(i+1);
                bests.push_back(ymSorted[i]);
                if(ymSorted[i].getValue() < YsMin){
                    YsMin =ymSorted[i].getValue();
                    iMin=i;
                }//if
                //break;
                //}
                // calcolo valori per calcolare dYcr per risparmiare calcoli

            }//if
        }//for



        for (int i = 0; i < rain_size-1; i++) {
            //TODO inserire variabili intervallo giorni
            int result1 = getDifferenceTime(activations[s].getStart(),rain[i].getTime());
            int result2 = getDifferenceTime(rain[i].getTime(),activations[s].getEnd());
            if(result1>=-2 && result2>=-1){
                //ymSorted[i].setI(i+1);
                //bests.push_back(ymSorted[i]);
                if(Y[i] < YsAbsMinInsideTheActivationInterval){
                    YsAbsMinInsideTheActivationInterval =Y[i];
                    //iMin=i;
                }//if
                //break;
                //}
                // calcolo valori per calcolare dYcr per risparmiare calcoli

            }//if

            if(Y[i] > Maxtmp){
                Maxtmp = Y[i];
                zMax.setI(i);
                zMax.setTime(rain[i].getTime());
                zMax.setValue(Maxtmp);

            }




        }//for

    }//for
    //std::cout << std::endl;

    if(iMin < 0)  iMin = 0;
    if(iMin > ymSorted.size()-1)  iMin = ymSorted.size()-1;
    int index=(iMin+1);
    ymMin= ymSorted[iMin];
    ymMin2 = ymSorted[iMin+1];
    dYcr = (ymMin.getValue()-ymMin2.getValue())/ymMin.getValue();

    momentoDelPrimoOrdine = 0;
    for (int i = 0; i < tb; i++) {
        momentoDelPrimoOrdine += Fi[i]*((i+1)-0.5);
    }

    // prima consideravamo il massimo assoluto all'interno delle date di attivazione
    Ym ymMax = ymSorted[0];

    //ma ora consideriamo il massimo assoluto della funzione (anche fuori dalle date di attivazione)

    //NOTE
    // Dettagliamo in N fascie (da input) l'altezza compresa da ymMax(il picco massimo all'interno delle date di attivazione)
    // e zMin(YsAbsMinInsideTheActivationInterval che sarebbe il minimo più basso all'interno delle date di attivazione).
    // La restante parte del grafico viene suddivisa in due fascie al di sotto di zMin e in due eventuali fascie al sopra di
    // ymMax ( se zMax > ymMax con zMax il massimo assoluto delle funzione anche al di fuori delle date dittivazione)

//    if(activations_size >= 2){
//        double dz = (ymMax.getValue()-YsAbsMinInsideTheActivationInterval)/((double)numberOfLines);

//        int prec =0;

//        if(zMax.getValue() > ymMax.getValue())
//        {
//            lines.push_back(zMax.getValue());
//            lines.push_back((zMax.getValue()-ymMax.getValue())/2);
//        }

//        lines.push_back(ymMax.getValue());
//        for (int i = numberOfLines-1; i >= 0; i--) {
//            lines.push_back(lines[prec]-dz);
//            prec++;
//        }


//        lines.push_back(lines[prec]/2);

//        if(lines[prec]/2 != 0)
//            lines.push_back(0);
//    }else
//    {
        double line = zMax.getValue()/numberOfLines;
        for (int i = numberOfLines; i >= 1; i--)
        {
            lines.push_back(line*i);
        }
        lines.push_back(0);
//    }

    //inside the activation range
//    vector<int> TP(lines.size(),0);// true positive
//    vector<int> FN(lines.size(),0);// false negative
    TP.resize(lines.size(),0);
    FN.resize(lines.size(),0);

    //outside the activation range
//    vector<int> FP(lines.size(),0);// false positive
    FP.resize(lines.size(),0);
//    vector<int> TN(lines.size(),0);// true negative
    TN.resize(lines.size(),0);


    for (int i = 0; i < lines.size(); ++i) {

        for(int t = 0; t < rain_size; t++) {
            bool jump = false;

            //controllo TP e FN
            for (int s = 0; s < activations_size; s++) {
                //TODO inserire variabili intervallo giorni
                int result1 = getDifferenceTime(activations[s].getStart(),rain[t].getTime());
                int result2 = getDifferenceTime(rain[t].getTime(),activations[s].getEnd());

                if(result1>=-2 && result2>=-1){
                    jump = true;
                }
            }

            if(jump)
            {
                //               if(Y[t] >= lines[i]){
                //                  TP[i]++;
                //                  FN[i]--;
                //                  break;
                //               }
                continue;
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




//    vector<double> TPR(lines.size(),0);// true positive rate
    TPR.resize(lines.size(),0);
//    vector<double> FPR(lines.size(),0);// False positive rate
    FPR.resize(lines.size(),0);

    for (int i = 0; i < lines.size(); ++i) {
        TPR[i] = (double) (TP[i]/((double) (TP[i]+FN[i])));
        double TNR =  (double)TN[i] / (double)(TN[i]+FP[i]);
        FPR[i] = (double) (1-((double) TNR));

        //  cout << TPR[i] << ";" << FPR[i] << ";"<< endl;
    }

    double AUC=0; // Area under the curve
    // primo trapezio
    //AUC += (FPR[0]+FPR[1])*(TPR[0]+TPR[1])*((double)(0.5));
    for (int i = 0; i < lines.size()-1; ++i) {
        double h = FPR[i+1]-FPR[i];
        double base = TPR[i]+TPR[i+1];
        double tmp = (((double)(0.5))*(h))*(base);
        //cout << "area trapezio "<<i<< " base --> " << base  <<" h --> " << h  <<"  = " << tmp <<endl;
        AUC += tmp;
    }
    AUC += (1-FPR[lines.size()-1])*((double)(0.5))*(1+TPR[lines.size()-1]);

    return AUC;
}

void ValidationController::getMobilityFunction(std::vector<double>&  Y,
                                               std::vector<Ym>& ym,
                                               std::vector<double> Fi,
                                               Rain *& rain,
                                               int rain_size,
                                               Activation * activations,
                                               int activations_size,
                                               int tb)
{
    Y.resize(rain_size);
    for (int t = 0; t < rain_size; t++) {
        double ym = 0;
        Y[t] = 0;
        for (int r = 0; r < t; r++)
            if ((t - r) < tb){
                ym += Fi[t - r] * rain[r].getRainMm();
            }
        Y[t] = ym;


    }

    double f=0;
    int countYm=0;

    for (int t = 1; t < rain_size-1; t++) {
        bool cross = (((Y[t] - Y[t - 1]) * (Y[t + 1] - Y[t])) < 0) && (Y[t] > Y[t - 1]);
        bool jump = false;
        if(cross){
            // trovato un picco deve essere considerato
            for (int a = 0; a < activations_size; a++) {
                if(diffTimeInterval(activations[a].getStart(), activations[a].getEnd(),rain[t].getTime())){
                    cout << "salto un pico all'interno di un intervallo " << endl;
                    jump = true;
                }
            }
            if(jump)
                continue;
            Ym p;
            p.setValue(Y[t]);
            p.setTime(rain[t].getTime());
            ym.push_back(p);
            countYm++;
        }
    }

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
}


void ValidationController::startValidationAUCROC(QString namePlot){

    std::vector<double>  Y;
    std::vector<Ym> ymSorted;
    std::vector<Ym> bests;
    vector<double> lines;
    //calcolo mobility function
    getMobilityFunction(Y,
                        ymSorted,
                        Fi,
                        rain,
                        rain_size,
                        activations,
                        activations_size,
                        size);

    qsort (&ymSorted[0], ymSorted.size(), sizeof(Ym),compareDouble);
    vector<int> TP;
    vector<int> FN;
    vector<int> FP;
    vector<int> TN;

    vector<double> TPR;
    vector<double> FPR;

    double dYcr;
    Ym ymMin;
    Ym ymMin2;
    double momentoDelPrimoOrdine;
    double AUC=getAUCROC(Y,
                         ymSorted,
                         Fi,
                         rain,
                         rain_size,
                         activations,
                         activations_size,
                         size,
                         dYcr,
                         ymMin,
                         ymMin2,
                         TP,
                         FN,
                         FP,
                         TN,
                         TPR,
                         FPR,
                         momentoDelPrimoOrdine,
                         bests,
                         lines,
                         numberOfLines); // Area under the curve



    ptrdiff_t pos = distance(MainWindow::threads.begin(), find(MainWindow::threads.begin(), MainWindow::threads.end(), this));

    emit this->updateROCPlot(pos,QVector<double>::fromStdVector(FPR),QVector<double>::fromStdVector(TPR),AUC);
    int indexPlot = getRightPlotFromName(namePlot);
    emit this->updateMobPlotAllInOne(pos,namePlot,rain,rain_size,activations, activations_size, Y,ymMin.getValue(),ymMin.getTime(), ymMin2.getValue(),ymMin2.getTime(),bests,widgetArray[indexPlot],arrowArray[indexPlot]);

    emit this->updateTextsValidationAllInOne(pos,namePlot,QString("%1").arg(AUC),
                                             QString("%1").arg(this->size),
                                             QString("%1").arg(dYcr),
                                             QString("%1").arg(momentoDelPrimoOrdine),
                                             QString("%1").arg(ymMin.getValue()),
                                             QString("%1").arg(ymMin2.getValue())
                                             );
     emit this->updateKernelPlot(pos,QVector<double>::fromStdVector(Fi),size);

    QString pathValidation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/workspace/validation/";
    QDir dirVal(pathValidation);
    if (!dirVal.exists()){
        dirVal.mkdir(".");
    }

    QString savePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/workspace/validation/"+projectName;

    QDir dir3(savePath);
    if (!dir3.exists()){
        dir3.mkdir(".");
    }

    savePath+="/metrics.csv";

    ofstream myfile;
    myfile.open (savePath.toStdString(),ios::out);

    myfile <<  "ztr ;";
    myfile <<  "TP ;";
    myfile <<  "FN ;";
    myfile <<  "FP ;";
    myfile <<  "TN ; \n";

    for (int i = 0; i < lines.size(); i++) {
        myfile << lines[i] <<";"<< TP[i] <<";"<< FN[i] <<";"<<FP[i] <<";"<< TN[i]<<";" << endl;
    }

    myfile.close();


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

    emit this->updateMobPlot(pos,rain,rain_size,activations, activations_size, Y,ymMin.getValue(),ymMin.getTime(), ymMin2.getValue(), ymMin2.getTime(),bests,widgetArray[0],arrowArray[0]);

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



void ValidationController::startValidationAllinOne(QString namePlot){

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
            if(ft == FitnessGMDn || ft == FitnessEqualWeights)
                for (int a = 0; a < activations_size; a++) {
                    if(diffTimeInterval(activations[a].getStart(), activations[a].getEnd(),rain[t].getTime())){
                        //                     cout << "salto un pico all'interno di un intervallo " << endl;
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
    if(ft == FitnessGMDn || ft == FitnessEqualWeights)
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
                if(ft == FitnessGMD || ft == FitnessGMDn)
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

    int indexPlot = getRightPlotFromName(namePlot);
//    emit this->updateMobPlotAllInOne(pos,namePlot,rain,rain_size,activations, activations_size, Y,ymMin.getValue(),ymMin.getTime(), ymMin2.getValue(), ymMin2.getTime(),bests,widgetArray[indexPlot],arrowArray[indexPlot]);

    QString tmp2 = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/workspace/validation/"+projectName;
    QDir dir3(tmp2);
    if (!dir3.exists()){
        dir3.mkdir(".");
    }

    tmp2 += "/mobilityFunction.csv";
    ofstream myfile;
    myfile.open (tmp2.toStdString(),ios::out);
    myfile << " x " << "; y " << endl;

    for (unsigned int  t = 0; t < rain_size; t++) {
        tm x = rain[t].getTime();
        double y = Y[t];
        int year = 1900 + x.tm_year;
        QString month;
        QString min;
        QString sec;
        QString hour;
        if(x.tm_mon < 10){
           month = QString("0%1").arg(x.tm_mon);
        }
        if(x.tm_mday < 10){
           month = QString("0%1").arg(x.tm_mday);
        }
        if(x.tm_min == 0){
           min = QString("00");
        }
        if(x.tm_sec == 0){
           sec = QString("00");
        }
        if(x.tm_hour == 0){
           hour = QString("00");
        }
        //cout << year << endl;

        myfile << year << "-" << month.toStdString() << "-" << x.tm_mday <<" " << hour.toStdString() << ":" << min.toStdString() << ":" << sec.toStdString()<< "."<<"000" << ";" << y<<endl;
    }

    myfile.close();



   // emit this->updateKernelPlot(pos,QVector<double>::fromStdVector(Fi),size);

    QString finalFitness;
    if(ft == FitnessGMD || ft == FitnessGMDn)
        finalFitness = QString("%1").arg((double) (f/fMax));
    if(ft == FitnessEqualWeights)
        finalFitness = QString("%1").arg((double) (f));

//    emit this->updateTextsValidationAllInOne(pos,namePlot,finalFitness,
//                                             QString("%1").arg(this->size),
//                                             QString("%1").arg(dYcr),
//                                             QString("%1").arg(momentoDelPrimoOrdine)
//                                             );
    emit this->updateTextsValidationAllInOneFitness(pos,namePlot,finalFitness);
    mainwindows->mutex.unlock();
    // mutex->unlock();
    //delete ym;

}

void ValidationController::startThread(){
    QThread::start();
}

