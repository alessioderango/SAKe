/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

 The above line is usefulin Emacs-like editors
 */

/*
 Template for EO objects initialization in EO
 ============================================
 */

#ifndef _eoSAKeInit_h
#define _eoSAKeInit_h

// include the base definition of eoInit
#include <eoInit.h>
#include <string.h>
#include <iostream>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * There is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO (e.g. to initialize
 *    atoms of an eoVector you will need an eoInit<AtomType>)
 */
template<class GenotypeT>
class eoSAKeInit: public eoInit<GenotypeT> {
public:
	/// Ctor - no requirement
// START eventually add or modify the anyVariable argument
//  eoSAKeInit()
    eoSAKeInit(int _tbMin,int _tbMax, string _pattern)
// END eventually add or modify the anyVariable argument
			{
		// START Code of Ctor of an eoSAKeInit object
		tbMin = _tbMin;
		tbMax = _tbMax;
		pattern = _pattern;
		count=0;
		// END   Code of Ctor of an eoSAKeInit object
	}

    double * GetFunzioneFiltro(int tb,string Inputpattern) {
      double* fi = (double*) malloc(sizeof(double)*tb);
//      double* fi = (double*) malloc(sizeof(double)*tb);

       // double a[] = {0.0140886, 0.0140731, 0.0148799, 0.00641096, 0.0198833, 0.0426108, 0.00702339, 0.0223509, 0.0207891, 0.0189719, 0.00330791, 0.00138106, 0.00725694, 0.0195603, 0.0134993, 0.0138206, 0.00893735, 0.00091538, 0.0021898, 0.034607, 0.00453408, 0.00508186, 0.00832767, 0.0284317, 0.0246107, 0.0109869, 0.000642201, 0.0233997, 0.0112176, 0.0235053, 0.0130252, 0.0422384, 0.0137323, 0.0207241, 0.00608007, 0.0103282, 0.0018829, 0.0264447, 0.0207448, 0.0051812, 0.00916462, 0.00176417, 0.0020222, 0.00557744, 0.018521, 0.00372957, 0.0213894, 0.00490169, 0.00658428, 0.0134024, 0.0102284, 0.0163666, 0.0024028, 0.00820829, 0.00665848, 0.0152779, 0.00347516, 0.0249736, 0.0133602, 0.0133022, 0.0118701, 0.0217224, 0.0344464, 0, 0.0105916, 0.00745105, 0.00028579, 0.00340127, 0.000654508, 7.67994e-05, 0.006621, 0.00115821, 0.0137442, 0.00307311, 0.00926798, 0.00700678, 0.00901325, 0.00949795, 0.00894231, 0.00037155, 2.98291e-05, 0.00306792, 0.000933896, 0.000124391, 0.00475086, 0.00198542, 0.00213003, 0.00126922, 0.00439848, 0.00116742, 0.00804708, 0.00296889, 8.54421e-05, 0.00319077, 0.00254777, 0.000142181, 1.70368e-06, 2.10551e-05, 0.00194676, 0.00382474, 0.00186127, 0.00366163, 0.000740777, 0.00157702, 0, 0.000166184, 2.13059e-05, 2.89464e-06, 2.80818e-05, 3.37693e-06, 0.000333217, 6.98996e-05, 0, 4.35248e-06, 0.000212191, 0.000204102, 1.23352e-05, 9.60709e-05, 1.42581e-06, 3.45197e-06, 1.12564e-06, 8.383e-06, 0, 8.14349e-06, 0, 1.10177e-05, 0, 6.46689e-06, 3.11369e-06, 1.60475e-05, 6.22737e-06, 1.43709e-06, 8.86203e-06, 1.41313e-05, 6.22737e-06, 2.39514e-07, 0, 2.25143e-05, 1.22152e-05, 2.32329e-05, 2.17958e-05, 7.18543e-07, 5.98786e-06, 0, 0, 0, 5.01046e-06};
    //  double a[] = {0.0123422, 0.0189815, 0.00989347, 0.00455653, 0.01197, 0.0415514, 0.0436271, 0.0271489, 0.0168873, 0.0171932, 0.00546354, 0.0178603, 0.0152608, 0.0169403, 0.0145013, 0.0172218, 0.0296209, 0.00844848, 0.00211963, 0.0334979, 0.00438877, 0.004919, 0.00242062, 0.0266333, 0.00569402, 0.0235565, 0.0132973, 0.0112464, 0.0335627, 0.0226233, 0.0307254, 0.0197413, 0.00972613, 0.00572915, 0.00951656, 0.00873014, 0.013493, 0.0041227, 0.00680523, 0.0103946, 0.0123023, 0.000305349, 0.00601257, 0.00519335, 0.00529652, 0.00904479, 0.0116452, 0.00503007, 0.00814024, 0.00694945, 0.00661694, 0.0158808, 0.000415886, 0.0108697, 0.00254908, 0.00710032, 0.00833233, 0.0014768, 0.00611145, 0.0101391, 0.00643726, 0.00989848, 0.00130215, 0.00671487, 0.00447096, 0.00880208, 0.00236757, 0.00139666, 0.00395057, 0.000852229, 0.0133781, 0.00310712, 0.00754249, 0.013973, 0.00374976, 0.0114101, 0.0013208, 0.0129902, 0.00842199, 0.0170603, 0.00732072, 0.00448048, 0.00953496, 0.00855683, 0.00895633, 0.00668303, 0.00388626, 0.00498762, 0.00257377, 0.00946682, 0.00568593, 0.00209777, 6.0372e-05, 0.00225455, 0.00180021, 0.000100463, 1.2038e-06, 1.48772e-05, 0.00137555, 0.0027025, 0.00131514, 0.00258725, 0.000523421, 0.0011143, 0, 0.000117423, 1.50544e-05, 2.0453e-06, 1.98421e-05, 2.38608e-06, 0.000235445, 4.93899e-05, 0, 3.07539e-06, 0.00014993, 0.000144215, 8.71586e-06, 6.78821e-05, 1.00746e-06, 2.43911e-06, 7.9536e-07, 5.92329e-06, 0, 5.75405e-06, 0, 7.78489e-06, 0, 4.56939e-06, 2.20008e-06, 1.13389e-05, 4.40016e-06, 1.01542e-06, 6.26176e-06, 9.98497e-06, 4.40016e-06, 1.69237e-07, 0, 1.59083e-05, 8.63108e-06, 1.6416e-05, 1.54006e-05, 5.07711e-07, 4.23092e-06, 0, 0, 0, 3.54031e-06};


       //  double a[] = { 0.0388789, 0.0193931, 0.024672, 0.0235319, 0.0330699, 0.033032, 0.0299585, 0.0299585, 0.0299585, 0.0299585, 0.0299585, 0.0299585, 0.0300591, 0.0300591, 0.0295657, 0.0295657, 0.021256, 0.0213524, 0.0213524, 0.0213524, 0.0213524, 0.0213524, 0.0215206, 0.0215206, 0.0209809, 0.0209809, 0.0209809, 0.0209809, 0.0209809, 0.0209809, 0.0158564, 0.0158564, 0.0147464, 0.0127453, 0.00542204, 0.00287049, 0.00175419, 0.0124388, 0.0113225, 0.0100467, 0.0102062, 0.00693758, 0.0144424, 0.0147634, 0.0131181, 0.0111984, 0.00543921, 0.0127981, 0.0286358, 0.0108784};
        int i;
        //string rettangolo = "Rettangolare";
        if (Inputpattern.compare("Rettangolare") == 0) {
            for (i = 0; i < tb; i++) {
                double e = (1 /(double)tb);
                fi[i] = e;
            }
        } else
            if (Inputpattern.compare("Triangolare Disc") == 0) {
            for (i = 0; i < tb; i++) {
                double hMax = (double)(2 /(double) tb);
//                 printf(" %d \n",hMax);
//                  printf("\n");
                fi[i] = ((double)(tb - i) /(double)( tb * hMax));
//                printf(" %f \n",(double)(tb - i));
//                printf(" %f \n",(double)( tb * hMax));
//                  printf("\n");
            }
        } else if (Inputpattern.compare( "Triangolare Asc") == 0) {
            for (i = 0; i < tb; i++) {
                double hMax = (double)(2 /(double)tb);
                fi[i] = ((double)(i / (double)(tb * hMax)));
            }
        }

//        for (i = 0; i < tb; i++) {
//               fi[i] = a[i];
//        }

//        for (i = 0; i < tb; i++) {
//            printf(" %f ",fi[i]);
//        }
//        printf("\n");
		return fi;
	}

	/** initialize a genotype
	 *
	 * @param _genotype  generally a genotype that has been default-constructed
	 *                   whatever it contains will be lost
	 */
	void operator()(GenotypeT & _genotype) {
		// START Code of random initialization of an eoSAKe object
        int tb =( rand()%(tbMax-tbMin))+tbMin;
//        _genotype.setSize(tb);
       // int tb =50;
         _genotype.setSize(tb);

//        cout <<"OK " << _genotype.getSize() << endl;
		double* fi = GetFunzioneFiltro(tb, pattern);
		_genotype.setFi(fi);
		_genotype.number=count;
		count++;
		_genotype.invalidate();
	}

	int count;
private:
// START Private data of an eoSAKeInit object
	int tbMin;
	int tbMax;
    string pattern;

//  varType anyVariable;		   // for example ...
// END   Private data of an eoSAKeInit object
};

#endif
