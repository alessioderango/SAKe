#ifndef SELECTIONDELTACR_H
#define SELECTIONDELTACR_H

#include "selectionstrategy.h"

template <class EOT>
class SelectionDeltaCr: public SelectionStrategy<EOT>
{
public:
    SelectionFitness(){
        roundedDigits=3;
    }
private:
    int roundedDigits;
    /* virtual */bool selection(int gen1, int gen2, EOT* &popTmp,eoPop<EOT> &offspring, int counter)
    {
        double deltaGen1 =(popTmp[gen1].getYmMinConst().getValue()-popTmp[gen1].getYmMin2Const().getValue())/popTmp[gen1].getYmMinConst().getValue();
        double deltaGen2 =(popTmp[gen2].getYmMinConst().getValue()-popTmp[gen2].getYmMin2Const().getValue())/popTmp[gen2].getYmMinConst().getValue();

        if(this->roundMy(deltaGen1,roundedDigits) > this->roundMy(deltaGen2,roundedDigits)){
//            printf("delta Gen 1 %f > delta Gen 2 %f\n ",deltaGen1,deltaGen2 );
            EOT a;
            double * r = (double*) malloc(sizeof(double)*popTmp[gen1].getSize());
            a.setFi(r);
            a.setSize(popTmp[gen1]. getSize());
            for (int tmp = 0; tmp < popTmp[gen1].getSize(); tmp++) {
                a.setFiIndex(tmp, popTmp[gen1]. getFiIndex(tmp));
            }
            offspring[counter]=a;
            return true;
        }else
            if(this->roundMy(deltaGen1,roundedDigits) < this->roundMy(deltaGen2,roundedDigits)){
//                printf("delta Gen 1 %f < delta Gen 2 %f\n ",deltaGen1,deltaGen2 );

                EOT a;
                double * r = (double*) malloc(sizeof(double)*popTmp[gen2].getSize());
                a.setFi(r);
                a.setSize(popTmp[gen2].getSize());
                for (int tmp = 0; tmp < popTmp[gen2].getSize(); tmp++) {
                    a.setFiIndex(tmp, popTmp[gen2].getFiIndex(tmp));
                }
                offspring[counter]=a;
                return true;
            }else{
                return false;
            }

    }


    /* virtual */void selectionLast(int gen1, int gen2, EOT* &popTmp,eoPop<EOT> &offspring, int counter)
    {
        double deltaGen1 =(popTmp[gen1].getYmMinConst().getValue()-popTmp[gen1].getYmMin2Const().getValue())/popTmp[gen1].getYmMinConst().getValue();
        double deltaGen2 =(popTmp[gen2].getYmMinConst().getValue()-popTmp[gen2].getYmMin2Const().getValue())/popTmp[gen2].getYmMinConst().getValue();


//        printf("delta Gen 1 %f > delta Gen 2 %f\n ",deltaGen1,deltaGen2 );
        EOT a;
        double * r = (double*) malloc(sizeof(double)*popTmp[gen2]. getSize());
        a.setFi(r);
        a.setSize(popTmp[gen1]. getSize());
        for (int tmp = 0; tmp < popTmp[gen1].getSize(); tmp++) {
            a.setFiIndex(tmp, popTmp[gen1]. getFiIndex(tmp));
        }
        offspring[counter]=a;

    }

};

#endif // SELECTIONDELTACR_H
