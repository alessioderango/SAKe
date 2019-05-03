#ifndef EOGENCONTINUEMY
#define EOGENCONTINUEMY


#include <eoContinue.h>
#include <utils/eoParam.h>
#include <utils/eoLogger.h>
#include <fstream>
#include <algorithm>    // std::sort
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

    /// Ctor for setting a
    eoGenContinueMy( QString _savePath, int _frequencySavePop)
        : eoCountContinue<EOT>( ),
          eoValueParam<unsigned>(0, "Generations", "Generations"),
          stop( false )

    {
        //_savePath.remove(0,8);
        savePath=_savePath+"/kernel.csv";
        savePopulation=_savePath+"/population.csv";
        frequencySavePop = _frequencySavePop;
        step=1;
    }


    /** Returns false when a certain number of generations is
         * reached */
    virtual bool operator() ( const eoPop<EOT>& _vEO ) {

        //SALVATAGGIO ULTIMA GENERAZIONE
        ofstream myfile;
        myfile.open (savePath.toStdString(),ios::out);

        myfile << "Y calcolata : ";
        for (int t = 0; t < _vEO.best_element().getYCombinataConst().size(); t++) {
            myfile <<  _vEO.best_element().getYCombinataConst(t) << " ;";
        }

        myfile << "\n";
        myfile << "Equation : \n";
        myfile << "Nash–Sutcliffe efficiency : " << _vEO.best_element().fitness() << " \n";

        myfile << "Type ; Weight ; alfa ; beta; translation;  \n";
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

        myfile << "Type ; Weight ; alfa ; beta; translation;  \n";
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

        if(step%frequencySavePop ==0)
        {

            cout << " salvoooo " << endl;

            myfile.open (savePopulation.toStdString(),ios::out);

            for (int gen = 0; gen < _vEO.size(); ++gen) {



                // Weight
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

                    if(abs(_vEO[gen].getPercentageVariationWeightConst(t)) < value){
                        myfile << 0;
                    }else
                        myfile << _vEO[gen].getPercentageVariationWeightConst(t);

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
                        myfile << 0 << " ,";
                    }else
                        myfile <<  _vEO[gen].getParConst(t).getParameters(2);//translation
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";
                // FunctionType
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

                    if(abs(_vEO[gen].getFunctionTypeConst(t)) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                    myfile <<  _vEO[gen].getFunctionTypeConst(t);
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";

                // PercentageWeigh
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

                    if(abs(_vEO[gen].getPercentageVariationWeightConst(t) ) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                    myfile <<  _vEO[gen].getPercentageVariationWeightConst(t) ;
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";

                // PercentageLinearA
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

                    if(abs(_vEO[gen].getPercentageVariationLinearAConst(t)) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                    myfile <<  _vEO[gen].getPercentageVariationLinearAConst(t) ;
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";

                // PercentageLinearB
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

                    if(abs(_vEO[gen].getPercentageVariationLinearBConst(t)) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                    myfile <<  _vEO[gen].getPercentageVariationLinearBConst(t);
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";

                // PercentageGammaA
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {
                    if(abs(_vEO[gen].getPercentageVariationGammaAConst(t)) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                    myfile <<  _vEO[gen].getPercentageVariationGammaAConst(t);
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";

                // PercentageGammaB
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {

                    if(abs(_vEO[gen].getPercentageVariationGammaBConst(t)) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                    myfile <<  _vEO[gen].getPercentageVariationGammaBConst(t) ;
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";

                // PercentageTranslation
                for (int t = 0; t < _vEO[gen].getWConst().size(); t++) {
                    if(abs(_vEO[gen].getTranslationConst(t)) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                    myfile <<  _vEO[gen].getTranslationConst(t) ;
                    if(t !=  _vEO[gen].getWConst().size() -1)
                        myfile << ",";

                }
                myfile << ";";

                // YCombinata
                for (int t = 0; t < _vEO[gen].getYCombinataConst().size(); t++) {

                    if(abs(_vEO[gen].getYCombinataConst(t)) < value)
                    {
                        myfile << 0 << " ,";
                    }else
                    myfile <<  _vEO[gen].getYCombinataConst(t);
                    if(t !=  _vEO[gen].getYCombinataConst().size() -1)
                        myfile << ",";

                }
                myfile << ";" << endl;

            }

            myfile.close();
        }

        step++;


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
    int step;
};


#endif // EOGENCONTINUEMY

