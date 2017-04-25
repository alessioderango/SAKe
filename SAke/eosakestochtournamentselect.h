#ifndef EOSAKESTOCHTOURNAMENTSELECT_H
#define EOSAKESTOCHTOURNAMENTSELECT_H

#include <functional>  //
#include <numeric>     // accumulate

#include <eoFunctor.h>
#include <eoPop.h>
#include <utils/eoLogger.h>
#include <utils/selectors.h>
#include <SAke/selectionstrategy.h>
#include <vector>

template <class EOT>
const EOT& SAKe_stochastic_tournament(const eoPop<EOT>& _pop, unsigned _t_rate, SelectionStrategy<EOT> ** selectionStrategy, eoRng& _gen = rng)
{

    typename eoPop<EOT>::const_iterator i1 = _pop.begin() + _gen.random(_pop.end() - _pop.begin());
    typename eoPop<EOT>::const_iterator i2 = _pop.begin() + _gen.random(_pop.end() - _pop.begin());


    bool return_better = _gen.flip(_t_rate);

    if (*i1 < *i2)
    {
        if (return_better) return *i2;
        // else

        return *i1;
    }
    else
    {
        if (return_better) return *i1;
        // else
    }

    SELECTIONID tmpSelection;
    for (int i = 1; i < 4; i++) {

        tmpSelection = selectionStrategy[i]->selectionStoch(*i1,*i2);

        if(tmpSelection == BESTGEN2){
            if (return_better) return *i2;
            return *i1;
        }else
            if(tmpSelection == BESTGEN1)
                if (return_better) return *i1;

    }

    return *i2;
}


template <class EOT> class eoSAKeStochTournamentSelect: public eoSelectOne<EOT>
{
public:

    ///
    eoSAKeStochTournamentSelect(SelectionStrategy<EOT> ** _selectionStrategy, double _Trate = 1.0 ) : eoSelectOne<EOT>(), Trate(_Trate)
    {
        // consistency checks
        if (Trate < 0.5) {
            std::cerr << "Warning, Tournament rate should be > 0.5\nAdjusted to 0.55\n";
            Trate = 0.55;
        }
        if (Trate > 1) {
            std::cerr << "Warning, Tournament rate should be < 1\nAdjusted to 1\n";
            Trate = 1;
        }

        selectionStrategy = _selectionStrategy;
    }

    eoSAKeStochTournamentSelect(double _Trate = 1.0 ) : eoSelectOne<EOT>(), Trate(_Trate)
    {
        // consistency checks
        if (Trate < 0.5) {
            std::cerr << "Warning, Tournament rate should be > 0.5\nAdjusted to 0.55\n";
            Trate = 0.55;
        }
        if (Trate > 1) {
            std::cerr << "Warning, Tournament rate should be < 1\nAdjusted to 1\n";
            Trate = 1;
        }

    }

    /** Perform the stochastic tournament  */
    virtual const EOT& operator()(const eoPop<EOT>& pop)
    {
        return SAKe_stochastic_tournament(pop, Trate, selectionStrategy);
    }

private:
    double Trate;
    SelectionStrategy<EOT> ** selectionStrategy;

};


#endif // EOSAKESTOCHTOURNAMENTSELECT_H
