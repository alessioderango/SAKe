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
#include "boost/date_time/local_time_adjustor.hpp"
#include "boost/date_time/c_local_time_adjustor.hpp"
#include <ctime>
#include <time.h>
#include "Regression/Genotype.h"
#include <QVector>
using namespace std;
using boost::posix_time::ptime;
using namespace boost::posix_time;
using namespace boost::gregorian;

enum FitnessType { FitnessGMD = 4, FitnessGMDn =0, FitnessEqualWeights =1, FitnessAUCROC =2};


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
    static int loadCSVGenationsFromFile(QString fileurl,QVector<double> &generationsX, QVector<double> &generationsBest, QVector<double> &generationsAvg);


};

#endif // HANDLERCSV_H
