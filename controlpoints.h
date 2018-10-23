#ifndef CONTROLPOINTS_H
#define CONTROLPOINTS_H

#include <vector>
#include <iostream>
#include <QVector>
using namespace std;

class ControlPoints
{
public:
    ControlPoints();
    void calculateControlPoints(double *kernel, int size_kernel);
    std::vector<double> getX() const;
    void setX(const std::vector<double> &value);

    std::vector<double> getY() const;
    void setY(const std::vector<double> &value);

    void getSubdividePointsFromKernel(double *kernel, int size_kernel, int n, std::vector<double> &x, std::vector<double> &y);
    void getSubdividePointsFromControlPoints(std::vector<double> x, std::vector<double> y, int n, std::vector<double> &xOutput, std::vector<double> &yOutput);
private:
    std::vector< double> x;
    std::vector< double> y;

};

#endif // CONTROLPOINTS_H
