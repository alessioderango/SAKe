/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is usefulin Emacs-like editors
 */

/*
Template for creating a new representation in EO
================================================

This is the template main file.
It includes all other files that have been generated by the script create.sh
so it is the only file to compile.

In case you want to build up a separate library for your new Evolving Object,
you'll need some work - follow what's done in the src/ga dir, used in the
main file BitEA in tutorial/Lesson4 dir.
Or you can wait until we do it :-)
*/

// Miscilaneous include and declaration
#include <iostream>
#include <stdlib.h>
#include "db/DBmanager.h"
//#define _OPENMP
using namespace std;

// eo general include
#include "eo"
// the real bounds (not yet in general eo include)
#include "utils/eoRealVectorBounds.h"

// include here whatever specific files for your representation
// Basically, this should include at least the following

/** definition of representation:
 * class eoSAKe MUST derive from EO<FitT> for some fitness
 */
#include "eoSAKe.h"

/** definition of initilizqtion:
 * class eoSAKeInit MUST derive from eoInit<eoSAKe>
 */
#include "eoSAKeInit.h"

/** definition of evaluation:
 * class eoSAKeEvalFunc MUST derive from eoEvalFunc<eoSAKe>
 * and should test for validity before doing any computation
 * see tutorial/Templates/evalFunc.tmpl
 */
#include "eoSAKeEvalFunc.h"

// GENOTYPE   eoSAKe ***MUST*** be templatized over the fitness

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// START fitness type: double or eoMaximizingFitness if you are maximizing
//                     eoMinimizingFitness if you are minimizing
typedef eoMaximizingFitness MyFitT ;	// type of fitness
// END fitness type
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// Then define your EO objects using that fitness type
typedef eoSAKe<MyFitT> Indi;      // ***MUST*** derive from EO

// create an initializer
#include "make_genotype_SAKe.h"
eoInit<Indi> & make_genotype(eoParser& _parser, eoState&_state, Indi _eo,int tbMin,
                             int tbMax,
                             string pattern)
{
  return do_make_genotype(_parser, _state, _eo,tbMin,tbMax,pattern);
}

// and the variation operaotrs
#include "make_op_SAKe.h"
eoGenOp<Indi>&  make_op(eoParser& _parser, eoState& _state, eoInit<Indi>& _init, int tbMin,int tbMax,
                        double Pme,
                        double Pmb,
                        double dHpMin,
                        double dHpMax)
{
  return do_make_op(_parser, _state, _init,tbMin,tbMax,Pme,Pmb,dHpMin,dHpMax);
}

// Use existing modules to define representation independent routines
// These are parser-based definitions of objects

// how to initialize the population
// it IS representation independent if an eoInit is given
#include <do/make_pop.h>
eoPop<Indi >&  make_pop(eoParser& _parser, eoState& _state, eoInit<Indi> & _init)
{
  return do_make_pop(_parser, _state, _init);
}

// the stopping criterion
#include <do/make_continue.h>
eoContinue<Indi>& make_continue(eoParser& _parser, eoState& _state, eoEvalFuncCounter<Indi> & _eval)
{
  return do_make_continue(_parser, _state, _eval);
}

// outputs (stats, population dumps, ...)
#include <do/make_checkpoint.h>
eoCheckPoint<Indi>& make_checkpoint(eoParser& _parser, eoState& _state, eoEvalFuncCounter<Indi>& _eval, eoContinue<Indi>& _continue)
{
  return do_make_checkpoint(_parser, _state, _eval, _continue);
}

// evolution engine (selection and replacement)
//#include "make_algo_scalar_my.h"
//eoAlgo<Indi>&  make_algo_scalar(eoParser& _parser, eoState& _state, eoEvalFunc<Indi>& _eval, eoContinue<Indi>& _continue,eoQuadOp<Indi>& _cross, float _crate,
//                                eoMonOp<Indi>& _mutate, float _mrate)
//{
//  return do_make_algo_scalar_my(_parser, _state, _eval, _continue, _cross,_crate,_mutate,_mrate);
//}
//eoAlgo<Indi>&  make_algo_scalar(eoParser& _parser, eoState& _state, eoEvalFunc<Indi>& _eval, eoContinue<Indi>& _continue, eoGenOp<Indi>& _op)
//{
//    return do_make_algo_scalar_my(_parser, _state, _eval, _continue, _op);
//}

// simple call to the algo. stays there for consistency reasons
// no template for that one
#include <do/make_run.h>
// the instanciating fitnesses
#include <eoScalarFitness.h>
void run_ea(eoAlgo<Indi>& _ga, eoPop<Indi>& _pop)
{
  do_run(_ga, _pop);
}

// checks for help demand, and writes the status file
// and make_help; in libutils
void make_help(eoParser & _parser);

//#include <utils/eoParallel.h>
//void make_parallel_my(eoParser & _parser){
//	make_parallel(_parser);
//}


//// now use all of the above, + representation dependent things
//int main(int argc, char* argv[])
//{

//  try
//  {
//      eoParser parser(argc, argv);  // for user-parameter reading

//  eoState state;    // keeps all things allocated

//  Rain * rain;
//  int rain_size;
//  DBmanager db;
//  Activation * activations;
//  int activations_size;
//  try {
//  		db.getConnection();
//  		db.executeQueryRain(rain,rain_size);
//  		db.executeQueryActivation(activations,activations_size);
//  		db.disconnect();

//  	} catch (const std::exception &e) {
//  		cerr << e.what() << std::endl;
//  		return 1;
//  	}
//  	for (int i = 0; i < activations_size; ++i) {
//		cout << "Activation Start = " <<"    "<<"  "<< activations[i].getStart().tm_hour<< ":" << activations[i].getStart().tm_min << ":"<< activations[i].getStart().tm_sec << "   " <<activations[i].getStart().tm_mday << "-"<< activations[i].getStart().tm_mon << "-"<< 1900+activations[i].getStart().tm_year << endl;
//		cout << "Activation End = " <<"    "<<"  "<< activations[i].getEnd().tm_hour<< ":" << activations[i].getEnd().tm_min << ":"<< activations[i].getEnd().tm_sec << "   " <<activations[i].getEnd().tm_mday << "-"<< activations[i].getEnd().tm_mon << "-"<< 1900+activations[i].getEnd().tm_year << endl;
//	}



//    // The fitness
//    //////////////
//   eoSAKeEvalFunc<Indi> plainEval(rain,rain_size,activations,activations_size)/* (varType  _anyVariable) */;

//   // turn that object into an evaluation counter
//   eoEvalFuncCounter<Indi> eval(plainEval);

//  // the genotype - through a genotype initializer
//  eoInit<Indi>& init = make_genotype(parser, state, Indi());

//  // Build the variation operator (any seq/prop construct)
//  eoGenOp<Indi>& op = make_op(parser, state, init);


//  //// Now the representation-independent things
//  //
//  // YOU SHOULD NOT NEED TO MODIFY ANYTHING BEYOND THIS POINT
//  // unless you want to add specific statistics to the checkpoint
//  //////////////////////////////////////////////

//  // initialize the population
//  // yes, this is representation indepedent once you have an eoInit
//  eoPop<Indi>& pop   = make_pop(parser, state, init);

//  // stopping criteria
//  eoContinue<Indi> & term = make_continue(parser, state, eval);
//  // output
//  eoCheckPoint<Indi> & checkpoint = make_checkpoint(parser, state, eval, term);
//  // algorithm (need the operator!)
//  eoAlgo<Indi>& ga = make_algo_scalar(parser, state, eval, checkpoint, op);

//  ///// End of construction of the algorithm
//  make_parallel_my(parser);
//  /////////////////////////////////////////
//  // to be called AFTER all parameters have been read!!!
//  //make_help(parser);

//  //// GO
//  ///////
//  // evaluate intial population AFTER help and status in case it takes time
//  apply<Indi>(eval, pop);
//  // if you want to print it out
//   cout << "Initial Population\n";
//   pop.sortedPrintOn(cout);
//   cout << endl;

//   run_ea(ga, pop); // run the ga

//  cout << "Final Population\n";
////  cout << pop.it_best_element().base()->fitness() << endl;
////  cout << *(pop.it_best_element())<< endl;
//  pop.sortedPrintOn(cout);
//  cout << endl;

//  }
//  catch(exception& e)
//  {
//    cout << e.what() << endl;
//  }
//  return 0;
//}