#ifndef SELECTIONSIZE_H
#define SELECTIONSIZE_H

#include "selectionstrategy.h"

template <class EOT>
class SelectionSize: public SelectionStrategy<EOT>
{
public:
    SelectionSize(){
        roundedDigits=3;
    }
private:
    int roundedDigits;
    /* virtual */bool selection(int gen1, int gen2, EOT* &popTmp, eoPop<EOT> &offspring, int counter)
    {
        int sizeGen1 = popTmp[gen1].getSizeConst();
        int sizeGen2 = popTmp[gen2].getSizeConst();
        if(this->roundMy(sizeGen1,4) < this->roundMy(sizeGen2,4)){
//            printf("size Gen 1 %f < size Gen 2 %f\n ",sizeGen1,sizeGen2 );

            EOT a;
            double * r = (double*) malloc(sizeof(double)*popTmp[gen1]. getSize());
            a.setFi(r);
            a.setSize(popTmp[gen1].getSize());
            for (int tmp = 0; tmp < popTmp[gen1].getSize(); tmp++) {
                a.setFiIndex(tmp, popTmp[gen1]. getFiIndex(tmp));
            }
            offspring[counter]=a;
            return true;
        }else
            if(this->roundMy(sizeGen1,4) > this->roundMy(sizeGen2,4)){
//                printf("size Gen 1 %f > size Gen 2 %f\n ",sizeGen1,sizeGen2 );
                EOT a;
                double * r = (double*) malloc(sizeof(double)*popTmp[gen2]. getSize());
                a.setFi(r);
                a.setSize(popTmp[gen2]. getSize());
                for (int tmp = 0; tmp < popTmp[gen2].getSize(); tmp++) {
                    a.setFiIndex(tmp, popTmp[gen2]. getFiIndex(tmp));
                }
                offspring[counter]=a;
                 return true;
            }else
            {
                return false;
            }

    }
    /* virtual */void selectionLast(int gen1, int gen2, EOT* &popTmp, eoPop<EOT> &offspring, int counter)
    {
        int sizeGen1 = popTmp[gen1].getSizeConst();
        int sizeGen2 = popTmp[gen2].getSizeConst();

        EOT a;
        double * r = (double*) malloc(sizeof(double)*popTmp[gen2]. getSize());
        a.setFi(r);
        a.setSize(popTmp[gen1].getSize());
        for (int tmp = 0; tmp < popTmp[gen1].getSize(); tmp++) {
            a.setFiIndex(tmp, popTmp[gen1]. getFiIndex(tmp));
        }
        offspring[counter]=a;


    }

};

#endif // SELECTIONSIZE_H
