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
                         const QVariant &propSelection,
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
                         const QVariant &selectionOrder4,
                         const QVariant &numberElitist
                         ){

    // **** converto e verifico che siano arrrivati dal QML tutti i parametri

    if(tipo.toInt()==1 )
    {
        xmlManager->SaveXMLFileAlreadyExistCalibrationProject(_projectName.toString(),
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
                                                              propSelection.toString(),
                                                              propCrossover.toString(),
                                                              propMutation.toString(),
                                                              pme.toString(),
                                                              pmb.toString(),
                                                              pattern.toString(),
                                                              filename.toString(),
                                                              _filenameActivation.toString(),
                                                              typeAlgorithm.toString(),
                                                              numberElitist.toString());
    }else{
        xmlManager->SaveXMLFileCalibrationProject(_projectName.toString(),
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
                                                  propSelection.toString(),
                                                  propCrossover.toString(),
                                                  propMutation.toString(),
                                                  pme.toString(),
                                                  pmb.toString(),
                                                  pattern.toString(),
                                                  filename.toString(),
                                                  _filenameActivation.toString(),
                                                  typeAlgorithm.toString(),
                                                  numberElitist.toString());
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

           qDebug() << "selection arrivato " << selection << "\n";
           qDebug() << "pattern arrivato " << pattern << "\n";
           qDebug() << "ipop arrivato " <<   pop << "\n";
           qDebug() << "imaxGen arrivato " << maxGen << "\n";
           qDebug() << "itbMax arrivato " <<   tbMax << "\n";
           qDebug() << "itbMin arrivato " <<   tbMin << "\n";
           qDebug() << "idHpMax arrivato " <<   dHpMax << "\n";
           qDebug() << "idHpMin arrivato " <<   dHpMin << "\n";
           qDebug() << "fpropCrossover arrivato " << propCrossover << "\n";
           qDebug() << "fpropMutation arrivato " << propMutation << "\n";
           qDebug() << "fpme arrivato " << pme << "\n";
           qDebug() << "fpmb arrivato " << pmb << "\n";
           qDebug() << "filename arrivato " << sfilenameRain << "\n";
           qDebug() << "sfilenameActivation arrivato " << sfilenameActivation << "\n";
           qDebug() << "_projectName  arrivato " << sprojectname << "\n";
           qDebug() << "_numberProcessor arrivato " << inumberProcessor << "\n";
           qDebug() << "ipara1 arrivato " << ipara1 << "\n";
           qDebug() << "ipara2 arrivato " << ipara2 << "\n";
    qDebug() << "selectionOrder1 arrivato " << selectionOrder1 << "\n";
    qDebug() << "selectionOrder2 arrivato " << selectionOrder2 << "\n";
    qDebug() << "selectionOrder3 arrivato " << selectionOrder3 << "\n";
    qDebug() << "selectionOrder4 arrivato " << selectionOrder4 << "\n";
    qDebug() << "numberElitist arrivato " << numberElitist << "\n";
    qDebug() << "tipo arrivato " << tipo << "\n";

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
    Rain * rain;
    int rain_size;
    Activation * activation;
    int activation_size;
    QObject *errorHandlerRain = rootObject->findChild<QObject*>("errorcsvRain");
    QObject *errorHandlerActivation = rootObject->findChild<QObject*>("errorcsvActivation");
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
            controller->setPropSelection(propSelection.toFloat());
            controller->setPlotMobility(qCustomPlotMobilityFunction);
            controller->setPlotkernel(qCustomPlotKernel);
            controller->setApplication(a);
            progressBar->setProperty("maximumValue",100);
            progressBar->setProperty("minimumValue",0);

            controller->setProgressBar(progressBar);
            //FINE
            QObject::connect(buttonStop, SIGNAL(clicked()),controller, SLOT( stopThread()));
            //eseguo l'algoritmo genetico e setto il segnale di stop
            controller->startThread();
            threadsController.push_back(controller);
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
    Rain * rain;
    int rain_size;
    Activation * activation;
    int activation_size;
    double * Fi;
    int size_Fi;
    double zCr;
    QObject *rootObject = engine->rootObjects().first();

    QObject *errorHandler = rootObject->findChild<QObject*>("errorcsvHandler");

    int errorRain = HandlerCSV::loadCSVRain(filenameRainPath.toString(), rain, rain_size, errorHandler);
    if(errorRain){
        int errorActivation = HandlerCSV::loadCSVActivation(filenameActivaionPath.toString(), activation, activation_size, errorHandler);
        if(errorActivation){
            int errorKernel = HandlerCSV::loadCSVKernel(filenameKernelPath.toString(), Fi, size_Fi,zCr);
//            if(errorKernel){
                ValidationController * validationController=new ValidationController(
                            rain,
                            rain_size,
                            activation,
                            activation_size,
                            Fi,
                            size_Fi,
                            zCr
                            );
                int idProject = threadsController.size();
//                validationController->setActivations(activation);
//                validationController->setActivations_size(activation_size);
//                validationController->setRain(rain);
//                validationController->setRain_size(rain_size);
                QVariant returnedValue;
                QVariant msg = "Validation - "+_projectName.toString();
                QObject *rectMain = rootObject->findChild<QObject*>("Rectanglemain");

                QMetaObject::invokeMethod(rectMain, "addTabValidation", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, msg),Q_ARG(QVariant, idProject));
                //FINE

                //identifico i puntatori agli oggetti che in seguito dovrò aggiornare
                //INIZIO
                CustomPlotMobilityFunction *qCustomPlotMobilityFunction = rootObject->findChild<CustomPlotMobilityFunction*>( QString("customPlotMobilityFunction%1").arg(idProject) );
                QObject *fitness = rootObject->findChild<QObject*>(QString("fitness%1").arg(idProject));
                QObject *tb = rootObject->findChild<QObject*>(QString("tb%1").arg(idProject));
                QObject *deltaCritico = rootObject->findChild<QObject*>(QString("deltaCritico%1").arg(idProject));
                QObject *momentoDelPrimoOrdine = rootObject->findChild<QObject*>(QString("momentoDelPrimoOrdine%1").arg(idProject));
                validationController->setDeltaCritico(deltaCritico);
                validationController->setMomentoDelPrimoOrdine(momentoDelPrimoOrdine);
                validationController->setTb(tb);
                validationController->setPlotMobility(qCustomPlotMobilityFunction);
                validationController->setFitness(fitness);
                validationController->updatePlot();

                CustomPlotKernel *qCustomPlotKernel = rootObject->findChild<CustomPlotKernel*>(QString("customPlotKernel%1").arg(idProject) );


                validationController->setKernelPlot(qCustomPlotKernel);
                validationController->updateKernelPlot();
                SAKeController* tmp =new SAKeController();


                threadsController.push_back(tmp);



            }
        }
    //}

    
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / (double)RAND_MAX;
    return fMin + f * (fMax - fMin);
}


void SAKeStart::startRegression(   const QVariant &_projectaname,
                                   const QVariant &selection,
                                   const QVariant &selectionElitist,
                                   const QVariant &populationSize,
                                   const QVariant &percentageCrossover,
                                   const QVariant &percentageMutation,
                                   const QVariant &numberProcessor,
                                   const QVariant &maxGeneration,
                                   const QVariant &fileurl,
                                   const QVariant &tipo,
                                   const QVariantList &matrxGamma1QML,
                                   const QVariantList &matrixGamma2QML,
                                   const QVariantList &matrixLinearQML,
                                   const QVariant &checkControlpoints,
                                   const QVariant &checkKernel,
                                   const QVariant &checkN,
                                   const QVariant &checkControlPointsWithN,
                                   const QVariant &textN,
                                   const QVariant &para1,
                                   const QVariant &para2,
                                   const QVariant &itypeAlgorithm,
                                   const QVariant &propSelection
                                   )
{
    std::vector<std::vector<double> > matrixGamma1;
    int numberElementsTable = 12;
    QList <QVariant> tmpGamma1 = matrxGamma1QML[0].toList();
    for (int i = 1; i < tmpGamma1[0].toInt()+1; ++i) {
        QList <QVariant> tmpGammat1 = matrxGamma1QML[i].toList();
        std::vector<double> tmp;
        for (int j = 0; j < numberElementsTable; ++j) {
            cout << tmpGammat1[j].toDouble() << " ";
            tmp.push_back(tmpGammat1[j].toDouble());
        }
        matrixGamma1.push_back(tmp);
        cout << endl;
    }

    std::vector<std::vector<double> > matrixGamma2;
    QList <QVariant> tmpGamma2 = matrixGamma2QML[0].toList();
    for (int i = 1; i < tmpGamma2[0].toInt()+1; ++i) {
        QList <QVariant> tmpGammat2 = matrixGamma2QML[i].toList();
        std::vector<double> tmp;
        for (int j = 0; j < numberElementsTable; ++j) {
            cout << tmpGammat2[j].toDouble() << " ";
            tmp.push_back(tmpGammat2[j].toDouble());
        }
        matrixGamma2.push_back(tmp);
        cout << endl;
    }

    std::vector<std::vector<double> > matrixLinear;
    QList <QVariant> tmpGamma3 = matrixLinearQML[0].toList();
    for (int i = 1; i < tmpGamma3[0].toInt()+1; ++i) {
        QList <QVariant> tmpGammat3 = matrixLinearQML[i].toList();
        std::vector<double> tmp;
        for (int j = 0; j < numberElementsTable; ++j) {
            cout << tmpGammat3[j].toDouble() << " ";
            tmp.push_back(tmpGammat3[j].toDouble());
        }
        matrixLinear.push_back(tmp);
        cout << endl;
    }

    QString typeExecution="0";
    if(checkKernel.toBool()){
        typeExecution="1";
    }else
        if(checkN.toBool()){
            typeExecution="2";
        }
    if(tipo.toInt()==1 )
    {
        xmlManager->SaveXMLFileAlreadyExistRegressionProject(_projectaname.toString(),
                                                             selection.toString(),
                                                             selectionElitist.toString(),
                                                             "-1",
                                                             populationSize.toString(),
                                                             percentageCrossover.toString(),
                                                             percentageMutation.toString(),
                                                             numberProcessor.toString(),
                                                             maxGeneration.toString(),
                                                             fileurl.toString(),
                                                             matrixGamma1,
                                                             matrixGamma2,
                                                             matrixLinear,
                                                             checkControlPointsWithN,
                                                             textN,
                                                             typeExecution);


    }else{
        xmlManager->SaveXMLFileRegressionProject(_projectaname.toString(),
                                                 selection.toString(),
                                                 selectionElitist.toString(),
                                                 "-1",
                                                 populationSize.toString(),
                                                 percentageCrossover.toString(),
                                                 percentageMutation.toString(),
                                                 numberProcessor.toString(),
                                                 maxGeneration.toString(),
                                                 fileurl.toString(),
                                                 matrixGamma1,
                                                 matrixGamma2,
                                                 matrixLinear,
                                                 checkControlPointsWithN,
                                                 textN,
                                                 typeExecution);
    }

    QString sselction= selection.toString();
    int iselectionElitist = selectionElitist.toInt();
    int ipopulationSize = populationSize.toInt();
    int imaxGeneration = maxGeneration.toInt();
    double dpercentageCrossover = percentageCrossover.toDouble();
    double dpercentageMutation = percentageMutation.toDouble();
    int inumberProcessor = numberProcessor.toInt();
    QString sfileurl = fileurl.toString();
    bool checkControlPointsBool = checkControlpoints.toBool();
    bool checkKernelBool = checkKernel.toBool();
    bool checkNBool = checkN.toBool();
    bool checkControlPointsWithNBool = checkControlPointsWithN.toBool();
    int n = textN.toInt();

    //    qDebug() << "sselction : " << sselction ;
    //    qDebug() << "iselectionElitist : " << iselectionElitist   ;
    //    qDebug() << "ipopulationSize : " << ipopulationSize   ;
    //    qDebug() << "dpercentageCrossover : " << dpercentageCrossover   ;
    //    qDebug() << "dpercentageMutation : " << dpercentageMutation   ;
    //    qDebug() << "sselctiodpercentageWeightn : " << dpercentageWeight   ;
    //    qDebug() << "inumberProcessor : " << inumberProcessor   ;
    //    qDebug() << "inumberGamma : " << inumberGamma   ;
    //    qDebug() << "dpercentageGammaA : " << dpercentageGammaA   ;
    //    qDebug() << "dpercentageGammaB : " << dpercentageGammaB   ;
    //    qDebug() << "inumberLinear : " << inumberLinear   ;
    //    qDebug() << "dpercentageLinearA : " << dpercentageLinearA   ;
    //    qDebug() << "dpercentageLinearB : " << dpercentageLinearB   ;
    //    qDebug() << "imaxGeneration : " << imaxGeneration     ;
    //    qDebug() << "sfileurl : " << sfileurl     ;
    int idProject = threadsController.size();
    QObject *rootObject = engine->rootObjects().first();
    QObject *rectMain = rootObject->findChild<QObject*>("Rectanglemain");
    QVariant msg = "Regression - "+ _projectaname.toString();
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
    progressBar->setProperty("maximumValue",100);
    progressBar->setProperty("minimumValue",0);
    qCustomPlotRegression->setNumber_of_function(matrixGamma1.size()+matrixGamma2.size()+matrixLinear.size());

    QObject *buttonStop = rootObject->findChild<QObject*>(QString("stop%1").arg(idProject));


    Update * update = new Update();
    UpdateProjects * updateprojects = new UpdateProjects(update);
    updateprojects->UpdateProjectsRegression(currentMaximumFitness,
                                             absoluteMaximumFitness,
                                             currentAverageFitness,
                                             absoluteAverageFitness,
                                             gen);

    int dimension=matrixGamma1.size()+matrixGamma2.size()+matrixLinear.size();
    double * weight = new double[dimension];
    int count =0;
    for (int i = 0; i < matrixLinear.size(); ++i) {
        double tmp1=fRand(matrixLinear[i][4],matrixLinear[i][5]);
        weight[count] = tmp1;
        count++;
    }
    for (int i = 0; i < matrixGamma1.size(); ++i) {
        double tmp1=fRand(matrixGamma1[i][4],matrixGamma1[i][5]);
        weight[count] = tmp1;
        count++;
    }
    for (int i = 0; i <  matrixGamma2.size(); ++i) {
        double tmp1=fRand(matrixGamma2[i][4],matrixGamma2[i][5]);
        weight[count] = tmp1;
        count++;
    }

    int * functionType = new int[dimension];

    double * percantageGammaA;
    percantageGammaA= new double[dimension];
    double * percantageGammaB;
    percantageGammaB= new double[dimension];
    double * percantageLinearA;
    percantageLinearA= new double[dimension];
    double * percantageLinearB;
    percantageLinearB= new double[dimension];
    double * percantageW;
    percantageW= new double[dimension];
    double* translation= new double[dimension];

    count = 0;
    for (int i = 0; i < matrixLinear.size(); ++i) {
        functionType[count]=0;
        percantageLinearA[count]=matrixLinear[i][6];
        percantageLinearB[count]=matrixLinear[i][7];
        percantageW[count]=matrixLinear[i][8];
        translation[count] = matrixLinear[i][11];
        count++;
    }
    for (int i = 0; i < matrixGamma1.size(); ++i) {
        functionType[count]=1;
        percantageGammaA[count]=(matrixGamma1[i][6]);
        percantageGammaB[count]=(matrixGamma1[i][7]);
        percantageW[count]=(matrixGamma1[i][8]);
        translation[count] =matrixGamma1[i][11];
        count++;
    }
    for (int i =  0; i <  matrixGamma2.size(); ++i) {
        functionType[count]=2;
        percantageGammaA[count]=(matrixGamma2[i][6]);
        percantageGammaB[count]=(matrixGamma2[i][7]);
        percantageW[count]=matrixGamma2[i][8];
        translation[count] =matrixGamma2[i][11];
        count++;
    }

    Parameters *parameters = new Parameters[dimension];

    count = 0;
    for (int i = 0; i < matrixLinear.size(); ++i) {
        Parameters tmp;
        double tmp1=fRand(matrixLinear[i][0],matrixLinear[i][1]);
        //std::cout <<tmp1<< std::endl;
        tmp.addParameters(tmp1);
        double tmp2=fRand(matrixLinear[i][2],matrixLinear[i][3]);
        //std::cout <<tmp2<< std::endl;
        tmp.addParameters(tmp2);
        double tmp3=fRand(matrixLinear[i][9],matrixLinear[i][10]);
        //std::cout <<tmp3<< std::endl;
        tmp.addParameters(tmp3);
        parameters[count]=tmp;
        count++;
    }

    for (int i = 0; i < matrixGamma1.size(); ++i) {
        Parameters tmp;
        double tmp1=fRand(matrixGamma1[i][0],matrixGamma1[i][1]);
        //std::cout <<tmp1<< std::endl;
        tmp.addParameters(tmp1);
        double tmp2=fRand(matrixGamma1[i][2],matrixGamma1[i][3]);
        //std::cout <<tmp2<< std::endl;
        tmp.addParameters(tmp2);
        double tmp3=fRand(matrixGamma1[i][9],matrixGamma1[i][10]);
        //std::cout <<tmp3<< std::endl;
        tmp.addParameters(tmp3);
        parameters[count]=tmp;
        count++;

    }
    for (int i = 0; i < matrixGamma2.size(); ++i) {
        Parameters tmp;
        double tmp1=fRand(matrixGamma2[i][0],matrixGamma2[i][1]);
        //std::cout <<tmp1<< std::endl;
        tmp.addParameters(tmp1);
        double tmp2=fRand(matrixGamma2[i][2],matrixGamma2[i][3]);
        //std::cout <<tmp2<< std::endl;
        tmp.addParameters(tmp2);
        double tmp3=fRand(matrixGamma2[i][9],matrixGamma2[i][10]);
        //std::cout <<tmp3<< std::endl;
        tmp.addParameters(tmp3);
        parameters[count]=tmp;
        count++;

    }

    double *kernel;
    int size_kernel;
    double Delta_cr;
    QObject *errorHandler = rootObject->findChild<QObject*>("errorcsvHandler");
    int errorRain = HandlerCSV::loadCSVKernel(sfileurl,kernel,size_kernel,Delta_cr, errorHandler);
    //HandlerCSV::loadCSVKernel(sfileurl,kernel,size_kernel,Delta_cr,errorRain);
    RegressionController * regressionController= new RegressionController(
                _projectaname.toString(),
                percantageW,
                percantageLinearA,
                percantageLinearB,
                percantageGammaA,
                percantageGammaB,
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
                inumberProcessor,
                translation,
                propSelection.toInt(),
                para1.toInt(),
                para2.toInt(),
                itypeAlgorithm.toInt(),
                selection.toString()
                );

    std::vector< double> x;
    std::vector< double> y;

    ControlPoints * controlPoints = new ControlPoints();
    //TODO
    if(checkControlPointsBool)
    {
        controlPoints->calculateControlPoints(kernel,size_kernel);
        x = controlPoints->getX();
        y = controlPoints->getY();
    }else
        if(checkKernelBool){
            std::vector< double> tmp(kernel,kernel+size_kernel);
            y = tmp;
            for(int i=0; i< size_kernel; i++){
                x.push_back(i+1);
            }
        }else
            if(checkNBool){
                if( checkControlPointsWithNBool){
                    controlPoints->calculateControlPoints(kernel,size_kernel);
                    controlPoints->getSubdividePointsFromControlPoints(controlPoints->getX(),controlPoints->getY(),n,x,y);
                }else
                {
                    controlPoints->calculateControlPoints(kernel,size_kernel);
                    controlPoints->getSubdividePointsFromKernel(kernel,size_kernel,n,x,y);
                }

            }

    delete controlPoints;

    qCustomPlotRegression->setX(x);


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

bool SAKeStart::deleteProject(const QVariant & idProject){
    bool tmp = xmlManager->deleteProject(idProject.toInt());
     xmlManager->ReadCalibrationProjectXML();
     return tmp;
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

void SAKeStart::openFile(const QVariant &filePath)
{
    QDesktopServices::openUrl(QUrl(filePath.toString(), QUrl::TolerantMode));
}

void SAKeStart::stopSAKeController(int count){
    cout << "count " << count << endl;
    cout << "threadsSakeController.size() " << threadsController.size() << endl;
    if(threadsController[count]->isRunning ()){
        ((SAKeController*) threadsController[count])->stopThread();
        while(threadsController[count]->isRunning ()){

        }

        threadsController[count]=NULL;
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
    threadsController[count]=NULL;
}
void SAKeStart::stopRegressionController(int count){
    cout << "count " << count << endl;
    cout << "threadsSakeController.size() " << threadsController.size() << endl;
    if(threadsController[count]->isRunning ()){
        ((RegressionController*) threadsController[count])->stopThread();
        while(threadsController[count]->isRunning ()){

        }
    }
    threadsController[count]=NULL;
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


