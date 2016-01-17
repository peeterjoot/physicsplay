/** \file mysolver.h
 */
#if !defined phy1610_ps5_mysolver_h_included
#define phy1610_ps5_mysolver_h_included

#include <gsl/gsl_roots.h>

/**
   interval and derivative solver methods supplied by gsl
 */
enum class solver
{
   undefined,
   bisection,
   falsepos,
   brent,
   newton,
   secant,
   steffenson
} ;

inline bool isFdfSolver( solver s )
{
   return s >= solver::newton ;
}

/**
   gsl based derivative root solver.
 */
class fdfSolver
{
   const gsl_root_fdfsolver_type *  T ;
   gsl_function_fdf                 F ;
   gsl_root_fdfsolver *             s ;

public:
   /**
      Initialize and allocation resources for root solving algorithm.
    */
   fdfSolver( const solver whichSolver ) ;

   /**
      Deallocate resources.
    */
   ~fdfSolver() ;

   /**
      Perform the root solution iteration.

      \param x0 [in]
         Initial guess.

      \param max_iter [in]
         Abort iteration if not finished in this many iterations.

      \param r_expected [in]
         Expected root (for informational purposes in verbose print loop).

      \param err [in]
         Required root precision.
    */
   int iterate( const double x0, const Uint max_iter, const double r_expected, const double err ) ;
} ;

/**
   gsl based interval based root solver.
 */
class fSolver
{
   const gsl_root_fsolver_type *  T ;
   gsl_function                   F ;
   gsl_root_fsolver *             s ;

public:
   /**
      Initialize and allocation resources for root solving algorithm.
    */
   fSolver( const solver whichSolver ) ;

   /**
      Deallocate resources.
    */
   ~fSolver() ;

   /**
      Perform the root solution iteration.

      \param x_lo [in]
         Initial lower bound for the interval that contains the root.

      \param x_hi [in]
         Initial upper bound for the interval that contains the root.

      \param max_iter [in]
         Abort iteration if not finished in this many iterations.

      \param r_expected [in]
         Expected root (for informational purposes in verbose print loop).

      \param err [in]
         Required root precision.
    */
   int iterate( const double x_lo, const double x_hi, const Uint max_iter, const double r_expected, const double err ) ;
} ;

#endif
