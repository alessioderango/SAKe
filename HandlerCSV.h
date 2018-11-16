#ifndef HANDLERCSV_H
#define HANDLERCSV_H

#include "Rain.h"
#include "Activation.h"
#include <QObject>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <time.h>
#include "Regression/Genotype.h"
using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

enum FitnessType { FitnessGMD = 0,FitnessGMDn , FitnessEqualWeights, FitnessAUCROC };


class HandlerCSV
{
public:
    HandlerCSV();
    static void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
    static int loadCSVRain(QString fileurl, Rain * &rain, int &size, int &row, QString &_e);
    static int loadCSVActivation(QString fileurl, Activation *&activation, int &activation_size,int &row, QString&  _e);
    static int loadCSVKernel(QString fileurl, double *& Fi, int & size, double & zCr);
    static int loadCSVKernel(QString fileurl, std::vector<double> &Fi, int & size, double & zCr);
    static int loadCSVPopFromFile(QString fileurl,vector<vector<double>> &popFromFile, int& numberGen);
    static int loadCSVPopFromFileRegression(QString fileurl,
                                       std::vector<Genotype> &g,
                                       int& numberGen);


};

#endif // HANDLERCSV_H
