#ifndef HANDLERCSV_H
#define HANDLERCSV_H

#include "SAke/Rain.h"
#include "SAke/Activation.h"
#include <QObject>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <time.h>
#include <QQmlEngine>
#include <QQmlComponent>
using namespace std;
using namespace boost::posix_time;

class HandlerCSV
{
public:
    HandlerCSV();
    static void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
    static int loadCSVRain(QString fileurl,Rain * &rain,int &size,QObject * errorHandler);
    static int loadCSVActivation(QString fileurl,Activation *&activation,int &activation_size,QObject * errorHandler);
    static int loadCSVKernel(QString fileurl,double *& Fi,int & size, double & zCr,QObject * errorHandler);
    static int loadCSVKernel(QString fileurl,double *& Fi,int & size, double & zCr);
    static int loadCSVPopFromFile(QString fileurl,vector<vector<double>> &popFromFile, int& numberGen);


};

#endif // HANDLERCSV_H
