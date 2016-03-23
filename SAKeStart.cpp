#include "SAKeStart.h"

SAKeStart::SAKeStart(QQmlApplicationEngine* _engine,QApplication * _a,XMLManager * _xmlManager,QObject *parent) : QObject(parent)
{
    engine = _engine;
    a=_a;
    numberProject =0;
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
                         const QVariant &_elitists,
                         const QVariant &_thresholdKernel,
                         const QVariant &tipo
                         ){

    // **** converto e verifico che siano arrrivati dal QML tutti i parametri
      qDebug() << "Tipo arrivato " << tipo.toInt() << "\n";
    if(tipo.toInt()==1 )
    {
        xmlManager->SaveXMLFileAlreadyExist(_projectName.toString(),
                                selection.toString(),
                                _elitists.toString(),
                                _elitists.toString(),
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
                                _elitists.toString(),
                                _elitists.toString(),
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
    int      ielitists           = _elitists.toInt();
    float    fpropCrossover      = propCrossover.toFloat();
    float    fpropMutation       = propMutation.toFloat();
    float    fpme                = pme.toFloat();
    float    fpmb                = pmb.toFloat();
    double   dthresholdKernel     = _thresholdKernel.toDouble();

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
//       qDebug() << "ielitists arrivato " << ielitists << "\n";
    // FINE

    //Aggiungere nell'XML il nuovo Progetto

    //aggiungo una nuova Tab nell'interfaccia
    //INIZIO
    QVariant returnedValue;
    QVariant msg = sprojectname;
    QObject *rootObject = engine->rootObjects().first();
    QObject *rectMain = rootObject->findChild<QObject*>("Rectanglemain");
    numberProject++;


    QMetaObject::invokeMethod(rectMain, "addTab", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, msg),Q_ARG(QVariant, numberProject));
    //FINE

    //identifico i puntatori agli oggetti che in seguito dovrò aggiornare
    //INIZIO
    CustomPlotItem *qCustomPlotFitness = rootObject->findChild<CustomPlotItem*>(QString("customPlotFitness%1").arg(numberProject));
    CustomPlotMobilityFunction *qCustomPlotMobilityFunction = rootObject->findChild<CustomPlotMobilityFunction*>( QString("customPlotMobilityFunction%1").arg(numberProject) );
    CustomPlotKernel *qCustomPlotKernel = rootObject->findChild<CustomPlotKernel*>(QString("customPlotKernel%1").arg(numberProject) );
    QObject *gen = rootObject->findChild<QObject*>(QString("gen%1").arg(numberProject));
    QObject *currentMaximumFitness = rootObject->findChild<QObject*>(QString("currentMaximumFitness%1").arg(numberProject));
    QObject *absoluteMaximumFitness = rootObject->findChild<QObject*>(QString("absoluteMaximumFitness%1").arg(numberProject));
    QObject *currentAverageFitness = rootObject->findChild<QObject*>(QString("currentAverageFitness%1").arg(numberProject));
    QObject *absoluteAverageFitness = rootObject->findChild<QObject*>(QString("absoluteAverageFitness%1").arg(numberProject));
    QObject *progressBar = rootObject->findChild<QObject*>(QString("progressBar%1").arg(numberProject));
    QObject *tb = rootObject->findChild<QObject*>(QString("tb%1").arg(numberProject));
    QObject *deltaCritico = rootObject->findChild<QObject*>(QString("deltaCritico%1").arg(numberProject));
    QObject *momentoDelPrimoOrdine = rootObject->findChild<QObject*>(QString("momentoDelPrimoOrdine%1").arg(numberProject));


    QObject *buttonStop = rootObject->findChild<QObject*>(QString("stop%1").arg(numberProject));



    Update * update = new Update();
    UpdateProjects * updateprojects = new UpdateProjects(currentMaximumFitness,
                                                         absoluteMaximumFitness,
                                                         currentAverageFitness,
                                                         absoluteAverageFitness,
                                                         gen,
                                                         tb,
                                                         deltaCritico,
                                                         momentoDelPrimoOrdine,
                                                         update);


    SAKeController * controller = new SAKeController(qCustomPlotFitness,
                                                     sselection,
                                                     spattern,
                                                     sfilenameRain,
                                                     sfilenameActivation,
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
                                                     ielitists,
                                                     dthresholdKernel,
                                                     update,
                                                     sprojectname);
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


    QVariant returnedValue;
    QVariant msg = _projectName.toString();
    QObject *rootObject = engine->rootObjects().first();
    QObject *rectMain = rootObject->findChild<QObject*>("Rectanglemain");
    numberProject++;


    QMetaObject::invokeMethod(rectMain, "addTabValidation", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, msg),Q_ARG(QVariant, numberProject));
    //FINE

    //identifico i puntatori agli oggetti che in seguito dovrò aggiornare
    //INIZIO
    CustomPlotMobilityFunction *qCustomPlotMobilityFunction = rootObject->findChild<CustomPlotMobilityFunction*>( QString("customPlotMobilityFunction%1").arg(numberProject) );
    validationController->setPlotMobility(qCustomPlotMobilityFunction);
    validationController->updatePlot();

    CustomPlotKernel *qCustomPlotKernel = rootObject->findChild<CustomPlotKernel*>(QString("customPlotKernel%1").arg(numberProject) );
    validationController->setKernelPlot(qCustomPlotKernel);
    validationController->updateKernelPlot();

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


