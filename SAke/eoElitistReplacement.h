#ifndef EOELISTREPLACEMENT
#define EOELISTREPLACEMENT

template <class EOT>
class eoElitistReplacement : public eoReplacement<EOT>
{
public :
  typedef typename EOT::Fitness Fitness;

  // Ctor, takes an eoReplacement
  eoElitistReplacement(eoReplacement<EOT> & _replace,int replacement) :
    replace(_replace) {numberElementReplacement=replacement; }




  /// do replacement
  void operator()(eoPop<EOT>& _pop, eoPop<EOT>& _offspring)
  {

   _pop.sort();
  _offspring.sort();
  std::cerr << "STAMPO ARRAY pop " << std::endl;
  for (unsigned int  i = 0; i < _pop.size(); i++) {
    std::cerr << _pop[i].fitness() << " ";
  }
  std::cerr << std::endl;
  std::cerr << "STAMPO ARRAY offspring " << std::endl;
  for (unsigned int  i = 0; i < _offspring.size(); i++) {
    std::cerr << _offspring[i].fitness() << " ";
  }
  std::cerr << std::endl;
  std::cerr << "numberElementReplacement " << numberElementReplacement <<"   _pop.size() " << _pop.size()<<std::endl;
    for(int  i = 0 ; i < numberElementReplacement; i++)
    {
        if(_pop[_pop.size()-i-1].fitness() < _offspring[i].fitness()){
            typename eoPop<EOT>::iterator itGuy = _offspring.begin()+(_offspring.size()-i-1);
            (*itGuy) = *(_pop.begin()+i);
        }
            //_pop[numberElementReplacement-i] = _offspring[i];
    }

  std::cerr << "STAMPO ARRAY offspring FITNESS DOPO REPLACE " << std::endl;
    for (unsigned int  i = 0; i < _offspring.size(); i++) {
        std::cerr << _offspring[i].fitness() << " ";
    }

  std::cerr << "\n ";
  std::cerr << "replace(_pop, _offspring); " << std::endl;
  _pop.swap(_offspring);
  _pop.sort();

    std::cerr << "STAMPO ARRAY offspring FITNESS DOPO CAMBIO " << std::endl;
    for (unsigned int  i = 0; i < _pop.size(); i++) {
        std::cerr << _pop[i].fitness() << " ";
    }
    std::cerr << std::endl;

 //_pop.swap(_offspring);
  }
private:
  eoReplacement<EOT> & replace;
  int numberElementReplacement;
};

#endif // EOELISTREPLACEMENT

