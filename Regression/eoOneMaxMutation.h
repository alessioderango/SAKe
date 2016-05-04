/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is useful in Emacs-like editors
 */

/*
Template for simple mutation operators
======================================
*/

#ifndef eoOneMaxMutation_H
#define eoOneMaxMutation_H


#include <eoOp.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT>
class eoOneMaxMutation: public eoMonOp<GenotypeT>
{
public:
    /**
     * Ctor - no requirement
     */
    // START eventually add or modify the anyVariable argument
    eoOneMaxMutation(    double _percentualePeso,
                         double _percentualeLineareA,
                         double _percentualeLineareB,
                         double _percentualeGammaA,
                         double _percentualeGammaB)
    //  eoOneMaxMutation( varType  _anyVariable) : anyVariable(_anyVariable)
    // END eventually add or modify the anyVariable argument
    {
        // START Code of Ctor of an eoOneMaxEvalFunc object
        // END   Code of Ctor of an eoOneMaxEvalFunc object

        percentualePeso= _percentualePeso;
        percentualeLineareA = _percentualeLineareA;
        percentualeLineareB = _percentualeLineareB;
        percentualeGammaA = _percentualeGammaA;
        percentualeGammaB = _percentualeGammaB;
    }

    /// The class name. Used to display statistics
    string className() const { return "eoOneMaxMutation"; }

    double fRand(double fMin, double fMax)
    {
        double f = (double)rand() / (double)RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    /**
     * modifies the parent
     * @param _genotype The parent genotype (will be modified)
     */
    bool operator()(GenotypeT & _genotype)
    {
        bool isModified(true);
        // START code for mutation of the _genotype object

        /** Requirement
         * if (_genotype has been modified)
         *     isModified = true;
         * else
         *     isModified = false;
         */

        int rndMaxMut= rand() %  _genotype.getParConst().size();

        //        _genotype.B().setParametersExponential(rnd,_genotype.B().getParametersExponential(rnd)+150);
        //         double percentuale=0.01;
        //         double percentualePeso=0.09;
        //         double percentualeLineareA=0.06;
        //         double percentualeLineareB=0.06;
        //         double percentualeGammaA=0.12;
        //         double percentualeGammaB=0.12;

        for (int i = 0; i < rndMaxMut; i++) {

            if(_genotype.getFunctionType(i) == 0){
                double tmp1 =_genotype.getPar(i).getParameters(0);
                double tmp2 = _genotype.getPar(i).getParameters(1);
                double rndDoubleAlfa= fRand(-(tmp1*percentualeLineareA),tmp1*percentualeLineareA);
                double rndDoubleBeta= fRand(-(tmp2*percentualeLineareB),tmp2*percentualeLineareB);
                double tmpAlfa = tmp1 + rndDoubleAlfa;
                double tmpBeta = tmp2+ rndDoubleBeta;
                _genotype.setParameters(i,0,tmpAlfa);
                _genotype.setParameters(i,1,tmpBeta);

                double rndDoubleW= fRand(-(_genotype.getW(i)*percentualePeso),_genotype.getW(i)*percentualePeso);
                if(_genotype.getW(i)+rndDoubleW < 0)
                    _genotype.setW(i,_genotype.getW(i)-rndDoubleW);
                else
                 _genotype.setW(i,_genotype.getW(i)+rndDoubleW);
                //controllo > 0

            }else
                if(_genotype.getFunctionType(i) == 1){
                    //double tmp =_genotype.getPar(i).getParameters(0);
                    double rndDouble= fRand(-(_genotype.getPar(i).getParameters(0)*0.0001),_genotype.getPar(i).getParameters(0)*0.0001);
                    _genotype.setParameters(i,0,_genotype.getPar(i).getParameters(0)+ rndDouble);

                    //controllo > 0

                }else
                    if(_genotype.getFunctionType(i) == 2){
                        double tmp1 =_genotype.getPar(i).getParameters(0);
                        double tmp2 = _genotype.getPar(i).getParameters(1);
                        double rndDoubleAlfa= fRand(-(tmp1*percentualeGammaA),tmp1*percentualeGammaA);
                        double rndDoubleBeta= fRand(-(tmp2*percentualeGammaB),tmp2*percentualeGammaB);

                        double tmpAlfa = tmp1 + rndDoubleAlfa;
                        if(tmpAlfa < 0)
                            tmpAlfa = 0.00001;

                        double tmpBeta = tmp2+ rndDoubleBeta;
                        if(tmpBeta < 0)
                            tmpBeta = 0.00001;
                        _genotype.setParameters(i,0,tmpAlfa);
                        _genotype.setParameters(i,1,tmpBeta);

                        //controllo > 0
                        double rndDoubleW= fRand(-(_genotype.getW(i)*percentualePeso),_genotype.getW(i)*percentualePeso);
                        if(_genotype.getW(i)+rndDoubleW < 0)
                            _genotype.setW(i,_genotype.getW(i)-rndDoubleW);
                        else
                         _genotype.setW(i,_genotype.getW(i)+rndDoubleW);
                    }

            //pesi fissi all'inizio





        }





        return isModified;
        // END code for mutation of the _genotype object
    }

private:
    // START Private data of an eoOneMaxMutation object
    //  varType anyVariable;		   // for example ...
    double percentualePeso;
    double percentualeLineareA;
    double percentualeLineareB;
    double percentualeGammaA;
    double percentualeGammaB;
    // END   Private data of an eoOneMaxMutation object
};

#endif
