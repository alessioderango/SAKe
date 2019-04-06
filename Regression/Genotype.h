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

    void setWeight(string x);
    void setParameters(string x);
    void setPercantageW(string x);
    void setFunctionType(string x);
    void setPercantageLinearA(string x);
    void setPercantageLinearB(string x);
    void setPercantageGammaA(string x);
    void setPercantageGammaB(string x);
    void setTranslation(string x);


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
