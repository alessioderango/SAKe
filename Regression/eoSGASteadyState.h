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
        int _maxNumberToConsider)
    : cont(_cont),
          mutate(_mutate),
          mutationRate(_mrate),
          cross(_cross),
          crossoverRate(_crate),
          select(_select,_selectRate),
          eval(_eval) {
      maxNumberToConsider =_maxNumberToConsider;
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
    EOT* popTmp;
    do
      {
        int counter=-1;

        popTmp= new EOT[_pop.size()];
        for (int i=0; i<_pop.size(); i++){
              popTmp[i]=_pop[i];
        }
        qsort (popTmp, _pop.size(), sizeof(EOT),compareEOT);

        //SELECTION
        offspring.clear();
        offspring.resize(_pop.size());

        for (int i=0; i<_pop.size(); i++){
            if(counter < maxNumberToConsider){
                counter++;
                EOT a;
                a.setWFromNew(popTmp[counter].getW());
                a.setParFromNew(popTmp[counter].getPar());
                a.setFunctionTypeFromNew(popTmp[counter].getFunctionType());
                a.setYcombinataFromNew(popTmp[counter].getYCombinata());
                a.setPercentageVariationWeight(popTmp[counter].getPercentageVariationWeight());
                a.setPercentageVariationLinearA(popTmp[counter].getPercentageVariationLinearA());
                a.setPercentageVariationLinearB(popTmp[counter].getPercentageVariationLinearB());
                a.setPercentageVariationGammaA(popTmp[counter].getPercentageVariationGammaA());
                a.setPercentageVariationGammaB(popTmp[counter].getPercentageVariationGammaB());
                a.setTranslation(popTmp[counter].getTranslation());

                offspring[counter]=a;
                 continue;
            }
            counter++;
           // = min + rand()%(max - min);
            int gen1=maxNumberToConsider+(rand()%(_pop.size()-maxNumberToConsider));//-maxNumberToConsider) + maxNumberToConsider;
            int gen2=maxNumberToConsider+(rand()%(_pop.size()-maxNumberToConsider));//-maxNumberToConsider) + maxNumberToConsider;

            if(popTmp[gen1].fitness() < popTmp[gen2].fitness() ){
                EOT a;
                a.setWFromNew(popTmp[counter].getW());
                a.setParFromNew(popTmp[counter].getPar());
                a.setFunctionTypeFromNew(popTmp[counter].getFunctionType());
                a.setYcombinataFromNew(popTmp[counter].getYCombinata());
                a.setPercentageVariationWeight(popTmp[counter].getPercentageVariationWeight());
                a.setPercentageVariationLinearA(popTmp[counter].getPercentageVariationLinearA());
                a.setPercentageVariationLinearB(popTmp[counter].getPercentageVariationLinearB());
                a.setPercentageVariationGammaA(popTmp[counter].getPercentageVariationGammaA());
                a.setPercentageVariationGammaB(popTmp[counter].getPercentageVariationGammaB());
                a.setTranslation(popTmp[counter].getTranslation());

                offspring[counter]= a;
            }
            else{
                EOT a;
                a.setWFromNew(popTmp[counter].getW());
                a.setParFromNew(popTmp[counter].getPar());
                a.setFunctionTypeFromNew(popTmp[counter].getFunctionType());
                a.setYcombinataFromNew(popTmp[counter].getYCombinata());
                a.setPercentageVariationWeight(popTmp[counter].getPercentageVariationWeight());
                a.setPercentageVariationLinearA(popTmp[counter].getPercentageVariationLinearA());
                a.setPercentageVariationLinearB(popTmp[counter].getPercentageVariationLinearB());
                a.setPercentageVariationGammaA(popTmp[counter].getPercentageVariationGammaA());
                a.setPercentageVariationGammaB(popTmp[counter].getPercentageVariationGammaB());
                a.setTranslation(popTmp[counter].getTranslation());

                offspring[counter]= a;
            }


        }
        // END SELECTION


        unsigned i;
        for (i=maxNumberToConsider; i<_pop.size()/2; i++)
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

        for (i=maxNumberToConsider; i < offspring.size(); i++)
          {
            if (rng.flip(mutationRate) )
            {
                     if (mutate(offspring[i]))
                         offspring[i].invalidate();
            }

          }

        offspring.invalidate();
        _pop.clear();
        _pop.swap(offspring);
        delete[] popTmp;
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



#endif // EOSGASTEADYSTATE

