/**
   \file ps5solver.h
 */
#if !defined phy1610_psN_ps5solver_h_included
#define phy1610_psN_ps5solver_h_included

#include "ps5function.h"
#include "mysolver.h"

/**
   This template is explicit instantatiated in ps5solver.cc
 */
extern template class fSolver<ps5function> ;
extern template class fdfSolver<ps5function> ;

#endif
