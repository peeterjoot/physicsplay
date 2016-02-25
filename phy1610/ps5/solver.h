/** \file solver.h
 */
#if !defined phy1610_solver_h_included
#define phy1610_solver_h_included

#include <gsl/gsl_roots.h>
#include <vector>
#include <string>
#include "integers.h"

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
   double      m_x ;          ///< The root at the conclusion of the iteration
   double      m_xPrev ;      ///< The previous iteration point when finished (for fdf solvers)

   iterationResults() :
      m_solvername{},
      m_converged{false},
      m_iter{0},
      m_status{0},
      m_strerror{},
      m_x{0.0},
      m_xPrev{0}
   {
   }
} ;

/**
   Input parameters for gsl solver iteration.
 */
struct iterationParameters
{
   const Uint     m_max_iter ;  ///< Maximum number of iterations before giving up.
   const double   m_abserr ;    ///< the absolute error criteria for convergence.
   const double   m_relerr ;    ///< the relative error criteria for convergence.
   const bool     m_verbose ;   ///< verbose output

   iterationParameters( const Uint     max_iter,
                        const double   abserr,
                        const double   relerr,
                        const bool     verbose ) :
         m_max_iter{max_iter},
         m_abserr{abserr},
         m_relerr{relerr},
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
                            const double   abserr,
                            const double   relerr,
                            const bool     verbose = false ) :
        iterationParameters( max_iter, abserr, relerr, verbose ),
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
   double      m_xLo ;              ///< Final lower bound for the interval
   double      m_xHi ;              ///< Final upper bound for the interval
   Uint        m_numBisections ;    ///< For iterateBracketed, the number of bisection iterations.

   intervalIterationResults() :
      iterationResults{},
      m_xLo{0.0},
      m_xHi{0.0},
      m_numBisections{0}
   {
   }
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
   paramType &                    m_params ; ///< parameter object and associated functions.

public:
   /**
      Initialize and allocation resources for root solving algorithm.
    */
   fSolver( paramType & p ) ;

   /**
      Deallocate resources.
    */
   ~fSolver( ) ;

   /**
      Perform the root solution iteration.

      \param p [in]
         Input parameters for the root solving iteration.

      \retval
         Output parameters for the root solving iteration.
    */
   void iterate( const intervalIterationInputs & p, intervalIterationResults & r ) ;
} ;

#endif
