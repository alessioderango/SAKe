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
    /* virtual */bool selectionDet(EOT best, EOT competitor)
    {
        double momentoPrimoOrdineGen1 = best.getMomentoDelPrimoOrdineConst();
        double momentoPrimoOrdineGen2 = competitor.getMomentoDelPrimoOrdineConst();

        if(this->roundMy(momentoPrimoOrdineGen1,roundedDigits) > this->roundMy(momentoPrimoOrdineGen2,roundedDigits))
            return true;
        else
            return false;
    }


    SELECTIONID selectionStoch(EOT best, EOT competitor){
        double momentoPrimoOrdineGen1 = best.getMomentoDelPrimoOrdineConst();
        double momentoPrimoOrdineGen2 = competitor.getMomentoDelPrimoOrdineConst();

        if(this->roundMy(momentoPrimoOrdineGen1,roundedDigits) < this->roundMy(momentoPrimoOrdineGen2,roundedDigits)){
            return BESTGEN1;
        }else
            if(this->roundMy(momentoPrimoOrdineGen1,roundedDigits) > this->roundMy(momentoPrimoOrdineGen2,roundedDigits))
            {
                return BESTGEN2;
            }else
                return NOONEBEST;
    }
};


#endif // SELECTIONMOMENTOPRIMOORDINE_H
