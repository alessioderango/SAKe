#include "SAKeController.h"

bool fileExists(QString path) {
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}
SAKeController::SAKeController(){

}

SAKeController::SAKeController(CustomPlotItem *& _qCustomPlot,
                               QString  sselection,
                               QString  spattern,
                               Rain *rain,
                               int rain_size,
                               Activation * activation,
                               int activation_size,
                               int      ipop,
                               int      imaxGen,
                               int      itbMax,
                               int      itbMin,
                               int      idHpMax,
                               int      idHpMin,
                               float    fpropCrossover,
                               float    fpropMutation,
                               float    fpme,
                               float    fpmb,
                               QObject *_currentMaximumFitness,
                               QObject *_absoluteMaximumFitness,
                               QObject *_currentAverageFitness,
                               QObject *_absoluteAverageFitness,
                               int _numberofProcessor,
                               int para1,
                               int para2,
                               QString spara1,
                               bool _lastGeneration,
                               Update* _update,
                               const QString& projectName,
                               vector<QString> orders,
                               int itypeAlgorithm)

{

    this->rain=rain;
    this->rain_size = rain_size;
    this->activations=activation;
    this->activations_size = activation_size;
    typeAlgorithm =itypeAlgorithm;
    this->start=false;
    this->finish=true;
    qCustomPlot = _qCustomPlot;
    qCustomPlot->initCustomPlotFitness();
    try {
        // db.getConnection();
        //db.executeQueryRain(this->rain,this->rain_size);
        //db.executeQueryActivation(activations,activations_size);
        // db.disconnect();

    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        //       return 1;
    }

    if(orders.size() != 0){
        selectionStrategy = new SelectionStrategy<Indi>*[4];
        for(unsigned i = 0; i < orders.size(); i++){

            if(QString::compare(orders[i], "Fitness", Qt::CaseInsensitive)==0)
            {
                selectionStrategy[i] = new SelectionFitness<Indi>();
            }else
                if(QString::compare(orders[i], "Delta critico", Qt::CaseInsensitive)==0)
                {
                    selectionStrategy[i] = new SelectionDeltaCr<Indi>();
                }else
                    if(QString::compare(orders[i], "Momento del primo ordine", Qt::CaseInsensitive)==0)
                    {
                        selectionStrategy[i] = new SelectionMomentoDelPrimoOrdine<Indi>();
                    }else
                        if(QString::compare(orders[i], "tempo base", Qt::CaseInsensitive)==0)
                        {
                            selectionStrategy[i] = new SelectionSize<Indi>();
                        }
        }
    }

         for (int i = 0; i < activations_size; ++i) {
             cout << "Activation Start = " <<"    "<<"  "<< activations[i].getStart().tm_hour<< ":" << activations[i].getStart().tm_min << ":"<< activations[i].getStart().tm_sec << "   " <<activations[i].getStart().tm_mday << "-"<< activations[i].getStart().tm_mon << "-"<< 1900+activations[i].getStart().tm_year << endl;
             cout << "Activation End = " <<"    "<<"  "<< activations[i].getEnd().tm_hour<< ":" << activations[i].getEnd().tm_min << ":"<< activations[i].getEnd().tm_sec << "   " <<activations[i].getEnd().tm_mday << "-"<< activations[i].getEnd().tm_mon << "-"<< 1900+activations[i].getEnd().tm_year << endl;
         }
         qDebug() << "Activation End = " <<"    "<<"  "<< this->rain[0].getRainMm()<< endl;


    selection        = sselection;
    pattern          = spattern;
    pop              = ipop;
    maxGen           = imaxGen;
    tbMax            = itbMax;
    tbMin            = itbMin;
    dHpMax           = idHpMax;
    dHpMin           = idHpMin;
    propCrossover    = fpropCrossover;
    propMutation     = fpropMutation;
    pme              = fpme;
    pmb              = fpmb;
    currentMaximumFitness=_currentMaximumFitness;
    absoluteMaximumFitness=_absoluteMaximumFitness;
    currentAverageFitness= _currentAverageFitness;
    absoluteAverageFitness=_absoluteAverageFitness;
    update = _update;

    QString tmp2 = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/workspace/calibration/"+projectName;
    QDir dir3(tmp2);
    if (!dir3.exists()){
        dir3.mkdir(".");
    }

    savePath = tmp2;

    if(QString::compare(selection, "StochTour(t)", Qt::CaseInsensitive)==0)
    {
        parameter1=para1;
        parameter2=para2;
        selection = QString("StochTour(%1)").arg(parameter1);
    }else
        if( QString::compare(selection, "DetTour(T)", Qt::CaseInsensitive)==0){
            parameter1=para1;
            parameter2=para2;
            selection = QString("DetTour(%1)").arg(parameter1);
        }else
            if( QString::compare(selection, "Ranking(p,e)", Qt::CaseInsensitive)==0){
                parameter1=para1;
                parameter2=para2;
                selection = QString("Ranking(%1,%2)").arg(parameter1,parameter2);
            }else
                if( QString::compare(selection, "Roulette", Qt::CaseInsensitive)==0){
                    parameter1=para1;
                    parameter2=para2;
                    //selection = QString("Ranking(%1,%2)").arg(parameter1,parameter2);
                }else
                    if( QString::compare(selection, "Sequential(ordered/unordered)", Qt::CaseInsensitive)==0){

                        parameter2=para2;
                        selection = QString("Sequential("+ spara1 +")").arg(parameter1,parameter2);
                    }


    maxNumberToConsider=para1;
    numberofProcessor=_numberofProcessor;

    if(fileExists(tmp2+"/currentGeneration.csv")){
        lastGeneration = _lastGeneration;
    }else
        lastGeneration = false;


}
void SAKeController::startAlgorithm()
{
    parallel.setNumberProcessor(numberofProcessor);
    srand(time(0));
    //    qDebug() << "Start Algorithm %d /n"<< "/n";

    int argc=1;
    char **x= (char**)malloc(sizeof(char*) * 1);
    x[0]= (char*)malloc(sizeof(char)*1);
    x[0]=(char*) 'a';
    try
    {

        eoParser parser(argc,x);  // for user-parameter readi ng
        vector<vector<double>> popFromFile;
        if(lastGeneration){
            int numGen;
            HandlerCSV::loadCSVPopFromFile(savePath+"/currentGeneration.csv",popFromFile,numGen);
        }

        if(typeAlgorithm==4)
            parser.setORcreateParam(eoParamParamType(selection.toStdString()), "selection", "Selection: DetTour(T), StochTour(t), Roulette, Ranking(p,e) or Sequential(ordered/unordered)", 'S', "Evolution Engine");
        //        parser.setORcreateParam(eoParamParamType("ElitistReplacement(8)"), "replacement", "Replacement: Comma, Plus or EPTour(T), SSGAWorst, SSGADet(T), SSGAStoch(t)", 'R', "Evolution Engine");

        //parser.setORcreateParam(eoParamParamType("MySelection"), "selection", "Selection: DetTour(T), StochTour(t), Roulette, Ranking(p,e) or Sequential(ordered/unordered)", 'S', "Evolution Engine");

        parser.setORcreateParam(unsigned(this->pop), "popSize", "Population Size", 'P', "Evolution Engine");
        parser.setORcreateParam(unsigned(this->maxGen), "maxGen", "Maximum number of generations () = none)",'G',"Stopping criterion");
        //          parser.setORcreateParam(relRateCrossover, "cross1Rate", "Relative rate for crossover 1", '1', "Variation Operators").value();
        //          parser.setORcreateParam(relRateMutation, "mut1Rate", "Relative rate for mutation 1", '1', "Variation Operators").value();
        //parser.setORcreateParam(propCrossover, "pCross", "Probability of Crossover", 'C', "Variation Operators" );
        //parser.setORcreateParam(propMutation, "pMut", "Probability of Mutation", 'M', "Variation Operators" );
        //parser.setORcreateParam(uint32_t(0), "seed", "Random number seed", 'S');

        //          int tbMin=30;
        //          int tbMax=180;
        //          double Pme=25;
        //          double Pmb=0.3;
        //          double dHpMin=0;
        //          double dHpMax=10;
        //          string pattern = "Triangolare Disc";



        eoState state;    // keeps all things allocated

        //plotMobility->initCustomPlotMobilityFunction();

        // The fitness
        //////////////
        eoSAKeEvalFunc<Indi> plainEval(rain,rain_size,activations,activations_size)/* (varType  _anyVariable) */;

        // turn that object into an evaluation counter
        eoEvalFuncCounter<Indi> eval(plainEval);


        // the genotype - through a genotype initializerdo_make_genotype(_parser, _state, _eo);
        eoInit<Indi>& init = do_make_genotype(parser, state, Indi(),tbMin,tbMax,pattern.toStdString(), popFromFile,lastGeneration);

        // Build the variation operator (any seq/prop construct)
        //eoGenOp<Indi>& op = do_make_op(parser, state, init,tbMin,tbMax,pme,pmb,dHpMin,dHpMax);

        eoQuadOp<Indi> *cross = new eoSAKeQuadCrossover<Indi> /* (varType  _anyVariable) */;
        eoMonOp<Indi> *mut = new eoSAKeMutation<Indi>(tbMin,tbMax, pme, pmb,dHpMin,dHpMax)/* (varType  _anyVariable) */;



        //// Now the representation-independent things
        //
        // YOU SHOULD NOT NEED TO MODIFY ANYTHING BEYOND THIS POINT
        // unless you want to add specific statistics to the checkpoint
        //////////////////////////////////////////////

        // initialize the population
        // yes, this is representation indepedent once you have an eoInit
        eoPop<Indi>& pop   = do_make_pop(parser, state, init);

        this->stop = new eoGenContinueMy<Indi>(savePath);
        // stopping criteria
        eoContinue<Indi> & term = do_make_continue_my(parser, state, eval,this->stop);
        // output
        eoCheckPoint<Indi> & checkpoint = do_make_checkpoint_my(parser, state, eval, term,qCustomPlot,plotMobility,rain,rain_size,plotkernel,progressBar,this->maxGen,   currentMaximumFitness,
                                                                absoluteMaximumFitness,
                                                                currentAverageFitness,
                                                                absoluteAverageFitness, a,update);
        // algorithm (need the operator!)
        eoAlgo<Indi>& ga = do_make_algo_scalar_my(parser, state, eval, checkpoint, *cross,propCrossover,*mut,propMutation,maxNumberToConsider,typeAlgorithm,selectionStrategy);

        ///// End of construction of the algorithm

        //parallel.make_parallel_my(numberofProcessor);

#ifdef _OPENMP
        omp_set_num_threads( numberofProcessor );
#endif // !_OPENMP
        //parallel.setNumberProcessor(numberofProcessor);
        //parallel.setNumberProcessor(8);

        /////////////////////////////////////////
        // to be called AFTER all parameters have been read!!!
        //make_help(parser);

        //// GO
        ///////
        // evaluate intial population AFTER help and status in case it takes time

        apply<Indi>(eval, pop);
        // if you want to print it out
        //           cout << "Initial Population\n";
        //           pop.sortedPrintOn(cout);
        //           qDebug() << "initialized population %d /n"<< "/n";
        //           cout << endl;
        //            qDebug() << "start %d /n"<< "/n";
        do_run(ga, pop); // run the ga
        //            cout << "tempo esecuzione " << end_time -start_time<< "\n";
        //          cout << "Final Population\n";
        //  cout << pop.it_best_element().base()->fitness() << endl;
        //  cout << *(pop.it_best_element())<< endl;
        //          pop.sortedPrintOn(cout);
        //          cout << endl;

    }
    catch(exception& e)
    {
        //            cout << e.what() << endl;
    }
}

int SAKeController::getCsvHandlerstatusRain() const
{
    return csvHandlerstatusRain;
}

void SAKeController::setCsvHandlerstatusRain(int value)
{
    csvHandlerstatusRain = value;
}

CustomPlotKernel *SAKeController::getPlotkernel() const
{
    return plotkernel;
}

void SAKeController::setPlotkernel(CustomPlotKernel *value)
{
    plotkernel = value;
    plotkernel->initCustomPlotFitness();
}

void SAKeController::setPlotMobility(CustomPlotMobilityFunction *value)
{
    plotMobility = value;
    plotMobility->setActivation(activations,activations_size);
    plotMobility->setRain(this->rain,this->rain_size);
    plotMobility->initCustomPlotMobilityFunction();
}

void SAKeController::setProgressBar(QObject* _progressBar){
    progressBar=_progressBar;
}

void SAKeController::run(){
    startAlgorithm();
}

void SAKeController::startThread(){
    QThread::start();
}

void SAKeController::setApplication(QApplication * _a){
    a=_a;
}

void SAKeController::stopThread(){
    qDebug() << "close " << "\n";
    //this->moveToThread(QApplication::instance()->thread());
    //  this->exit(0);
    //    this->requestInterruption();
    //    if(this->isInterruptionRequested())
    //        this->stop();
    //    this->sleep(10000);
    if(stop){
        qDebug() << "close2 " << "\n";
        stop->setStop(true);
    }

}

