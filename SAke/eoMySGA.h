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
        numberElitist=_maxNumberToConsider;
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
        //_pop.printOn(std::cout);
        //numberElitist=8;


        do
        {

            // creare una eoPop temporanea con i primi n-e della popolazione dopo
            // avarli ordinati. Applicare la selezione sulla eoPop appena creata e
            // aggiungere gli n-e alla offspring insieme agli e (elitisti) precedentemente
            // conservati.
            eoPop<EOT> offspring;
            eoPop<EOT> matingPool;
            offspring.resize(_pop.size());

            _pop.sort();
            int N =_pop.size();

            std::cout << numberElitist << std::endl;
            for (unsigned int i=0; i< numberElitist; i++)
            {
                typename eoPop<EOT>::iterator itPoorGuy = offspring.begin() + i;
                EOT a;
                std::vector<double> r;
                r.resize(_pop[i].getSize());
                a.setFi(r);
                a.setSize(_pop[i].getSize());
                for (int tmp = 0; tmp < _pop[i].getSize(); tmp++) {
                    a.setFiIndex(tmp, _pop[i].getFi()[tmp]);
                    //std::cout << "a.getFi()[tmp] " << a.getFi()[tmp] << "  =  " << "_pop[i].getFi()[tmp]  = " << _pop[i].getFi()[tmp]<<std::endl;
                }
                (*itPoorGuy) = a;
            }

            _pop.resize(N-numberElitist);
            select(_pop,matingPool);

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

            int posOffspring = numberElitist;
            for (unsigned int i=0; i< (offspring.size()-numberElitist); i++){

                typename eoPop<EOT>::iterator itPoorGuy = offspring.begin() + posOffspring;
                EOT a;
                std::vector<double> r;
                r.resize(matingPool[i].getSize());
                a.setFi(r);
                a.setSize(matingPool[i].getSize());
                for (int tmp = 0; tmp < matingPool[i].getSize(); tmp++) {
                    a.setFiIndex(tmp, matingPool[i].getFiIndex(tmp));
                }
                (*itPoorGuy) = a;
                posOffspring++;
            }

            _pop.clear();
            _pop.swap(offspring);
            apply<EOT>(eval, _pop);
        } while(cont(_pop));
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


#endif // EOMYSGA

