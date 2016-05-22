#include "funtciontype.h"

funtcionType::funtcionType(    double _percentageWeight,
                               double _percentageLinearA,
                               double _percentageLinearB,
                               double _percentageGammaA,
                               double _percentageGammaB,
                               int _type)
{
//     percentageWeight=_percentageWeight;
//     percentageLinearA=_percentageLinearA;
//     percentageLinearB,
//     percentageGammaA,
//     percentageGammaB,
//     type=_type;


}

double funtcionType::getPercentageWeight() const
{
    return percentageWeight;
}

void funtcionType::setPercentageWeight(double value)
{
    percentageWeight = value;
}

double funtcionType::getPercentageLinearA() const
{
    return percentageLinearA;
}

void funtcionType::setPercentageLinearA(double value)
{
    percentageLinearA = value;
}

double funtcionType::getPercentageLinearB() const
{
    return percentageLinearB;
}

void funtcionType::setPercentageLinearB(double value)
{
    percentageLinearB = value;
}

double funtcionType::getPercentageGammaA() const
{
    return percentageGammaA;
}

void funtcionType::setPercentageGammaA(double value)
{
    percentageGammaA = value;
}

double funtcionType::getPercentageGammaB() const
{
    return percentageGammaB;
}

void funtcionType::setPercentageGammaB(double value)
{
    percentageGammaB = value;
}
