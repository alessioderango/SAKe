#ifndef EOSGASTEADYSTATE
#define EOSGASTEADYSTATE

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
class eoSGASteadyState : public eoAlgo<EOT>
{
public :

  // added this second ctor as I didn't like the ordering of the parameters
  // in the one above. Any objection :-) MS
  eoSGASteadyState(
        eoSelectOne<EOT>& _select,
        float _selectRate,
        eoQuadOp<EOT>& _cross, float _crate,
        eoMonOp<EOT>& _mutate, float _mrate,
        eoEvalFunc<EOT>& _eval,
        eoContinue<EOT>& _cont,
        int _numberElitist)
    : cont(_cont),
          mutate(_mutate),
          mutationRate(_mrate),
          cross(_cross),
          crossoverRate(_crate),
          select(_select),
          eval(_eval) {
      numberElitist =_numberElitist;
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
    do
      {

        eoPop<EOT> offspring;
        eoPop<EOT> matingPool;
        offspring.resize(_pop.size());
        //matingPool.resize(_pop.size());

        select(_pop, matingPool);

         _pop.sort();


        //SELECTION

        for (int i=0; i < numberElitist; i++){

            typename eoPop<EOT>::iterator itPoorGuy = offspring.begin() + i;
                EOT a;
                a.setWFromNew(_pop[i].getW());
                a.setParFromNew(_pop[i].getPar());
                a.setFunctionTypeFromNew(_pop[i].getFunctionType());
                a.setYcombinataFromNew(_pop[i].getYCombinata());
                a.setPercentageVariationWeight(_pop[i].getPercentageVariationWeight());
                a.setPercentageVariationLinearA(_pop[i].getPercentageVariationLinearA());
                a.setPercentageVariationLinearB(_pop[i].getPercentageVariationLinearB());
                a.setPercentageVariationGammaA(_pop[i].getPercentageVariationGammaA());
                a.setPercentageVariationGammaB(_pop[i].getPercentageVariationGammaB());
                a.setTranslation(_pop[i].getTranslation());

                (*itPoorGuy) = a;

        }
        // END SELECTION


        unsigned i;
        for (i=0; i<matingPool.size()/2; i++)
          {
            if ( rng.flip(crossoverRate) )
            {
                    // this crossover generates 2 offspring from two parents
                    if (cross(matingPool[2*i], matingPool[2*i+1]))
                       {
                             matingPool[2*i].invalidate();
                             matingPool[2*i+1].invalidate();
                       }
            }
          }

        for (i=0; i < matingPool.size(); i++)
          {
            if (rng.flip(mutationRate) )
            {
                     if (mutate(matingPool[i]))
                         matingPool[i].invalidate();
            }

          }

        for (unsigned int i=numberElitist; i< matingPool.size(); i++){
             typename eoPop<EOT>::iterator itPoorGuy = offspring.begin() + i;
            EOT a;
            a.setWFromNew(matingPool[i].getW());
            a.setParFromNew(matingPool[i].getPar());
            a.setFunctionTypeFromNew(matingPool[i].getFunctionType());
            a.setYcombinataFromNew(matingPool[i].getYCombinata());
            a.setPercentageVariationWeight(matingPool[i].getPercentageVariationWeight());
            a.setPercentageVariationLinearA(matingPool[i].getPercentageVariationLinearA());
            a.setPercentageVariationLinearB(matingPool[i].getPercentageVariationLinearB());
            a.setPercentageVariationGammaA(matingPool[i].getPercentageVariationGammaA());
            a.setPercentageVariationGammaB(matingPool[i].getPercentageVariationGammaB());
            a.setTranslation(matingPool[i].getTranslation());
            (*itPoorGuy) = a;
        }

        _pop.clear();
        _pop.swap(offspring);
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
      int numberElitist;
};



#endif // EOSGASTEADYSTATE

