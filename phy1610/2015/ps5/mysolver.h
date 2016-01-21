/**
   \file mysolver.h
 */
#if !defined phy1610_ps5_mysolver_h_included
#define phy1610_ps5_mysolver_h_included

#include <gsl/gsl_roots.h>
#include <vector>
#include <string>
#include "integers.h"

/**
   interval and derivative solver methods supplied by gsl
 */
enum class solver
{
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
   Output parameters for gsl solver iteration.
 */
struct iterationResults
{
   std::string m_solvername ; ///< gsl_root_fdfsolver_name().
   bool        m_converged ;  ///< did the iteration converge in the specfied number of iterations.
   Uint        m_iter ;       ///< The number of iterations performed before root is found or we give up.
   int         m_status ;     ///< The last successful or unsuccessful gsl function return code.
   std::string m_strerror ;   ///< gsl_strerror() output for m_status.

   iterationResults() :
      m_solvername{},
      m_converged{false},
      m_iter{0},
      m_status{0},
      m_strerror{}
   {
   }
} ;

/**
   Input parameters for gsl solver iteration.
 */
struct iterationParameters
{
   const Uint     m_max_iter ;  ///< Maximum number of iterations before giving up.
   const double   m_relerr ;    ///< the relative error criteria for convergence.
   const double   m_abserr ;    ///< the absolute error criteria for convergence.
   const bool     m_verbose ;   ///< verbose output

   iterationParameters( const Uint     max_iter,
                        const double   relerr,
                        const double   abserr,
                        const bool     verbose ) :
         m_max_iter{max_iter},
         m_relerr{relerr},
         m_abserr{abserr},
         m_verbose{verbose}
   {
   }
} ;

/**
   Input parameters for an gsl fsolver iteration.
 */
struct intervalIterationInputs : public iterationParameters
{
   const double   m_xLo ;        ///< Initial lower bound for the interval that contains the root (or at least contains a zero crossing)
   const double   m_xHi ;        ///< Initial upper bound for the interval that contains the root (or at least contains a zero crossing)

   intervalIterationInputs( const double   xLo,
           const double   xHi,
           const Uint     max_iter,
           const double   relerr,
           const double   abserr,
           const bool     verbose = false ) :
        iterationParameters( max_iter, relerr, abserr, verbose ),
        m_xLo{xLo},
        m_xHi{xHi}
   {
   }
} ;

/**
   Output parameters for an gsl fsolver iteration.
 */
struct intervalIterationResults : public iterationResults
{
   double      m_xLo ;        ///< Final lower bound for the interval
   double      m_xHi ;        ///< Final upper bound for the interval
   double      m_r ;          ///< The root at the conclusion of the iteration

   intervalIterationResults() :
      iterationResults{},
      m_xLo{0},
      m_xHi{0},
      m_r{0}
   {
   }
} ;

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

   /** Output parameters for an gsl fdf solver iteration.
    */
   struct results : public iterationResults
   {
      double      m_x ;                ///< The point at which the root was found (or the last place we looked).
      double      m_xPrev ;            ///< The previous iteration point when finished.
      Uint        m_numBisections ;    ///< For iterateBracketed, the number of bisection iterations.

      results() :
         iterationResults{},
         m_x{0},
         m_xPrev{0}
      {
      }
   } ;

   /**
      Input parameters for an gsl fdf solver iteration.
    */
   struct inputs : public iterationParameters
   {
      const double   m_x0 ;        ///< Initial guess for the root.

      inputs( const double   x0,
              const Uint     max_iter,
              const double   relerr,
              const double   abserr,
              const bool     verbose = false ) :
           iterationParameters( max_iter, relerr, abserr, verbose ),
           m_x0{x0}
      {
      }
   } ;

   /**
      Perform the root solution iteration.

      \param p [in]
         Input parameters for the root solving iteration.

      \retval
         Output parameters for the root solving iteration.
    */
   void iterate( const inputs & p, results & r ) ;

   /**
      Perform the root solution iteration, but use bisection at any point that the
      gsl iteration takes the root outside of the 

      \param p [in]
         Input parameters for the root solving iteration.

      \retval
         Output parameters for the root solving iteration.
    */
   void iterateBracketed( const intervalIterationInputs & p, intervalIterationResults & r ) ;
} ;

/**
   Attempt to increase the initial interval to find one that brackets the root.

   \param f [in]
      Parameter function object.

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
template <class paramType>
bool increaseIntervalIfNotBracketed( const paramType & f, double & x_min, double & x_max, const Uint iter_max ) ;

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

   using inputs = intervalIterationInputs ;
   using results = intervalIterationResults ;

   /**
      Perform the root solution iteration.

      \param p [in]
         Input parameters for the root solving iteration.

      \retval
         Output parameters for the root solving iteration.
    */
   void iterate( const inputs & p, results & r ) ;
} ;

#endif
