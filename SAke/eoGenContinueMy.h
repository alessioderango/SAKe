#ifndef EOGENCONTINUEMY
#define EOGENCONTINUEMY


#include <eoContinue.h>
#include <utils/eoParam.h>
#include <QtQuick>
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
    eoGenContinueMy( QString _savePath)
        : eoCountContinue<EOT>( ),
          eoValueParam<unsigned>(0, "Generations", "Generations"),
          stop( false )

    {
        //_savePath.remove(0,8);
        savePath=_savePath;
        //SALVATAGGIO ULTIMA GENERAZIONE
        savePathKernels=savePath+"/kernels.csv";
        savePath+="/currentGeneration.csv";
        numberOfKernels=1000;
    }

    double roundMy(double x, int prec)
    {
        double power = 1.0;
        int i;

        if (prec > 0)
            for (i = 0; i < prec; i++)
                power *= 10.0;
        else if (prec < 0)
            for (i = 0; i < prec; i++)
                power /= 10.0;

        if (x > 0)
            x = floor(x * power + 0.5) / power;
        else if (x < 0)
            x = ceil(x * power - 0.5) / power;

        if (x == -0)
            x = 0;

        return x;
    }


    bool presents(std::vector<std::vector<double>> kernels,EOT _eo,double fitness, double delta,int tb, double momento){
        //        int equalElements=0;
        for(int i=0;i<kernels.size();i++ ){
            //            equalElements=0;
            //            if(_eo.getSizeConst() == (kernels[i].size()-5)){
            //                for(int k=0;k < _eo.getSizeConst();k++){
            //                    if(_eo.getFiConst()[k] == kernels[i][k+5])
            //                        equalElements++;
            //                }
            //                if(equalElements == (_eo.getSizeConst()))
            double fitnessRoundInput = roundMy(fitness,4);
            double fitnessRoundKernel = roundMy(kernels[i][0],4);
            double momentoRoundInput = roundMy(momento,4);
            double momentoRoundKernel = roundMy(kernels[i][4],4);

            if(fitnessRoundInput == fitnessRoundKernel && (kernels[i][1]/delta)>=0.999 && (kernels[i][1]/delta)<=1.001
                    && tb == kernels[i][3] && momentoRoundInput == momentoRoundKernel)
                return true;
            //            }
        }
        return false;
    }


    bool allElementsEqualFitness(std::vector<std::vector<double>> kernels){
        for (int g = 1; g < kernels.size(); g++) {
            if(kernels[1][0] != kernels[g][0]){
                return false;
            }
        }
        return true;
    }

    /** Returns false when a certain number of generations is
         * reached */
    virtual bool operator() ( const eoPop<EOT>& _vEO ) {

        //SALVATAGGIO ULTIMA GENERAZIONE
        ofstream myfile;
        myfile.open (savePath.toStdString(),ios::out);

        ofstream kernelStream;
        kernelStream.open (savePathKernels.toStdString(),ios::out);

        bool numElementsEqualFitness=allElementsEqualFitness(kernels);

        for (int t = 0; t < _vEO.size(); t++) {
            double tmp = _vEO[t].fitness();

            int stop =  _vEO[t].getSizeConst();
            myfile << thisGeneration << " ;";
            myfile << tmp << " ;";
            double delta =(_vEO[t].getYmMinConst().getValue()-_vEO[t].getYmMin2Const().getValue())/_vEO[t].getYmMinConst().getValue() ;
            myfile << delta << " ;";
            myfile << _vEO[t].getYmMinConst().getValue() << " ;";
            myfile << stop << " ;";
            myfile << _vEO[t].getMomentoDelPrimoOrdineConst() << " ;";
            //myfile << " ;";
            //  myfile << "fitness ; "<<tmp <<" ; ";
            for (int i = 0; i < stop; i++) {
                myfile << _vEO[t].getFiConst()[i] << ";";
            }
            myfile << "\n";





            if(!presents(kernels,_vEO[t],tmp,delta,stop,_vEO[t].getMomentoDelPrimoOrdineConst())){
                if(kernels.size() < numberOfKernels )
                {
                    //                    //myfile << " ;";
                    //                    //  myfile << "fitness ; "<<tmp <<" ; ";
                    std::vector<double> tmpKernel;
                    tmpKernel.push_back(tmp);
                    tmpKernel.push_back(delta);
                    tmpKernel.push_back(_vEO[t].getYmMinConst().getValue());
                    tmpKernel.push_back(stop);
                    tmpKernel.push_back(_vEO[t].getMomentoDelPrimoOrdineConst() );
                    for (int i = 0; i < stop; i++) {
                        //kernelStream << _vEO[t].getFiConst()[i] << ";";
                        tmpKernel.push_back(_vEO[t].getFiConst()[i]);
                    }
                    //kernelStream << "\n";
                    kernels.push_back(tmpKernel);
                }else
                {
                    if(!numElementsEqualFitness)
                    {
                        std::sort(kernels.begin(), kernels.end(),[](const std::vector<double>& a, const std::vector<double>& b) {
                            return a[0] > b[0];
                        });

                        for (int g = 0; g < kernels.size(); g++) {
                            if(kernels[g][0] < tmp){
                                std::vector<double> tmpKernel;
                                tmpKernel.push_back(tmp);
                                tmpKernel.push_back(delta);
                                tmpKernel.push_back(_vEO[t].getYmMinConst().getValue());
                                tmpKernel.push_back(stop);
                                tmpKernel.push_back(_vEO[t].getMomentoDelPrimoOrdineConst() );
                                for (int i = 0; i < stop; i++) {
                                    //kernelStream << _vEO[t].getFiConst()[i] << ";";
                                    tmpKernel.push_back(_vEO[t].getFiConst()[i]);
                                }
                                //kernelStream << "\n";
                                kernels.insert(kernels.begin()+g,tmpKernel);
                                kernels.erase(kernels.begin()+numberOfKernels);
                                break;
                            }
                        }



                    }else
                    {
                        std::sort(kernels.begin(), kernels.end(),[](const std::vector<double>& a, const std::vector<double>& b) {
                            return a[1] > b[1];
                        });

                        for (int g = 0; g < kernels.size(); g++) {
                            if(kernels[g][1] < delta){
                                std::vector<double> tmpKernel;
                                tmpKernel.push_back(tmp);
                                tmpKernel.push_back(delta);
                                tmpKernel.push_back(_vEO[t].getYmMinConst().getValue());
                                tmpKernel.push_back(stop);
                                tmpKernel.push_back(_vEO[t].getMomentoDelPrimoOrdineConst() );
                                for (int i = 0; i < stop; i++) {
                                    //kernelStream << _vEO[t].getFiConst()[i] << ";";
                                    tmpKernel.push_back(_vEO[t].getFiConst()[i]);
                                }
                                //kernelStream << "\n";
                                kernels.insert(kernels.begin()+g,tmpKernel);
                                kernels.erase(kernels.begin()+numberOfKernels);
                                break;
                            }
                        }

                    }
                }
            }

        }
        myfile.close();

        for (int i = 0; i < kernels.size(); i++) {
            for (int j = 0; j < kernels[i][3]; j++) {
                kernelStream <<kernels[i][j] << ";";

            }
            kernelStream << "\n";
        }


        kernelStream.close();



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
    QString savePathKernels;
    QObject *gen;
    std::vector<std::vector<double>> kernels;
    int numberOfKernels;
};


#endif // EOGENCONTINUEMY

