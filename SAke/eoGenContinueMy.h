#ifndef EOGENCONTINUEMY
#define EOGENCONTINUEMY


#include <eoContinue.h>
#include <utils/eoParam.h>
#include <utils/eoLogger.h>
#include <fstream>
#include <algorithm>    // std::sort
#include <set>
#include <iomanip>
#include <QVector>
#include "SAKeController.h"
#include "HandlerCSV.h"
using namespace std;

struct row {
    double fitness;
    int tb;
    double safetyMargin;
    double firstOrderMomentum;
    double ymin;
    double zcr;
    Ym zjminTime;
    Ym zcrTime;
    std::vector<double> kernel;
    std::vector<Ym> kernelYm;
};



struct compareRow {
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

    bool operator()(const row& r1, const row& r2) {
        return compare(r1,r2);
    }
    bool absequal(const double a,const double b, const double e){
        return fabs(a-b) < e;
    }
    bool doubleMin(const double a,const double b, const double e){
        return (((a - b) < 0) && ( fabs(a-b) > e));
    }

    bool doubleMax(const double a,const double b, const double e){
        return (((a - b) > 0) && ( fabs(a-b) > e));
    }

    bool compare(const row& r1, const row& r2) {

        const double e = 0.000001;
        if (doubleMax(r1.fitness,r2.fitness,e)  ) return true;
        if (absequal(r1.fitness,r2.fitness,e) && r1.tb < r2.tb) return true;
        if (absequal(r1.fitness,r2.fitness,e) && r1.tb == r2.tb && doubleMax(r1.safetyMargin,r2.safetyMargin,e)) return true;
        if (absequal(r1.fitness,r2.fitness,e) && r1.tb == r2.tb
                && absequal(r1.safetyMargin,r2.safetyMargin,e)
                && doubleMin(r1.firstOrderMomentum,r2.firstOrderMomentum,e))
            return true;
//        if (absequal(r1.fitness,r2.fitness,e) && r1.tb == r2.tb
//                && absequal(r1.safetyMargin,r2.safetyMargin,e)
//                && absequal(r1.firstOrderMomentum,r2.firstOrderMomentum,e)
//                && doubleMax(r1.ymin,r2.ymin,e))
//            return true;
//        if (absequal(r1.fitness,r2.fitness,e) && r1.tb == r2.tb
//                && absequal(r1.safetyMargin,r2.safetyMargin,e)
//                && absequal(r1.firstOrderMomentum,r2.firstOrderMomentum,e)
//                && absequal(r1.ymin,r2.ymin,e)
//                && doubleMax(r1.zcr,r2.zcr,e))
//            return true;
        return false;
    }
};

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
    eoGenContinueMy( QString _savePath,
                     int _stepToSave,
                     int _numberOfKernelToBeSaved,
                     QString _fitnessFile,
                     SAKeController* s,
                     Rain * _rain,
                     int _rain_size,
                     Activation *_activation,
                     int _activation_size)
        : eoCountContinue<EOT>( ),
          eoValueParam<unsigned>(0, "Generations", "Generations"),
          stop( false )


    {
        //_savePath.remove(0,8);
        savePath=_savePath;
        savePathWithHeader=_savePath;
        //SALVATAGGIO ULTIMA GENERAZIONE
        savePathKernels=savePath+"/kernels.csv";
        saveFitnessGenerations=savePath+"/fitnessHistory.csv";
        savePath+="/currentGeneration.csv";
        savePathWithHeader+= "/currentGAiteration.csv";
        numberOfKernelToBeSaved=_numberOfKernelToBeSaved;
        stepToSave = _stepToSave;

        //        ofstream myfile;
        //        myfile.open (saveFitnessGenerations.toStdString(),ios::out);
        //        myfile.close();
        fitnessFile=_fitnessFile;
        controller = s;
        P=_rain;
        rain_size=_rain_size;
        activation =_activation;
        activation_size = _activation_size;


    }

    static Fitness sumFitness(double _sum, const EOT& _eot){
        _sum += _eot.fitness();
        return _sum;
    }



    virtual bool operator() ( const eoPop<EOT>& _vEO ) {


        int nd = MainWindow::numberofdecimals;

        if(thisGeneration == 0){ // first step
            QVector<double> x;
            QVector<double> yBest;
            QVector<double> yAverage;
            HandlerCSV::loadCSVGenationsFromFile(saveFitnessGenerations, x, yBest, yAverage);
            numGenerations = x.size();

        }

        //SALVATAGGIO ULTIMA GENERAZIONE
        //        ofstream myfile;
        //        myfile.open (savePath.toStdString(),ios::out);

        ofstream myfileWithHeader;
        myfileWithHeader.open (savePathWithHeader.toStdString(),ios::out);





        myfileWithHeader <<  "Iteration ;";
        myfileWithHeader <<  "Fitness " << fitnessFile.toStdString() << ";";
        myfileWithHeader <<  "tb ;";
        myfileWithHeader <<  "Safety margin ;";
        myfileWithHeader <<  "First-order momentum;";
        myfileWithHeader <<  "zj-min ;";
        myfileWithHeader <<  "zcr ;";
        myfileWithHeader <<  "Kernel ;\n";

        for (unsigned int  t = 0; t < _vEO.size(); t++) {
            double fitnessDouble = _vEO[t].fitness();

            int tb =  _vEO[t].getSizeConst();
            //            myfile << thisGeneration+numGenerations << " ;";
            //            myfile << fitnessDouble << " ;";
            double Safetymargin =(_vEO[t].getYmMinConst().getValue()-_vEO[t].getYmMin2Const().getValue())/_vEO[t].getYmMinConst().getValue() ;
            //            myfile << delta << " ;";
            //            myfile << _vEO[t].getYmMinConst().getValue() << " ;";
            //            myfile << tb << " ;";
            //            myfile << _vEO[t].getMomentoDelPrimoOrdineConst() << " ;";
            //myfile << " ;";
            //  myfile << "fitness ; "<<fitnessDouble <<" ; ";
            //            for (int i = 0; i < tb; i++) {
            //                myfile << _vEO[t].getFiConstIndex(i) << ";";
            //            }
            //            myfile << "\n";

            myfileWithHeader << thisGeneration+numGenerations << " ;";
            myfileWithHeader << fitnessDouble << " ;";
            myfileWithHeader << tb << " ;";
            myfileWithHeader << setprecision(nd) <<Safetymargin << " ;";
            myfileWithHeader << setprecision(nd) <<_vEO[t].getMomentoDelPrimoOrdineConst() << " ;";
            myfileWithHeader << setprecision(nd) <<_vEO[t].getYmMinConst().getValue() << " ;";// zj-min
            myfileWithHeader << setprecision(nd) <<_vEO[t].getYmMin2Const().getValue() << " ;";// zcr
            for (int i = 0; i < tb; i++) {
                myfileWithHeader << setprecision(15) <<_vEO[t].getFiConstIndex(i) << ";";
            }
            myfileWithHeader << "\n";
        }


        for (unsigned int  t = 0; t < _vEO.size(); t++) {
            double cFitness = _vEO[t].fitness();
            int tb =  _vEO[t].getSizeConst();
            double safetyMargin =(_vEO[t].getYmMinConst().getValue()-_vEO[t].getYmMin2Const().getValue())/_vEO[t].getYmMinConst().getValue() ;
            double firstOrderMomentum = _vEO[t].getMomentoDelPrimoOrdineConst();

            double ymin = _vEO[t].getYmMinConst().getValue();
            double zcrdouble = _vEO[t].getYmMin2Const().getValue();

            std::vector<double> tmpKernel;
            std::vector<Ym> tmpKernelYm;
            for (int i = 0; i < _vEO[t].getBestsConst().size(); i++) {
                Ym ymTmp = _vEO[t].getBestsConstIndex(i);
                tmpKernelYm.push_back(ymTmp);
            }
            for (int i = 0; i < tb; i++) {
                tmpKernel.push_back(_vEO[t].getFiConstIndex(i));
            }
            row r1 = {cFitness,
                      tb,
                      safetyMargin,
                      firstOrderMomentum,
                      ymin,
                      zcrdouble,
                      _vEO[t].getYmMinConst(),
                      _vEO[t].getYmMin2Const(),
                      tmpKernel,
                      tmpKernelYm};
            kernels.insert(r1);

        }

        if(kernels.size() > numberOfKernelToBeSaved){
            auto del = kernels.begin();
            advance(del,numberOfKernelToBeSaved);
            kernels.erase(del,kernels.end() );
        }
        cout << "controller->getMaxGen() " << controller->getMaxGen() << " thisGeneration "<< thisGeneration   << endl;

        if((stepToSave  != 0 && (eoCountContinue<EOT>::thisGeneration+1)%stepToSave ==0) || (controller->getMaxGen() == (thisGeneration+1)) || this->getStop())
        {
            cout << "Salvo Kernelsssss" << endl;
            ofstream kernelStream;
            kernelStream.open (savePathKernels.toStdString(),ios::out);

            kernelStream <<  "Fitness " << fitnessFile.toStdString() << ";";
            kernelStream <<  "tb ;";
            kernelStream <<  "Safety margin ;";
            kernelStream <<  "First-order momentum;";
            kernelStream <<  "zj-min ;";
            kernelStream <<  "zcr ;";
            kernelStream <<  "Kernel ;\n";

            for (const auto row : kernels) {
                kernelStream << setprecision(nd) << row.fitness << ";" <<row.tb << ";"<<row.safetyMargin  << ";"<<  row.firstOrderMomentum  <<";"<< row.ymin << ";"<<row.zcr << ";";
                for(int i = 0; i < row.kernel.size(); i++)
                {
                    kernelStream  << setprecision(15) <<row.kernel[i]<< ";";
                }
                kernelStream << "\n";

            }

            kernelStream.close();
        }

        auto bestAbsoluteKernel = *(kernels.begin());
        ptrdiff_t index = distance(MainWindow::threads.begin(), find(MainWindow::threads.begin(), MainWindow::threads.end(), controller));
        controller->getMainwindows()->mutex.lock();
        emit controller->updateTextsBestAbsolute(index,
                                                 QString("%1").arg(bestAbsoluteKernel.tb),
                                                 QString("%1").arg(bestAbsoluteKernel.safetyMargin, 0, 'g', nd),
                                                 QString("%1").arg(bestAbsoluteKernel.firstOrderMomentum, 0, 'g', nd),
                                                 QString("%1").arg(bestAbsoluteKernel.ymin, 0, 'g', nd),
                                                 QString("%1").arg(bestAbsoluteKernel.zcr, 0, 'g', nd));


        //        myfile.close();
        myfileWithHeader.close();

        //const EOT best_element= _vEO.best_element();
        std::vector<double> Y;
        Y.resize(rain_size);

        for (int t = 0; t < rain_size; t++) {
            double ym = 0;
            Y[t] = 0;
            for (int r = 0; r < t; r++)
                if ((t - r) < bestAbsoluteKernel.kernel.size()){
                    ym += bestAbsoluteKernel.kernel[t - r] * P[r].getRainMm();
                }
            Y[t] = ym;
        }

        emit controller->updateMobPlot(index,P,rain_size,activation, activation_size, Y,
                                       bestAbsoluteKernel.ymin,
                                       bestAbsoluteKernel.zjminTime.getTime(),
                                       bestAbsoluteKernel.zcr,
                                       bestAbsoluteKernel.zcrTime.getTime(),
                                       bestAbsoluteKernel.kernelYm,
                                       controller->widgetArray,
                                       controller->arrowArray);

        emit controller->updateKernelPlot(index,
                                          QVector<double>::fromStdVector(bestAbsoluteKernel.kernel),
                                          bestAbsoluteKernel.kernel.size());


        controller->getMainwindows()->mutex.unlock();
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
        //eoCountContinue<EOT>::reset();
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
    QString savePathWithHeader;
    QString savePathKernels;
    QString saveFitnessGenerations;
    QObject *gen;
    //std::vector<std::vector<double>> kernels;
    set <row, compareRow> kernels;
    int numberOfKernelToBeSaved;
    int stepToSave;

    int numGenerations;
    QString fitnessFile;
    SAKeController* controller;
    Rain * P;
    int rain_size;
    Activation *activation;
    int activation_size;
};


#endif // EOGENCONTINUEMY

