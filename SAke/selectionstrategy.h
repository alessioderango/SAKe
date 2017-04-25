#ifndef SELECTIONSTARTEGY_H
#define SELECTIONSTARTEGY_H
#include <eoPop.h>

enum SELECTIONID { BESTGEN1 = 0 ,BESTGEN2  , NOONEBEST };

template <class EOT>
class SelectionStrategy
{
public:
    SelectionStrategy(){}
    double roundMy(double x, int prec)
    {
        double power = 1.0;
        int i;

        if (prec > 0)
            for (i = 0; i < prec; i++)
                power *= 10.0;
        else if (prec < 0)
            for (i = 0; i < prec; i++)
                power /= 10.0;

        if (x > 0)
            x = floor(x * power + 0.5) / power;
        else if (x < 0)
            x = ceil(x * power - 0.5) / power;

        if (x == -0)
            x = 0;

        return x;
    }
    virtual bool selectionDet(EOT best, EOT competitor) = 0;
    virtual SELECTIONID selectionStoch(EOT best, EOT competitor) = 0;
//    virtual void selectionLast(int a, int b,EOT* &popTmp, eoPop<EOT> &offspring, int counter) = 0;
};

#endif // SELECTIONSTARTEGY_H
