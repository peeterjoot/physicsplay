/** \file solverMethod
 */
#include "gslsolver.h"

static const void * solverMethod[] =
{
   (const void *)gsl_root_fsolver_bisection,
   (const void *)gsl_root_fsolver_falsepos,
   (const void *)gsl_root_fsolver_brent,
   (const void *)gsl_root_fdfsolver_newton,
   (const void *)gsl_root_fdfsolver_secant,
   (const void *)gsl_root_fdfsolver_steffenson
} ;

const gsl_root_fsolver_type * solverToMethod( const solver whichSolver )
{
   return (const gsl_root_fsolver_type *)solverMethod[ (int)whichSolver ] ;
}

const gsl_root_fdfsolver_type * solverToFdfMethod( const solver whichSolver )
{
   return (const gsl_root_fdfsolver_type *)solverMethod[ (int)whichSolver ] ;
}
