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
                  unsigned  _vecSize) : vecSize(_vecSize)
      // END eventually add or modify the anyVariable argument
    {
        // START Code of Ctor of an eoOneMaxInit object
        this->weights = weights;
        this->weightsSize = weightsSize;
        this->functionTypes = functionTypes;
        this->functionTypesSize = functionTypesSize;
        this->parameters = parameters;
        this->parametersSize = parametersSize;


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


//              _genotype.addW(1);
//              _genotype.addW(1);

//                //gamma
//              _genotype.addW(0.073);
//              _genotype.addW(0.99);
//              _genotype.addW(0.83);
//              _genotype.addW(0.974);
//              _genotype.addW(0.907);

//              _genotype.addFunctionType(0);
//              _genotype.addFunctionType(0);
//              _genotype.addFunctionType(2);
//              _genotype.addFunctionType(2);
//              _genotype.addFunctionType(2);
//              _genotype.addFunctionType(2);
//              _genotype.addFunctionType(2);

//              //linear par
//              Parameters tmp;
//              tmp.addParameters(0.000046);
//              tmp.addParameters(0);
//              _genotype.addPar(tmp);

//              Parameters tmp1;
//              tmp1.addParameters(-0.04);
//              tmp1.addParameters(0.55);
//              _genotype.addPar(tmp1);

//              //gamma par

//              Parameters tmp2;
//              tmp2.addParameters(52.9);
//              tmp2.addParameters(0.05);
//              _genotype.addPar(tmp2);


//              Parameters tmp3;
//              tmp3.addParameters(1000);
//              tmp3.addParameters(0.120119);
//              _genotype.addPar(tmp3);


//              Parameters tmp4;
//              tmp4.addParameters(899);
//              tmp4.addParameters(0.0173);
//              _genotype.addPar(tmp4);

//              Parameters tmp5;
//              tmp5.addParameters(4.37);
//              tmp5.addParameters(7.18);
//              _genotype.addPar(tmp5);

//              Parameters tmp6;
//              tmp6.addParameters(699);
//              tmp6.addParameters(40);
//              _genotype.addPar(tmp6);

        //RANDOM

//        double random=fRand(0,1000);
//        _genotype.addW(random);
//        random=fRand(0,1000);
//        _genotype.addW(random);

//        //gamma
//        random=fRand(0,1000);
//        _genotype.addW(random);
//        random=fRand(0,1000);
//        _genotype.addW(random);
//        random=fRand(0,1000);
//        _genotype.addW(random);
//        random=fRand(0,1000);
//        _genotype.addW(random);
//        random=fRand(0,1000);
//        _genotype.addW(random);

//        _genotype.addFunctionType(0);
//        _genotype.addFunctionType(0);
//        _genotype.addFunctionType(2);
//        _genotype.addFunctionType(2);
//        _genotype.addFunctionType(2);
//        _genotype.addFunctionType(2);
//        _genotype.addFunctionType(2);

//        //linear par
//        Parameters tmp;
//        random=fRand(-100,100);
//        tmp.addParameters(random);
//        random=fRand(-100,100);
//        tmp.addParameters(random);
//        _genotype.addPar(tmp);

//        Parameters tmp1;
//        random=fRand(-100,100);
//        tmp1.addParameters(random);
//        random=fRand(-100,100);
//        tmp1.addParameters(random);
//        _genotype.addPar(tmp1);

//        //gamma par

//        Parameters tmp2;
//        random=fRand(0,2000);
//        tmp2.addParameters(random);
//        random=fRand(0,2000);
//        tmp2.addParameters(random);
//        _genotype.addPar(tmp2);


//        Parameters tmp3;
//        random=fRand(0,2000);
//        tmp3.addParameters(random);
//        random=fRand(0,2000);
//        tmp3.addParameters(random);
//        _genotype.addPar(tmp3);


//        Parameters tmp4;
//        random=fRand(0,2000);
//        tmp4.addParameters(random);
//        random=fRand(0,2000);
//        tmp4.addParameters(random);
//        _genotype.addPar(tmp4);

//        Parameters tmp5;
//        random=fRand(0,2000);
//        tmp5.addParameters(random);
//        random=fRand(0,2000);
//        tmp5.addParameters(random);
//        _genotype.addPar(tmp5);

//        Parameters tmp6;
//        random=fRand(0,2000);
//        tmp6.addParameters(random);
//        random=fRand(0,2000);
//        tmp6.addParameters(random);
//        _genotype.addPar(tmp6);

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
    //  varType anyVariable;		   // for example ...
    // END   Private data of an eoOneMaxInit object
};

#endif
