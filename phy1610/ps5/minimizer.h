/** \file minimizer.h
 */
#if !defined phy1610_minimizer_h_included
#define phy1610_minimizer_h_included

#include "integers.h"
#include <string>

/**
   Output parameters from a gsl minimizer run.
 */
struct minimizerResults
{
   std::string m_solvername ; ///< gsl_root_fdfsolver_name().
   int         m_status ;     ///< The last successful or unsuccessful gsl function return code.
   std::string m_strerror ;   ///< gsl_strerror() output for m_status.
   bool        m_converged ;  ///< did the iteration converge in the specfied number of iterations.
   Uint        m_iter ;       ///< the final iteration count at the point of convergence, error, or non-convergence.
   double      m_a ;          ///< final lower bound for the bracket
   double      m_b ;          ///< final upper bound for the bracket

public:
   minimizerResults() :
      m_solvername{},
      m_status{0},
      m_strerror{},
      m_converged{false},
      m_iter{0},
      m_a{0.0},
      m_b{0.0}
   {
   }
} ;

/**
   Input parameters for gsl minimizer run
 */
struct minimizerParameters
{
   const Uint     m_max_iter ;  ///< Maximum number of iterations before giving up.
   const double   m_abserr ;    ///< the absolute error criteria for convergence.
   const double   m_relerr ;    ///< the relative error criteria for convergence.
   const bool     m_verbose ;   ///< verbose output
   const double   m_a ;         ///< initial lower bound for the bracket
   const double   m_b ;         ///< initial upper bound for the bracket

   minimizerParameters( const Uint     max_iter = 100,
                        const double   abserr = 0.001,
                        const double   relerr = 0,
                        const bool     verbose = true,
                        const double   a = 0.0,
                        const double   b = 6.0 ) :
         m_max_iter{max_iter},
         m_abserr{abserr},
         m_relerr{relerr},
         m_verbose{verbose},
         m_a{a},
         m_b{b}
   {
   }
} ;

#endif
