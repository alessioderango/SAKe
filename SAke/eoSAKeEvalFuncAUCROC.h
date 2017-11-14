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
    /// Ctor - no requirement
    // START eventually add or modify the anyVariable argument
    eoSAKeEvalFuncAUCROC(Rain * _rain, int _rain_size, Activation* _activation,
                         int _activation_size)
    //  eoSAKeEvalFunc( varType  _anyVariable) : anyVariable(_anyVariable)
    // END eventually add or modify the anyVariable argument
    {
        rain = _rain;
        rain_size = _rain_size;
        activations = _activation;
        activations_size = _activation_size;
        numeroValitazioni=0;
        // START Code of Ctor of an eoSAKeEvalFunc object
        // END   Code of Ctor of an eoSAKeEvalFunc object
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


    double getFitness(std::vector<double> Y,EOT & _eo){
//        cout << "Start Fitness AUC ROC" << endl;
        std::vector<Ym> ym;

        for (int t = 1; t < rain_size-1; t++) {
            bool cross = (((Y[t] - Y[t - 1]) * (Y[t + 1] - Y[t])) < 0) && (Y[t] > Y[t - 1]);
            if(cross){
                // trovato un picco deve essere considerato
                Ym p;
                p.setValue(Y[t]);
                p.setTime(rain[t].getTime());
                ym.push_back(p);
            }
        }

        qsort (&ym[0], ym.size(), sizeof(Ym),compareDouble);


        Ym ymMax = ym[0];

        double line = ymMax.getValue()/10;

//        cout << ymMax.getValue() << endl;
//        cout << line << endl;

        vector<double> lines;
        for (int i = 10; i >= 1; i--) {
            lines.push_back(line*i);
        }

        //inside the activation range
        vector<int> TP(10,0);// true positive
        vector<int> FN(10,0);// false negative

        //outside the activation range
        vector<int> FP(10,0);// false positive
        vector<int> TN(10,0);// true negative


        for (int i = 0; i < lines.size(); ++i) {

            for(int t = 0; t < rain_size; t++) {

                bool jump = false;
                //controllo TP e FN
                for (int s = 0; s < activations_size; s++) {
                    //TODO inserire variabili intervallo giorni
                    int result1 = getDifferenceTime(activations[s].getStart(),rain[t].getTime());
                    int result2 = getDifferenceTime(rain[t].getTime(),activations[s].getEnd());

                    if(result1>=-2 && result2>=-1){
                        jump = true;
                    }
                }

                if(jump)
                    continue;


                //controllo FP e TN
                if(Y[t] < lines[i])
                   TN[i]++;
                else
                   FP[i]++;
            }
        }

        for (int i = 0; i < lines.size(); ++i) {
            FN[i] = activations_size;
            for (int s = 0; s < activations_size; s++) {

                //controllo TP e FN

                for(int t = 0; t < rain_size; t++) {
                    //TODO inserire variabili intervallo giorni
                    int result1 = getDifferenceTime(activations[s].getStart(),rain[t].getTime());
                    int result2 = getDifferenceTime(rain[t].getTime(),activations[s].getEnd());

                    if(result1>=-2 && result2>=-1){
                        if(Y[t] >= lines[i]){
                            TP[i]++;
                            FN[i]--;
                            break;
                        }
                    }
                }
            }
        }






        vector<double> TPR(10,0);// true positive rate
        vector<double> FPR(10,0);// False positive rate

        for (int i = 0; i < 10; ++i) {
            TPR[i] = (double) (TP[i]/((double) (TP[i]+FN[i])));
            double TNR =  (double)TN[i] / (double)(TN[i]+FP[i]);
            FPR[i] = (double) (1-((double) TNR));



            //cout << TPR[i] << ";" << FPR[i] << ";"<< endl;
        }

        double AUC=0; // Area under the curve
        // primo trapezio
        AUC += FPR[0]*TPR[0]*((double)(0.5));
        for (int i = 0; i < 9; ++i) {
            double h = FPR[i+1]-FPR[i];
            double base = TPR[i]+TPR[i+1];
            double tmp = (((double)(0.5))*(h))*(base);
            //scout << "area trapezio "<<i<< " base --> " << base  <<" h --> " << h  <<"  = " << tmp <<endl;
            AUC += tmp;
        }
        AUC += (1-FPR[9])*((double)(0.5))*(1+TPR[9]);

        //cout << "AUC "<<AUC<<endl;

        double YsMin = 999999999;
        int iMin =-1;
        std::vector<Ym> bests;
        for (int s = 0; s < activations_size; s++) {
            for (int i = 0; i < ym.size(); i++) {
                //TODO inserire variabili intervallo giorni
                int result1 = getDifferenceTime(activations[s].getStart(),ym[i].getTime());
                int result2 = getDifferenceTime(ym[i].getTime(),activations[s].getEnd());
                if(result1>=-2 && result2>=-1){
                    ym[i].setI(i+1);
                    bests.push_back(ym[i]);
                    if(ym[i].getValue() < YsMin){
                        YsMin =ym[i].getValue();
                        iMin=i;
                    }//if
                    break;
                    //}
                    // calcolo valori per calcolare dYcr per risparmiare calcoli

                }//if
            }//for
        }//for
        //std::cout << std::endl;

        _eo.setTP(TP);
        _eo.setFN(FN);
        _eo.setFP(FP);
        _eo.setTN(TN);

        _eo.setTPR(TPR);
        _eo.setFPR(FPR);

        _eo.setAUC(AUC);



        _eo.setBests(bests);
        if(iMin < 0)  iMin = 0;
        if(iMin > ym.size()-1)  iMin = ym.size()-1;
        int index=(iMin+1);
        double dYcr = (YsMin-ym[index].getValue())/YsMin;

        _eo.setdYcr(dYcr);

        Ym ymMin= ym[iMin];
        Ym ymMin2 = ym[index];
        _eo.setYmMin(ymMin);
        _eo.setYmMin2(ymMin2);




        return AUC;

    }

    /** Actually compute the fitness
     *
     * @param EOT & _eo the EO object to evaluate
     *                  it should stay templatized to be usable
     *                  with any fitness type
     */
    void operator()(EOT & _eo) {
        numeroValitazioni++;

        int tb = _eo.getSize();

        //Calcolo funzione di mobilità
        std::vector<double> Y = getY(rain, _eo.getFi(), tb);

        bool allzero=true;

        for (int i = 0; i < Y.size(); ++i) {
            if(Y[i] != 0){
                allzero=false;
            }
        }

        double f;
        if(allzero){
            f=0;
        }
        else{
            f = getFitness(Y,_eo);

            double momentoDelPrimoOrdine = 0;
            for (int i = 0; i < tb; i++) {
                momentoDelPrimoOrdine += _eo.getFi()[i]*((i+1)-0.5);
            }
            _eo.setMomentoDelPrimoOrdine(momentoDelPrimoOrdine);
        }
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
    int numeroValitazioni;
    // END   Private data of an eoSAKeEvalFunc object
};

#endif
