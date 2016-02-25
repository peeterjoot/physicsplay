#include <stdio.h>
#include <cassert>
#include <cmath>
#include <limits>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include "minimizer.h"
#include "gslhelper.h"

void f_min_one( const double a, const double b, minimizerParameters & p, oneMinimumResult & r )
{
   gsl_function F ;
   r.m_initial_a  = a ;
   r.m_initial_b  = b ;
   r.m_a          = a ;
   r.m_b          = b ;
   F.function     = &p.m_f.function ;
   F.params       = &p.m_f ;
   r.m_xmin       = (r.m_b + r.m_a)/2 ;

   // turn off the print and abort on error behavior, and use explicit error checking.
   gsl_set_error_handler_off() ;

   const gsl_min_fminimizer_type * T = gsl_min_fminimizer_brent ;
   gsl_min_fminimizer * s = gsl_min_fminimizer_alloc( T ) ;

   if ( !s )
   {
      throw std::bad_alloc() ;
   }

   r.m_solvername = gsl_min_fminimizer_name( s ) ;

   r.m_status = gsl_min_fminimizer_set( s, &F, r.m_xmin, r.m_a, r.m_b ) ;
   if ( !r.m_status )
   {
      if ( p.m_verbose )
      {
         printf( "using %s method\n", gsl_min_fminimizer_name(s) ) ;

         printf( "%5s [%9s, %9s] %9s %9s\n",
                 "r.m_iter", "lower", "upper", "min", "err(est)" ) ;

         printf( "%5d [%.7f, %.7f] %.7f %.7f\n",
                 (int)r.m_iter, r.m_a, r.m_b, r.m_xmin, r.m_b - r.m_a ) ;
      }

      do
      {
         r.m_iter++ ;
         r.m_status = gsl_min_fminimizer_iterate( s ) ;
         if ( r.m_status )
         {
            break ;
         }

         r.m_xmin = gsl_min_fminimizer_x_minimum( s ) ;
         r.m_a = gsl_min_fminimizer_x_lower( s ) ;
         r.m_b = gsl_min_fminimizer_x_upper( s ) ;

         r.m_status = min_test_interval( r.m_a, r.m_b, p.m_abserr, p.m_relerr ) ;

         if ( isGslStatusFatal( r.m_status ) )
         {
            break ;
         }

         if ( p.m_verbose )
         {
            printf( "%5d [%.7f, %.7f] "
                    "%.7f %.7f\n", (int)r.m_iter, r.m_a, r.m_b, r.m_xmin, r.m_b - r.m_a ) ;
         }
      } while ( r.m_status == GSL_CONTINUE && r.m_iter < p.m_max_iter ) ;
   }

   r.m_strerror = gsl_strerror( r.m_status ) ;

   gsl_min_fminimizer_free( s ) ;

   if ( !r.m_status )
   {
      r.m_fmin = p.m_f( r.m_xmin ) ;
   }
}

void minimizerResults::f_min_all( minimizerParameters & p )
{
#if 0
   /*

      Attempt 1:

      Suppose that we've found one of m=A or m=B for something with at least two
      local minimums:

                              *
                        ******
      ***              *
        ****      **** *
           ****  **   *
               *
      a        A      B  b
      | (1) | (2) | (3) | (4) |

      Carve the both of the [a,m], and [m,b] intervals into a pair of intervals, and look for other
      local minimums in these subdivisions.  This depends a bit on luck, since you could imagine two
      local minimums very close to each other.  What if, for example, there was a local minimum in the
      interval right next to the global minimum.  Would the minimizer return the global minimum that's
      sitting on end point of such an interval?

      Imagine for example, we were seeking the min for a parabola y = (x-2)^2, and find the x=2 min in the [0,4]
      interval.  If we then look for other local mins (not knowing it's a parabola with only one global=local min)
      will we get back a local min from Brent's method at x=2 with a [1,2] search interval?

      The answer appears to be no.  Instead such a search appears to result in status = GSL_EINVAL (invalid argument supplied by user)
      so gsl is already doing what we want, not treating a min found exactly on the end point of the interval as valid.  This is
      convienent, allowing us to just discard any unsuccessful min search.

   */
   {
      oneMinimumResult r ;

      double a = p.m_a ;
      double b = p.m_b ;

      f_min_one( a, b, p, r ) ;

      // start with one iteration looking for either a local or global minimum:
      m_rv.push_back( r ) ;
      if ( r.m_status )
      {
         // If this first min attempt didn't work, we can't do much more
         return ;
      }
   }

   {
      double a = p.m_a ;
      double b = r.m_min ;
      double midpoint = (a + b)/2 ;
      assert( a <= midpoint ) ;
      assert( midpoint <= b ) ;

      oneMinimumResult r1 ;
      oneMinimumResult r2 ;

      f_min_one( a, midpoint, p, r1 ) ;
      f_min_one( midpoint, b, p, r2 ) ;

      if ( !r1.m_status )
      {
         m_rv.push_back( r1 ) ;
      }

      if ( !r2.m_status )
      {
         m_rv.push_back( r2 ) ;
      }
   }

   {
      double a = r.m_min ;
      double b = p.m_b ;
      double midpoint = (a + b)/2 ;
      assert( a <= midpoint ) ;
      assert( midpoint <= b ) ;

      oneMinimumResult r1 ;
      oneMinimumResult r2 ;

      f_min_one( a, midpoint, p, r1 ) ;
      f_min_one( midpoint, b, p, r2 ) ;

      if ( !r1.m_status )
      {
         m_rv.push_back( r1 ) ;
      }

      if ( !r2.m_status )
      {
         m_rv.push_back( r2 ) ;
      }
   }
#else
   /*
      Attempt 2:

   */
   {
      double a = p.m_a ;
      double b = p.m_b ;
      double c = (a + b)/2 ;

      oneMinimumResult r1 ;
      oneMinimumResult r2 ;

      f_min_one( a, c, p, r1 ) ;
      f_min_one( c, b, p, r2 ) ;

      if ( !r1.m_status )
      {
         m_rv.push_back( r1 ) ;
      }
      else
      {
         oneMinimumResult r3 ;
         oneMinimumResult r4 ;
         double mid = (a + c)/2 ;

         f_min_one( a, mid, p, r3 ) ;
         f_min_one( mid, c, p, r4 ) ;

         if ( !r3.m_status )
         {
            m_rv.push_back( r3 ) ;
         }

         if ( !r4.m_status )
         {
            m_rv.push_back( r4 ) ;
         }
      }

      if ( !r2.m_status )
      {
         m_rv.push_back( r2 ) ;
      }
      else
      {
         oneMinimumResult r3 ;
         oneMinimumResult r4 ;
         double mid = (c + b)/2 ;

         f_min_one( c, mid, p, r3 ) ;
         f_min_one( mid, b, p, r4 ) ;

         if ( !r3.m_status )
         {
            m_rv.push_back( r3 ) ;
         }

         if ( !r4.m_status )
         {
            m_rv.push_back( r4 ) ;
         }
      }
   }
#endif
}

void minimizerResults::compareLocalMinimums()
{
   // skip this array search if already done.
   if ( m_minIndex < 0 )
   {
      assert( m_maxIndex == (Sint)-1 ) ;

      constexpr double inf{ std::numeric_limits<double>::infinity() } ;
      double fMinValue{ -inf } ;
      double fMaxValue{ inf } ;

      size_t sz = m_rv.size() ;
      assert( sz <= 2 ) ;
      assert( sz >= 1 ) ;

      for ( size_t i = 0 ; i < sz ; i++ )
      {
         if ( !m_rv[i].m_status )
         {
            double f = m_rv[i].m_fmin ;

            if ( f > fMinValue )
            {
               fMinValue = f ;
               m_minIndex = i ;
            }

            if ( f < fMaxValue )
            {
               fMaxValue = f ;
               m_maxIndex = i ;
            }
         }
      }
   }

   assert( m_minIndex > 0 ) ;
   assert( m_maxIndex > 0 ) ;
}

double minimizerResults::diff() const
{
   compareLocalMinimums() ;

   double xmin = m_rv[m_minIndex].m_xmin - m_rv[m_maxIndex].m_xmin ;

   return xmin ;
}

double minimizerResults::xmin() const
{
   compareLocalMinimums() ;

   return m_rv[m_minIndex].m_xmin ;
}

double minimizerResults::xmax() const
{
   compareLocalMinimums() ;

   return m_rv[m_maxIndex].m_xmin ;
}

double minimizerResults::fmin() const
{
   compareLocalMinimums() ;

   return m_rv[m_minIndex].m_fmin ;
}

double minimizerResults::fmax() const
{
   compareLocalMinimums() ;

   return m_rv[m_maxIndex].m_fmin ;
}
