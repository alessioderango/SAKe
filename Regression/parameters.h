#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <iostream>
#include <vector>
using namespace std;

class Parameters
{
public:
    Parameters();
    std::vector<double> getParametersConst() const;
    double getParameters(int i);
    void setParameters(int i, double value);
    void addParameters(double value);


private:
      std::vector<double> parameters;
};

#endif // PARAMETERS_H
