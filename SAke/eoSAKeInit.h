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
    eoSAKeInit(int _tbMin,
               int _tbMax,
               string _pattern,
               std::vector<std::vector<double>> populationfromFile,
               bool _lastGeneration)
    // END eventually add or modify the anyVariable argument
    {
        // START Code of Ctor of an eoSAKeInit object
        tbMin = _tbMin;
        tbMax = _tbMax;
        pattern = _pattern;
        count=0;
        popFromFile=populationfromFile;
        lastGeneration=_lastGeneration;
        // END   Code of Ctor of an eoSAKeInit object
    }

    std::vector<double> GetFunzioneFiltro(int tb,string Inputpattern) {
       // double* fi = (double*) malloc(sizeof(double)*tb);
        std::vector<double> fi;
        fi.resize(tb);
        int i;
        if (Inputpattern.compare("Rectangular") == 0) {
            for (i = 0; i < tb; i++) {
                double e = (1 /(double)tb);
                fi[i] = e;
            }
        } else
            if (Inputpattern.compare("Decreasing triangular") == 0) {
                for (i = 0; i < tb; i++) {
                    double hMax = (double)(2 /(double) tb);
                    fi[i] = ((double)(tb - i) /(double)( tb * hMax));
                }
            } else if (Inputpattern.compare( "Increasing triangular") == 0) {
                for (i = 0; i < tb; i++) {
                    double hMax = (double)(2 /(double)tb);
                    fi[i] = ((double)(i / (double)(tb * hMax)));
                }
            }
        return fi;
    }

    /** initialize a genotype
     *
     * @param _genotype  generally a genotype that has been default-constructed
     *                   whatever it contains will be lost
     */
    void operator()(GenotypeT & _genotype) {
        // START Code of random initialization of an eoSAKe object

        if(lastGeneration){

            int tb = popFromFile[count].size();
            _genotype.setSize(tb);
            //double* fi = GetFunzioneFiltro(tb, pattern);
            //double* fi= (double*) malloc(sizeof(double)*tb);
            std::vector<double> fi;
            fi.resize(tb);
            for (int i = 0; i < tb; i++) {
                fi[i] =  popFromFile[count][i];
            }
            _genotype.setFi(fi);
            _genotype.number=count;
            count++;
            _genotype.invalidate();

        }else
        {
//            cout << tbMax << " "<< tbMin << endl;
            int tb =( rand()%(tbMax-tbMin))+tbMin;
//             cout << tb  << endl;
            _genotype.setSize(tb);
            //double* fi = GetFunzioneFiltro(tb, pattern);
            std::vector<double> fi = GetFunzioneFiltro(tb, pattern);
            //fi.resize(tb);
            _genotype.setFi(fi);
            _genotype.number=count;
            count++;
            _genotype.invalidate();
        }

    }

    int count;
private:
    // START Private data of an eoSAKeInit object
    int tbMin;
    int tbMax;
    string pattern;
    vector<vector<double>> popFromFile;
    bool lastGeneration;

    //  varType anyVariable;		   // for example ...
    // END   Private data of an eoSAKeInit object
};

#endif
