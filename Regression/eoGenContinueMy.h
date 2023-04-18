#ifndef EOGENCONTINUEMY
#define EOGENCONTINUEMY


#include <eoContinue.h>
#include <utils/eoParam.h>
#include <utils/eoLogger.h>
#include <fstream>
#include <algorithm>    // std::sort
#include "regressioncontroller.h"
#include "HandlerCSV.h"
using namespace std;

/**
    Generational continuator: continues until a number of generations is reached

    @ingroup Continuators
*/
template< class EOT>
class eoGenContinueMy: public eoCountContinue<EOT>, public eoValueParam<unsigned>
{
public:

    using eoCountContinue<EOT>::thisGeneration;
    using eoCountContinue<EOT>::thisGenerationPlaceholder;

    typedef typename EOT::Fitness Fitness;
    /// Ctor for setting a
    eoGenContinueMy( QString _savePath, int _frequencySavePop)
        : eoCountContinue<EOT>( ),
          eoValueParam<unsigned>(0, "Generations", "Generations"),
          stop( false )

    {
        //_savePath.remove(0,8);
        saveFitnessGenerations=_savePath+"/fitnessHistory.csv";
        savePath=_savePath+"/kernel.csv";
        savePopulation=_savePath+"/population.csv";
        frequencySavePop = _frequencySavePop;
        numGenerations=0;

    }

    static Fitness sumFitness(double _sum, const EOT& _eot){
        _sum += _eot.fitness();
        return _sum;
    }
    /** Returns false when a certain number of generations is
         * reached */
    virtual bool operator() ( const eoPop<EOT>& _vEO ) {


        if(thisGeneration == 0){ // first step
            QVector<double> x;
            QVector<double> yBest;
            QVector<double> yAverage;
            HandlerCSV::loadCSVGenationsFromFile(saveFitnessGenerations, x, yBest, yAverage);
            numGenerations = x.size();

        }


        //SALVATAGGIO ULTIMA GENERAZIONE
        ofstream myfile;
        myfile.open (savePath.toStdString(),ios::out);

        myfile << "H(t) : ";
        for (int t = 0; t < _vEO.best_element().getYCombinataConst().size(); t++) {
            myfile <<  _vEO.best_element().getYCombinataConst(t) << " ;";
        }

        myfile << "\n";
        myfile << "Equation : \n";
        myfile << "Nash–Sutcliffe efficiency : " << _vEO.best_element().fitness() << " \n";

        myfile << "Type ; weight ; alfa ; beta; shift;  \n";
        for (int t = 0; t < _vEO.best_element().getWConst().size(); t++) {
            if(_vEO.best_element().getFunctionTypeConst(t) == 0 )
                continue;
            else
                myfile <<  "gamma" << " ; ";
            myfile <<  _vEO.best_element().getWConst(t) << " ;";
            myfile <<  _vEO.best_element().getParConst(t).getParameters(0) << " ;";//alfa
            myfile <<  _vEO.best_element().getParConst(t).getParameters(1) << " ;";//beta
            myfile <<  _vEO.best_element().getParConst(t).getParameters(2) << " ;";//translation
            myfile << "\n";

        }

        myfile << "Type ; weight ; m ; q ; shift;  \n";
        for (int t = 0; t < _vEO.best_element().getWConst().size(); t++) {
            if(_vEO.best_element().getFunctionTypeConst(t) == 0 )
                myfile <<  "linear" << ";";
            else
                continue;
            myfile <<  _vEO.best_element().getWConst(t) << " ;";
            myfile <<  _vEO.best_element().getParConst(t).getParameters(0) << " ;";
            myfile <<  _vEO.best_element().getParConst(t).getParameters(1) << " ;";
            myfile <<  _vEO.best_element().getParConst(t).getParameters(2) << " ;";
            myfile << "\n";

        }



        myfile.close();
        double value = 0.00000001;
        double valuemax = 1.0;

        if((frequencySavePop  != 0 && (eoCountContinue<EOT>::thisGeneration+1)%frequencySavePop ==0) || this->getStop())
        {


            myfile.open (savePopulation.toStdString(),ios::out);
            myfile << "weight for each function"  //
                   << "; alfa, beta, shift for each function" //
                   << "; Type function for each function" //
//                   << "; Weight of for each function" //
//                   << "; Change percentage of  for each linear function" //
//                   << "; Change percentage for each gamma function parameters" //
//                   << "; Shift percentage for each gamma function " //
                   << "; H(t)" << ";" << endl; //
            for (int gen = 0; gen < _vEO.size(); ++gen) {
                // Weight
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

                    if(abs(_vEO[gen].getWConst(t)) < value){
                        myfile << 0;
                    }else
                        myfile << _vEO[gen].getWConst(t);

                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";


                }
                myfile << ";";
                // Parameters
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

                    if(abs(_vEO[gen].getParConst(t).getParameters(0)) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                        myfile <<  _vEO[gen].getParConst(t).getParameters(0) << " ,";//alfa

                    if(abs(_vEO[gen].getParConst(t).getParameters(1)) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                        myfile <<  _vEO[gen].getParConst(t).getParameters(1) << " ,";//beta

                    if(abs(_vEO[gen].getParConst(t).getParameters(2)) < value)
                    {
                        myfile << 0;
                    }else
                        myfile <<  _vEO[gen].getParConst(t).getParameters(2) ;//translation
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";
                // FunctionType
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

                    if(_vEO[gen].getFunctionTypeConst(t)  == 0)
                            myfile << "Linear";
                    else
                            myfile << "Gamma";

//                    myfile <<  _vEO[gen].getFunctionTypeConst(t);
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";

//                // PercentageWeigh
//                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

//                    if(abs(_vEO[gen].getPercentageVariationWeightConst(t) ) < value)
//                    {
//                        myfile << 0;
//                    }else
//                        if(abs(_vEO[gen].getPercentageVariationWeightConst(t) ) > valuemax)
//                        {
//                            myfile << 1;
//                        }else
//                    myfile <<  _vEO[gen].getPercentageVariationWeightConst(t) ;
//                    if(t !=  _vEO[gen].getWConst().size() -1)
//                        myfile << ",";

//                }
//                myfile << ";";

//                // PercentageLinearA
//                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

//                    if(abs(_vEO[gen].getPercentageVariationLinearAConst(t)) < value)
//                    {
//                        myfile << 0;
//                    }else
//                            if(abs(_vEO[gen].getPercentageVariationLinearAConst(t) ) > valuemax)
//                            {
//                                myfile << 1;
//                            }else
//                    myfile <<  _vEO[gen].getPercentageVariationLinearAConst(t) ;
//                    if(t !=  _vEO[gen].getWConst().size() -1)
//                        myfile << ",";

//                }
//                myfile << ";";

//                // PercentageLinearB
//                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

//                    if(abs(_vEO[gen].getPercentageVariationLinearBConst(t)) < value)
//                    {
//                        myfile << 0;
//                    }else
//                        if(abs(_vEO[gen].getPercentageVariationLinearBConst(t) ) > valuemax)
//                        {
//                            myfile << 1;
//                        }else
//                    myfile <<  _vEO[gen].getPercentageVariationLinearBConst(t);
//                    if(t !=  _vEO[gen].getWConst().size() -1)
//                        myfile << ",";

//                }
//                myfile << ";";

//                // PercentageGammaA
//                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {
//                    if(abs(_vEO[gen].getPercentageVariationGammaAConst(t)) < value)
//                    {
//                        myfile << 0 ;
//                    }else
//                    myfile <<  _vEO[gen].getPercentageVariationGammaAConst(t);
//                    if(t !=  _vEO[gen].getWConst().size() -1)
//                        myfile << ",";

//                }
//                myfile << ";";

//                // PercentageGammaB
//                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

//                    if(abs(_vEO[gen].getPercentageVariationGammaBConst(t)) < value)
//                    {
//                        myfile << 0;
//                    }else
//                    myfile <<  _vEO[gen].getPercentageVariationGammaBConst(t) ;
//                    if(t !=  _vEO[gen].getWConst().size() -1)
//                        myfile << ",";

//                }
//                myfile << ";";

//                // PercentageTranslation
//                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {
//                    if(abs(_vEO[gen].getTranslationConst(t)) < value)
//                    {
//                        myfile << 0;
//                    }else
//                    myfile <<  _vEO[gen].getTranslationConst(t) ;
//                    if(t !=  _vEO[gen].getWConst().size() -1)
//                        myfile << ",";

//                }
//                myfile << ";";

                // H(t)
                for (int t = 0; t < _vEO[gen].getYCombinataConst().size(); t++) {

                    if(abs(_vEO[gen].getYCombinataConst(t)) < value)
                    {
                        myfile << 0;
                    }else
                    myfile <<  _vEO[gen].getYCombinataConst(t);
                    if(t !=  _vEO[gen].getYCombinataConst().size() -1)
                        myfile << ",";

                }
                myfile << ";" << endl;

            }

            myfile.close();
        }


        ofstream fitnessGenerator;
        fitnessGenerator.open (saveFitnessGenerations.toStdString(),ios::app);

        Fitness v = std::accumulate(_vEO.begin(), _vEO.end(), Fitness(0.0), eoGenContinueMy::sumFitness);

        fitnessGenerator << thisGeneration+numGenerations << ";" << _vEO.best_element().fitness() << ";" << v/_vEO.size() << endl;

        fitnessGenerator.close();



        thisGeneration++;
        if(stop){
            eo::log << eo::logging << "STOP in eoGenContinue: stop execution \n";
            return false;
        }
        return true;
    }

    /** Sets the number of generations to reach
            and sets the current generation to 0 (the begin)

        @todo replace this by an "init" method
    */
    virtual void setStop( bool _stop ) {
        stop = _stop;
        eoCountContinue<EOT>::reset();
    }

    /** Returns the number of generations to reach*/
    virtual bool getStop( )
    {
        return stop;
    }

    virtual std::string className(void) const { return "eoGenContinueMy"; }



private:
    bool stop;
    QString savePath;
    QString savePopulation;
    QObject *gen;
    int frequencySavePop;
     QString saveFitnessGenerations;
     int numGenerations;
};


#endif // EOGENCONTINUEMY

