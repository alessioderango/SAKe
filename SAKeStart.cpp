#include "SAKeStart.h"

SAKeStart::SAKeStart(QQmlApplicationEngine* _engine,QApplication * _a,XMLManager * _xmlManager,QObject *parent) : QObject(parent)
{
    engine = _engine;
    a=_a;
    xmlManager = _xmlManager;
}

int SAKeStart::existProjectName(const QVariant &_projectName){
    return xmlManager->findProjectName(_projectName.toString());

}

void SAKeStart::InitAlgo(const QVariant &selection,
                         const QVariant &pop,
                         const QVariant &maxGen,
                         const QVariant &tbMax,
                         const QVariant &tbMin,
                         const QVariant &dHpMax,
                         const QVariant &dHpMin,
                         const QVariant &propCrossover,
                         const QVariant &propMutation,
                         const QVariant &pme,
                         const QVariant &pmb,
                         const QVariant &pattern,
                         const QVariant &filename,
                         const QVariant &_filenameActivation,
                         const QVariant &_projectName,
                         const QVariant &_numberProcessor,
                         const QVariant &_para1,
                         const QVariant &_para2,
                         const QVariant &_lastGeneration,
                         const QVariant &tipo,
                         const QVariant &typeAlgorithm,
                         const QVariant &selectionOrder1,
                         const QVariant &selectionOrder2,
                         const QVariant &selectionOrder3,
                         const QVariant &selectionOrder4
                         ){

    // **** converto e verifico che siano arrrivati dal QML tutti i parametri
    qDebug() << "Tipo arrivato " << tipo.toInt() << "\n";
    if(tipo.toInt()==1 )
    {
        xmlManager->SaveXMLFileAlreadyExist(_projectName.toString(),
                                            selection.toString(),
                                            _para1.toString(),
                                            _para2.toString(),
                                            _numberProcessor.toString(),
                                            pop.toString(),
                                            maxGen.toString(),
                                            tbMax.toString(),
                                            tbMin.toString(),
                                            dHpMax.toString(),
                                            dHpMin.toString(),
                                            propCrossover.toString(),
                                            propMutation.toString(),
                                            pme.toString(),
                                            pmb.toString(),
                                            pattern.toString(),
                                            filename.toString(),
                                            _filenameActivation.toString());
    }else{
        xmlManager->SaveXMLFile(_projectName.toString(),
                                selection.toString(),
                                _para1.toString(),
                                _para2.toString(),
                                _numberProcessor.toString(),
                                pop.toString(),
                                maxGen.toString(),
                                tbMax.toString(),
                                tbMin.toString(),
                                dHpMax.toString(),
                                dHpMin.toString(),
                                propCrossover.toString(),
                                propMutation.toString(),
                                pme.toString(),
                                pmb.toString(),
                                pattern.toString(),
                                filename.toString(),
                                _filenameActivation.toString());
    }
    // INIZIO
    QString  sselection          = selection.toString();
    QString  spattern            = pattern.toString();
    QString  sfilenameRain       = filename.toString();
    QString  sfilenameActivation = _filenameActivation.toString();
    QString  sprojectname          = _projectName.toString();
    int      ipop                = pop.toInt();
    int      imaxGen             = maxGen.toInt();
    int      itbMax              = tbMax.toInt();
    int      itbMin              = tbMin.toInt();
    int      idHpMax             = dHpMax.toInt();
    int      idHpMin             = dHpMin.toInt();
    int      inumberProcessor    = _numberProcessor.toInt();
    int      ipara1=-1;
    QString  spara1="";
    if(QString::compare(_para1.toString(), "ordered", Qt::CaseInsensitive)==0||
            QString::compare(_para1.toString(), "unordered", Qt::CaseInsensitive)==0   )
    {
        spara1 = _para1.toString();
    }else{
        ipara1              = _para1.toInt();
    }
    int      ipara2              = _para2.toInt();
    int      itypeAlgorithm      = typeAlgorithm.toInt();
    float    fpropCrossover      = propCrossover.toFloat();
    float    fpropMutation       = propMutation.toFloat();
    float    fpme                = pme.toFloat();
    float    fpmb                = pmb.toFloat();
    bool     bLastGeneration     = _lastGeneration.toBool();

    //       qDebug() << "selection arrivato " << selection << "\n";
    //       qDebug() << "pattern arrivato " << pattern << "\n";
    //       qDebug() << "ipop arrivato " <<   pop << "\n";
    //       qDebug() << "imaxGen arrivato " << maxGen << "\n";
    //       qDebug() << "itbMax arrivato " <<   tbMax << "\n";
    //       qDebug() << "itbMin arrivato " <<   tbMin << "\n";
    //       qDebug() << "idHpMax arrivato " <<   dHpMax << "\n";
    //       qDebug() << "idHpMin arrivato " <<   dHpMin << "\n";
    //       qDebug() << "fpropCrossover arrivato " << propCrossover << "\n";
    //       qDebug() << "fpropMutation arrivato " << propMutation << "\n";
    //       qDebug() << "fpme arrivato " << pme << "\n";
    //       qDebug() << "fpmb arrivato " << pmb << "\n";
    //       qDebug() << "filename arrivato " << sfilenameRain << "\n";
    //       qDebug() << "sfilenameActivation arrivato " << sfilenameActivation << "\n";
    //       qDebug() << "_projectName  arrivato " << sprojectname << "\n";
    //       qDebug() << "_numberProcessor arrivato " << inumberProcessor << "\n";
    //       qDebug() << "ipara1 arrivato " << ipara1 << "\n";
    //       qDebug() << "ipara2 arrivato " << ipara2 << "\n";
    qDebug() << "selectionOrder1 arrivato " << selectionOrder1 << "\n";
    qDebug() << "selectionOrder2 arrivato " << selectionOrder2 << "\n";
    qDebug() << "selectionOrder3 arrivato " << selectionOrder3 << "\n";
    qDebug() << "selectionOrder4 arrivato " << selectionOrder4 << "\n";

    vector<QString> orders;
    orders.push_back(selectionOrder1.toString());
    orders.push_back(selectionOrder2.toString());
    orders.push_back(selectionOrder3.toString());
    orders.push_back(selectionOrder4.toString());

    // FINE


    //Aggiungere nell'XML il nuovo Progetto

    //aggiungo una nuova Tab nell'interfaccia
    //INIZIO
    QVariant returnedValue;
    QVariant msg = "Calibration - "+sprojectname;
    QObject *rootObject = engine->rootObjects().first();
    QObject *rectMain = rootObject->findChild<QObject*>("Rectanglemain");
    QObject *errorHandlerRain = rootObject->findChild<QObject*>("errorcsvRain");
    QObject *errorHandlerActivation = rootObject->findChild<QObject*>("errorcsvRain");
    Rain * rain;
    int rain_size;
    Activation * activation;
    int activation_size;
    int errorRain = HandlerCSV::loadCSVRain(sfilenameRain, rain, rain_size, errorHandlerRain);
    if(errorRain){
        int errorActivation = HandlerCSV::loadCSVActivation(sfilenameActivation, activation, activation_size, errorHandlerActivation);
        if(errorActivation){
            int idProject = threadsController.size();


            QMetaObject::invokeMethod(rectMain, "addTab", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, msg),Q_ARG(QVariant, idProject));
            //FINE

            //identifico i puntatori agli oggetti che in seguito dovrò aggiornare
            //INIZIO
            CustomPlotItem *qCustomPlotFitness = rootObject->findChild<CustomPlotItem*>(QString("customPlotFitness%1").arg(idProject));
            CustomPlotMobilityFunction *qCustomPlotMobilityFunction = rootObject->findChild<CustomPlotMobilityFunction*>( QString("customPlotMobilityFunction%1").arg(idProject) );
            CustomPlotKernel *qCustomPlotKernel = rootObject->findChild<CustomPlotKernel*>(QString("customPlotKernel%1").arg(idProject) );
            QObject *gen = rootObject->findChild<QObject*>(QString("gen%1").arg(idProject));
            QObject *currentMaximumFitness = rootObject->findChild<QObject*>(QString("currentMaximumFitness%1").arg(idProject));
            QObject *absoluteMaximumFitness = rootObject->findChild<QObject*>(QString("absoluteMaximumFitness%1").arg(idProject));
            QObject *currentAverageFitness = rootObject->findChild<QObject*>(QString("currentAverageFitness%1").arg(idProject));
            QObject *absoluteAverageFitness = rootObject->findChild<QObject*>(QString("absoluteAverageFitness%1").arg(idProject));
            QObject *progressBar = rootObject->findChild<QObject*>(QString("progressBar%1").arg(idProject));
            QObject *tb = rootObject->findChild<QObject*>(QString("tb%1").arg(idProject));
            QObject *deltaCritico = rootObject->findChild<QObject*>(QString("deltaCritico%1").arg(idProject));
            QObject *momentoDelPrimoOrdine = rootObject->findChild<QObject*>(QString("momentoDelPrimoOrdine%1").arg(idProject));


            QObject *buttonStop = rootObject->findChild<QObject*>(QString("stop%1").arg(idProject));


            Update * update = new Update();
            UpdateProjects * updateprojects = new UpdateProjects(update);
            updateprojects->UpdateProjectsSAke(currentMaximumFitness,
                                               absoluteMaximumFitness,
                                               currentAverageFitness,
                                               absoluteAverageFitness,
                                               gen,
                                               tb,
                                               deltaCritico,
                                               momentoDelPrimoOrdine);


            SAKeController * controller = new SAKeController(qCustomPlotFitness,
                                                             sselection,
                                                             spattern,
                                                             rain,
                                                             rain_size,
                                                             activation,
                                                             activation_size,
                                                             ipop,
                                                             imaxGen,
                                                             itbMax,
                                                             itbMin,
                                                             idHpMax,
                                                             idHpMin,
                                                             fpropCrossover,
                                                             fpropMutation,
                                                             fpme,
                                                             fpmb,
                                                             currentMaximumFitness,
                                                             absoluteMaximumFitness,
                                                             currentAverageFitness,
                                                             absoluteAverageFitness,
                                                             inumberProcessor,
                                                             ipara1,
                                                             ipara2,
                                                             spara1,
                                                             bLastGeneration,
                                                             update,
                                                             sprojectname,
                                                             orders,
                                                             itypeAlgorithm);
            std::cout << "OK" << std::endl;
            controller->setPlotMobility(qCustomPlotMobilityFunction);
            controller->setPlotkernel(qCustomPlotKernel);
            controller->setApplication(a);
            progressBar->setProperty("maximumValue",100);
            progressBar->setProperty("minimumValue",0);

            controller->setProgressBar(progressBar);
            //FINE
            QObject::connect(buttonStop, SIGNAL(clicked()),controller, SLOT( stopThread()));
            //eseguo l'algoritmo genetico e setto il segnale di stop
            std::cout << "OK" << std::endl;
            controller->startThread();
            threadsController.push_back(controller);
            std::cout << "OK" << std::endl;
        }
    }
}


void SAKeStart::startValidation(
        const QVariant &_projectName,
        const QVariant &filenameRainPath,
        const QVariant &filenameActivaionPath,
        const QVariant &filenameKernelPath,
        const QVariant &folderSave
        )
{


    ValidationController * validationController=new ValidationController(filenameRainPath.toString(),filenameActivaionPath.toString(),filenameKernelPath.toString(),folderSave.toString());
    int idProject = threadsController.size();

    QVariant returnedValue;
    QVariant msg = "Validation - "+_projectName.toString();
    QObject *rootObject = engine->rootObjects().first();
    QObject *rectMain = rootObject->findChild<QObject*>("Rectanglemain");



    QMetaObject::invokeMethod(rectMain, "addTabValidation", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, msg),Q_ARG(QVariant, idProject));
    //FINE

    //identifico i puntatori agli oggetti che in seguito dovrò aggiornare
    //INIZIO
    CustomPlotMobilityFunction *qCustomPlotMobilityFunction = rootObject->findChild<CustomPlotMobilityFunction*>( QString("customPlotMobilityFunction%1").arg(idProject) );
    validationController->setPlotMobility(qCustomPlotMobilityFunction);
    validationController->updatePlot();

    CustomPlotKernel *qCustomPlotKernel = rootObject->findChild<CustomPlotKernel*>(QString("customPlotKernel%1").arg(idProject) );
    validationController->setKernelPlot(qCustomPlotKernel);
    validationController->updateKernelPlot();
    SAKeController* tmp =new SAKeController();
    threadsController.push_back(tmp);
    
}

double getHMed(double *kernel, int SIZE){
    double sum=0;
    for (int i = 0; i < SIZE; i++) {
        sum+=kernel[i];
    }
    return sum/SIZE;

}

double getHMax(double *kernel, int SIZE){
    double max=-1;
    for (int i = 0; i < SIZE; i++) {
        if(max< kernel[i])
            max = kernel[i];
    }
    return max;

}

void initAlreadyConsidered(double *&alreadyConsidered, int SIZE){
    for (int i = 0; i < SIZE; i++) {
        alreadyConsidered[i]=-1;
    }
}

void stampa(double *kernel, int SIZE){
    for (int i = 0; i < SIZE; i++) {
        cout << kernel[i] << " ";
    }
    cout << endl;
}
int getInterset(double *kernel,double *&alreadyConsidered,double *&alreadyConsideredTemp,double boundary, int SIZE){
    int count=0;
    for (int i = 0; i < SIZE; i++) {
        if(alreadyConsidered[i]==-1  && kernel[i] >= boundary){
            alreadyConsideredTemp[i]=kernel[i];
            alreadyConsidered[i]=kernel[i];
            count++;
        }
    }
    return count;
}

void getPoints(double *&a,std::vector< double> &xVec,std::vector< double> &yVec, int SIZE){


    double sum=0;
    double x=0;
    int count=0;
    for (int i = 0; i < SIZE-1; i++) {
        if(a[i]!=-1){
            if(a[i+1]==-1 && a[i-1] ==-1){
                //write << i+1 << "; " << a[i] << "; " << endl;
                xVec.push_back(i+1);
                yVec.push_back(a[i]);
                cout << " x = " << i+1 << " y = " << a[i] << endl;
            }else{
                sum+=a[i];
                x+=i;
                count++;
                if(a[i+1]==-1){
                    //write << (x/count)+1 << "; " << sum/count << "; " << endl;
                    xVec.push_back((x/count)+1);
                    yVec.push_back(sum/count);
                    cout << " x = " << (x/count)+1 << " y = " << sum/count << endl;
                    sum=0;
                    count=0;
                    x=0;
                }
            }
        }
    }


}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / (double)RAND_MAX;
    return fMin + f * (fMax - fMin);
}


void SAKeStart::startRegression(   const QVariant &selection,
                                   const QVariant &selectionElitist,
                                   const QVariant &populationSize,
                                   const QVariant &percentageCrossover,
                                   const QVariant &percentageMutation,
                                   const  QVariant &percentageWeight,
                                   const  QVariant &numberProcessor,
                                   const  QVariant &numberGamma,
                                   const  QVariant& percentageGammaA,
                                   const  QVariant &percentageGammaB,
                                   const  QVariant &numberLinear,
                                   const  QVariant& percentageLinearA,
                                   const  QVariant &percentageLinearB,
                                   const  QVariant &maxGeneration,
                                   const  QVariant &fileurl)
{

    QString sselction= selection.toString();
    int iselectionElitist = selectionElitist.toInt();
    int ipopulationSize = populationSize.toInt();
    int imaxGeneration = maxGeneration.toInt();
    double dpercentageCrossover = percentageCrossover.toDouble();
    double dpercentageMutation = percentageMutation.toDouble();
    int inumberProcessor = numberProcessor.toInt();

    double dpercentageWeight  = percentageWeight.toDouble();
    int inumberGamma = numberGamma.toInt();
    double dpercentageGammaA = percentageGammaA.toDouble();
    double dpercentageGammaB = percentageGammaB.toDouble();
    int inumberLinear = numberLinear.toInt();
    double dpercentageLinearA = percentageLinearA.toDouble();
    double dpercentageLinearB = percentageLinearB.toDouble();
    QString sfileurl = fileurl.toString();

    qDebug() << "sselction : " << sselction ;
    qDebug() << "iselectionElitist : " << iselectionElitist   ;
    qDebug() << "ipopulationSize : " << ipopulationSize   ;
    qDebug() << "dpercentageCrossover : " << dpercentageCrossover   ;
    qDebug() << "dpercentageMutation : " << dpercentageMutation   ;
    qDebug() << "sselctiodpercentageWeightn : " << dpercentageWeight   ;
    qDebug() << "inumberProcessor : " << inumberProcessor   ;
    qDebug() << "inumberGamma : " << inumberGamma   ;
    qDebug() << "dpercentageGammaA : " << dpercentageGammaA   ;
    qDebug() << "dpercentageGammaB : " << dpercentageGammaB   ;
    qDebug() << "inumberLinear : " << inumberLinear   ;
    qDebug() << "dpercentageLinearA : " << dpercentageLinearA   ;
    qDebug() << "dpercentageLinearB : " << dpercentageLinearB   ;
    qDebug() << "imaxGeneration : " << imaxGeneration     ;
    qDebug() << "sfileurl : " << sfileurl     ;
    int idProject = threadsController.size();
    QObject *rootObject = engine->rootObjects().first();
    QObject *rectMain = rootObject->findChild<QObject*>("Rectanglemain");
    QVariant msg = "Regression - ";
    QVariant returnedValue;
    QMetaObject::invokeMethod(rectMain, "addTabRegression", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, msg),Q_ARG(QVariant, threadsController.size()));
    //FINE

    //identifico i puntatori agli oggetti che in seguito dovrò aggiornare
    //INIZIO
//    CustomPlotItem *qCustomPlotFitness = rootObject->findChild<CustomPlotItem*>(QString("customPlotFitness%1").arg(idProject));
    //    CustomPlotRegression *qCustomPlotRegression = rootObject->findChild<CustomPlotRegression*>( QString("customPlotRegression%1").arg(numberProject) );
    CustomPlotRegression *qCustomPlotRegression = rootObject->findChild<CustomPlotRegression*>( QString("customPlotRegression%1").arg(idProject) );
    QObject *gen = rootObject->findChild<QObject*>(QString("gen%1").arg(idProject));
    QObject *currentMaximumFitness = rootObject->findChild<QObject*>(QString("currentMaximumFitness%1").arg(idProject));
    QObject *absoluteMaximumFitness = rootObject->findChild<QObject*>(QString("absoluteMaximumFitness%1").arg(idProject));
    QObject *currentAverageFitness = rootObject->findChild<QObject*>(QString("currentAverageFitness%1").arg(idProject));
    QObject *absoluteAverageFitness = rootObject->findChild<QObject*>(QString("absoluteAverageFitness%1").arg(idProject));
    QObject *progressBar = rootObject->findChild<QObject*>(QString("progressBar%1").arg(idProject));

    QObject *buttonStop = rootObject->findChild<QObject*>(QString("stop%1").arg(idProject));


    Update * update = new Update();
    UpdateProjects * updateprojects = new UpdateProjects(update);
    updateprojects->UpdateProjectsRegression(currentMaximumFitness,
                                             absoluteMaximumFitness,
                                             currentAverageFitness,
                                             absoluteAverageFitness,
                                             gen);

    //    double percentualePeso=0.09,
    //            percentualeLineareA=0.01,
    //            percentualeLineareB=0.01,
    //            percentualeGammaA=0.06,
    //            percentualeGammaB=0.06;
    double percentualePeso=dpercentageWeight,
            percentualeLineareA=dpercentageGammaA,
            percentualeLineareB=dpercentageGammaB,
            percentualeGammaA=dpercentageLinearA,
            percentualeGammaB=dpercentageLinearB;

    int dimension=inumberGamma+inumberLinear;
   double * weight = new double[dimension];
   std::cout << "weight !!!!!!!!" << endl;

    for (int i = 0; i < inumberLinear; ++i) {
        weight[i] = 1;
    }
    for (int i = inumberLinear; i < dimension; ++i) {
        double tmp1=fRand(0,1);
        std::cout << tmp1 << endl;
        weight[i] = tmp1;
    }
    std::cout << "weight FINE!!!!!!!!" << endl;
//        weight[0]=1;
//        weight[1]=1;
//        weight[2]=0.073;
//        weight[3]=0.99;
//        weight[4]=0.83;
//        weight[5]=0.974;
//        weight[6]=0.907;

    int * functionType = new int[dimension];

    for (int i = 0; i < inumberLinear; ++i) {
        functionType[i]=0;
    }
    for (int i = inumberLinear; i < dimension; ++i) {
        functionType[i]=2;
    }

//        functionType[0]=0;
//        functionType[1]=0;
//        functionType[2]=2;
//        functionType[3]=2;
//        functionType[4]=2;
//        functionType[5]=2;
//        functionType[6]=2;

    Parameters *parameters = new Parameters[dimension];

    //              _genotype.addW(1);
    //              _genotype.addW(1);

    //                //gamma
    //              _genotype.addW(0.073);
    //              _genotype.addW(0.99);
    //              _genotype.addW(0.83);
    //              _genotype.addW(0.974);
    //              _genotype.addW(0.907);

    //              _genotype.addFunctionType(0);
    //              _genotype.addFunctionType(0);
    //              _genotype.addFunctionType(2);
    //              _genotype.addFunctionType(2);
    //              _genotype.addFunctionType(2);
    //              _genotype.addFunctionType(2);
    //              _genotype.addFunctionType(2);

    //              //linear par
//        Parameters tmp;
//        tmp.addParameters(0.000046);
//        tmp.addParameters(0);
//        parameters[0]=tmp;

//        Parameters tmp1;
//        tmp1.addParameters(-0.04);
//        tmp1.addParameters(0.55);
//        parameters[1]=tmp1;
//        //gamma par

//        Parameters tmp2;
//        tmp2.addParameters(52.9);
//        tmp2.addParameters(0.05);
//        parameters[2]=tmp2;

//        Parameters tmp3;
//        tmp3.addParameters(1000);
//        tmp3.addParameters(0.120119);
//        parameters[3]=tmp3;


//        Parameters tmp4;
//        tmp4.addParameters(899);
//        tmp4.addParameters(0.0173);
//        parameters[4]=tmp4;

//        Parameters tmp5;
//        tmp5.addParameters(4.37);
//        tmp5.addParameters(7.18);
//        parameters[5]=tmp5;

//        Parameters tmp6;
//        tmp6.addParameters(699);
//        tmp6.addParameters(40);
//        parameters[6]=tmp6;

    std::cout << "Parameters !!!!!!!!" << endl;
    for (int i = 0; i < inumberLinear; ++i) {
        Parameters tmp;
        double tmp1=fRand(0.00003,0.00008);
        std::cout <<tmp1<< std::endl;
        tmp.addParameters(tmp1);
        double tmp2=0.01;
        std::cout <<tmp2<< std::endl;
        tmp.addParameters(tmp2);
        parameters[i]=tmp;
    }
     std::cout << "Parameters FINE LINEAR!!!!!!!!" << endl;
    for (int i = inumberLinear; i < dimension; ++i) {
        Parameters tmp;
        double tmp1=fRand(0,1000);
        std::cout <<tmp1<< std::endl;
        tmp.addParameters(tmp1);
        double tmp2=fRand(0,1);
        std::cout <<tmp2<< std::endl;
        tmp.addParameters(tmp2);
        parameters[i]=tmp;
    }
//     std::cout << "Parameters FINE!!!!!!!!" << endl;
//#define SIZE 148

//    double kernel[SIZE]={0.0331607, 0, 0.0761892, 0.0299802, 0, 0.0308658, 0.0205697, 0.0215048, 0, 0.0119944, 0, 0.0409908, 0, 0.0083374, 0.0810852, 0, 0.0250647, 0, 0, 0.0400473, 0, 0, 0.0254148, 0, 0, 0.0131141, 0.0172503, 0.0432308, 0.0231627, 0, 0.0299524, 0.0166024, 0.0468721, 0, 0, 0.012991, 0.00460058, 0, 0, 0.0539517, 0.0041918, 0.0105375, 0, 0.0419468, 0, 0.00508404, 0.00906833, 0, 0.00123015, 0, 0, 0, 0, 0, 0, 0.0120725, 0.00637761, 0.00306278, 0.00116989, 0, 0.00104368, 0.0101821, 0, 0, 0, 0, 0.000840633, 0, 0, 0.00578786, 0.000361475, 0, 0.00212797, 0, 2.81101e-005, 0, 0, 0.000642682, 0, 7.75736e-005, 0, 0, 0.00150183, 0.000354716, 0, 0.00066226, 0.000382005, 0.00698852, 0, 0.000524334, 0, 0, 0, 0.00221679, 0, 0.00843141, 0.00281996, 0, 0.00582132, 0, 0.0072355, 0.00355681, 0, 0, 0, 0, 0, 0, 0.00324608, 0.00113272, 0, 0, 0, 0, 0.0133326, 0, 0, 0, 0, 0, 0.0219186, 0.000480746, 0, 0, 0.0123283, 0.011458, 0, 0, 0, 0, 0, 0.00487881, 0, 0, 0, 0, 0, 0.0167193, 0.0102274, 0.0110751, 0.00210047, 0, 0.00115638, 0.0228124, 0.00387118, 0, 0, 0};

//    double *p = new double[SIZE];
//    for (int i = 0; i < SIZE; ++i) {
//        p[i]=kernel[i];
//    }

        double *kernel;
        int size_kernel;
        double Delta_cr;
        HandlerCSV::loadCSVKernel(sfileurl,kernel,size_kernel,Delta_cr);
    RegressionController * regressionController= new RegressionController(
                percentualePeso,
                percentualeLineareA,
                percentualeLineareB,
                percentualeGammaA,
                percentualeGammaB,
                weight,
                dimension,
                functionType,
                dimension,
                parameters,
                dimension,
                size_kernel,
                kernel,
                iselectionElitist,
                ipopulationSize,
                imaxGeneration,
                dpercentageCrossover,
                dpercentageMutation,
                inumberProcessor
                );




    std::cout << "setQCustomPlotRegression" << std::endl;


    progressBar->setProperty("maximumValue",100);
    progressBar->setProperty("minimumValue",0);

    std::cout << "setQCustomPlotFitness" << std::endl;
    //    regressionController->setQCustomPlotFitness(qCustomPlotFitness);
    std::cout << "setQCustomPlotRegression" << std::endl;


    std::vector< double> x;
    std::vector< double> y;

    double hmed= getHMed(kernel,size_kernel);
    double hmax = getHMax(kernel,size_kernel);
    double hmed2= hmed/2;
    double hmedmax= (hmed+hmax)/2;

    cout << "hmax = " << hmax << endl;
    cout << "hmedmax = " << hmedmax << endl;
    cout << "hmed = "<< hmed << endl;
    cout << "hmed2 = " << hmed2 <<endl;

    //    double alreadyConsideredHMax[size_kernel];
    //    double alreadyConsideredHMedMax[size_kernel];
    //    double alreadyConsideredHMed[size_kernel];
    //    double alreadyConsideredHMed2[size_kernel];
    //    double alreadyConsidered[size_kernel];
    double *alreadyConsideredHMax = new double[size_kernel];
    double *alreadyConsideredHMedMax= new double[size_kernel];
    double *alreadyConsideredHMed= new double[size_kernel];
    double *alreadyConsideredHMed2= new double[size_kernel];
    double *alreadyConsidered= new double[size_kernel];
    initAlreadyConsidered(alreadyConsidered,size_kernel);
    initAlreadyConsidered(alreadyConsideredHMax,size_kernel);
    initAlreadyConsidered(alreadyConsideredHMedMax,size_kernel);
    initAlreadyConsidered(alreadyConsideredHMed,size_kernel);
    initAlreadyConsidered(alreadyConsideredHMed2,size_kernel);
    int count = getInterset(kernel,alreadyConsidered,alreadyConsideredHMax,hmax,size_kernel);
    cout << "ho trovato " << count << " barre superiori a " << hmax << endl;
    count=getInterset(kernel,alreadyConsidered,alreadyConsideredHMedMax,hmedmax,size_kernel);
    cout << "ho trovato " << count << " barre superiori a " << hmedmax << endl;
    count=getInterset(kernel,alreadyConsidered,alreadyConsideredHMed,hmed,size_kernel);
    cout << "ho trovato " << count << " barre superiori a " << hmed << endl;
    count=getInterset(kernel,alreadyConsidered,alreadyConsideredHMed2,hmed2,size_kernel);
    cout << "ho trovato " << count << " barre superiori a " << hmed2 << endl;
    //stampa(alreadyConsideredHMax);
    //stampa(alreadyConsideredHMedMax);
    //stampa(alreadyConsideredHMed);
    //stampa(alreadyConsideredHMed2);
    cout << " points from hmax" << endl;
    getPoints(alreadyConsideredHMax,x,y,size_kernel);
    cout << " points from hmedhmax" << endl;
    getPoints(alreadyConsideredHMedMax,x,y,size_kernel);
    cout << " points from hmed" << endl;
    getPoints(alreadyConsideredHMed,x,y,size_kernel);
    cout << " points from hmed2" << endl;
    getPoints(alreadyConsideredHMed2,x,y,size_kernel);
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] <<" " << y[i] << endl;
    }


    int alto;
    for (alto = x.size() - 1; alto > 0; alto-- )
    {
        for (int i=0; i<alto; i++)
        {
            if (x[i]>x[i+1]) /* sostituire ">" con "<" per avere un ordinamento decrescente */
            {
                double tmp = x[i];
                x[i] = x[i+1];
                x[i+1] = tmp;
                double tmp2 = y[i];
                y[i] = y[i+1];
                y[i+1] = tmp2;

            }
        }
    }

    delete [] alreadyConsideredHMax;
    delete [] alreadyConsideredHMedMax;
    delete [] alreadyConsideredHMed;
    delete [] alreadyConsideredHMed2;
    delete [] alreadyConsidered;

    for (int i = 0; i < x.size(); i++) {
        cout << x[i] <<" " << y[i] << endl;
    }
    regressionController->setQCustomPlotRegression(qCustomPlotRegression);
    qCustomPlotRegression->setupQuadraticDemo(&y[0],y.size(),&x[0],x.size());
    regressionController->setX(x);
    regressionController->setY(y);

    regressionController->setProgressBar(progressBar);
    regressionController->setCurrentAverageFitness(currentAverageFitness);
    regressionController->setCurrentMaximumFitness(currentMaximumFitness);
    regressionController->setAbsoluteAverageFitness(absoluteAverageFitness);
    regressionController->setAbsoluteMaximumFitness(absoluteMaximumFitness);
    regressionController->setUpdate(update);
    //FINE
    QObject::connect(buttonStop, SIGNAL(clicked()),regressionController, SLOT( stopThread()));
    //eseguo l'algoritmo genetico e setto il segnale di stop

    regressionController->startThread();
    threadsController.push_back(regressionController);
}


QVariantList SAKeStart::getAllElementsFromProjectName(const QVariant &_projectName){
    return xmlManager->getAllElementsFromProjectName(_projectName.toString());
}

string SAKeStart::getPattern() const
{
    return pattern;
}

void SAKeStart::setPattern(const string &value)
{
    pattern = value;
}

float SAKeStart::getPmb() const
{
    return Pmb;
}

void SAKeStart::setPmb(float value)
{
    Pmb = value;
}

float SAKeStart::getPme() const
{
    return Pme;
}

void SAKeStart::setPme(float value)
{
    Pme = value;
}

float SAKeStart::getDHpMax() const
{
    return dHpMax;
}

void SAKeStart::setDHpMax(float value)
{
    dHpMax = value;
}

float SAKeStart::getDHpMin() const
{
    return dHpMin;
}

void SAKeStart::setDHpMin(float value)
{
    dHpMin = value;
}

float SAKeStart::getTbMax() const
{
    return tbMax;
}

void SAKeStart::setTbMax(float value)
{
    tbMax = value;
}

float SAKeStart::getTbMin() const
{
    return tbMin;
}

void SAKeStart::setTbMin(float value)
{
    tbMin = value;
}

float SAKeStart::getPropCrossover() const
{
    return propCrossover;
}

void SAKeStart::setPropCrossover(float value)
{
    propCrossover = value;
}

float SAKeStart::getPropMutation() const
{
    return propMutation;
}

void SAKeStart::setPropMutation(float value)
{
    propMutation = value;
}

float SAKeStart::getRelRateMutation() const
{
    return relRateMutation;
}

void SAKeStart::setRelRateMutation(float value)
{
    relRateMutation = value;
}

float SAKeStart::getRelRateCrossover() const
{
    return relRateCrossover;
}

void SAKeStart::setRelRateCrossover(float value)
{
    relRateCrossover = value;
}

int SAKeStart::getMaxGen() const
{
    return maxGen;
}

void SAKeStart::setMaxGen(int value)
{
    maxGen = value;
}

int SAKeStart::getPopSize() const
{
    return popSize;
}

void SAKeStart::setPopSize(int value)
{
    popSize = value;
}

string SAKeStart::getReplecament() const
{
    return replecament;
}

void SAKeStart::setReplecament(const string &value)
{
    replecament = value;
}

string SAKeStart::getSelection() const
{
    return selection;
}

void SAKeStart::setSelection(const string &value)
{
    selection = value;
}

void SAKeStart::update(){

    qApp->processEvents();
}

void SAKeStart::stopSAKeController(int count){
    cout << "count " << count << endl;
    cout << "threadsSakeController.size() " << threadsController.size() << endl;
    if(threadsController[count]->isRunning ()){
        ((SAKeController*) threadsController[count])->stopThread();
        while(threadsController[count]->isRunning ()){

        }

        threadsController.erase(threadsController.begin() + (count));
    }
}
void SAKeStart::stopValidationController(int count){
    cout << "count " << count << endl;
    cout << "threadsSakeController.size() " << threadsController.size() << endl;
    //        if(threadsController[count]->isRunning ()){
    //            ((ValidationController*)threadsController[count])->stopThread();
    //            while(threadsController[count]->isRunning ()){

    //            }
    //        }
    threadsController.erase(threadsController.begin() + (count));
}
void SAKeStart::stopRegressionController(int count){
    cout << "count " << count << endl;
    cout << "threadsSakeController.size() " << threadsController.size() << endl;
    if(threadsController[count]->isRunning ()){
        ((RegressionController*) threadsController[count])->stopThread();
        while(threadsController[count]->isRunning ()){

        }
    }
    threadsController.erase(threadsController.begin() + (count));
}

//void SAKeStart::updateCurrentMaximumFitness(QString s){

//    _currentMaximumFitness->setProperty("text",s);
//}

//void SAKeStart::updateAbosulteMaximumFitness(QString s){

//    _absoluteMaximumFitness->setProperty("text",s);
//}

//void SAKeStart::updateCurrentAvarageFitness(QString s){

//    _currentAverageFitness->setProperty("text",s);
//}

//void SAKeStart::updateAbsoluteAvarageFitness(QString s){

//    _absoluteAverageFitness->setProperty("text",s);
//}
//void SAKeStart::updateGen(QString s){

//    _gen->setProperty("text",s);
//}


