#include "HandlerCSV.h"

HandlerCSV::HandlerCSV()
{


}
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void HandlerCSV::ReplaceStringInPlace(std::string& subject, const std::string& search,
                                      const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

int HandlerCSV::loadCSVRain(QString fileurl,Rain * &rain,int &size,int &row,QString&  _e,
                            string &rainMinDate,
                            string &rainMaxDate)
{


    //    qDebug() << "Entrato in loadCSV";
    //fileurl.remove(0,8);
    //       qDebug() << fileurl;
    size=0;
    //       qDebug() << fileurl;

    std::ifstream in(fileurl.toStdString());

    std::string line;
    std::vector< std::vector<std::string>> rows;
    while (std::getline(in, line)){
        size++;
        std::vector<std::string> x;
        x = split(line, ';');
        rows.push_back(x);
        // cout << line << endl;
    }
    rain = new Rain[size];
    size=0;

    string previousDate;
    int deltaT = 0;
    rainMinDate = rows[0].at(0);
    rainMaxDate = rows[rows.size()-1].at(0);
    for(unsigned int i =0; i < rows.size();i++){
        try{
            double mm = atof(rows[i].at(1).c_str());
            string actualDate =  rows[i].at(0);

            if(mm < 0){
                std::cout << "rain row = " << i << std::endl;
                QString error= "In rains, at row "+ QString::number(i) + " mm can not be negative \n";
                _e.append(error);
                row = i;
                return 0;
            }
            QString actualDateQString = QString::fromStdString(actualDate);
            if(actualDateQString.contains(QRegExp("^\d{4}[\-\/\s]?((((0[13578])|(1[02]))[\-\/\s]?(([0-2][0-9])|(3[01])))|(((0[469])|(11))[\-\/\s]?(([0-2][0-9])|(30)))|(02[\-\/\s]?[0-2][0-9])) (([0-1][0-9])|([2][0-3])):([0-5][0-9]):([0-5][0-9]).([0-5][0-9][0-9])")))
            {
                std::cout << "rain row = " << i << std::endl;
                QString error= "In rains, at row "+ QString::number(i) + " date  is not in the format yyyy-mm-dd hh:mm:ss.sss \n";
                _e.append(error);
                row = i;
                return 0;
            }

            if(i > 0){
                ptime previousTime = time_from_string(previousDate);
                ptime actualTime = time_from_string(actualDate);
                int a = Jan;
                //ptime firstTime = ptime(date(1970, Jan, 1));
                boost::posix_time::time_duration diff1 =(previousTime-ptime(date(1900, Jan, 1)));
                boost::posix_time::time_duration diff2 =(actualTime-ptime(date(1900, Jan, 1)));
                std::time_t begin = diff1.total_seconds();
                std::time_t end = diff2.total_seconds();

                int difference = std::difftime(end, begin);

                if(difference <= 0){
                    std::cout << " rain row = " << i<< std::endl;
                    QString error= "In rains, at row "+ QString::number(i) + " date is incorrect \n";
                    _e.append(error);
                    row = i;

                    return 0;
                }

                if(i == 1)
                {
                    deltaT = difference;
                    //cout << "deltaT = " << deltaT << endl;
                }

                if(i > 1){
                    if(difference > deltaT){
                        std::cout << "rain row = " << i << std::endl;
                        QString error= "In rains, at row "+ QString::number(i) + " deltaT is wrong.  \n";
                        _e.append(error);
                        row = i;
                        return 0;
                    }
                }


            }


            ptime rain0;


            rain0 = time_from_string(actualDate);
            rain[size]= Rain(to_tm(rain0),mm);
            size++;
            previousDate = actualDate;

        }catch(std::exception& e){
            std::cout << "rain row = " << i << std::endl;
            QString err = "In rains, " + QString::fromStdString(e.what());
            _e.append(err);
            row = i;

            return 0;
        }

    }

    return 1;

}


int HandlerCSV::loadCSVActivation(QString fileurl,
                                  Activation *&activation,
                                  int &activation_size,
                                  int &row,
                                  QString& _e,
                                  string rainMinDate,
                                  string rainMaxDate)
{

    //    qDebug() << "Entrato in loadCSV";
    //fileurl.remove(0,8);
    //       qDebug() << fileurl;
    activation_size=0;
    //       qDebug() << fileurl;

    std::ifstream in(fileurl.toStdString());

    std::string line;
    std::vector< std::vector<std::string>> rows;

    //    clock_t start=clock();
    while (std::getline(in, line)){
        activation_size++;
        std::vector<std::string> x;
        x = split(line, ';');
        rows.push_back(x);
        //        cout << line << endl;
    }
    //    clock_t stop=clock();
    //           qDebug() <<double(stop-start)/CLOCKS_PER_SEC << " seconds\n";
    //           qDebug() << activation_size;
    activation = new Activation[activation_size];
    activation_size=0;

    ptime rainMinDateTime = time_from_string(rainMinDate);
    ptime rainMaxDateTime = time_from_string(rainMaxDate);
    int a = Jan;
    //ptime firstTime = ptime(date(1970, Jan, 1));
    boost::posix_time::time_duration diff1 =(rainMinDateTime-ptime(date(1900, Jan, 1)));
    boost::posix_time::time_duration diff2 =(rainMaxDateTime-ptime(date(1900, Jan, 1)));
    std::time_t rainMinDateTimet = diff1.total_seconds();
    std::time_t rainMaxDateTimet = diff2.total_seconds();

    for(unsigned int i =0; i < rows.size();i++){
        try{
            string dateStart =  rows[i].at(0);
            string dateEnd =  rows[i].at(1);

            ptime activationStart = time_from_string(dateStart);
            ptime activationEnd = time_from_string(dateEnd);
            int a = Jan;
            //ptime firstTime = ptime(date(1970, Jan, 1));
            boost::posix_time::time_duration diff1 =(activationStart-ptime(date(1900, Jan, 1)));
            boost::posix_time::time_duration diff2 =(activationEnd-ptime(date(1900, Jan, 1)));
            std::time_t begin = diff1.total_seconds();
            std::time_t end = diff2.total_seconds();

            int difference = std::difftime(end, begin);

            if(difference < 0){
                std::cout << " activations row = " << i<< std::endl;
                QString error= "In activations, at row "+ QString::number(i) + " please, check the range. \n";
                _e.append(error);
                row = i;

                return 0;
            }

            QString stringfinal = " please, check date (out of rain range). \n";

            difference = std::difftime(begin , rainMinDateTimet);
            if(difference < 0){
                QString error= "In activations, at row "+ QString::number(i) + stringfinal;
                _e.append(error);
                row = i;

                return 0;
            }
            difference = std::difftime(end, rainMinDateTimet);
            if(difference < 0){
                QString error= "In activations, at row "+ QString::number(i) + stringfinal;
                _e.append(error);
                row = i;

                return 0;
            }
            difference = std::difftime(rainMaxDateTimet, begin);
            if(difference < 0){
                QString error= "In activations, at row "+ QString::number(i) + stringfinal;
                _e.append(error);
                row = i;

                return 0;
            }
            difference = std::difftime(rainMaxDateTimet, end);
            if(difference < 0){
                QString error= "In activations, at row "+ QString::number(i) + stringfinal;
                _e.append(error);
                row = i;

                return 0;
            }

            cout << " dateStart " << dateStart << " dateEnd " << dateEnd << endl;

            activation[activation_size]= Activation(to_tm(activationStart),to_tm(activationEnd));
            activation_size++;

        }catch(std::exception& e){
            //std::cout << "  Exception: " <<  e.what() << std::endl;
            QString err = "In activations, " + QString::fromStdString(e.what());
            _e.append(err);
            row = i;

            return 0;
        }
    }

    return 1;

}

int HandlerCSV::loadCSVKernel(QString fileurl, std::vector<double> &Fi, int & size, double & zCr){

    std::ifstream in(fileurl.toStdString());

    std::string line;

    std::getline(in, line);
    std::vector<string> x;
    x = split(line, ';');
    zCr = std::stod(x[2]);
    //cout << line << endl;
    x.erase(x.begin(),x.begin()+5);

    Fi.resize(x.size());
    size=x.size();

    for(unsigned int i =0; i < x.size();i++){
        double tmp = std::stod(x[i]);
        cout << " tmp " << tmp <<  endl;
        Fi[i]= tmp;

    }

    //    for (int i = 0; i < x.size(); ++i) {
    //        cout << Fi[i] <<  endl;
    //    }
    //    cout << "zCr = " << zCr << endl;
    //    cout << "size = " << size << endl;
    //    cout << "x.size() = " << x.size() << endl;

    return 0;
}

int HandlerCSV::loadCSVKernel(QString fileurl, double *& Fi, int & size, double & zCr){
    fileurl.remove(0,8);
    std::ifstream in(fileurl.toStdString());

    std::string line;

    std::getline(in, line);
    std::vector<string> x;
    x = split(line, ';');
    zCr = std::stod(x[3]);
    x.erase(x.begin(),x.begin()+6);
    //    cout << line << endl;

    //           qDebug() <<double(stop-start)/CLOCKS_PER_SEC << " seconds\n";
    //           qDebug() << activation_size;
    Fi = new double[x.size()];
    size=x.size();

    for(unsigned int i =0; i < x.size();i++){
        double tmp = std::stod(x[i]);
        //cout << " tmp " << tmp <<  endl;
        try{
            Fi[i]= tmp;
        }catch(std::exception& e){
            std::cout << "  Exception: " <<  e.what() << std::endl;
            return 0;
        }
    }

    //    for (int i = 0; i < x.size(); ++i) {
    //        cout << Fi[i] <<  endl;
    //    }
    //    cout << "zCr = " << zCr << endl;
    //    cout << "size = " << size << endl;
    //    cout << "x.size() = " << x.size() << endl;

    return 0;
}

int HandlerCSV::loadCSVPopFromFile(QString fileurl,vector<vector<double>> &popFromFile,int& numberGen){
    std::ifstream in(fileurl.toStdString());
    std::string line;
    std::getline(in, line);// jump header line
    while (std::getline(in, line)){
        std::vector<string> x;
        x = split(line, ';');
        numberGen = std::stod(x[0]);
        x.erase(x.begin(),x.begin()+6);
        std::vector<double> tmp;
        for (unsigned int i = 0; i < x.size(); i++) {
            tmp.push_back(std::stod(x[i]));
        }
        popFromFile.push_back(tmp);
        cout << line << endl;
    }
    //    cout << popFromFile.size()<< endl;
    //    for(int i=0;i <popFromFile.size();i++){
    //        cout << popFromFile[i].size() << endl;
    //    }
    //    cout << numberGen << endl;
    return 0;
}

int HandlerCSV::loadCSVGenationsFromFile(QString fileurl, QVector<double> &generationsX, QVector<double> &generationsBest, QVector<double> &generationsAvg){
    std::ifstream in(fileurl.toStdString());
    std::string line;

    if (in.is_open()) {
        std::getline(in, line);
        while (std::getline(in, line)){
            std::vector<string> x;
            x = split(line, ';');
            //numberGen = std::stod(x[0]);
            generationsX.push_back(std::stod(x[0]));
            generationsBest.push_back(std::stod(x[1]));
            generationsAvg.push_back(std::stod(x[2]));
            //        cout << line << endl;
        }
    }else
        return 0;

    return 1;
}

int HandlerCSV::loadCSVPopFromFileRegression(QString fileurl,
                                             std::vector<Genotype> &g,
                                             int& numberGen){
    std::ifstream in(fileurl.toStdString());
    std::string line;

    cout << "leggo popolazione regressione" << endl;
    cout << fileurl.toStdString() << endl;

    while (std::getline(in, line)){
        std::vector<string> x;
        x = split(line, ';');
        Genotype tmp(numberGen);

        tmp.setWeight(x[0]);
        tmp.setParameters(x[1]);
        tmp.setFunctionType(x[2]);
        tmp.setPercantageW(x[3]);
        tmp.setPercantageLinearA(x[4]);
        tmp.setPercantageLinearB(x[5]);
        tmp.setPercantageGammaA(x[6]);
        tmp.setPercantageGammaB(x[7]);
        tmp.setTranslation(x[8]);

        g.push_back(tmp);

    }

    return 0;
}


