/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

 The above line is usefulin Emacs-like editors
 */

/*
 Template for evaluator in EO, a functor that computes the fitness of an EO
 ==========================================================================
 */

#ifndef _eoSAKeEvalFuncEqualWeights_h
#define _eoSAKeEvalFuncEqualWeights_h

// include whatever general include you need
#include <stdexcept>
#include <fstream>
#include <ctime>
using namespace std;
#define DAYS  ((60) (*) (60) (*) (24))
#define HOURS ((60) (*) (60))

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


template<class EOT>
class eoSAKeEvalFuncEqualWeights: public eoEvalFunc<EOT> {
public:
    eoSAKeEvalFuncEqualWeights(Rain * _rain, int _rain_size, Activation* _activation,
            int _activation_size)

			{
		rain = _rain;
		rain_size = _rain_size;
		activations = _activation;
        activations_size = _activation_size;
        numeroValitazioni=0;
	}

    std::vector<double> getY(Rain *& P, std::vector<double> Fi, int tb) {

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

        }

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
        boost::posix_time::time_duration diff1 =(rain0-ptime(date(1900, Jan, 1)));
        boost::posix_time::time_duration diff2 =(rainLast-ptime(date(1900, Jan, 1)));
        std::time_t x = diff1.total_seconds();
        std::time_t y = diff2.total_seconds();
	    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
	    {
            //TODO [differenza in minuti] [differenza in ore] [ differenza in giorni ]
            int difference = std::difftime(y, x);
//	        std::cout << std::ctime(&x);
//	        std::cout << std::ctime(&y);
//	        std::cout << "difference = " << difference << " days" << std::endl;
			return difference;
	    }
		return -1;
	}


    bool diffTimeInterval(tm actStart, tm actEnd, tm pichTime){
        int result1 = getDifferenceTime(actStart,pichTime);
        int result2 = getDifferenceTime(pichTime,actEnd);
         if(result1>=0 && result2>=0){
             return true;
         }
         else
             return false;
    }


    double getFitness(std::vector<double> Y,EOT & _eo){

		double f=0;
        std::vector<Ym> ym;//= new Ym[rain_size];
        //ym.resize(rain_size);
		int countYm=0;

		for (int t = 1; t < rain_size-1; t++) {
            bool cross = (((Y[t] - Y[t - 1]) * (Y[t + 1] - Y[t])) < 0) && (Y[t] > Y[t - 1]);

            bool jump = false;
            if(cross){

                for (int a = 0; a < activations_size; a++) {
                     if(diffTimeInterval(activations[a].getStart(), activations[a].getEnd(),rain[t].getTime())){
//                         cout << "salto un pico all'interno di un intervallo " << endl;
                         jump = true;
                     }
                }

                if(jump)
                    continue;
                Ym p;
                p.setValue(Y[t]);
                p.setTime(rain[t].getTime());
                ym.push_back(p);
//				ym[countYm].setValue(Y[t]);
//				ym[countYm].setTime(rain[t].getTime());
//                countYm++;
			}
		}

        for (int s = 0; s < activations_size; s++) {
            double maxPich = 0;
            int tMax =0;
            for (int t = 1; t < rain_size-1; t++) {

                if(diffTimeInterval(activations[s].getStart(), activations[s].getEnd(),rain[t].getTime())){
                    if(Y[t] > maxPich)
                    {
                        maxPich = Y[t];
                        tMax = t;
                    }
                }
            }
            Ym p;
            p.setValue(Y[tMax]);
            p.setTime(rain[tMax].getTime());
            ym.push_back(p);

        }

        //getYmDecr(ym,countYm);
        qsort (&ym[0], ym.size(), sizeof(Ym),compareDouble);

//        for (int i = 0; i < countYm; i++) {
//               printf("ym[%d] %f \n",i, ym[i].getValue());

//        }
//        printf("countYm %d \n",countYm);


        double YsMin = 999999999;
        int iMin =-1;
        std::vector<Ym> bests;
        for (int s = 0; s < activations_size; s++) {
            for (int i = 0; i < ym.size(); i++) {
                //TODO inserire variabili intervallo giorni
                int result1 = getDifferenceTime(activations[s].getStart(),ym[i].getTime());
                int result2 = getDifferenceTime(ym[i].getTime(),activations[s].getEnd());
                if(result1>=-2 && result2>=-1){
                    //if(i<countYm)
                    //if(i<(activations_size)){
//                       printf("i %d \n",i);


                    if(i < activations_size)
                      f += 1 / (double)activations_size;
                    else
                      f += 1 / (double)(i + 1);

//                        printf("f %f \n",f);
                        ym[i].setI(i+1);
                        bests.push_back(ym[i]);
//                        int year = ym[i].getTime().tm_year +1900;
//                        int mon = ym[i].getTime().tm_mon +1;
//                        int day = ym[i].getTime().tm_mday ;
//                        std::cout << "year " << year << " mon " << mon << " day " << day << std::endl;
//                        std::cout << "ym[i] value " << ym[i].getValue() << std::endl;
                        //printf("+  %f \n",(1 / (double)(i + 1)));
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
        _eo.setBests(bests);
		if(iMin < 0)  iMin = 0;
        if(iMin > ym.size()-1)  iMin = ym.size()-1;
        int index=(iMin+1);
        double dYcr = (YsMin-ym[index].getValue())/YsMin;
//        printf("dYcr %f \n",dYcr);
//        printf("YsMin %f \n",YsMin);
//        printf("YsMin2 %f \n",ym[index].getValue());
        _eo.setdYcr(dYcr);
        //_eo.setYsMin(YsMin);
        //_eo.setYsMin2(ym[index].getValue());
        //_eo.setiMin(iMin);
        Ym ymMin= ym[iMin];
        Ym ymMin2 = ym[index];
        _eo.setYmMin(ymMin);
        _eo.setYmMin2(ymMin2);

//       printf("f %f fMax %f fitness = %f \n",f,fMax,(double) (f/fMax));

        //delete []ym;

        return (double) (f);
	}

	/** Actually compute the fitness
	 *
	 * @param EOT & _eo the EO object to evaluate
	 *                  it should stay templatized to be usable
	 *                  with any fitness type
	 */
	void operator()(EOT & _eo) {
        numeroValitazioni++;
        //printf("numeroValitazioni  %d ",numeroValitazioni);
        // test for invalid to avoid recomputing fitness of unmodified individuals
        //if (_eo.invalid()) {
			int tb = _eo.getSize();
            //printf("valito individuo con tb %d \n",tb);

			//Prelevo kernels
            //double * Fi = _eo.getFi();
            //Calcolo funzione di mobilità
            std::vector<double> Y = getY(rain, _eo.getFi(), tb);
//			il primo elemento il dato relativo alla prima piogge
//			tm temp = rain[0].getTime();
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
