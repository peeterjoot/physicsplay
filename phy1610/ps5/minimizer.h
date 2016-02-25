/** \file minimizer.h
 */
#if !defined phy1610_minimizer_h_included
#define phy1610_minimizer_h_included

#include "integers.h"
#include <string>
#include <vector>
#include <cmath>

/**
   Output parameters from a gsl minimizer run.
 */
struct oneMinimumResult
{
   std::string m_solvername ; ///< gsl_min_fminimizer_name().
   int         m_status ;     ///< The last successful or unsuccessful gsl function return code.
   std::string m_strerror ;   ///< gsl_strerror() output for m_status.
   bool        m_converged ;  ///< did the iteration converge in the specfied number of iterations.
   Uint        m_iter ;       ///< the final iteration count at the point of convergence, error, or non-convergence.
   double      m_initial_a ;  ///< initial lower bound for the bracket
   double      m_initial_b ;  ///< initial upper bound for the bracket
   double      m_a ;          ///< final lower bound for the bracket
   double      m_b ;          ///< final upper bound for the bracket
   double      m_xmin ;       ///< final position value found by the min search
   double      m_fmin ;       ///< value of the function at m_xmin, provided m_status is not an error.

public:
   oneMinimumResult() :
      m_solvername{},
      m_status{},
      m_strerror{},
      m_converged{},
      m_iter{},
      m_initial_a{},
      m_initial_b{},
      m_a{},
      m_b{},
      m_xmin{}
   {
   }
} ;

/**
   Interval related parameters for gsl minimizer run.
 */
struct minimizerParameters
{
   const Uint              m_max_iter ;   ///< Maximum number of iterations before giving up.
   const double            m_abserr ;     ///< the absolute error criteria for convergence.
   const double            m_relerr ;     ///< the relative error criteria for convergence.
   const bool              m_verbose ;    ///< verbose output
   double                  m_a ;          ///< initial lower bound for the bracket
   double                  m_b ;          ///< initial upper bound for the bracket

   minimizerParameters( const double   a,
                        const double   b,
                        const Uint     max_iter = 100,
                        const double   abserr   = 1e-6,
                        const double   relerr   = 1e-6,
                        const bool     verbose  = false ) :
         m_max_iter{max_iter},
         m_abserr{abserr},
         m_relerr{relerr},
         m_verbose{verbose},
         m_a{a},
         m_b{b}
   {
   }
} ;

/**
   Specific results for each minimum that is found, and aggregate info about the biggest and smallest minimum found.
 */
class minimizerResults
{
   Sint    m_minIndex ;                 ///< vector postion for the smallest local minimum
   Sint    m_maxIndex ;                 ///< vector postion for the largest local minimum

   /**
      Go through results array and see which of the local min found is the local vs global min
      This also allows the determination of the difference between the two (if more than one).

      These results are cached so that diff(), xmin(), ... can all consume this lookup.
    */
   void compareLocalMinimums() ;

public:
   std::vector<oneMinimumResult> m_rv ; ///< iteration counts, minimum value, and other info for each min found.

   minimizerResults() :
      m_minIndex{(Sint)-1},
      m_maxIndex{(Sint)-1},
      m_rv{}
   {
   }

   /**
      difference in x position of the smallest local minimum compared to the largest local minimum
    */
   double diff() ;

   /**
      position of the smallest local minimum found
    */
   double xmin() ;

   /**
      position of the largest local minimum found
    */
   double xmax() ;

   /**
      value of the function at the position of the smallest local minimum found
    */
   double fmin() ;

   /**
      value of the function at the position of the largest local minimum found
    */
   double fmax() ;
} ;

/**
   Search for a pair of local and global minimums using the 1D Brent's method gsl implementation.

   The partition search strategy used in this function is tailored to the ps5 "spring function",
   which is known to have one or two local minimums.  A plot of that function, it's derivative
   and the sign of that derivative, shows that the two minimums appear to be nicely
   separated, one in the left half of the [0,0.5] interval of interest and one on the right.

   Because we are specifically looking for one or two (nicely separated) local minimums
   the interval is subdivided successively.  For each side, if a local minumum is found, it
   is recorded in the results vector, and no further search is performed
   on that side of the interval.  If a local minimum is not found on a side, then it is
   subdivided once more and a further search is performed in each of the remaining quarter interval
   partitions.

   This method works nicely for both the very low mass case and the larger mass case where two
   minimums still exist (as we increase the mass enough, one of the minumums vanish).
 */
template <typename gslParams>
void f_min_all( const gslParams &            f,
                const minimizerParameters &  p,
                minimizerResults &           results ) ;

#endif
