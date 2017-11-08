#ifndef EOGENCONTINUEMY
#define EOGENCONTINUEMY


#include <eoContinue.h>
#include <utils/eoParam.h>
#include <utils/eoLogger.h>
#include <fstream>
#include <algorithm>    // std::sort
#include <set>
#include <iomanip>
using namespace std;

struct row {
    double fitness;
    int tb;
    double safetyMargin;
    double firstOrderMomentum;
    double ymin;
    std::vector<double> kernel;
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
        if (absequal(r1.fitness,r2.fitness,e) && r1.tb == r2.tb && absequal(r1.safetyMargin,r2.safetyMargin,e) && doubleMin(r1.firstOrderMomentum,r2.firstOrderMomentum,e))
            return true;
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

    /// Ctor for setting a
    eoGenContinueMy( QString _savePath, int _stepToSave, int _numberOfKernelToBeSaved)
        : eoCountContinue<EOT>( ),
          eoValueParam<unsigned>(0, "Generations", "Generations"),
          stop( false )

    {
        //_savePath.remove(0,8);
        savePath=_savePath;
        savePathWithHeader=_savePath;
        //SALVATAGGIO ULTIMA GENERAZIONE
        savePathKernels=savePath+"/kernels.csv";
        savePath+="/currentGeneration.csv";
        savePathWithHeader+= "/currentGenerationWithHeader.csv";
        numberOfKernelToBeSaved=_numberOfKernelToBeSaved;
        stepToSave = _stepToSave;
    }



    virtual bool operator() ( const eoPop<EOT>& _vEO ) {


        //SALVATAGGIO ULTIMA GENERAZIONE
        ofstream myfile;
        myfile.open (savePath.toStdString(),ios::out);

        ofstream myfileWithHeader;
        myfileWithHeader.open (savePathWithHeader.toStdString(),ios::out);

        ofstream kernelStream;
        kernelStream.open (savePathKernels.toStdString(),ios::out);



        myfileWithHeader <<  "Generations ;";
        myfileWithHeader <<  "Fitness ;";
        myfileWithHeader <<  "Safety margin ;";
        myfileWithHeader <<  "Ym min ;";
        myfileWithHeader <<  "Base time ;";
        myfileWithHeader <<  "First-order momentum;";
        myfileWithHeader <<  "Kernel ;\n";

        for (unsigned int  t = 0; t < _vEO.size(); t++) {
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
                myfile << _vEO[t].getFiConstIndex(i) << ";";
            }
            myfile << "\n";

            myfileWithHeader << thisGeneration << " ;";
            myfileWithHeader << tmp << " ;";
            myfileWithHeader << delta << " ;";
            myfileWithHeader << _vEO[t].getYmMinConst().getValue() << " ;";
            myfileWithHeader << stop << " ;";
            myfileWithHeader << _vEO[t].getMomentoDelPrimoOrdineConst() << " ;";
            for (int i = 0; i < stop; i++) {
                myfileWithHeader << _vEO[t].getFiConstIndex(i) << ";";
            }
            myfileWithHeader << "\n";
        }


        for (unsigned int  t = 0; t < _vEO.size(); t++) {
            double cFitness = _vEO[t].fitness();
            int tb =  _vEO[t].getSizeConst();
            double safetyMargin =(_vEO[t].getYmMinConst().getValue()-_vEO[t].getYmMin2Const().getValue())/_vEO[t].getYmMinConst().getValue() ;
            double firstOrderMomentum = _vEO[t].getMomentoDelPrimoOrdineConst();

            double ymin = _vEO[t].getYmMinConst().getValue();
            if(eoCountContinue<EOT>::thisGeneration%stepToSave ==0 ){
                std::vector<double> tmpKernel;
                for (int i = 0; i < tb; i++) {
                    tmpKernel.push_back(_vEO[t].getFiConstIndex(i));
                }
                row r1 = {cFitness, tb, safetyMargin, firstOrderMomentum,ymin,tmpKernel};
                kernels.insert(r1);
            }
        }

        if(kernels.size() > numberOfKernelToBeSaved){
            auto del = kernels.begin();
            advance(del,numberOfKernelToBeSaved);
            kernels.erase(del,kernels.end() );
        }

        for (const auto row : kernels) {
            kernelStream << setprecision(6) << row.fitness << ";" <<row.safetyMargin << ";"<<row.ymin << ";"<<  row.tb  <<";"<< row.firstOrderMomentum << ";";
            for(int i = 0; i < row.kernel.size(); i++)
            {
                kernelStream  << row.kernel[i]<< ";";
            }
            kernelStream << "\n";

        }



        myfile.close();
        myfileWithHeader.close();

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
    QString savePathWithHeader;
    QString savePathKernels;
    QObject *gen;
    //std::vector<std::vector<double>> kernels;
    set <row, compareRow> kernels;
    int numberOfKernelToBeSaved;
    int stepToSave;
};


#endif // EOGENCONTINUEMY

