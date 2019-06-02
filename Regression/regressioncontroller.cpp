#include "regressioncontroller.h"
#include "make_checkpoint_my.h"


RegressionController::RegressionController()
{

}

RegressionController::RegressionController(MainWindow *main, QString projectName,
                                           double* _percentualePeso,
                                           double* _percentualeLineareA,
                                           double* _percentualeLineareB,
                                           double* _percentualeGammaA,
                                           double* _percentualeGammaB,
                                           double *weights,
                                           int weightsSize,
                                           int *functionTypes,
                                           int functionTypesSize,
                                           Parameters *parameters,
                                           int parametersSize,
                                           std::vector<double> _xkernel,
                                           std::vector<double> _ykernel,
                                           int ielitist,
                                           int ipopulationSize,
                                           int imaxGeneration,
                                           double dpercentageCrossover,
                                           double dpercentageMutation,
                                           int inumberProcessor,
                                           double *translation,
                                           double para1,
                                           double para2,
                                           int itypeReplacement,
                                           QString  sselection,
                                           int _seed,
                                           std::vector<Genotype> &_g,
                                           bool _lastgeneration, int _frequencySavePop){

    typeReplacement =itypeReplacement;
    selection        = sselection;
    this->percentualePesoSize = weightsSize;
    percentualePeso=_percentualePeso;

    this->percentualeLineareASize = weightsSize;
    percentualeLineareA=_percentualeLineareA;

    this->percentualeLineareBSize = weightsSize;
    percentualeLineareB= _percentualeLineareB;

    this->percentualeGammaASize = weightsSize;
    percentualeGammaA= _percentualeGammaA;

    this->percentualeGammaBSize = weightsSize;
    percentualeGammaB= _percentualeGammaB;

    this->x = _xkernel;
    this->y = _ykernel;

    this->weights = weights;
    this->weightsSize =weightsSize;
    this->functionTypes = functionTypes;
    this->functionTypesSize = functionTypesSize;
    this->parameters = parameters;
    this->parametersSize = parametersSize;
    this->numberProcessor=inumberProcessor;


    this->elitist = ielitist;
    this->populationSize = ipopulationSize;
    this->maxGeneration = imaxGeneration;
    this->percentageCrossover = dpercentageCrossover;
    this->percentageMutation = dpercentageMutation;
    this->translation = translation;

    QString tmp2 = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/workspace/regression/"+projectName;
    QDir dir3(tmp2);
    if (!dir3.exists()){
        dir3.mkdir(".");
    }

    savePath = tmp2;

    if(QString::compare(selection, "Stochastic Tournament (Tr)", Qt::CaseInsensitive)==0)
    {
        parameter1=para1;
        parameter2=para2;
        selection = QString("StochTour(%1)").arg(parameter1);
    }else
        if( QString::compare(selection, "Deterministic Tournament (Ts)", Qt::CaseInsensitive)==0){
            parameter1=para1;
            parameter2=para2;
            selection = QString("DetTour(%1)").arg(parameter1);
        }else
            if( QString::compare(selection, "Ranking (s)", Qt::CaseInsensitive)==0){
                parameter1=para1;
                parameter2=-1;
                QString tmp = QString("Ranking(");
                tmp.append(QString::number(parameter1));
                tmp.append(",");
                tmp.append(QString::number(parameter2));
                tmp.append(")");
                selection = tmp;// QString("Ranking(%1,%2)").arg(parameter1,parameter2);
            }else
                if( QString::compare(selection, "Roulette", Qt::CaseInsensitive)==0){
                    parameter1=para1;
                    parameter2=para2;
                    selection = QString("Roulette");
                }else
                    if( QString::compare(selection, "Ranking (p,e)", Qt::CaseInsensitive)==0){
                        parameter1=para1;
                        parameter2=para2;
                        QString tmp = QString("Ranking(");
                        tmp.append(QString::number(parameter1));
                        tmp.append(",");
                        tmp.append(QString::number(parameter2));
                        tmp.append(")");
                        selection = tmp;//QString("Sequential(%1)").arg(para1);
                        //std::cout << typeAlgorithm << " "<< selection.toStdString()<< std::endl;
                    }

     clickCloseTab=false;
     mainwindows = main;
     seed=_seed;

     g = _g;
     lastgeneration = _lastgeneration;
     frequencySavePop = _frequencySavePop;

     if(!lastgeneration){
         QString stmp = savePath+"/fitnessHistory.csv";
         ofstream myfile;
         myfile.open (stmp.toStdString(),ios::out);
         myfile.close();
     }

}



void RegressionController::startAlgorithm(){


    //    qCustomPlotRegression->setKernely(&y[0]);
    //    qCustomPlotRegression->setSize_kernely(y.size());
    //    qCustomPlotRegression->setKernelx(&x[0]);
    //    qCustomPlotRegression->setSize_kernelx(x.size());
    //    void setupQuadraticDemo(  double * kernely,
    //                              int size_kernely,
    //                              double * kernelx,
    //                              int size_kernelx
    //                              );

    time_t start_time, end_time;
    this->start=true;
    int argc=1;
    char **input= (char**)malloc(sizeof(char*) * 1);
    input[0]= (char*)malloc(sizeof(char)*1);
    input[0]=(char*) 'a';
    try
    {
#ifdef _OPENMP
        omp_set_num_threads( numberProcessor );
#endif // !_OPENMP
        eoParser parser(argc,input);  // for user-parameter readi ng
        parser.setORcreateParam(eoParamParamType(selection.toStdString()), "selection", "Selection: DetTour(T), StochTour(t), Roulette, Ranking(p,e) or Sequential(ordered/unordered)", 'S', "Evolution Engine");
        // parser.setORcreateParam(eoParamParamType("Sequential(ordered)"), "selection", "Selection: DetTour(T), StochTour(t), Roulette, Ranking(p,e) or Sequential(ordered/unordered)", 'S', "Evolution Engine");
        //        parser.setORcreateParam(eoParamParamType("ElitistReplacement(8)"), "replacement", "Replacement: Comma, Plus or EPTour(T), SSGAWorst, SSGADet(T), SSGAStoch(t)", 'R', "Evolution Engine");
        parser.setORcreateParam(unsigned(populationSize), "popSize", "Population Size", 'P', "Evolution Engine");
        parser.setORcreateParam(unsigned(maxGeneration), "maxGen", "Maximum number of generations () = none)",'G',"Stopping criterion");
        //          parser.setORcreateParam(relRateCrossover, "cross1Rate", "Relative rate for crossover 1", '1', "Variation Operators").value();
        //          parser.setORcreateParam(relRateMutation, "mut1Rate", "Relative rate for mutation 1", '1', "Variation Operators").value();
        //        parser.setORcreateParam(0.8, "pCross", "Probability of Crossover", 'C', "Variation Operators" );
        //        parser.setORcreateParam(0.3, "pMut", "Probability of Mutation", 'M', "Variation Operators" );

        uint32_t t32 =  (uint32_t) seed;
        parser.setORcreateParam(t32, "seed", "Random number seed", 'S');
        eoState state;    // keeps all things allocated

        // The fitness
        //////////////
        eoOneMaxEvalFunc<Individual> plainEval(x,y)/* (varType  _anyVariable) */;
        // turn that object into an evaluation counter
        eoEvalFuncCounter<Individual> eval(plainEval);

        // the genotype - through a genotype initializer
        eoInit<Individual>& init = do_make_genotype(parser,
                                                    state,
                                                    weights,
                                                    weightsSize,
                                                    functionTypes,
                                                    functionTypesSize,
                                                    parameters,
                                                    parametersSize,
                                                    percentualePeso,
                                                    percentualePesoSize,
                                                    percentualeLineareA,
                                                    percentualeLineareASize,
                                                    percentualeLineareB,
                                                    percentualeLineareBSize,
                                                    percentualeGammaA,
                                                    percentualeGammaASize,
                                                    percentualeGammaB,
                                                    percentualeGammaBSize,
                                                    translation,
                                                    g,
                                                    lastgeneration,
                                                    Individual());

        // Build the variation operator (any seq/prop construct)
        //        eoGenOp<Individual>& op = do_make_op(parser, state, init);

        eoQuadOp<Individual> *cross = new eoOneMaxQuadCrossover<Individual> /* (varType  _anyVariable) */;
        eoMonOp<Individual> *mut = new eoOneMaxMutation<Individual>()/* (varType  _anyVariable) */;



        //// Now the representation-independent things
        //
        // YOU SHOULD NOT NEED TO MODIFY ANYTHING BEYOND THIS POINT
        // unless you want to add specific statistics to the checkpoint
        //////////////////////////////////////////////

        // initialize the population
        // yes, this is representation indepedent once you have an eoInit
        eoPop<Individual>& pop   = do_make_pop(parser, state, init);

        this->stop = new eoGenContinueMy<Individual>(savePath, frequencySavePop);
        // stopping criteria
        eoContinue<Individual> & term = do_make_continue_my(parser, state, eval, this->stop);
        // output
        eoCheckPoint<Individual> & checkpoint = do_make_checkpoint_my(parser,
                                                                      state,
                                                                      eval,
                                                                      term,
                                                                      maxGeneration,
                                                                      x,
                                                                      y,
                                                                      functionTypesSize,
                                                                      this);
        // algorithm (need the operator!)
        //  eoAlgo<Individual>& ga = make_algo_scalar_my(parser, state, eval, checkpoint, op);
        eoAlgo<Individual>& ga = do_make_algo_scalar_my(parser, state, eval, checkpoint, *cross,percentageCrossover,*mut,percentageMutation,elitist,typeReplacement);

        ///// End of construction of the algorithm

        /////////////////////////////////////////
        // to be called AFTER all parameters have been read!!!
        make_help(parser);

        //// GO
        ///////
        // evaluate intial population AFTER help and status in case it takes time
        apply<Individual>(eval, pop);
        // if you want to print it out
        //cout << "Initial Population\n";
        pop.sortedPrintOn(cout);
        //cout << endl;

        do_run(ga, pop); // run the ga

        //cout << "Final Population\n";
        pop.sortedPrintOn(cout);
        //cout << endl;
        //cout << "The Best" <<endl;
        pop.best_element().printOn(cout);

        //cout <<  endl;

//        for (int i = 0; i < x.size(); ++i) {
//            cout << pop.best_element().getYCombinataConst(i) << endl;
//        }

        mainwindows->mutex.lock();
        ptrdiff_t pos = distance(MainWindow::threads.begin(), find(MainWindow::threads.begin(), MainWindow::threads.end(), this));
        //MainWindow::threads.erase(MainWindow::threads.begin()+pos);
        if(clickCloseTab)
            emit finished(pos);
        mainwindows->mutex.unlock();

    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
}

void RegressionController::run(){
    startAlgorithm();
}

QString RegressionController::getSavePath() const
{
    return savePath;
}

void RegressionController::setSavePath(const QString &value)
{
    savePath = value;
}

bool RegressionController::getStop()
{
    if(stop){
        return stop->getStop();
    }
}

MainWindow *RegressionController::getMainwindows() const
{
    return mainwindows;
}

void RegressionController::setMainwindows(MainWindow *value)
{
    mainwindows = value;
}

bool RegressionController::getClickCloseTab() const
{
    return clickCloseTab;
}

void RegressionController::setClickCloseTab(bool value)
{
    clickCloseTab = value;
}

std::vector<double> RegressionController::getY()
{
    return y;
}

void RegressionController::setY(std::vector<double> &value)
{
    y = value;
}

std::vector<double> RegressionController::getX()
{
    return x;
}

void RegressionController::setX(std::vector<double> &value)
{
    x = value;
}



QObject *RegressionController::getAbsoluteAverageFitness() const
{
    return absoluteAverageFitness;
}

void RegressionController::setAbsoluteAverageFitness(QObject *value)
{
    absoluteAverageFitness = value;
}


int RegressionController::getNumberProcessor() const
{
    return numberProcessor;
}

void RegressionController::setNumberProcessor(int value)
{
    numberProcessor = value;
}

QObject *RegressionController::getCurrentAverageFitness() const
{
    return currentAverageFitness;
}

void RegressionController::setCurrentAverageFitness(QObject *value)
{
    currentAverageFitness = value;
}

QObject *RegressionController::getAbsoluteMaximumFitness() const
{
    return absoluteMaximumFitness;
}

void RegressionController::setAbsoluteMaximumFitness(QObject *value)
{
    absoluteMaximumFitness = value;
}

QObject *RegressionController::getCurrentMaximumFitness() const
{
    return currentMaximumFitness;
}

void RegressionController::setCurrentMaximumFitness(QObject *value)
{
    currentMaximumFitness = value;
}

QObject *RegressionController::getProgressBar() const
{
    return progressBar;
}

void RegressionController::setProgressBar(QObject *value)
{
    progressBar = value;
}



void RegressionController::startThread(){
    QThread::start();
}

void RegressionController::stopThread(){
//    qDebug() << "close " << "\n";
    //this->moveToThread(QApplication::instance()->thread());
    //  this->exit(0);
    //    this->requestInterruption();
    //    if(this->isInterruptionRequested())
    //        this->stop();
    //    this->sleep(10000);
    if(stop){
//        qDebug() << "close2 " << "\n";
        stop->setStop(true);
    }

}
