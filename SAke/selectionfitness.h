#ifndef SELECTIONFITNESS_H
#define SELECTIONFITNESS_H

#include "selectionstrategy.h"

template <class EOT>
class SelectionFitness: public SelectionStrategy<EOT>
{
public:
    SelectionFitness(){
        roundedDigits=4;
    }
private:

    int roundedDigits;
    /* virtual */bool selection(int gen1, int gen2, EOT* &popTmp, eoPop<EOT> &offspring, int counter)
    {
        double tmpFitnessGen1 = popTmp[gen1].fitness();
        double tmpFitnessGen2 = popTmp[gen2].fitness();
        if(this->roundMy(tmpFitnessGen1,roundedDigits) > this->roundMy(tmpFitnessGen2,roundedDigits) ){
//            printf("fitness Gen 1 %f > fitness Gen 2 %f\n ",tmpFitnessGen1,tmpFitnessGen2);
            EOT a;
            double * r = (double*) malloc(sizeof(double)*popTmp[gen1]. getSize());
            a.setFi(r);
            a.setSize(popTmp[gen1]. getSize());
            for (int tmp = 0; tmp < popTmp[gen1].getSize(); tmp++) {
                a.setFiIndex(tmp, popTmp[gen1]. getFiIndex(tmp));
            }
            offspring[counter]=a;
            return true;
        }
        else
            if(this->roundMy(tmpFitnessGen1,roundedDigits) < this->roundMy(tmpFitnessGen2,roundedDigits) ){
//                printf("fitness Gen 1 %f < fitness Gen 2 %f\n ",tmpFitnessGen1,tmpFitnessGen2);
                EOT a;
                double * r = (double*) malloc(sizeof(double)*popTmp[gen2]. getSize());
                a.setFi(r);
                a.setSize(popTmp[gen2]. getSize());
                for (int tmp = 0; tmp < popTmp[gen2].getSize(); tmp++) {
                    a. setFiIndex(tmp, popTmp[gen2]. getFiIndex(tmp));
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
        double tmpFitnessGen1 = popTmp[gen1].fitness();
        double tmpFitnessGen2 = popTmp[gen2].fitness();

//        printf("fitness Gen 1 %f > fitness Gen 2 %f\n ",tmpFitnessGen1,tmpFitnessGen2);
        EOT a;
        double * r = (double*) malloc(sizeof(double)*popTmp[gen1]. getSize());
        a.setFi(r);
        a.setSize(popTmp[gen1]. getSize());
        for (int tmp = 0; tmp < popTmp[gen1].getSize(); tmp++) {
            a.setFiIndex(tmp, popTmp[gen1]. getFiIndex(tmp));
        }
        offspring[counter]=a;


    }


};


#endif // SELECTIONFITNESS_H
