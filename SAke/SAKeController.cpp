#include "SAKeController.h"
#include "make_checkpoint_my.h"

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

SAKeController::SAKeController(MainWindow *_main,
                               QString  sselection,
                               QString  replacement,
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
                               int _numberofProcessor,
                               float para1,
                               float para2,
                               bool _lastGeneration,
                               const QString& projectName,
                               vector<QString> orders,
                               int itypeAlgorithm,
                               int numberElitist,
                               int _seed,
                               int _saveKernels,
                               int numberOfKernelToBeSaved)

{
    mainwindows = _main;
    this->rain=rain;
    this->rain_size = rain_size;
    this->activations=activation;
    this->activations_size = activation_size;
    typeAlgorithm =itypeAlgorithm;
    this->start=false;
    this->finish=true;
    this->replacement=replacement;

    seed =_seed;
    saveKernels = _saveKernels;

    if(orders.size() != 0){
        selectionStrategy = new SelectionStrategy<Indi>*[4];
        for(unsigned i = 0; i < orders.size(); i++){

            if(QString::compare(orders[i], "Fitness", Qt::CaseInsensitive)==0)
            {
                selectionStrategy[i] = new SelectionFitness<Indi>();
            }else
                if(QString::compare(orders[i], "Safety margin", Qt::CaseInsensitive)==0)
                {
                    selectionStrategy[i] = new SelectionDeltaCr<Indi>();
                }else
                    if(QString::compare(orders[i], "First-order momentum", Qt::CaseInsensitive)==0)
                    {
                        selectionStrategy[i] = new SelectionMomentoDelPrimoOrdine<Indi>();
                    }else
                        if(QString::compare(orders[i], "Base time", Qt::CaseInsensitive)==0)
                        {
                            selectionStrategy[i] = new SelectionSize<Indi>();
                        }
        }
    }

//         for (int i = 0; i < activations_size; ++i) {
//             cout << "Activation Start = " <<"    "<<"  "<< activations[i].getStart().tm_hour<< ":" << activations[i].getStart().tm_min << ":"<< activations[i].getStart().tm_sec << "   " <<activations[i].getStart().tm_mday << "-"<< activations[i].getStart().tm_mon << "-"<< 1900+activations[i].getStart().tm_year << endl;
//             cout << "Activation End = " <<"    "<<"  "<< activations[i].getEnd().tm_hour<< ":" << activations[i].getEnd().tm_min << ":"<< activations[i].getEnd().tm_sec << "   " <<activations[i].getEnd().tm_mday << "-"<< activations[i].getEnd().tm_mon << "-"<< 1900+activations[i].getEnd().tm_year << endl;
//         }
//         qDebug() << "Activation End = " <<"    "<<"  "<< this->rain[0].getRainMm()<< endl;


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
                    selection = QString("Roulette");
                }


    maxNumberToConsider=numberElitist;
    numberofProcessor=_numberofProcessor;

    if(fileExists(tmp2+"/currentGeneration.csv")){
        lastGeneration = _lastGeneration;
    }else
        lastGeneration = false;


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
    qDebug() << "rain_size arrivato " << rain_size << "\n";
    qDebug() << "act_size arrivato " << activation_size << "\n";
    qDebug() << "_projectName  arrivato " << projectName << "\n";
    qDebug() << "_numberProcessor arrivato " << numberofProcessor << "\n";
    qDebug() << "ipara1 arrivato " << parameter1 << "\n";
    qDebug() << "ipara2 arrivato " << parameter2 << "\n";
    qDebug() << "selectionOrder1 arrivato " << orders[0] << "\n";
    qDebug() << "selectionOrder2 arrivato " << orders[1] << "\n";
    qDebug() << "selectionOrder3 arrivato " << orders[2]  << "\n";
    qDebug() << "selectionOrder4 arrivato " << orders[3] << "\n";
    qDebug() << "numberElitist arrivato " << numberElitist << "\n";
    qDebug() << "tipo arrivato " << typeAlgorithm << "\n";
    qDebug() << "seed " << seed << "\n";
    qDebug() << "_saveKernels " << _saveKernels << "\n";
    qDebug() << "numberOfKernelToBeSaved" << numberOfKernelToBeSaved << "\n";
    qDebug() << "replacement" << replacement << "\n";

    clickCloseTab=false;

}
void SAKeController::startAlgorithm()
{

    parallel.setNumberProcessor(numberofProcessor);

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

        parser.setORcreateParam(eoParamParamType(selection.toStdString()), "selection", "Selection: DetTour(T), StochTour(t), Roulette, Ranking(p,e) or Sequential(ordered/unordered)", 'S', "Evolution Engine");
        parser.setORcreateParam(unsigned(this->pop), "popSize", "Population Size", 'P', "Evolution Engine");
        parser.setORcreateParam(unsigned(this->maxGen), "maxGen", "Maximum number of generations () = none)",'G',"Stopping criterion");
        uint32_t t32 =  (uint32_t) seed;
        parser.setORcreateParam(t32, "seed", "Random number seed", 'S');

        eoState state;    // keeps all things allocated

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

        // initialize the population
        // yes, this is representation indepedent once you have an eoInit
        eoPop<Indi>& pop   = do_make_pop(parser, state, init);

        this->stop = new eoGenContinueMy<Indi>(savePath, saveKernels);
        // stopping criteria
        eoContinue<Indi> & term = do_make_continue_my(parser, state, eval,this->stop);
        // output
        eoCheckPoint<Indi> & checkpoint = do_make_checkpoint_my(parser,
                                                                state,
                                                                eval,
                                                                term,
                                                                rain,
                                                                rain_size,
                                                                activations,
                                                                activations_size,
                                                                this->maxGen,
                                                                this);
        // algorithm (need the operator!)
        eoAlgo<Indi>& ga = do_make_algo_scalar_my(parser,
                                                  state,
                                                  eval,
                                                  checkpoint,
                                                  *cross,
                                                  propCrossover,
                                                  *mut,
                                                  propMutation,
                                                  maxNumberToConsider,
                                                  typeAlgorithm,
                                                  selectionStrategy
                                                  );

#ifdef _OPENMP
        omp_set_num_threads( numberofProcessor );
#endif // !_OPENMP

        apply<Indi>(eval, pop);
        do_run(ga, pop); // run the ga

    }
    catch(exception& e)
    {
        //            cout << e.what() << endl;
    }
    //QThread::sleep(10);
    getMainwindows()->mutex.lock();
    ptrdiff_t pos = distance(MainWindow::threads.begin(), find(MainWindow::threads.begin(), MainWindow::threads.end(), this));
    //MainWindow::threads.erase(MainWindow::threads.begin()+pos);
    if(clickCloseTab)
        emit finished(pos);
     getMainwindows()->mutex.unlock();
    //MainWindow::closeTab(pos);

}

MainWindow *SAKeController::getMainwindows() const
{
    return mainwindows;
}

void SAKeController::setMainwindows(MainWindow *value)
{
    mainwindows = value;
}

bool SAKeController::getClickCloseTab() const
{
    return clickCloseTab;
}

void SAKeController::setClickCloseTab(bool value)
{
    clickCloseTab = value;
}

int SAKeController::getCsvHandlerstatusRain() const
{
    return csvHandlerstatusRain;
}

void SAKeController::setCsvHandlerstatusRain(int value)
{
    csvHandlerstatusRain = value;
}


void SAKeController::run(){
    startAlgorithm();
}

void SAKeController::startThread(){
    QThread::start();
}


void SAKeController::stopThread(){

    if(stop){
        stop->setStop(true);
    }

}

bool SAKeController::getStop()
{
    if(stop){
        return stop->getStop();
    }

}

