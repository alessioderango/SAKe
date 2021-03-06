/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

 The above line is usefulin Emacs-like editors
 */

/*
 Template for creating a new representation in EO
 ================================================
 */

#ifndef _eoSAKe_h
#define _eoSAKe_h
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Ym.h"

using namespace std;
/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen

 * Note that you MUST derive your structure from EO<fitT>
 * but you MAY use some other already prepared class in the hierarchy
 * like eoVector for instance, if you handle a vector of something....

 * If you create a structure from scratch,
 * the only thing you need to provide are
 *        a default constructor
 *        IO routines printOn and readFrom
 *
 * Note that operator<< and operator>> are defined at EO level
 * using these routines
 */
template<class FitT>
class eoSAKe: public EO<FitT> {
public:
	/** Ctor: you MUST provide a default ctor.
	 * though such individuals will generally be processed
	 * by some eoInit object
	 */
	eoSAKe() {
	}

    eoSAKe(int _size) {
		// START Code of default Ctor of an eoSAKe object
		size = _size;
		Fi = NULL;
		number =0;
        dYcr=0;
//        YsMin=0;
//        YsMin2=0;
//        iMin=0;
//        min();
//        min2();
        momentoDelPrimoOrdine=0;
		// END   Code of default Ctor of an eoSAKe object
	}

	virtual ~eoSAKe() {
		// START Code of Destructor of an eoEASEAGenome object

		// END   Code of Destructor of an eoEASEAGenome object
	}

	virtual string className() const {
		return "eoSAKe";
	}

	/** printing... */
	void printOn(ostream& _os) const {
		// First write the fitness
//		EO<FitT>::printOn(_os);
//		_os << ' ';
//		// START Code of default output
//
//		/** HINTS
//		 * in EO we systematically write the sizes of things before the things
//		 * so readFrom is easier to code (see below)
//		 */
        _os << size << ' ';
        for (unsigned i = 0; i < size; i++)
            _os << Fi[i] << ' ';
		// END   Code of default output
	}


	// accessing and setting values
	void setSize(int _size) {
		this->size = _size;
	}

    int getSizeConst() const {
		return this->size;
	}

    int getSize() {
        return this->size;
    }

    void setFi(double *& _Fi)  {
		Fi =  _Fi;
	}

    void setdYcr(double _dYcr)  {
        dYcr =  _dYcr;
    }
    double getdYcr()  {
        return dYcr;
    }
    double getdYcrConst() const  {
        return dYcr;
    }


    void setMomentoDelPrimoOrdine(double _momentoDelPrimoOrdine)  {
        momentoDelPrimoOrdine =  _momentoDelPrimoOrdine;
    }
    double getMomentoDelPrimoOrdine()  {
        return momentoDelPrimoOrdine;
    }
    double getMomentoDelPrimoOrdineConst() const  {
        return momentoDelPrimoOrdine;
    }
//    void setYsMin(double _YsMin)  {
//        YsMin =  _YsMin;
//    }
//    double getYsMin()  {
//        return YsMin;
//    }
//    double getYsMinConst() const  {
//        return YsMin;
//    }

//    int getiMin()  {
//        return iMin;
//    }
//    int getiMinConst() const  {
//        return iMin;
//    }

//    void setiMin(int _iMin)  {
//        iMin =  _iMin;
//    }
//    void setYsMin2(double _YsMin2)  {
//        YsMin2 =  _YsMin2;
//    }
//    double getYsMin2()  {
//        return YsMin2;
//    }
//    double getYsMin2Const() const  {
//        return YsMin2;
//    }

        void setYmMin(Ym _YmMin)  {
            min =  _YmMin;
        }
        Ym getYmMin()  {
            return min;
        }
        Ym getYmMinConst() const  {
            return min;
        }

        void setYmMin2(Ym _YmMin2)  {
            min2 =  _YmMin2;
        }
        Ym getYmMin2()  {
            return min2;
        }
        Ym getYmMin2Const() const  {
            return min2;
        }

	void setFiIndex(int _i, double value) {
		Fi[_i] = value;
	}

    void setBests(std::vector<Ym> a) {
        bests = a;
    }

    std::vector<Ym> getBests() {
        return bests;
    }

    std::vector<Ym> getBestsConst() const {
        return bests;
    }

	double getFiIndex(int _i) {
		return Fi[_i];
	}
    double*& getFi() {
		return Fi;
	}

    double* getFiConst() const{
        return Fi;
    }

	void deleteFi() {
//		delete []Fi;
 		free(Fi);
	}

	int number;

private:
	// put all data here
	// START Private data of an eoSAKe object
	double* Fi;	// kernel function

	int size;

    double dYcr;

//    double YsMin;
//    double YsMin2;
//    int iMin;
    Ym min;
    Ym min2;
    double momentoDelPrimoOrdine;
    std::vector<Ym> bests;
	 	// size of the array Fi

	// END   Private data of an eoSAKe object
};

#endif
