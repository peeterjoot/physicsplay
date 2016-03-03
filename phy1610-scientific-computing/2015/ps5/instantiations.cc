/**
   \file instantiations.cc
 */
#include "ps5function.h"
#include "squareRootTwoFunction.h"
#include "gslsolver.cc"

/**
   Explicit template instantation.
 */
template class fSolver<ps5function> ;
template class fdfSolver<ps5function> ;

template
bool increaseIntervalIfNotBracketed( const ps5function & f, double & x_min, double & x_max, const Uint max ) ;
template
bool decreaseIntervalIfNotBracketed( const ps5function & f, double & x_min, double & x_max, const Uint max ) ;

template class fSolver<squareRootTwoFunction> ;
template class fdfSolver<squareRootTwoFunction> ;

template
bool increaseIntervalIfNotBracketed( const squareRootTwoFunction & f, double & x_min, double & x_max, const Uint max ) ;
template
bool decreaseIntervalIfNotBracketed( const squareRootTwoFunction & f, double & x_min, double & x_max, const Uint max ) ;

