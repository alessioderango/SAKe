#ifndef MAKE_CONTINUE_MY
#define MAKE_CONTINUE_MY
// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

//-----------------------------------------------------------------------------
// make_continue.h
// (c) Maarten Keijzer, Marc Schoenauer and GeNeura Team, 2000
/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact: todos@geneura.ugr.es, http://geneura.ugr.es
             Marc.Schoenauer@polytechnique.fr
             mkeijzer@dhi.dk
 */
//-----------------------------------------------------------------------------

/*
Contains the templatized version of parser-based choice of stopping criterion
It can then be instantiated, and compiled on its own for a given EOType
(see e.g. in dir ga, ga.cpp)
*/

// Continuators - all include eoContinue.h
#include <eoCombinedContinue.h>
#include <eoGenContinue.h>
#include <eoSteadyFitContinue.h>
#include <eoEvalContinue.h>
#include <eoFitContinue.h>
#ifndef _MSC_VER
#include <eoCtrlCContinue.h>  // CtrlC handling (using 2 global variables!)
#endif

  // also need the parser and param includes
#include <utils/eoParser.h>
#include <utils/eoState.h>
#include "Regression/eoGenContinueMy.h"


/////////////////// the stopping criterion ////////////////
 /**
 * @ingroup Builders
 */
template <class Individual>
eoCombinedContinue<Individual> * make_combinedContinue(eoCombinedContinue<Individual> *_combined, eoContinue<Individual> *_cont)
{
  if (_combined)                   // already exists
    _combined->add(*_cont);
  else
    _combined = new eoCombinedContinue<Individual>(*_cont);
  return _combined;
}

/**
 *
 * @ingroup Builders
 */
template <class Individual>
eoContinue<Individual> & do_make_continue_my(eoParser& _parser, eoState& _state, eoEvalFuncCounter<Individual> & _eval, eoGenContinueMy<Individual> *stop)
{
  //////////// Stopping criterion ///////////////////
  // the combined continue - to be filled
  eoCombinedContinue<Individual> *continuator = NULL;


  _state.storeFunctor(stop);
  // and "add" to combined
//  continuator = make_combinedContinue<Individual>(continuator, stop);
  // for each possible criterion, check if wanted, otherwise do nothing

  // First the eoGenContinue - need a default value so you can run blind
  // but we also need to be able to avoid it <--> 0
  eoValueParam<unsigned>& maxGenParam = _parser.getORcreateParam(unsigned(100), "maxGen", "Maximum number of generations () = none)",'G',"Stopping criterion");

    if (maxGenParam.value()) // positive: -> define and store
      {
        eoGenContinue<Individual> *genCont = new eoGenContinue<Individual>(maxGenParam.value());
        _state.storeFunctor(genCont);
        // and "add" to combined
        continuator = make_combinedContinue<Individual>(continuator, genCont);
      }

  // the steadyGen continue - only if user imput
  eoValueParam<unsigned>& steadyGenParam = _parser.createParam(unsigned(100), "steadyGen", "Number of generations with no improvement",'s', "Stopping criterion");
  eoValueParam<unsigned>& minGenParam = _parser.createParam(unsigned(0), "minGen", "Minimum number of generations",'g', "Stopping criterion");
    if (_parser.isItThere(steadyGenParam))
      {
        eoSteadyFitContinue<Individual> *steadyCont = new eoSteadyFitContinue<Individual>
          (minGenParam.value(), steadyGenParam.value());
        // store
        _state.storeFunctor(steadyCont);
        // add to combinedContinue
        continuator = make_combinedContinue<Individual>(continuator, steadyCont);
      }

  // Same thing with Eval - but here default value is 0
  eoValueParam<unsigned long>& maxEvalParam
      = _parser.getORcreateParam((unsigned long)0, "maxEval",
                                 "Maximum number of evaluations (0 = none)",
                                 'E', "Stopping criterion");

    if (maxEvalParam.value()) // positive: -> define and store
      {
        eoEvalContinue<Individual> *evalCont = new eoEvalContinue<Individual>(_eval, maxEvalParam.value());
        _state.storeFunctor(evalCont);
        // and "add" to combined
        continuator = make_combinedContinue<Individual>(continuator, evalCont);
      }
    /*
  // the steadyEval continue - only if user imput
  eoValueParam<unsigned>& steadyGenParam = _parser.createParam(unsigned(100), "steadyGen", "Number of generations with no improvement",'s', "Stopping criterion");
  eoValueParam<unsigned>& minGenParam = _parser.createParam(unsigned(0), "minGen", "Minimum number of generations",'g', "Stopping criterion");
    if (_parser.isItThere(steadyGenParam))
      {
        eoSteadyGenContinue<Individual> *steadyCont = new eoSteadyFitContinue<Individual>
          (minGenParam.value(), steadyGenParam.value());
        // store
        _state.storeFunctor(steadyCont);
        // add to combinedContinue
        continuator = make_combinedContinue<Individual>(continuator, steadyCont);
      }
    */
    // the target fitness
    eoFitContinue<Individual> *fitCont;
    eoValueParam<double>& targetFitnessParam = _parser.createParam(double(0.0), "targetFitness", "Stop when fitness reaches",'T', "Stopping criterion");
    if (_parser.isItThere(targetFitnessParam))
      {
        fitCont = new eoFitContinue<Individual>
          (targetFitnessParam.value());
        // store
        _state.storeFunctor(fitCont);
        // add to combinedContinue
        continuator = make_combinedContinue<Individual>(continuator, fitCont);
      }

#ifndef _MSC_VER
    // the CtrlC interception (Linux only I'm afraid)
    eoCtrlCContinue<Individual> *ctrlCCont;
    eoValueParam<bool>& ctrlCParam = _parser.createParam(false, "CtrlC", "Terminate current generation upon Ctrl C",'C', "Stopping criterion");
    if (ctrlCParam.value())
      {
        ctrlCCont = new eoCtrlCContinue<Individual>;
        // store
        _state.storeFunctor(ctrlCCont);
        // add to combinedContinue
        continuator = make_combinedContinue<Individual>(continuator, ctrlCCont);
      }
#endif

    // now check that there is at least one!
    if (!continuator)
      throw std::runtime_error("You MUST provide a stopping criterion");
  // OK, it's there: store in the eoState
  _state.storeFunctor(continuator);

  // and return
    return *continuator;
}


#endif // MAKE_CONTINUE_MY

