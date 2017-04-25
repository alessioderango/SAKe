#ifndef SELECTIONDELTACR_H
#define SELECTIONDELTACR_H

#include "selectionstrategy.h"

template <class EOT>
class SelectionDeltaCr: public SelectionStrategy<EOT>
{
public:
    SelectionDeltaCr(){
        roundedDigits=3;
    }
private:
    int roundedDigits;
    /* virtual */bool selectionDet(EOT best, EOT competitor)
    {
        double deltaGen1 =(best.getYmMinConst().getValue()-best.getYmMin2Const().getValue())/best.getYmMinConst().getValue();
        double deltaGen2 =(competitor.getYmMinConst().getValue()-competitor.getYmMin2Const().getValue())/competitor.getYmMinConst().getValue();


        if(this->roundMy(deltaGen1,roundedDigits) < this->roundMy(deltaGen2,roundedDigits)){
            return true;
        }else{
            return false;
        }



    }


    SELECTIONID selectionStoch(EOT best, EOT competitor){
        double deltaGen1 =(best.getYmMinConst().getValue()-best.getYmMin2Const().getValue())/best.getYmMinConst().getValue();
        double deltaGen2 =(competitor.getYmMinConst().getValue()-competitor.getYmMin2Const().getValue())/competitor.getYmMinConst().getValue();


        if(this->roundMy(deltaGen1,roundedDigits) < this->roundMy(deltaGen2,roundedDigits)){
            return BESTGEN1;
        }else
        if(this->roundMy(deltaGen1,roundedDigits) > this->roundMy(deltaGen2,roundedDigits)){
            return BESTGEN2;
        }else
            return NOONEBEST;
    }


};

#endif // SELECTIONDELTACR_H
