/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is usefulin Emacs-like editors
 */

/*
Template for EO objects initialization in EO
============================================
*/

#ifndef _eoOneMaxInit_h
#define _eoOneMaxInit_h

// include the base definition of eoInit
#include <eoInit.h>
#include <Regression/parameters.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * There is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO (e.g. to initialize
 *    atoms of an eoVector you will need an eoInit<AtomType>)
 */
template <class GenotypeT>
class eoOneMaxInit: public eoInit<GenotypeT> {
public:
    /// Ctor - no requirement
    // START eventually add or modify the anyVariable argument
    //  eoOneMaxInit()
    eoOneMaxInit( double *weights,
                  int weightsSize,
                  int *functionTypes,
                  int functionTypesSize,
                  Parameters *parameters,
                  int parametersSize,
                  unsigned  _vecSize,
                  double* _percentualePeso,
                  int _percentualePesoSize,
                  double* _percentualeLineareA,
                  int _percentualeLineareASize,
                  double* _percentualeLineareB,
                  int _percentualeLineareBSize,
                  double* _percentualeGammaA,
                  int _percentualeGammaASize,
                  double* _percentualeGammaB,
                  int _percentualeGammaBSize,
                  double* translation
                  ) : vecSize(_vecSize)
      // END eventually add or modify the anyVariable argument
    {
        // START Code of Ctor of an eoOneMaxInit object
        this->weights = weights;
        this->weightsSize = weightsSize;
        this->functionTypes = functionTypes;
        this->functionTypesSize = functionTypesSize;
        this->parameters = parameters;
        this->parametersSize = parametersSize;
        percentualePeso =_percentualePeso;
        percentualePesoSize= _percentualePesoSize;
        percentualeLineareA=_percentualeLineareA;
        percentualeLineareASize=_percentualeLineareASize;
        percentualeLineareB= _percentualeLineareB;
        percentualeLineareBSize=_percentualeLineareBSize;
        percentualeGammaA=_percentualeGammaA;
        percentualeGammaASize=_percentualeGammaASize;
        percentualeGammaB=_percentualeGammaB;
        percentualeGammaBSize=_percentualeGammaBSize;
        this->translation = translation;
        translationSize=functionTypesSize;

        // END   Code of Ctor of an eoOneMaxInit object
    }

    double fRand(double fMin, double fMax)
    {
        double f = (double)rand() / (double)RAND_MAX;
        return fMin + f * (fMax - fMin);
    }




    /** initialize a genotype
   *
   * @param _genotype  generally a genotype that has been default-constructed
   *                   whatever it contains will be lost
   */
    void operator()(GenotypeT & _genotype)
    {
        // START Code of random initialization of an eoOneMax object
        //    vector<bool> b(vecSize);
        //    for (unsigned i=0; i<vecSize; i++)
        //      b[i]=rng.flip();
        //    _genotype.setB(b);
        //    // END   Code of random initialization of an eoOneMax object
        //    _genotype.invalidate();	   // IMPORTANT in case the _genotype is old

        //        linear
        //              _genotype.addW(0.0171199623121444);

        for (int i = 0; i < weightsSize; i++) {
            _genotype.addW(this->weights[i]);
        }

        for (int i = 0; i < functionTypesSize; i++) {
            _genotype.addFunctionType(this->functionTypes[i]);
        }

        for (int i = 0; i < parametersSize; i++) {
            _genotype.addPar(this->parameters[i]);
        }

        for (int i = 0; i < percentualePesoSize; i++) {
            _genotype.addPercentageVariationWeight(percentualePeso[i]);
        }
        for (int i = 0; i < percentualeLineareASize; i++) {
            _genotype.addPercentageVariationLinearA(this->percentualeLineareA[i]);
        }
        for (int i = 0; i <  percentualeLineareBSize; i++) {
            _genotype.addPercentageVariationLinearB(this->percentualeLineareB[i]);
        }
        for (int i = 0; i < percentualeGammaASize; i++) {
            _genotype.addPercentageVariationGammaA(this->percentualeGammaA[i]);
        }
        for (int i = 0; i < percentualeGammaBSize; i++) {
            _genotype.addPercentageVariationGammaB(this->percentualeGammaB[i]);
        }
        for (int i = 0; i < percentualeGammaBSize; i++) {
            _genotype.addPercentageVariationGammaB(this->percentualeGammaB[i]);
        }

        for (int i = 0; i < translationSize; i++) {
            std::cout << " translation - ["<< i <<"] = "<< this->translation[i] << std::endl;
            _genotype.addTranslation(this->translation[i]);
        }
        std::cout <<  std::endl;
//        _genotype.setPercentageVariationWeight(percentageWeight);
//        _genotype.setPercentageVariationLinearA(percentageLineareA);
//        _genotype.setPercentageVariationLinearB(percentageLineareB);
//        _genotype.setPercentageVariationGammaA(percentageGammaA);
//        _genotype.setPercentageVariationGammaB(percentageGammaB);

    }

private:
    // START Private data of an eoOneMaxInit object
    unsigned vecSize;     // size of all bitstrings that this eoInit randomize
    double * weights;
    int weightsSize;
    int * functionTypes;
    int functionTypesSize;
    Parameters * parameters;
    int parametersSize;


    double* percentualePeso;
    int percentualePesoSize;
    double* percentualeLineareA;
    int percentualeLineareASize;
    double* percentualeLineareB;
    int percentualeLineareBSize;
    double* percentualeGammaA;
    int percentualeGammaASize;
    double* percentualeGammaB;
    int percentualeGammaBSize;
    double* translation;
    int translationSize;

    //  varType anyVariable;		   // for example ...
    // END   Private data of an eoOneMaxInit object
};

#endif
