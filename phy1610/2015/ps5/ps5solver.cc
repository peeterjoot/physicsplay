/**
   \file ps5solver.cc
 */
#include "ps5function.h"
#include "mysolver.cc"

/**
   Explicit template instantation.
 */
template class fSolver<ps5function> ;
template class fdfSolver<ps5function> ;
