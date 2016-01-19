/** \file mysolver.h
 */
#if !defined phy1610_ps5_mysolver_h_included
#define phy1610_ps5_mysolver_h_included

#include <gsl/gsl_roots.h>
#include <vector>
#include "integers.h"

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

/**
   Return true for any of:

   solver::newton,
   solver::secant,
   solver::steffenson
 */
inline bool isFdfSolver( solver s )
{
   return s >= solver::newton ;
}

/**
   Return the gsl function pointer for the specified solution method.

   If called for a gsl_root_fdfsolver_type method, that method will be inappropriately
   cast to gsl_root_fsolver_type.

   \param whichSolver [in]
      One of solver::bisection, solver::falsepos, solver::brent.
 */
const gsl_root_fsolver_type * solverToMethod( const solver whichSolver ) ;


/**
   Return the gsl function pointer for the specified solution method.

   If called for a gsl_root_fsolver_type method, that method will be inappropriately
   cast to gsl_root_fdfsolver_type.

   \param whichSolver [in]
      One of solver::newton, solver::secant, solver::steffenson.
 */
const gsl_root_fdfsolver_type * solverToFdfMethod( const solver whichSolver ) ;

/**
   gsl based derivative root solver.
 */
template <class paramType>
class fdfSolver
{
   const gsl_root_fdfsolver_type *  m_T ; ///< gsl function pointer
   gsl_function_fdf                 m_F ; ///< gsl function object
   gsl_root_fdfsolver *             m_s ; ///< gsl handle for root search
   paramType                        m_params ; ///< parameter object and associated functions.

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

      \param err [in]
         Required root precision.

      \retval
         gsl library status code.
    */
   int iterate( const double x0, const Uint max_iter, const double err ) ;
} ;

/**
   gsl based interval based root solver.
 */
template <class paramType>
class fSolver
{
   const gsl_root_fsolver_type *  m_T ; ///< gsl function pointer
   gsl_function                   m_F ; ///< gsl function object
   gsl_root_fsolver *             m_s ; ///< gsl handle for root search
   paramType                      m_params ; ///< parameter object and associated functions.

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
      Attempt to increase the initial interval to find one that brackets the root.

      \param x_min [in|out]
         starting lower bound on the interval.

      \param x_max [in|out]
         starting upper bound on the interval.

      \param iter_max [in]
         maximum number of times to attempt increasing the interval looking for a sign alternation.

      \retval
         true if a bracketing interval was found.
         false if a bracketing interval was not found.
    */
   bool increaseIntervalIfNotBracketed( double & x_min, double & x_max, const Uint iter_max ) ;

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

      \retval
         gsl library status code.
    */
   int iterate( const double x_lo, const double x_hi, const Uint max_iter, const double err ) ;
} ;

/**
   Parameters for running the solver as specified in the problem:
   - varying initial values x0 for x, or for varying starting intervals [0.0,x0], where x0 ranges from 0 to 10 in steps of 0.5.
 */
template <class paramType>
struct solverParams
{
   double m_x0 ;                 ///< initial upper bound for the first interval (fsolver) or root guess (fdfsolver)
   double m_xUpper ;             ///< upper bound for all the intervals (i.e. 10)
   double m_intervalStep ;       ///< step size
   Uint   m_max_iter ;           ///< max number of iterations when running a fsolver method
   Uint   m_max_iter_deriv ;     ///< max number of iterations when running an fdfsolver method
   double m_err ;                ///< desired error for convergence
   double m_intervalXMin ;       ///< lower bound for all the fsolver intervals

   /** set the default values for these parameters */
   solverParams() :
      m_x0{0.5},
      m_xUpper{10.0},
      m_intervalStep{0.5},
      m_max_iter{100},
      m_max_iter_deriv{1000},
      m_err{1e-4},
      m_intervalXMin{0.0}
   {
   }

   void runSolver( const std::vector<solver> & howToSolve ) const ;
} ;

#endif
