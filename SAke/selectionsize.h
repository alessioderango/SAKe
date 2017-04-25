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
    /* virtual */bool selectionDet(EOT best, EOT competitor)
    {
        int sizeGen1 = best.getSizeConst();
        int sizeGen2 = competitor.getSizeConst();

        if(this->roundMy(sizeGen1,4) > this->roundMy(sizeGen2,4)){
            return true;
        }else
        {
            return false;
        }



    }


    SELECTIONID selectionStoch(EOT best, EOT competitor){
        int sizeGen1 = best.getSizeConst();
        int sizeGen2 = competitor.getSizeConst();

        if(this->roundMy(sizeGen1,4) < this->roundMy(sizeGen2,4)){
            return BESTGEN1;
        }else
        if(this->roundMy(sizeGen1,4) > this->roundMy(sizeGen2,4)){
            return BESTGEN2;
        }else
            return NOONEBEST;
    }

};

#endif // SELECTIONSIZE_H
