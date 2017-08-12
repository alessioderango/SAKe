/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

 The above line is useful in Emacs-like editors
 */

/*
 Template for simple mutation operators
 ======================================
 */

#ifndef eoSAKeMutation_H
#define eoSAKeMutation_H

#include <eoOp.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT>
class eoSAKeMutation: public eoMonOp<GenotypeT> {
public:
	/**
	 * Ctor - no requirement
	 */
	// START eventually add or modify the anyVariable argument
	eoSAKeMutation(int _tbMin, int _tbMax, double _Pme, double _Pmb, double _dHpMin,
			double _dHpMax)
			//  eoSAKeMutation( varType  _anyVariable) : anyVariable(_anyVariable)
			// END eventually add or modify the anyVariable argument
			{
				tbMin = _tbMin;
				tbMax = _tbMax;
				Pme = _Pme;
				Pmb = _Pmb;
				dHpMin = _dHpMin;
				dHpMax = _dHpMax;

		// START Code of Ctor of an eoSAKeEvalFunc object
		// END   Code of Ctor of an eoSAKeEvalFunc object
	}


	void normalizeElementsMutation(GenotypeT & _genotype) {
		double s = 0;
		for (int i = 0; i < _genotype.getSize(); i++) {
            s += _genotype.getFiIndex(i);
        }
		if (s != 1) {
			for (int t = 0; t < _genotype.getSize(); t++) {
                _genotype.setFiIndex(t,(1 / s) * _genotype.getFiIndex(t));
			}
		}
	}

	/// The class name. Used to display statistics
	string className() const {
		return "eoSAKeMutation";
	}

	/**
	 * modifies the parent
	 * @param _genotype The parent genotype (will be modified)
	 */
	bool operator()(GenotypeT & _genotype) {

//        // Pmb probabilit� di mutazione tb
//        // Pme probabilit� di mutazione dh
        bool isModified=true;
        bool debug=false;
        int tb = (rand() % (tbMax-tbMin)) + tbMin;
        int tb0 = _genotype.getSize();
        int tb1 = 0;
		
//		if (debug) {
//			cout << "**************************** BEFORE MUTATION ***********************" << endl;
//			cout << "GENOTYPE : "<< _genotype.number << endl;
//			cout << "_genotype.getSize() : " << _genotype.getSize() << endl;
//            cout << "_genotype.getFi() : " << _genotype.getFi() << endl;
//			cout << "tb random : " << tb << endl;
//			for (int i = 0; i < tb0; ++i) {
//				double tmp =  _genotype.getFi()[i];
//				cout << tmp << " ";
//			}
//			cout << endl;
//		}

        if (tb > tb0){
            tb1 = tb0;
            //double dtb= ((double)tb/tb0);
//            cout << "+  " << tb << "   " << tb0 << "  dtb " << ((double)dtb) << endl;
        }
        else{
            //double dtb=((double) tb/tb0);
//            cout << "-  " << tb << "   " << tb0 << "  %dtb " << ((double)dtb)  << endl;
            tb1 = tb;
        }
        //double * FiTemp = (double*) malloc(sizeof(double)*tb);
        std::vector<double> FiTemp;
        FiTemp.resize(tb);
        for (int i = 0; i < tb1; i++)
            FiTemp[i] = _genotype.getFiIndex(i);
//		memcpy( FiTemp,_genotype.getFi(), tb1 * sizeof(double) );

        for (int i = tb1 ; i < tb; i++)
            FiTemp[i] = 0;

//      _genotype.deleteFi();
//		realloc(_genotype.getFi(),  tb * sizeof(double));
//		memcpy( _genotype.getFi(), FiTemp, tb * sizeof(double) );

        _genotype.setFi(FiTemp);
        _genotype.setSize(tb);

//		double * tmp = _genotype.getFi();

        // cerco hMax nell'array Fi
        double hMax = -10000000000;
        double v = 0;
        for (int t = 0; t < _genotype.getSize(); t++) {
            if (_genotype.getFiIndex(t) > hMax)
                hMax = _genotype.getFiIndex(t);
        }

        if (tb > tb0) {
            double tmp = (double)((tb - tb0)/tb0);
            v = tmp * 100;
        }
//        cout << "Pmb " << Pmb << " Pme  "<< Pme << " v "<< v <<endl;

        double Pme1 = (v / Pmb) * Pme;
//        cout <<"Pme1 " << Pme1 << endl;
        for (int t = 1; t <= tb; t++) {
            int tj = rand() % tb;

           double dHp = (rand() % ((int)(dHpMax -dHpMin)))+dHpMin;
           double result=  ((double)t / tb)*100;
//           cout << "t " << t << " tb " << tb << endl;
//            cout << "Pme1 " << Pme1 << " t / tb * 100 " << result << endl;
            if (result <= Pme1) {
 //               if (tb > tb0)
                    tj = (rand() % (tb-tb0)) + tb0;
//                    cout << "tb " << tb << " tb0 " << tb0 << " tj " << tj << endl;
//                else
//                    if(tb <= tb0)
//                        tj = rand() % tb;

                dHp = rand() % ((int) dHpMax+1);
            }
            if (result <= Pme) {
  //              cout << " ENTRATO PME MUTO GENE " << endl;
                double dH = (dHp / 100) * hMax;
//				cout << " tj  "<< tj << " tb size = " << tb << endl;
//				cout << "Pme =" << Pme <<  "  hMax="<<hMax <<"  dH="<< dH<< endl;
                _genotype.setFiIndex(tj, _genotype.getFiIndex(tj) + dH);
                if (_genotype.getFiIndex(tj) < 0) {
                    _genotype.setFiIndex(tj,0);
                }
            }

        }
        bool allzero=true;
        for (int i = 0; i < _genotype.getSize(); ++i) {
            if(_genotype.getFi()[i] != 0){
                allzero=false;
            }
        }
        if(!allzero)
        normalizeElementsMutation(_genotype);

//		if (debug) {
//			cout << "********************************* AFTER MUTATION ***********************" << endl;
//			cout << "GENOTYPE :" << endl;
//			cout << "_genotype.getSize() : " << _genotype.getSize() << endl;
//            cout << "_genotype.getFi() : " << _genotype.getFi() << endl;
//			cout << "size : " << tb << endl;
//			for (int i = 0; i < tb; ++i) {
//				cout << _genotype.getFi()[i] << " ";
//			}
//			cout << endl;
//		}

		return isModified;
		// END code for mutation of the _genotype object
	}

	int getTbMax() const {
		return tbMax;
	}

	void setTbMax(int tbMax) {
		this->tbMax = tbMax;
	}

	int getTbMin() const {
		return tbMin;
	}

	void setTbMin(int tbMin) {
		this->tbMin = tbMin;
	}

private:
// START Private data of an eoSAKeMutation object

	int tbMin;
	int tbMax;
	double Pme;
	double Pmb;
	double dHpMin;
	double dHpMax;
	//  varType anyVariable;		   // for example ...
// END   Private data of an eoSAKeMutation object
};

#endif
