#ifndef EOMYRANKING_H
#define EOMYRANKING_H


#include <eoPerf2Worth.h>

/** An instance of eoPerfFromWorth
 *  COmputes the ranked fitness: fitnesses range in [m,M]
 *  with m=2-pressure/popSize and M=pressure/popSize.
 *  in between, the progression depstd::ends on exponent (linear if 1).
 *
 *  @ingroup Selectors
 */
template <class EOT>
class eoMyRanking : public eoPerf2Worth<EOT> // false: do not cache fitness
{
public:

    using eoPerf2Worth<EOT>::value;

  /* Ctor:
   @param _p selective pressure (in (1,2]
   @param _e exponent (1 == linear)
  */
  eoMyRanking(double _p=2.0, double _e=1.0):
    pressure(_p), exponent(_e) {}

  /* helper function: finds index in _pop of _eo, an EOT * */
  int lookfor(const EOT *_eo, const eoPop<EOT>& _pop)
    {
      typename eoPop<EOT>::const_iterator it;
      for (it=_pop.begin(); it<_pop.end(); it++)
        {
          if (_eo == &(*it))
            return it-_pop.begin();
        }
      throw std::runtime_error("Not found in eoLinearRanking");
    }

  /* COmputes the ranked fitness: fitnesses range in [m,M]
     with m=2-pressure/popSize and M=pressure/popSize.
     in between, the progression depstd::ends on exponent (linear if 1).
   */
  virtual void operator()(const eoPop<EOT>& _pop)
    {
      std::vector<const EOT *> rank;
      _pop.sort(rank);
      unsigned pSize =_pop.size();
      unsigned int pSizeMinusOne = pSize-1;

      if (pSize <= 1)
        throw std::runtime_error("Cannot do ranking with population of size <= 1");

      // value() refers to the std::vector of worthes (we're in an eoParamvalue)
      value().resize(pSize);

      if (pressure < 1.0)         // exponent
        {
          double tmp = (1-pressure)/(1-pow(pressure,pSize));
          double sum =0.0;

          double p =0;
          for (unsigned i=0; i<pSize; i++)
            {

              int which = lookfor(rank[i], _pop);
              value()[which] = pow(pressure,i)*tmp;
              p = value()[which];
              sum += value()[which];
            }

        }
      else                                 // Linear
        {
          double tmp = (1/(double)pSize);
          for (unsigned i=0; i<pSize; i++)
            {
              int which = lookfor(rank[i], _pop);
              value()[which] = tmp * (pressure-2*(pressure-1)*( ((double)i) / ((double)(pSize-1))) );
            }
        }
    }
 private:
  double pressure;	// selective pressure
  double exponent;
};
#endif // EOMYRANKING_H
