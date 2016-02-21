#include "SAKeController.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    } 
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

int loadCSV(QString fileurl,Rain * &rain,int &size)
{

//    qDebug() << "Entrato in loadCSV";
        fileurl.remove(0,8);
//       qDebug() << fileurl;
       size=0;
//       qDebug() << fileurl;

       std::ifstream in(fileurl.toStdString());

           std::string line;
            std::vector< std::vector<std::string>> rows;

           clock_t start=clock();
           while (std::getline(in, line)){
               size++;
               std::vector<std::string> x;
               x = split(line, ';');
               rows.push_back(x);
             // cout << line << endl;
           }
           clock_t stop=clock();
//           qDebug() <<double(stop-start)/CLOCKS_PER_SEC << " seconds\n";
//           qDebug() << size;
           rain = new Rain[size];
           size=0;

           for(int i =0; i < rows.size();i++){
               double mm = atof(rows[i].at(3).c_str());
               string date =  rows[i].at(2);
               string a =" 00:00:00.000";
               date+=a;

               //cout << "mm " << mm << " date " << date << endl;

               ptime rain0 = time_from_string(date);
               rain[size]= Rain(to_tm(rain0),mm);
               size++;
           }

       return 0;

}


int loadCSVActivation(QString fileurl,Activation *&activation,int &activation_size)
{

//    qDebug() << "Entrato in loadCSV";
        fileurl.remove(0,8);
//       qDebug() << fileurl;
       activation_size=0;
//       qDebug() << fileurl;

       std::ifstream in(fileurl.toStdString());

           std::string line;
            std::vector< std::vector<std::string>> rows;

           clock_t start=clock();
           while (std::getline(in, line)){
               activation_size++;
               std::vector<std::string> x;
               x = split(line, ';');
               rows.push_back(x);
              cout << line << endl;
           }
           clock_t stop=clock();
//           qDebug() <<double(stop-start)/CLOCKS_PER_SEC << " seconds\n";
//           qDebug() << activation_size;
           activation = new Activation[activation_size];
           activation_size=0;

           for(int i =0; i < rows.size();i++){
               string dateStart =  rows[i].at(1);
               string dateEnd =  rows[i].at(2);


               cout << " dateStart " << dateStart << " dateEnd " << dateEnd << endl;

               ptime activationStart = time_from_string(dateStart);
               ptime activationEnd = time_from_string(dateEnd);
               activation[activation_size]= Activation(to_tm(activationStart),to_tm(activationEnd));
               activation_size++;
           }

       return 0;

}

SAKeController::SAKeController(CustomPlotItem *& _qCustomPlot,
                               QString  sselection,
                               QString  spattern,
                               QString  filenameRain,
							   QString  filenameActivaion,
							   QString  filenameSavePath,
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
                               int _maxNumberToConsider,
                               Update* _update)

{
    this->start=false;
    this->finish=true;
    qCustomPlot = _qCustomPlot;
//    qDebug() << "filenameSavePath = " <<"    "<<"  "<< filenameSavePath<< endl;
   qCustomPlot->initCustomPlotFitness();
   loadCSV(filenameRain,this->rain,this->rain_size);
   loadCSVActivation(filenameActivaion,activations,activations_size);
   try {
        // db.getConnection();
         //db.executeQueryRain(this->rain,this->rain_size);
         //db.executeQueryActivation(activations,activations_size);
        // db.disconnect();

     } catch (const std::exception &e) {
         cerr << e.what() << std::endl;
  //       return 1;
     }
//     for (int i = 0; i < activations_size; ++i) {
//         cout << "Activation Start = " <<"    "<<"  "<< activations[i].getStart().tm_hour<< ":" << activations[i].getStart().tm_min << ":"<< activations[i].getStart().tm_sec << "   " <<activations[i].getStart().tm_mday << "-"<< activations[i].getStart().tm_mon << "-"<< 1900+activations[i].getStart().tm_year << endl;
//         cout << "Activation End = " <<"    "<<"  "<< activations[i].getEnd().tm_hour<< ":" << activations[i].getEnd().tm_min << ":"<< activations[i].getEnd().tm_sec << "   " <<activations[i].getEnd().tm_mday << "-"<< activations[i].getEnd().tm_mon << "-"<< 1900+activations[i].getEnd().tm_year << endl;
//     }
//     qDebug() << "Activation End = " <<"    "<<"  "<< this->rain[0].getRainMm()<< endl;


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
   savePath = filenameSavePath;
   maxNumberToConsider=_maxNumberToConsider;
   numberofProcessor=_numberofProcessor;


}
void SAKeController::startAlgorithm()
{
    srand(time(0));
//    qDebug() << "Start Algorithm %d /n"<< "/n";
    time_t start_time, end_time;
    this->start=true;
int argc=1;
char **x= (char**)malloc(sizeof(char*) * 1);
 x[0]= (char*)malloc(sizeof(char)*1);
 x[0]=(char*) 'a';
          try
          {

              eoParser parser(argc,x);  // for user-parameter readi ng
//              qDebug() << "Start Algorithm %d /n"<< "/n";

          /* TODO
                GESTIRE ElitistReplacement(10) GUI
              replacement.toStdString()

          */
          //parser.setORcreateParam(eoParamParamType(selection.toStdString()), "selection", "Selection: DetTour(T), StochTour(t), Roulette, Ranking(p,e) or Sequential(ordered/unordered)", 'S', "Evolution Engine");
          parser.setORcreateParam(eoParamParamType("MySelection"), "selection", "Selection: DetTour(T), StochTour(t), Roulette, Ranking(p,e) or Sequential(ordered/unordered)", 'S', "Evolution Engine");
//        parser.setORcreateParam(eoParamParamType("ElitistReplacement(8)"), "replacement", "Replacement: Comma, Plus or EPTour(T), SSGAWorst, SSGADet(T), SSGAStoch(t)", 'R', "Evolution Engine");
          parser.setORcreateParam(unsigned(this->pop), "popSize", "Population Size", 'P', "Evolution Engine");
          parser.setORcreateParam(unsigned(this->maxGen), "maxGen", "Maximum number of generations () = none)",'G',"Stopping criterion");
//          parser.setORcreateParam(relRateCrossover, "cross1Rate", "Relative rate for crossover 1", '1', "Variation Operators").value();
//          parser.setORcreateParam(relRateMutation, "mut1Rate", "Relative rate for mutation 1", '1', "Variation Operators").value();
          parser.setORcreateParam(propCrossover, "pCross", "Probability of Crossover", 'C', "Variation Operators" );
          parser.setORcreateParam(propMutation, "pMut", "Probability of Mutation", 'M', "Variation Operators" );


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
          eoInit<Indi>& init = do_make_genotype(parser, state, Indi(),tbMin,tbMax,pattern.toStdString());

          // Build the variation operator (any seq/prop construct)
          eoGenOp<Indi>& op = do_make_op(parser, state, init,tbMin,tbMax,pme,pmb,dHpMin,dHpMax);

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
          eoAlgo<Indi>& ga = do_make_algo_scalar_my(parser, state, eval, checkpoint, *cross,propCrossover,*mut,propMutation,maxNumberToConsider);

          ///// End of construction of the algorithm
          //make_parallel_my(parser);

          parallel.setNumberProcessor(numberofProcessor);

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
            start_time = time(NULL);
           do_run(ga, pop); // run the ga
            end_time = time(NULL);
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

void SAKeController::stopThread(QQuickCloseEvent * selection){
//    qDebug() << "close " << "\n";
    //this->moveToThread(QApplication::instance()->thread());
    //  this->exit(0);
//    this->requestInterruption();
//    if(this->isInterruptionRequested())
//        this->stop();

    if(!this->stop)
    this->stop->setStop(true);

}

