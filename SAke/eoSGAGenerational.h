#ifndef EOSGAGENERATIONAL
#define EOSGAGENERATIONAL

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
class eoSGAGenerational : public eoAlgo<EOT>
{
public :

  // added this second ctor as I didn't like the ordering of the parameters
  // in the one above. Any objection :-) MS
  eoSGAGenerational(
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
      selectionProb = _selectRate;
  }

  double roundMy(double x, int prec)
  {
      double power = 1.0;
      int i;

      if (prec > 0)
          for (i = 0; i < prec; i++)
              power *= 10.0;
      else if (prec < 0)
          for (i = 0; i < prec; i++)
              power /= 10.0;

      if (x > 0)
          x = floor(x * power + 0.5) / power;
      else if (x < 0)
          x = ceil(x * power - 0.5) / power;

      if (x == -0)
          x = 0;

      return x;
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

  double fRand(double fMin, double fMax)
  {
      double f = (double)rand() / (double)RAND_MAX;
      return fMin + f * (fMax - fMin);
  }


  void operator()(eoPop<EOT>& _pop)
  {
    eoPop<EOT> offspring;

    do
      {

        int counter=-1;
        EOT* popTmp= new EOT[_pop.size()];//(EOT*) malloc(sizeof(EOT)*_pop.size());

        for (unsigned i=0; i<_pop.size(); i++){
            //std::cout << "Arrivo " << std::endl;
            popTmp[i] = _pop[i];
        }

        qsort (popTmp, _pop.size(), sizeof(EOT),compareEOT);
        //SELECTION
        offspring.clear();
        offspring.resize(_pop.size());
        for (unsigned int i=0; i<_pop.size(); i++){
            counter++;
//            std::cout << "Arrivo " << std::endl;
            if(counter < maxNumberToConsider){
               //  std::cout << "TORNEO!!!!!!! " << " " << std::endl;

                EOT a;
                double * r = (double*) malloc(sizeof(double)*popTmp[counter]. getSize());
                a.setFi(r);
                a.setSize(popTmp[counter]. getSize());
                for (int tmp = 0; tmp < popTmp[counter].getSize(); tmp++) {
                    a.setFiIndex(tmp, popTmp[counter]. getFiIndex(tmp));
                }
                offspring[counter]=a;
                // std::cout << "TORNEO!!!!!!! " << " " << std::endl;
                 continue;
            }
            int gen1=rand()%_pop.size();
            int gen2=rand()%_pop.size();

            double randomProb = fRand(0,1);
            EOT best;
            EOT worst;
            if(popTmp[gen1].fitness() > popTmp[gen2].fitness() ){
                double * r = (double*) malloc(sizeof(double)*popTmp[gen1]. getSize());
                best.setFi(r);
                best.setSize(popTmp[gen1]. getSize());
                for (int tmp = 0; tmp < popTmp[gen1].getSize(); tmp++) {
                    best.setFiIndex(tmp, popTmp[gen1]. getFiIndex(tmp));
                }
            }
            else{
                double * r = (double*) malloc(sizeof(double)*popTmp[gen2]. getSize());
                best.setFi(r);
                best.setSize(popTmp[gen2]. getSize());
                for (int tmp = 0; tmp < popTmp[gen2].getSize(); tmp++) {
                    best.setFiIndex(tmp, popTmp[gen2]. getFiIndex(tmp));
                }
            }

            if(popTmp[gen1].fitness() < popTmp[gen2].fitness() ){
                double * r = (double*) malloc(sizeof(double)*popTmp[gen1]. getSize());
                worst.setFi(r);
                worst.setSize(popTmp[gen1]. getSize());
                for (int tmp = 0; tmp < popTmp[gen1].getSize(); tmp++) {
                    worst.setFiIndex(tmp, popTmp[gen1]. getFiIndex(tmp));
                }
            }
            else{
                double * r = (double*) malloc(sizeof(double)*popTmp[gen2]. getSize());
                worst.setFi(r);
                worst.setSize(popTmp[gen2]. getSize());
                for (int tmp = 0; tmp < popTmp[gen2].getSize(); tmp++) {
                    worst.setFiIndex(tmp, popTmp[gen2]. getFiIndex(tmp));
                }
            }

            if(randomProb <= selectionProb){
                offspring[counter]=best;
            }else
            {
                offspring[counter]=worst;
            }

        }
        // END SELECTION


        unsigned i;


        //for (i=0; i<_pop.size()/2; i++)
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
      int countFitness;
      int countDeltaCritico;
      int countMomento;
      int countTb;
      float selectionProb;

};



#endif // EOSGAREPLACEMENT

