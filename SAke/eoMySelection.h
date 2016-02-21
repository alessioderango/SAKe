#ifndef EOMYSELECTION
#define EOMYSELECTION

//-----------------------------------------------------------------------------

#include <utils/eoRNG.h>
#include <utils/selectors.h>
#include <eoSelectOne.h>
#include <eoPop.h>
#include <stdlib.h>
#include <ctime>


/** eoProportionalSelect: select an individual proportional to her stored fitness
    value

    Changed the algorithm to make use of a cumulative array of fitness scores,
    This changes the algorithm from O(n) per call to  O(log n) per call. (MK)

    @ingroup Selectors
*/
template <class EOT> class eoMySelect: public eoSelectOne<EOT>
{
public:
  /// Sanity check
  eoMySelect(const eoPop<EOT>& /*pop*/ = eoPop<EOT>())
  {
    if (minimizing_fitness<EOT>())
      throw std::logic_error("eoProportionalSelect: minimizing fitness");

    maxNumberToConsider=8;
  }


  void setup(const eoPop<EOT>& _pop)
  {
        maxNumberToConsider=8;
        _pop.sort(result);
//         std::cout << "STAMPATO ORDINATO" <<  std::endl;
//        for (int i = 0; i < result.size(); i++) {
//                  std::cout << &(*(result[i])) << " " << result[i]->fitness() <<" " <<i << std::endl;
//                  std::cout.flush();
//          }
//        std::cout << " ********************* " <<  std::endl;
//        for (int i = 0; i < _pop.size(); i++) {
//                  std::cout << &(_pop[i]) << " "<< _pop[i].fitness() << "    " << i <<std::endl;
//                  std::cout.flush();
//          }
//        std::cout << " ********************* " <<  std::endl;
        counter=-1;
  }



  /** do the selection,
   */
  const EOT& operator()(const eoPop<EOT>& _pop)
  {
     // _pop.sort();
//     if(counter==-1)
//     for (int tmp = 0; tmp < result.size(); tmp++) {
//          std::cout << result[tmp]->fitness() << " -> ";
//       for (int i = 0; i < result[tmp]->getSizeConst() ; i++){
//          std::cout << result[tmp]->getFiConst()[i] << " ";
//          std::cout.flush();
//        }
//       std::cout <<  std::endl;
//     }

     if(counter < maxNumberToConsider){
         counter++;
         return *(result[counter]);
     }
    // counter=-1;

     int gen1=rand()%(_pop.size()-maxNumberToConsider) + maxNumberToConsider;
     int gen2=rand()%(_pop.size()-maxNumberToConsider) + maxNumberToConsider;

//     std::cout << "TORNEO!!!!!!! " << " " << std::endl;
//     std::cout << result[gen1]->fitness() << " ";

//     std::cout << result[gen2]->fitness() << " ";
//     std::cout << " FINE TORNEO!!!!!!! " << " " << std::endl;

     if(result[gen1]->fitness() > result[gen2]->fitness() )
         return *(result[gen1]);
     else
         return *(result[gen2]);

//     std::cout << " STAMPO RITORNO  "<< std::endl;
//     std::cout << " counter  "<<  counter <<std::endl;
//     std::cout << *(result[counter]) << std::endl;





//       std::cout << std::endl;
//        std::cout.flush();

//   std::cout << " tmp pop " << tmp <<  std::endl;
//    std::cout.flush();

//        std::cout << "STAMPO ARRAY pop " << std::endl;
//         std::cout.flush();
//        //for (int i = 0; i < _pop.size(); i++) {
//          std::cout << _pop[tmp].fitness() << " "<< std::endl;
//           std::cout.flush();
//        //}
//          for (int i = 0; i < _pop[tmp].getSizeConst() ; i++){
//                std::cout << _pop[tmp].getFiConst()[i] << " ";
//                 std::cout.flush();
//          }
//          std::cout << std::endl;
//           std::cout.flush();

//          for (int i = 0; i < _pop.size(); i++) {
//               std::cout << _pop[i].fitness() << " ";
//                std::cout.flush();
//          }
//           std::cout << std::endl;

//           std::cout.flush();

//           for (int i = 0; i < _pop.size(); ++i) {

//               double temporaneo = _pop[i].getFiConst()[0];
//                std::cout << " ################################ " << temporaneo << "    "<< _pop[i].getFiConst()[0] <<std::endl;
//               for (int j = 1; j < _pop[i].getSizeConst() ; j++)

//                     if(temporaneo != _pop[i].getFiConst()[j])
//                     {
//                        std::cout << " ALERT !!!!!!!!!!!!!!!      un elemento è cambiato" << std::endl;
//                        std::cout << temporaneo << "            " << _pop[i].getFiConst()[j] << std::endl;
//                        std::cout.flush();
//                     }
//               std::cout << " ################################# " << std::endl;
//               std::cout << std::endl;
//               std::cout.flush();
//    }

    //  return _pop[tmp];
  }

private :

    bool firstTime;
    int maxNumberToConsider;
    int counter;
    std::vector<const EOT*> result;


};

#endif // EOMYSELECTION

