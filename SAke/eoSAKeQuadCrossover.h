/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

 The above line is usefulin Emacs-like editors
 */

/*
 Template for simple quadratic crossover operators
 =================================================

 Quadratic crossover operators modify the both genotypes
 */

#ifndef eoSAKeQuadCrossover_H
#define eoSAKeQuadCrossover_H

#include <eoOp.h>
#include <float.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT>
class eoSAKeQuadCrossover: public eoQuadOp<GenotypeT> {
public:
	/**
	 * Ctor - no requirement
	 */
// START eventually add or modify the anyVariable argument
	eoSAKeQuadCrossover()
	//  eoSAKeQuadCrossover( varType  _anyVariable) : anyVariable(_anyVariable)
	// END eventually add or modify the anyVariable argument
	{
		// START Code of Ctor of an eoSAKeEvalFunc object
		// END   Code of Ctor of an eoSAKeEvalFunc object
	}

	/// The class name. Used to display statistics
	string className() const {
		return "eoSAKeQuadCrossover";
	}

	/**
	 * eoQuad crossover - modifies both parents
	 * @param _genotype1 The first parent
	 * @param _genotype2 The second parent
	 */

	void normalizaElement(GenotypeT& _genotype1) {
		double s = 0;
		for (int i = 0; i < _genotype1.getSize(); i++)
            s += _genotype1.getFi()[i];
		if (s != 1)
			for (int t = 0; t < _genotype1.getSize(); t++)
				_genotype1.getFi()[t] = (1 / s) * _genotype1.getFi()[t];


	}

	bool operator()(GenotypeT& _genotype1, GenotypeT & _genotype2) {
		bool oneAtLeastIsModified(true);
        bool debug = false;
		int tb1 = _genotype1.getSize();
		int tb2 = _genotype2.getSize();
		if (debug) {
			cout << "************************ BEFORE CROSSOVER ***********************" << endl;
			cout << "GENOTYPE 1:" << endl;
			cout << "size : " << tb1 << endl;
			for (int i = 0; i < tb1; ++i) {
				cout << _genotype1.getFi()[i] << " ";
			}
			cout << endl;
			cout << "GENOTYPE 2:" << endl;
			cout << "size : " << tb2 << endl;
			for (int i = 0; i < tb2; ++i) {
				cout << _genotype2.getFi()[i] << " ";
			}
			cout << endl;
		}

		int min = tb1;
		if (tb2 < min)
			min = tb2;

		int tbCut = rand() % min;


		for (int i = 0; i < tbCut; i++) {
//            cout << "min : " << min << endl;
//			cout << "tbCut : " << tbCut << endl;
//			cout << "i : " << i << endl;
//			cout << "GENOTYPE 1:" << endl;
//			cout << "_genotype1.getFiIndex(i) : " << _genotype1.getFiIndex(i) << endl;
//			cout << "size : " << tb1 << endl;
//			cout << "GENOTYPE 2:" << endl;
//			cout << "_genotype2.getFiIndex(i) : " << _genotype2.getFiIndex(i) << endl;
//            cout << "size : " << tb2 << endl;

			double fi1 = _genotype1.getFiIndex(i);
			double fi2 = _genotype2.getFiIndex(i);
			_genotype1.setFiIndex(i,fi2);
			_genotype2.setFiIndex(i,fi1);
		}

		normalizaElement(_genotype1);
		normalizaElement(_genotype2);

		// START code for crossover of _genotype1 and _genotype2 objects

		/** Requirement
		 * if (at least one genotype has been modified) // no way to distinguish
		 *     oneAtLeastIsModified = true;
		 * else
		 *     oneAtLeastIsModified = false;
		 */

		if (debug) {
			cout << "******************** AFTER CROSSOVER ***********************" << endl;
			cout << "GENOTYPE 1:" << endl;
			cout << "size : " << tb1 << endl;
			for (int i = 0; i < tb1; ++i) {
				cout << _genotype1.getFi()[i] << " ";
			}
			cout << endl;
			cout << "GENOTYPE 2:" << endl;
			cout << "size : " << tb2 << endl;
			for (int i = 0; i < tb2; ++i) {
				cout << _genotype2.getFi()[i] << " ";
			}
			cout << endl;
		}

		return oneAtLeastIsModified;
		// END code for crossover of _genotype1 and _genotype2 objects
	}

};

#endif
