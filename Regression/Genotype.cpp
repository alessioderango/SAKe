#include "Genotype.h"

Genotype::Genotype(int dimension)
{
    weight = new double[dimension];
    parameters = new Parameters[dimension];
    functionType = new int[dimension];
    percantageW= new double[dimension];
    percantageLinearA= new double[dimension];
    percantageLinearB= new double[dimension];
    percantageGammaA= new double[dimension];
    percantageGammaB= new double[dimension];
    translation= new double[dimension];
    numFunctions = dimension;

}

std::vector<std::string> &splitGen(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> splitGen(const std::string &s, char delim) {
    std::vector<std::string> elems;
    splitGen(s, delim, elems);
    return elems;
}


void Genotype::setWeight(string x)
{
    std::vector<string> x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < x1.size(); i++) {
        weight[i] = std::stod(x1[i]);
    }
}

void Genotype::setParameters(string x)
{
    std::vector<string>  x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < numFunctions; i++) {
        Parameters tmp;
        int partmp = i*3;

        tmp.addParameters(std::stod(x1[partmp]));
        tmp.addParameters(std::stod(x1[partmp+1]));
        if( std::stod(x1[partmp+1]) < 0){

            std::cout << "negativo letturaaaaaa " << std::stod(x1[partmp+1]) <<std::endl;
        }
        tmp.addParameters(std::stod(x1[partmp+2]));

        parameters[i] = tmp;
    }

}

void Genotype::setPercantageW(string x)
{
    std::vector<string> x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < x1.size(); i++) {
        percantageW[i] = std::stod(x1[i]);
    }
}

void Genotype::setFunctionType(string x)
{
   std::vector<string> x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < x1.size(); i++) {
        functionType[i] = std::stoi(x1[i]);
    }
}

void Genotype::setPercantageLinearA(string x)
{
    std::vector<string> x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < x1.size(); i++) {
        percantageLinearA[i] = std::stod(x1[i]);
    }
}

void Genotype::setPercantageLinearB(string x)
{
    std::vector<string> x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < x1.size(); i++) {
        percantageLinearB[i] = std::stod(x1[i]);
    }
}

void Genotype::setPercantageGammaA(string x)
{
    std::vector<string> x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < x1.size(); i++) {
        percantageGammaA[i] = std::stod(x1[i]);
    }
}

void Genotype::setPercantageGammaB(string x)
{
    std::vector<string> x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < x1.size(); i++) {
        percantageGammaB[i] = std::stod(x1[i]);
    }
}

void Genotype::setTranslation(string x)
{
    std::vector<string> x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < x1.size(); i++) {
        translation[i] = std::stod(x1[i]);
    }
}

double *Genotype::getWeight()
{
    return weight;
}

Parameters *Genotype::getParameters()
{
    return parameters;
}

int *Genotype::getFunctionType()
{
    return functionType;
}

double *Genotype::getPercantageW()
{
    return percantageW;
}

double *Genotype::getPercantageLinearA()
{
    return percantageLinearA;
}

double *Genotype::getPercantageLinearB()
{
    return percantageLinearB;
}

double *Genotype::getPercantageGammaA()
{
    return percantageGammaA;
}

double *Genotype::getPercantageGammaB()
{
    return percantageGammaB;
}

double *Genotype::getTranslation()
{
    return translation;
}

QVector<double> Genotype::getYCombinata() const
{
    return yCombinata;
}

void Genotype::setYCombinata(const QVector<double> &value)
{
    yCombinata = value;
}

void Genotype::setYCombinataFromString(string x)
{
    std::vector<string> x1 = splitGen(x, ',');
    for (unsigned int i = 0; i < x1.size(); i++) {
        yCombinata.push_back(std::stod(x1[i]));
    }
}
