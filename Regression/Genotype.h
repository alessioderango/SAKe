#ifndef GENOTYPE_H
#define GENOTYPE_H

#include "parameters.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>

class Genotype
{
public:
    Genotype(int dimension);

    setWeight(string x);
    setParameters(string x);
    setPercantageW(string x);
    setFunctionType(string x);
    setPercantageLinearA(string x);
    setPercantageLinearB(string x);
    setPercantageGammaA(string x);
    setPercantageGammaB(string x);
    setTranslation(string x);


    double *getWeight() ;

    Parameters *getParameters() ;

    int *getFunctionType() ;

    double *getPercantageW() ;

    double *getPercantageLinearA() ;

    double *getPercantageLinearB() ;

    double *getPercantageGammaA() ;

    double *getPercantageGammaB() ;

    double *getTranslation() ;

private:
    double * weight;
    Parameters *parameters;
    int * functionType;
    double * percantageW;
    double * percantageLinearA;
    double * percantageLinearB;
    double * percantageGammaA;
    double * percantageGammaB;
    double* translation;
    int numFunctions;
};

#endif // GENOTYPE_H
