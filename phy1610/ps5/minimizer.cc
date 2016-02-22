#include <stdio.h>
#include <cmath>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include "minimizer.h"
#include "gslhelper.h"


void f_min_all( minimizerParameters & p, minimizerResults & r )
{
   gsl_function F ;
   r.m_a          = p.m_a ;
   r.m_b          = p.m_b ;
   F.function     = &p.m_f.function ;
   F.params       = &p.m_f ;
   r.m_min = (r.m_b + r.m_a)/2 ;

   // turn off the print and abort on error behavior, and use explicit error checking.
   gsl_set_error_handler_off() ;

   const gsl_min_fminimizer_type * T = gsl_min_fminimizer_brent ;
   gsl_min_fminimizer * s = gsl_min_fminimizer_alloc( T ) ;

   if ( !s )
   {
      throw std::bad_alloc() ;
   }

   r.m_status = gsl_min_fminimizer_set( s, &F, r.m_min, r.m_a, r.m_b ) ;
   if ( !r.m_status )
   {
      if ( p.m_verbose )
      {
         printf( "using %s method\n", gsl_min_fminimizer_name (s) ) ;

         printf( "%5s [%9s, %9s] %9s %9s\n",
                 "r.m_iter", "lower", "upper", "min", "err(est)" ) ;

         printf( "%5d [%.7f, %.7f] %.7f %.7f\n",
                 (int)r.m_iter, r.m_a, r.m_b, r.m_min, r.m_b - r.m_a ) ;
      }

      do
      {
         r.m_iter++ ;
         r.m_status = gsl_min_fminimizer_iterate( s ) ;
         if ( r.m_status )
         {
            break ;
         }

         r.m_min = gsl_min_fminimizer_x_minimum( s ) ;
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
                    "%.7f %.7f\n", (int)r.m_iter, r.m_a, r.m_b, r.m_min, r.m_b - r.m_a ) ;
         }
      } while ( r.m_status == GSL_CONTINUE && r.m_iter < p.m_max_iter ) ;
   }

   r.m_strerror = gsl_strerror( r.m_status ) ;

   gsl_min_fminimizer_free( s ) ;
}
