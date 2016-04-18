#ifndef EOMYSGA
#define EOMYSGA

#include <eoInvalidateOps.h>
#include <eoContinue.h>
#include <eoPop.h>
#include <eoSelectOne.h>
#include <eoSelectPerc.h>
#include <eoEvalFunc.h>
#include <eoAlgo.h>
#include <apply.h>

/** The Simple Genetic Algorithm, following Holland and Goldberg
 *
 * Needs a selector (class eoSelectOne) a crossover (eoQuad, i.e. a
 * 2->2 operator) and a mutation with their respective rates, of
 * course an evaluation function (eoEvalFunc) and a continuator
 * (eoContinue) which gives the stopping criterion. Performs full
 * generational replacement.
 *
 * @ingroup Algorithms
 */
template <class EOT>
class eoMySGA : public eoAlgo<EOT>
{
public :

    // added this second ctor as I didn't like the ordering of the parameters
    // in the one above. Any objection :-) MS
    eoMySGA(
            eoSelectOne<EOT>& _select,
            float _selectRate,
            eoQuadOp<EOT>& _cross, float _crate,
            eoMonOp<EOT>& _mutate, float _mrate,
            eoEvalFunc<EOT>& _eval,int _maxNumberToConsider,
            eoContinue<EOT>& _cont)
        : cont(_cont),
          mutate(_mutate),
          mutationRate(_mrate),
          cross(_cross),
          crossoverRate(_crate),
          select(_select,_selectRate),
          eval(_eval) {
        maxNumberToConsider=_maxNumberToConsider;
    }



    static int  compareEOT (const void * a, const void * b)
    {
        // - perche decrescente
        if( (double)(((EOT*)a)->fitness()) > (double)(((EOT*)b)->fitness()) ){
            return -  1;
        }
        if( (double)(((EOT*)a)->fitness()) < (double)(((EOT*)b)->fitness()) ){
            return 1;
        }
        if( (double)(((EOT*)a)->fitness()) == (double)(((EOT*)b)->fitness()) ){
            return 0;
        }
    }


    void operator()(eoPop<EOT>& _pop)
    {

        eoPop<EOT> offspring;

        do
        {
            select(_pop, offspring);

            unsigned i;



            //for (i=0; i<_pop.size()/2; i++)
            for (i=4; i<_pop.size()/2; i++)
            {
                if ( rng.flip(crossoverRate) )
                {
                    // this crossover generates 2 offspring from two parents
                    if (cross(offspring[2*i], offspring[2*i+1]))
                    {
                        offspring[2*i].invalidate();
                        offspring[2*i+1].invalidate();
                    }
                }
            }

            for (i=8; i < offspring.size(); i++)
            {
                if (rng.flip(mutationRate) )
                {
                    if (mutate(offspring[i]))
                        offspring[i].invalidate();
                }

            }

            eoPop<EOT> popTmp;
            popTmp.resize(_pop.size());
            int counter=0;
            for (int i=0; i<_pop.size(); i++){
                EOT a;
                double * r = (double*) malloc(sizeof(double)*offspring[counter].getSize());
                a.setFi(r);
                a.setSize(offspring[counter]. getSize());
                for (int tmp = 0; tmp < offspring[counter].getSize(); tmp++) {
                    a.setFiIndex(tmp, offspring[counter]. getFiIndex(tmp));
                }
                popTmp[counter]=a;
                counter++;
            }


            _pop.clear();
            _pop.swap(popTmp);
            apply<EOT>(eval, _pop);

        } while (cont(_pop));
    }
private :

    eoContinue<EOT>& cont;
    /// eoInvalidateMonOp invalidates the embedded operator
    eoInvalidateMonOp<EOT> mutate;
    float mutationRate;
    // eoInvalidateQuadOp invalidates the embedded operator
    eoInvalidateQuadOp<EOT> cross;
    float crossoverRate;
    eoSelectPerc<EOT> select;
    eoEvalFunc<EOT>& eval;
    int maxNumberToConsider;
};


#endif // EOMYSGA

