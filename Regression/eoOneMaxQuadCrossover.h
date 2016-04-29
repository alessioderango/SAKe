/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is usefulin Emacs-like editors
*/

/*
Template for simple quadratic crossover operators
=================================================

Quadratic crossover operators modify the both genotypes
*/

#ifndef eoOneMaxQuadCrossover_H
#define eoOneMaxQuadCrossover_H

#include <eoOp.h>
#include <Regression/parameters.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT>
class eoOneMaxQuadCrossover: public eoQuadOp<GenotypeT>
{
public:
    /**
     * Ctor - no requirement
     */
// START eventually add or modify the anyVariable argument
    eoOneMaxQuadCrossover()
    //  eoOneMaxQuadCrossover( varType  _anyVariable) : anyVariable(_anyVariable)
    // END eventually add or modify the anyVariable argument
	{
	    // START Code of Ctor of an eoOneMaxEvalFunc object
	    // END   Code of Ctor of an eoOneMaxEvalFunc object
	}

    /// The class name. Used to display statistics
    string className() const { return "eoOneMaxQuadCrossover"; }

    /**
     * eoQuad crossover - modifies both parents
     * @param _genotype1 The first parent
     * @param _genotype2 The second parent
     */
    bool operator()(GenotypeT& _genotype1, GenotypeT & _genotype2)
	{
	    bool oneAtLeastIsModified(true);
	    // START code for crossover of _genotype1 and _genotype2 objects


	    /** Requirement
	     * if (at least one genotype has been modified) // no way to distinguish
	     *     oneAtLeastIsModified = true;
	     * else
	     *     oneAtLeastIsModified = false;
	     */

        int rndPar= rand() %  _genotype1.getParConst().size();
        int rndW= rand() %  _genotype1.getWConst().size();


        for (int i = 0; i < rndW; i++) {
            double tmp1 = _genotype1.getW(i);
            double tmp2 = _genotype2.getW(i);
            _genotype1.setW(i,tmp2);
            _genotype2.setW(i,tmp1);

        }

        for (int i = 0; i < rndPar; i++) {
            int tmp1 = _genotype1.getFunctionType(i);
            int tmp2 = _genotype2.getFunctionType(i);
            _genotype1.setFunctionType(i,tmp2);
            _genotype2.setFunctionType(i,tmp1);

            Parameters tmp3 = _genotype1.getPar(i);
            Parameters tmp4 = _genotype2.getPar(i);

            //               if(_genotype1.getFunctionType(i) == 1){
            //                   double tmp = tmp3.getParameters(0);
            //                   tmp3.setParameters(0,tmp4.getParameters(0));
            //                   tmp4.setParameters(0,tmp);

            //               }else
            //                      if(_genotype1.getFunctionType(i) == 0 || _genotype1.getFunctionType(i) == 2){
            //                          double tmpPar = tmp3.getParameters(0);
            //                          tmp3.setParameters(0,tmp4.getParameters(0));
            //                          tmp4.setParameters(0,tmpPar);
            //                          double tmpPar2 = tmp3.getParameters(1);
            //                          tmp3.setParameters(1,tmp4.getParameters(1));
            //                          tmp4.setParameters(1,tmpPar2);
            //                      }

            _genotype1.setPar(i,tmp3);
            _genotype2.setPar(i,tmp4);

        }



	    return oneAtLeastIsModified;
	    // END code for crossover of _genotype1 and _genotype2 objects
	}

private:
// START Private data of an eoOneMaxQuadCrossover object
    //  varType anyVariable;		   // for example ...
// END   Private data of an eoOneMaxQuadCrossover object
};

#endif
