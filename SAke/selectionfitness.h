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
    /* virtual */bool selectionDet(EOT gen1, EOT gen2)
    {
        double tmpFitnessGen1 = gen1.fitness();
        double tmpFitnessGen2 = gen2.fitness();

            if(this->roundMy(tmpFitnessGen1,roundedDigits) < this->roundMy(tmpFitnessGen2,roundedDigits) ){
                return true;
            }else
            {
                return false;
            }

    }

    SELECTIONID selectionStoch(EOT gen1, EOT gen2){
        double tmpFitnessGen1 = gen1.fitness();
        double tmpFitnessGen2 = gen2.fitness();

        if(this->roundMy(tmpFitnessGen1,roundedDigits) < this->roundMy(tmpFitnessGen2,roundedDigits) ){
            return BESTGEN1;
        }else
            if(this->roundMy(tmpFitnessGen1,roundedDigits) > this->roundMy(tmpFitnessGen2,roundedDigits) )
            {
                return BESTGEN2;
            }else
                return NOONEBEST;
    }



};


#endif // SELECTIONFITNESS_H
