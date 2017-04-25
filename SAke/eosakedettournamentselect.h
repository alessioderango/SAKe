#ifndef EOSAKEDETTOURNAMENTSELECT_H
#define EOSAKEDETTOURNAMENTSELECT_H


#include <functional>  //
#include <numeric>     // accumulate

#include <eoFunctor.h>
#include <eoPop.h>
#include <utils/eoLogger.h>
#include <utils/selectors.h>
#include <SAke/selectionstrategy.h>
#include <vector>

/** eoSAKeDetTournamentSelect: a selection method that selects ONE individual by
 deterministic tournament


 @ingroup Selectors
 */

template <class EOT>
const EOT& SAKe_deterministic_tournament(const eoPop<EOT>& _pop, unsigned _t_size, SelectionStrategy<EOT> ** selectionStrategy, eoRng& _gen = rng)
{

    typename eoPop<EOT>::const_iterator best = _pop.begin() + _gen.random(_pop.end() - _pop.begin());

    for (unsigned i = 0; i < _t_size - 1; ++i)
    {
        typename eoPop<EOT>::const_iterator competitor = _pop.begin() + _gen.random(_pop.end() - _pop.begin());

        if (*best < *competitor)
        {
            best = competitor;
        }
        else
        {
            bool tmpSelection=0;

             for (int i = 1; i < 4; i++) {
                tmpSelection = selectionStrategy[i]->selectionDet(*best,*competitor);
                if(tmpSelection){
                    best = competitor;
                    break;
                }
            }
        }


    }

    return *best;
}



template <class EOT>
class eoSAKeDetTournamentSelect: public eoSelectOne<EOT>
{
public:
    /* (Default) Constructor -
     @param _tSize tournament size
  */
    eoSAKeDetTournamentSelect(SelectionStrategy<EOT> ** _selectionStrategy, unsigned _tSize = 2 ):eoSelectOne<EOT>(), tSize(_tSize) {
        // consistency check
        if (tSize < 2) {
            eo::log << eo::warnings << "Tournament size should be >= 2, adjusted to 2" << std::endl;
            tSize = 2;
        }
        selectionStrategy = _selectionStrategy;
    }
    eoSAKeDetTournamentSelect(unsigned _tSize = 2 ):eoSelectOne<EOT>(), tSize(_tSize) {
        // consistency check
        if (tSize < 2) {
            eo::log << eo::warnings << "Tournament size should be >= 2, adjusted to 2" << std::endl;
            tSize = 2;
        }
    }

    /* Perform deterministic tournament calling the appropriate fn
     see selectors.h
  */
    virtual const EOT& operator()(const eoPop<EOT>& _pop)
    {
        return SAKe_deterministic_tournament(_pop, tSize, selectionStrategy);
    }

private:
    unsigned tSize;
    SelectionStrategy<EOT> ** selectionStrategy;
};

//-----------------------------------------------------------------------------



#endif // EOSAKEDETTOURNAMENTSELECT_H
