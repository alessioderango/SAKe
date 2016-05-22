#ifndef FUNTCIONTYPE_H
#define FUNTCIONTYPE_H


class funtcionType
{
public:
    funtcionType(    double percentageWeight,
    double percentageLinearA,
    double percentageLinearB,
    double percentageGammaA,
    double percentageGammaB,
    int type);

    double getPercentageWeight() const;
    void setPercentageWeight(double value);

    double getPercentageLinearA() const;
    void setPercentageLinearA(double value);

    double getPercentageLinearB() const;
    void setPercentageLinearB(double value);

    double getPercentageGammaA() const;
    void setPercentageGammaA(double value);

    double getPercentageGammaB() const;
    void setPercentageGammaB(double value);

private:
    double percentageWeight;
    double percentageLinearA;
    double percentageLinearB;
    double percentageGammaA;
    double percentageGammaB;
    int type;
};

#endif // FUNTCIONTYPE_H
