#ifndef EOSGAREPLACEMENT
#define EOSGAREPLACEMENT

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
class eoSGAReplacement : public eoAlgo<EOT>
{
public :

  // added this second ctor as I didn't like the ordering of the parameters
  // in the one above. Any objection :-) MS
  eoSGAReplacement(
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
        //std::cout << "TORNEO!!!!!!! " << " " << _pop.size() << std::endl;

        //popTmp.resize(_pop.size());
        for (int i=0; i<_pop.size(); i++){
//            EOT a;
//            popTmp[i] = a;
//            popTmp[i].setWFromNew(_pop[i].getW());
//             std::cout << "TORNEO!!!!!!! " << " " << i <<std::endl;
//             popTmp[i].setParFromNew(_pop[i].getPar());
//              popTmp[i].setFunctionTypeFromNew(_pop[i].getFunctionType());
//               popTmp[i].setYcombinataFromNew(_pop[i].getYCombinata());
//              std::cout << "TORNEO!!!!!!! " << " " << i <<std::endl;
              popTmp[i]=_pop[i];

            //  std::cout << &popTmp[i] << " -> " << &_pop[i] << endl;
        }
        //std::cout << "FINE!! " << " " << std::endl;
        qsort (popTmp, _pop.size(), sizeof(EOT),compareEOT);
//        for (int i=0; i<_pop.size(); i++){


//            std::cout << popTmp[i].fitness() << " -  " << _pop[i].fitness() << endl;

//        }
        //std::cout << "TORNEO!!!!!!! " << " " << std::endl;
        //_pop.sort(result);
        //SELECTION
        offspring.clear();
        offspring.resize(_pop.size());

       // std::cout << "TORNEO!!!!!!! " << " " << _pop.size() <<std::endl;
        for (int i=0; i<_pop.size(); i++){
       // std::cout << "TORNEO!!!!!!! " << " " << std::endl;
            if(counter < maxNumberToConsider){
               // std::cout << "TORNEO!!!!!!! " << " " << std::endl;
                counter++;
                EOT a;
                a.setWFromNew(popTmp[counter].getW());
                a.setParFromNew(popTmp[counter].getPar());
                a.setFunctionTypeFromNew(popTmp[counter].getFunctionType());
                a.setYcombinataFromNew(popTmp[counter].getYCombinata());

                offspring[counter]=a;
                // std::cout << "TORNEO!!!!!!! " << " " << std::endl;
                 continue;
            }
           // counter=-1;
            counter++;
            int gen1=rand()%_pop.size();//-maxNumberToConsider) + maxNumberToConsider;
            int gen2=rand()%_pop.size();//-maxNumberToConsider) + maxNumberToConsider;

            //std::cout << "TORNEO!!!!!!! " << " " << std::endl;
           // std::cout << popTmp[gen1].fitness() << " ";

            //std::cout << popTmp[gen2].fitness() << " ";
            //std::cout << " FINE TORNEO!!!!!!! " << " " << std::endl;

            if(popTmp[gen1].fitness() < popTmp[gen2].fitness() ){
                EOT a;
                a.setWFromNew(popTmp[counter].getW());
                a.setParFromNew(popTmp[counter].getPar());
                a.setFunctionTypeFromNew(popTmp[counter].getFunctionType());
                a.setYcombinataFromNew(popTmp[counter].getYCombinata());
                offspring[counter]= a;
            }
            else{
                EOT a;
                a.setWFromNew(popTmp[counter].getW());
                a.setParFromNew(popTmp[counter].getPar());
                a.setFunctionTypeFromNew(popTmp[counter].getFunctionType());
                a.setYcombinataFromNew(popTmp[counter].getYCombinata());
                offspring[counter]= a;
            }


        }
        //  std::cout << "TORNEO!!!!!!! " << " " << std::endl;
        // END SELECTION

        //delete []popTmp;

        unsigned i;

 //std::cout << "BEFORE CROSSOVER AND MUTATION  " << std::endl;

// for (int tmp = 0; tmp < offspring.size(); tmp++) {
//      if(!offspring[tmp].invalid())
//     std::cout << offspring[tmp].fitness() << " -> " ;
//  for (int j = 0; j < offspring[tmp].getSizeConst() ;j++){
//      std::cout << offspring[tmp].getFiConst()[j] << " ";
//      std::cout.flush();
//    }
//   std::cout <<  std::endl;

// }

        //for (i=0; i<_pop.size()/2; i++)
        for (i=1; i<_pop.size()/2; i++)
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
// std::cout << "DOPO CROSSOVER  " << std::endl;

//        for (int tmp = 0; tmp < offspring.size(); tmp++) {
//            if(!offspring[tmp].invalid())
//              std::cout << offspring[tmp].fitness() << " -> ";
//         for (int j = 0; j < offspring[tmp].getSizeConst() ;j++){
//             std::cout << offspring[tmp].getFiConst()[j] << " ";
//             std::cout.flush();
//           }
//  std::cout <<  std::endl;
//        }


        for (i=1; i < offspring.size(); i++)
          {
            if (rng.flip(mutationRate) )
            {
                     if (mutate(offspring[i]))
                         offspring[i].invalidate();
            }

          }

     //  std::cout << "DOPO MUTATION  " << std::endl;


//        for (int tmp = 0; tmp < offspring.size(); tmp++) {
//            if(!offspring[tmp].invalid())
//              std::cout << offspring[tmp].fitness() << " -> ";
//         for (int j = 0; j < offspring[tmp].getSizeConst() ;j++){
//             std::cout << offspring[tmp].getFiConst()[j] << " ";
//             std::cout.flush();
//           }
//  std::cout <<  std::endl;
//        }


        offspring.invalidate();
        _pop.clear();
        _pop.swap(offspring);
        delete[] popTmp;
//        for (i=0; i < offspring.size(); i++)
//        {
//            _pop[i]=offspring[i];
//        }
        apply<EOT>(eval, _pop);
         // std::cout << "FINE!!!!!!! " << " " << std::endl;
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



#endif // EOSGAREPLACEMENT

