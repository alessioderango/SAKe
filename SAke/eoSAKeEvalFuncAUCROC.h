/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

 The above line is usefulin Emacs-like editors
 */

/*
 Template for evaluator in EO, a functor that computes the fitness of an EO
 ==========================================================================
 */

#ifndef _eoSAKeEvalFuncAUCROC_h
#define _eoSAKeEvalFuncAUCROC_h

// include whatever general include you need
#include <stdexcept>
#include <fstream>
#include <ctime>
using namespace std;
#define DAYS  ((60) (*) (60) (*) (24))
#define HOURS ((60) (*) (60))

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"
#include "Rain.h"
#include "Ym.h"
#include "Activation.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/local_time_adjustor.hpp"
#include "boost/date_time/c_local_time_adjustor.hpp"
#include "ValidationController.h"

using boost::posix_time::ptime;
using namespace boost::gregorian;
using namespace boost::posix_time;
/**
 Always write a comment in this format before class definition
 if you want the class to be documented by Doxygen
 */
template<class EOT>
class eoSAKeEvalFuncAUCROC: public eoEvalFunc<EOT> {
public:
    eoSAKeEvalFuncAUCROC(Rain * _rain, int _rain_size, Activation* _activation,
                         int _activation_size, int _numberOfLines)
    {
        rain = _rain;
        rain_size = _rain_size;
        activations = _activation;
        activations_size = _activation_size;
        numberOfLines = _numberOfLines;
    }

    std::vector<double> getY(Rain *& P, std::vector<double> Fi, int tb) {
        //        printf("rain_size %d \n",rain_size);
        //        for (int i = 0; i < tb; i++) {
        //               printf("Fi[%d] %f \n",i, Fi[i]);

        //        }
        //        printf("tb %d %d  \n",tb,rain_size);
        //        ofstream myfile;
        //        myfile.open ("C:\\Users\\Alessio\\Documents\\workspace\\calibration\\seed1\\calibration.csv",ios::out);
        //                for (int i = 0; i < tb; i++) {
        //                     //  printf("Fi[%d] %f \n",i, Fi[i]);
        //                    myfile << "Fi[ " << i<<"] = " << Fi[i] << "\n";
        //                }
        //double * Y = new double[rain_size];
        std::vector<double> Y;
        Y.resize(rain_size);
        for (int t = 0; t < rain_size; t++) {
            double ym = 0;
            Y[t] = 0;
            for (int r = 0; r < t; r++)
                if ((t - r) < tb){
                    ym += Fi[t - r] * P[r].getRainMm();
                    // myfile << "Fi[t - r] = " << Fi[t - r] << ", P[r].getRainMm() " << rain[r].getRainMm() << "\n";
                }
            Y[t] = ym;
            //            myfile << "Y[" << t << "] " << ym << "\n";
            //printf("Y[%d] %f \n",t, ym);

        }
        //        myfile.close();

        return Y;

    }

    static int  compareDouble (const void * a, const void * b)
    {
        // - perche decrescente
        if( (double)(((Ym*)a)->getValue()) > (double)(((Ym*)b)->getValue()) ){
            return -1;
        }
        if( (double)(((Ym*)a)->getValue()) < (double)(((Ym*)b)->getValue()) ){
            return 1;
        }
        if( (double)(((Ym*)a)->getValue()) == (double)(((Ym*)b)->getValue()) ){
            return 0;
        }
    }

    void getYmDecr(Ym*&ym,int &size){
        qsort (ym, size, sizeof(Ym),compareDouble);

    }

    int getDifferenceTime(tm temp1,tm temp2){
        ptime rain0 = ptime_from_tm(temp1);
        ptime rainLast = ptime_from_tm(temp2);
        boost::posix_time::time_duration diff1 =(rain0-ptime(date(1970, Jan, 1)));
        boost::posix_time::time_duration diff2 =(rainLast-ptime(date(1970, Jan, 1)));
        std::time_t x = diff1.total_seconds();
        std::time_t y = diff2.total_seconds();
        if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
        {
            //TODO [differenza in minuti] [differenza in ore] [ differenza in giorni ]
            int difference = std::difftime(y, x) / (60*60*24);
            //	        std::cout << std::ctime(&x);
            //	        std::cout << std::ctime(&y);
            //	        std::cout << "difference = " << difference << " days" << std::endl;
            return difference;
        }
        return -1;
    }


    double getFitness(EOT & _eo){

        std::vector<double> Y;
        std::vector<Ym> ym;
        std::vector<Ym> bests;
        int tb = _eo.getSize();
//        std::vector<double> Fi = _eo.getFi();
        ValidationController::getMobilityFunction(Y,
                                                  ym,
                                                   _eo.getFi(),
                                                  rain,
                                                  rain_size,
                                                  activations,
                                                  activations_size,
                                                  tb);
        bool allzero=true;
        for (int i = 0; i < Y.size(); ++i) {
            if(Y[i] != 0){
                allzero=false;
            }
        }

        if(allzero){
            return 0;
        }

        qsort (&ym[0], ym.size(), sizeof(Ym),compareDouble);

        vector<int> TP;
        vector<int> FN;
        vector<int> FP;
        vector<int> TN;

        vector<double> TPR;
        vector<double> FPR;

        double dYcr;
        Ym ymMin;
        Ym ymMin2;
        double momentoDelPrimoOrdine;
        vector<double> lines;
        double AUC = ValidationController::getAUCROC(Y,
                                        ym,
                                        _eo.getFi(),
                                        rain,
                                        rain_size,
                                        activations,
                                        activations_size,
                                        tb,
                                        dYcr,
                                        ymMin,
                                        ymMin2,
                                        TP,
                                        FN,
                                        FP,
                                        TN,
                                        TPR,
                                        FPR,
                                        momentoDelPrimoOrdine,
                                        bests,
                                        lines,
                                        numberOfLines);

        _eo.setTP(TP);
        _eo.setFN(FN);
        _eo.setFP(FP);
        _eo.setTN(TN);

        _eo.setTPR(TPR);
        _eo.setFPR(FPR);

        _eo.setAUC(AUC);

        _eo.setBests(bests);
        _eo.setdYcr(dYcr);
        _eo.setYmMin(ymMin);
        _eo.setYmMin2(ymMin2);
        _eo.setMomentoDelPrimoOrdine(momentoDelPrimoOrdine);




        return AUC;

    }

    /** Actually compute the fitness
     *
     * @param EOT & _eo the EO object to evaluate
     *                  it should stay templatized to be usable
     *                  with any fitness type
     */
    void operator()(EOT & _eo) {

        //int tb = _eo.getSize();

        //Calcolo funzione di mobilità
        //        std::vector<double> Y = getY(rain, _eo.getFi(), tb);

        //        bool allzero=true;

        //        for (int i = 0; i < Y.size(); ++i) {
        //            if(Y[i] != 0){
        //                allzero=false;
        //            }
        //        }


        //        if(allzero){
        //            f=0;
        //        }
        //        else{
        //            f = getFitness(Y,_eo);

        //            double momentoDelPrimoOrdine = 0;
        //            for (int i = 0; i < tb; i++) {
        //                momentoDelPrimoOrdine += _eo.getFi()[i]*((i+1)-0.5);
        //            }
        //            _eo.setMomentoDelPrimoOrdine(momentoDelPrimoOrdine);
        //        }


        double f =getFitness(_eo);
        //delete []Y;
        _eo.fitness(f);
        //}
    }

private:
    // START Private data of an eoSAKeEvalFunc object
    //  varType anyVariable;		   // for example ...
    Rain * rain;
    int rain_size;
    Activation * activations;
    int activations_size;
    int numberOfLines;
    // END   Private data of an eoSAKeEvalFunc object
};

#endif
