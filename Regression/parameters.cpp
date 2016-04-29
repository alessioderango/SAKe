#include "parameters.h"

Parameters::Parameters()
{

}

std::vector<double> Parameters::getParametersConst() const{
    return parameters;
}
double Parameters::getParameters(int i){
    return parameters[i];
}

void Parameters::setParameters(int i,double value){
    parameters[i]=value;
}

void Parameters::addParameters(double value){
    parameters.push_back(value);
}

