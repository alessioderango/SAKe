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
    eoOneMaxMutation()
    //  eoOneMaxMutation( varType  _anyVariable) : anyVariable(_anyVariable)
    // END eventually add or modify the anyVariable argument
    {
        // START Code of Ctor of an eoOneMaxEvalFunc object
        // END   Code of Ctor of an eoOneMaxEvalFunc object

//        percentualePeso= _percentualePeso;
//        percentualeLineareA = _percentualeLineareA;
//        percentualeLineareB = _percentualeLineareB;
//        percentualeGammaA = _percentualeGammaA;
//        percentualeGammaB = _percentualeGammaB;
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
//        std::cout <<" ************************** " << std::endl;
//        std::cout << "MUTATION " << std::endl;
        // START code for mutation of the _genotype object

        /** Requirement
         * if (_genotype has been modified)
         *     isModified = true;
         * else
         *     isModified = false;
         */

        int rndMaxMut= rand() %  (_genotype.getParConst().size()+1);

        //TODO sostituire i valoroi costanti con i parametri in maschera
        double maxLinearFactor = 1;
        double minLinearFactor = -1;

        double maxLinearIntercept = 2;
        double minLinearIntercept  = -2;

        double maxLinearWeight  = 2;
        double minLinearWeight  = 0.2;

        double maxGammaBeta = 10;
        double minGammaBeta  = 0.0001;

        double maxGammaWeight  = 2;
        double minGammaWeight  = 0.2;

        double maxAlfaGammaMinus1 = 0.9999;
        double minAlfaGammaMinus1 = 0.0001;

        double maxBetaGammaMinus1 = 250;
        double minBetaGammaMinus1 = 0.0001;
        int numberofGammaFunction =0;
        for (int i = 0; i < _genotype.getFunctionTypeConst().size(); ++i) {
            if(_genotype.getFunctionType(i) != 0)
                numberofGammaFunction++;
        }

        for (int j = 0; j < rndMaxMut; j++) {
            int i =  rand() %  (_genotype.getParConst().size());
            //Linear
            if(_genotype.getFunctionType(i) == 0){
                //coefficiente angolare
                double tmp1 =_genotype.getPar(i).getParameters(0);
                //termine noto
                double tmp2 = _genotype.getPar(i).getParameters(1);
                // random tra (- tmpi, +tmpi)
                double rndLinearFactor= fRand(-(tmp1*_genotype.getPercentageVariationLinearA(i)),tmp1*_genotype.getPercentageVariationLinearA(i));

                double rndLinearIntercept= fRand(-(tmp2*_genotype.getPercentageVariationLinearB(i)),tmp2*_genotype.getPercentageVariationLinearB(i));
                double tmpLinearFactor = tmp1 + rndLinearFactor;
                double tmpLinearIntercept = tmp2 + rndLinearIntercept;


                if(tmpLinearFactor > maxLinearFactor)
                    tmpLinearFactor = maxLinearFactor;

                if(tmpLinearFactor < minLinearFactor)
                    tmpLinearFactor = minLinearFactor;

                if(tmpLinearIntercept > maxLinearIntercept)
                    tmpLinearIntercept = maxLinearIntercept;

                if(tmpLinearIntercept < minLinearIntercept)
                    tmpLinearIntercept = minLinearIntercept;


                _genotype.setParameters(i,0,tmpLinearFactor);
                _genotype.setParameters(i,1,tmpLinearIntercept);

                double rndDoubleW= fRand(-(_genotype.getW(i)*_genotype.getPercentageVariationWeight(i)),_genotype.getW(i)*_genotype.getPercentageVariationWeight(i));
                double tmpLinearWeight=_genotype.getW(i)+rndDoubleW;

                if(tmpLinearWeight > maxLinearWeight)
                    tmpLinearWeight = maxLinearWeight;

                if(tmpLinearWeight < minLinearWeight)
                    tmpLinearWeight = minLinearWeight;

                 _genotype.setW(i,tmpLinearWeight);

                //controllo > 0

            }else
                if(_genotype.getFunctionType(i) == 1){
                    //Alfa
                    double tmp1 =_genotype.getPar(i).getParameters(0);
                    //Beta
                    double tmp2 = _genotype.getPar(i).getParameters(1);
                    double rndDoubleAlfa= fRand(-(tmp1*_genotype.getPercentageVariationGammaA(i)),tmp1*_genotype.getPercentageVariationGammaA(i));
                    double rndDoubleBeta= fRand(-(tmp2*_genotype.getPercentageVariationGammaB(i)),tmp2*_genotype.getPercentageVariationGammaB(i));

                    double tmpAlfa = tmp1+ rndDoubleAlfa;
                    double tmpBeta = tmp2+ rndDoubleBeta;

                    if(tmpBeta > maxBetaGammaMinus1)
                        tmpBeta = maxBetaGammaMinus1;

                    if(tmpBeta <= minBetaGammaMinus1)
                        tmpBeta = minBetaGammaMinus1;


                    if(tmpAlfa > maxAlfaGammaMinus1)
                        tmpAlfa = maxAlfaGammaMinus1;

                    if(tmpAlfa <= minAlfaGammaMinus1)
                        tmpAlfa = minAlfaGammaMinus1;


                    _genotype.setParameters(i,0,tmpAlfa);
                    _genotype.setParameters(i,1,tmpBeta);

                    //controllo > 0
                    double rndDoubleW= fRand(-(_genotype.getW(i)*_genotype.getPercentageVariationWeight(i)),_genotype.getW(i)*_genotype.getPercentageVariationWeight(i));
                    double tmpGammaWeight=_genotype.getW(i)+rndDoubleW;
                    if(tmpGammaWeight > maxGammaWeight)
                        tmpGammaWeight = maxGammaWeight;

                    if(tmpGammaWeight < minGammaWeight)
                        tmpGammaWeight = minGammaWeight;

                    _genotype.setW(i,tmpGammaWeight);

                }else
                    if(_genotype.getFunctionType(i) == 2){
                        double tmp1 =_genotype.getPar(i).getParameters(0);
                        double tmp2 = _genotype.getPar(i).getParameters(1);
                        double rndDoubleAlfa= fRand(-(tmp1*_genotype.getPercentageVariationGammaA(i)),tmp1*_genotype.getPercentageVariationGammaA(i));
                        double rndDoubleBeta= fRand(-(tmp2*_genotype.getPercentageVariationGammaB(i)),tmp2*_genotype.getPercentageVariationGammaB(i));



                        double tmpBeta = tmp2+ rndDoubleBeta;

                        if(tmpBeta > maxGammaBeta)
                            tmpBeta = maxGammaBeta;

                        if(tmpBeta <= minGammaBeta)
                            tmpBeta = minGammaBeta;


                        double tmpAlfa = tmp1 + rndDoubleAlfa;

                        if(tmpBeta > 0 && tmpBeta <= 1)
                        {
                            if(tmpAlfa > 10)
                                tmpAlfa = 10;
//                            if(tmpAlfa > 500)
//                                tmpAlfa = 500;

                            if(tmpAlfa <= 1)
                                tmpAlfa = 1.0001;
                        }else
                            if(tmpBeta > 1 && tmpBeta <= 10)
                            {
                                if(tmpAlfa > 10)
                                    tmpAlfa = 10;
//                                if(tmpAlfa > 100)
//                                    tmpAlfa = 100;

                                if(tmpAlfa <= 1)
                                    tmpAlfa = 1.0001;
                            }
                            else
                                if(tmpBeta > 10 && tmpBeta <= 100)
                                {
                                    if(tmpAlfa > 25)
                                        tmpAlfa = 25;
//                                    if(tmpAlfa > 40)
//                                        tmpAlfa = 40;

                                    if(tmpAlfa <= 1)
                                        tmpAlfa = 1.0001;
                                }else
                                    if(tmpBeta > 100 && tmpBeta <= 400)
                                    {
                                        if(tmpAlfa > 4)
                                            tmpAlfa = 4;
//                                        if(tmpAlfa > 8)
//                                            tmpAlfa = 8;

                                        if(tmpAlfa <= 1)
                                            tmpAlfa = 1.0001;
                                    }

                        _genotype.setParameters(i,0,tmpAlfa);
                        _genotype.setParameters(i,1,tmpBeta);

                        //controllo > 0
                        double rndDoubleW= fRand(-(_genotype.getW(i)*_genotype.getPercentageVariationWeight(i)),_genotype.getW(i)*_genotype.getPercentageVariationWeight(i));
                        double tmpGammaWeight=_genotype.getW(i)+rndDoubleW;
                        if(tmpGammaWeight > maxGammaWeight)
                            tmpGammaWeight = maxGammaWeight;

                        if(tmpGammaWeight < minGammaWeight)
                            tmpGammaWeight = minGammaWeight;

                        _genotype.setW(i,tmpGammaWeight);
                    }

//                    std::cout <<" ************************** " << std::endl;
//                    std::cout << _genotype.getTranslationConst(i) << std::endl;
                    if(_genotype.getTranslationConst(i) != 0)
                    {
                        //valore attuale della traslazione
                        double translationValue = _genotype.getPar(i).getParameters(2);
                        double coefficienteMolt = _genotype.getTranslation(i);

                        double tmpTranslation= fRand(-(translationValue*coefficienteMolt),translationValue*coefficienteMolt);

//                        std::cout <<" ************************** " << std::endl;
//                        std::cout << _genotype.getTranslation(i) << std::endl;

//                        if(tmpTranslation < 0){
//                            tmpTranslation=0;
//                        }
                        if(translationValue+tmpTranslation > (_genotype.getYCombinataConst().size())){
                            _genotype.setParameters(i,2,_genotype.getYCombinataConst().size()/numberofGammaFunction);
                            //tmpTranslation = _genotype.getYCombinataConst().size()/2;
                        }else
                             _genotype.setParameters(i,2,_genotype.getPar(i).getParameters(2)+tmpTranslation);
//                        std::cout << (_genotype.getTranslation(i)+tmpTranslation) << std::endl;
//                        std::cout << std::endl;


                    }


        }

        return isModified;
        // END code for mutation of the _genotype object
    }

private:
    // START Private data of an eoOneMaxMutation object
    //  varType anyVariable;		   // for example ...
//    std::vector<double> percentualePeso;
//    std::vector<double> percentualeLineareA;
//    std::vector<double> percentualeLineareB;
//    std::vector<double> percentualeGammaA;
//    std::vector<double> percentualeGammaB;
    // END   Private data of an eoOneMaxMutation object
};

#endif
