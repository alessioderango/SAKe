/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is usefulin Emacs-like editors
 */

/*
Template for evaluator in EO, a functor that computes the fitness of an EO
==========================================================================
*/

#ifndef _eoOneMaxEvalFunc_h
#define _eoOneMaxEvalFunc_h

// include whatever general include you need
#include <stdexcept>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"
#include <iostream>
#include <boost/math/distributions/gamma.hpp>


using namespace std;


/**
  Always write a comment in this format before class definition
  if you want the class to be documented by Doxygen
*/
template <class EOT>
class eoOneMaxEvalFunc : public eoEvalFunc<EOT>
{
public:
    /// Ctor - no requirement
    // START eventually add or modify the anyVariable argument
    eoOneMaxEvalFunc(   std::vector<double> _x, std::vector<double> _y)
    //  eoOneMaxEvalFunc( varType  _anyVariable) : anyVariable(_anyVariable)
    // END eventually add or modify the anyVariable argument
    {
        // START Code of Ctor of an eoOneMaxEvalFunc object
        // END   Code of Ctor of an eoOneMaxEvalFunc object
        x=_x;
        y=_y;
    }

    double gamma_pdf(double alfa, double beta, double x) {
        return boost::math::gamma_p_derivative(alfa, x / beta)/beta;
    }

    //DEFINITION OF FUNCTION TYPE
    //    0 linear
    //    1 negative esponential
    //    2 gamma
    //    3 power





    void operator()(EOT & _eo)
    {
        // test for invalid to avoid recomputing fitness of unmodified individuals
        if (_eo.invalid())
        {
            _eo.clearYCombinata();



            //cout << "fitness "<< endl;
            std::vector< std::vector<double> > matrixY(_eo.getWConst().size(),std::vector<double>(x.size()));

            //            cout << endl;
            //cout << "x.size() " << x.size() << endl;

            for (int i = 0; i < _eo.getWConst().size(); ++i) {


//                cout << "translation  " << translationTmp << endl;
                for (int j = 0; j < x.size(); j++) {
                    double yTmp=0;


                    if(_eo.getFunctionType(i) == 0){
                        yTmp =(_eo.getPar(i).getParameters(0)*x[j])+_eo.getPar(i).getParameters(1);
                        // cout << "yTmp 1 " << yTmp << endl;
                        if(yTmp <0)
                            yTmp=0;

                    }else
                         if(_eo.getFunctionType(i) == 2 || _eo.getFunctionType(i) == 1){
                                double alfa=_eo.getPar(i).getParameters(0);
                                double beta=_eo.getPar(i).getParameters(1);
//                                if(alfa < 0)
//                                {
//                                    alfa = 0;
//                                    cout << "alfa negativa" << endl;
//                                }
//                                if(beta < 0)
//                                {

//                                    cout << "beta negativa    " << beta << endl;
//                                     beta = 0;
//                                }
                                    yTmp = gamma_pdf(alfa,beta,x[j]);
                            }

                      matrixY[i][j]=(_eo.getW(i)*yTmp);
                      //matrixY[i][j]=(yTmp);
                }
                //cout << "*********************************************** FINE" << endl;
            }






            //Swift translazione
            for (int i = 0; i < _eo.getWConst().size(); ++i) {
               //  for (int j = 0; j < x.size(); j++) {
                     std::vector<double> Yswifted;
                     //translation
                     long long int s = (int)_eo.getPar(i).getParameters(2);
                     int xsize = x.size();

//                     for (int k = 0; k < x.size(); ++k) {
//                         Yswifted.push_back(0);
//                     }
//                     
//                     {
//                         cout <<" x = "  <<x.size() << " --  s =" << s << endl;
////                     }
//                     cout <<" BEFORE  SWIFT "  << endl;
//                     for (int k = 0; k < xsize; ++k) {
//                          cout << " matrixY["<< i << "]["<< k << "] = " << matrixY[i][k] <<endl;
//                     }


                     if(s >= 0)
                     {
                         if(s > xsize)
                             s=xsize;

                         for (int k = 0; k < s; ++k) {
                             Yswifted.push_back(0);
                         }
//                         cout <<" xsize = "  <<xsize << " --  s =" << s << endl;
//                         cout << " x.size()-s = " << xsize-s << endl;
                         for (int k = 0; k < xsize-s; ++k) {
//                             if(s > x.size())
//                             cout << "i = " << i << "k = " << k <<endl;
                             Yswifted.push_back(matrixY[i][k]);
                         }
                     }
                     else
                     {
                         s=abs(s);
                         if(s < -xsize)
                         {
                             s=0;
                         }
                         if(s > xsize)
                             s=xsize;
//                         cout <<" xsize = "  <<xsize << " --  s =" << s << endl;
//                         cout << " x.size()-s = " << xsize-s << endl;
                         for (int k = s; k < xsize; ++k) {
//                             if(s > x.size())
//                             cout << "i = " << i << " k = " << k <<endl;
                             Yswifted.push_back(matrixY[i][k]);
                         }
                         for (int k = 0; k < s; ++k) {
                             Yswifted.push_back(0);
                         }

                     }

//                     cout <<" AFTER  SWIFT "  << endl;
//                     for (int k = 0; k < xsize; ++k) {
//                          cout << "  Yswifted[" << k << "] = " <<  Yswifted[k] <<endl;
//                     }

                     for (int k = 0; k < x.size(); ++k) {
                        matrixY[i][k] =  Yswifted[k];
                     }

               //  }

            }


            for (int i = 0; i < x.size(); i++) {
                double sum=0;
                for (int j = 0; j < _eo.getWConst().size(); j++) {
                    sum+=matrixY[j][i];
                }
                _eo.addYCombinata(sum);
            }

            double fitness=0;
            for (int i = 0; i < y.size(); i++) {
                double tmp = y[i]-_eo.getYCombinataConst(i);
                fitness+=pow(tmp,2);
            }
            //            cout << "fitness " << fitness << endl;

            double media = 0;
            for (int i = 0; i < y.size(); i++) {
                media += y[i];
            }
            media = media/y.size();

            //            cout << "media " << media << endl;

            double sommaMedia=0;
            for (int i = 0; i < y.size(); i++) {
                double tmp = y[i]-media;
                sommaMedia+=pow(tmp,2);
            }

            //            cout << "sommaMedia " << sommaMedia << endl;

            //            cout << "fitness/sommaMedia " << fitness/sommaMedia << endl;

            double fitFinale = (100*(1-(fitness/sommaMedia)));
            //cout << "fitness finale " << fitFinale << endl;

            //            cout << "Stampo valutazione" << endl;
            //            cout << "Pesi " << endl;
            //            for (int i = 0; i < _eo.getWConst().size(); ++i) {
            //                cout <<_eo.getW(i) << endl;
            //            }
            //            cout << endl;
            //            cout << "Parametri " << endl;
            //            for (int i = 0; i < _eo.getParConst().size(); ++i) {
            //                cout <<_eo.getFunctionType(i) << endl;
            //                if(_eo.getFunctionType(i) == 0){
            //                    cout << _eo.getPar(i).getParameters(0) << endl;
            //                    cout << _eo.getPar(i).getParameters(1) << endl;
            //                    cout << endl;
            //                }else
            //                    if(_eo.getFunctionType(i) == 1){
            //                        cout << _eo.getPar(i).getParameters(0) << endl;
            //                         cout << endl;
            //                    }else
            //                        if(_eo.getFunctionType(i) == 2){
            //                            cout << _eo.getPar(i).getParameters(0) << endl;
            //                            cout << _eo.getPar(i).getParameters(1) << endl;
            //                            cout << endl;
            //                        }


            //            }
            //            cout << endl;
            //            cout << "Fine " << endl;


            _eo.fitness(fitFinale);



        }
    }




private:
    // START Private data of an eoOneMaxEvalFunc object
    //  varType anyVariable;		   // for example ...
    // END   Private data of an eoOneMaxEvalFunc object

    std::vector<double> x;
    std::vector<double> y;
};


#endif
