#ifndef SELECTIONMOMENTOPRIMOORDINE_H
#define SELECTIONMOMENTOPRIMOORDINE_H

#include "selectionstrategy.h"

template <class EOT>
class SelectionMomentoDelPrimoOrdine: public SelectionStrategy<EOT>
{
public:
    SelectionMomentoDelPrimoOrdine(){
        roundedDigits=2;
    }
private:
    int roundedDigits;
    /* virtual */bool selection(int gen1, int gen2, EOT* &popTmp,eoPop<EOT> &offspring, int counter)
    {
        double momentoPrimoOrdineGen1 = popTmp[gen1].getMomentoDelPrimoOrdineConst();
        double momentoPrimoOrdineGen2 = popTmp[gen2].getMomentoDelPrimoOrdineConst();

        if(this->roundMy(momentoPrimoOrdineGen1,roundedDigits) > this->roundMy(momentoPrimoOrdineGen2,roundedDigits)){
            printf("momentoPrimoOrdine Gen 1 %f > momentoPrimoOrdine Gen 2 %f\n ",momentoPrimoOrdineGen1,momentoPrimoOrdineGen2 );
            EOT a;
            double * r = (double*) malloc(sizeof(double)*popTmp[gen1]. getSize());
            a.setFi(r);
            a.setSize(popTmp[gen1]. getSize());
            for (int tmp = 0; tmp < popTmp[gen1].getSize(); tmp++) {
                a.setFiIndex(tmp, popTmp[gen1]. getFiIndex(tmp));
            }
            offspring[counter]=a;
            return true;
        }else
            if(this->roundMy(momentoPrimoOrdineGen1,roundedDigits) < this->roundMy(momentoPrimoOrdineGen2,roundedDigits)){
                printf("momentoPrimoOrdine Gen 1 %f < momentoPrimoOrdine Gen 2 %f\n ",momentoPrimoOrdineGen1,momentoPrimoOrdineGen2 );
                EOT a;
                double * r = (double*) malloc(sizeof(double)*popTmp[gen2]. getSize());
                a.setFi(r);
                a.setSize(popTmp[gen2]. getSize());
                for (int tmp = 0; tmp < popTmp[gen2].getSize(); tmp++) {
                    a.setFiIndex(tmp, popTmp[gen2]. getFiIndex(tmp));
                }
                offspring[counter]=a;
                return true;
            }else{
                return false;
            }

    }

    /* virtual */void selectionLast(int gen1, int gen2, EOT* &popTmp,eoPop<EOT> &offspring, int counter)
    {
        double momentoPrimoOrdineGen1 = popTmp[gen1].getMomentoDelPrimoOrdineConst();
        double momentoPrimoOrdineGen2 = popTmp[gen2].getMomentoDelPrimoOrdineConst();

//        printf("momentoPrimoOrdine Gen 1 %f > momentoPrimoOrdine Gen 2 %f\n ",momentoPrimoOrdineGen1,momentoPrimoOrdineGen2 );

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


#endif // SELECTIONMOMENTOPRIMOORDINE_H
