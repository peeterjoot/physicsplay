/**
   \file mysolver.cc
 */

#include <new>
#include <iostream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include <stdio.h>
#include <cmath>
#include <cassert>
#include "integers.h"
#include "mysolver.h"
#include "signof.h"

template <class paramType>
fdfSolver<paramType>::fdfSolver( const solver whichSolver ) : m_T( solverToFdfMethod( whichSolver ) ), m_params{}
{
   m_F.f = paramType::function ;
   m_F.df = paramType::derivative ;
   m_F.fdf = paramType::functionAndDerivative ;
   m_F.params = &m_params ;

   // turn off the print and abort on error behavior
   gsl_set_error_handler_off() ;

   m_s = gsl_root_fdfsolver_alloc( m_T ) ;
   if ( !m_s )
   {
      throw std::bad_alloc() ;
   }
}

template <class paramType>
fdfSolver<paramType>::~fdfSolver()
{
   gsl_root_fdfsolver_free( m_s ) ;
}

template <class paramType>
void fdfSolver<paramType>::iterate( const derivativeIterationInputs & p, derivativeIterationResults & r )
{
   const double r_expected { m_params.expectedRoot() } ;

   r.m_xPrev      = p.m_x0 ;
   r.m_x          = p.m_x0 ;
   r.m_status     = gsl_root_fdfsolver_set( m_s, &m_F, r.m_xPrev ) ;
   r.m_solvername = gsl_root_fdfsolver_name( m_s ) ;

   if ( p.m_verbose )
   {
      printf( "%5s %9s %10s %9s\n",
              "iter", "root", "err", "err(est)" ) ;
   }

   if ( !r.m_status )
   {
      do {
         r.m_iter++ ;

         // Can return GSL_EBADFUNC, GSL_EZERODIV (singular value or divide by zero)
         r.m_status = gsl_root_fdfsolver_iterate( m_s ) ;
         if ( isGslStatusFatal( r.m_status ) )
         {
            break ;
         }

         r.m_xPrev = r.m_x ;
         r.m_x = gsl_root_fdfsolver_root( m_s ) ;

         // Option: could potentially also (or instead) have a gsl_root_test_residual based exit criteria.
         r.m_status = root_test_delta( r.m_x, r.m_xPrev, p.m_abserr, p.m_relerr ) ;
         if ( isGslStatusFatal( r.m_status ) )
         {
            break ;
         }

         if ( p.m_verbose )
         {
            printf( "%5d %10.7f %+10.7f %10.7f\n",
                    (int)r.m_iter, r.m_x, r.m_x - r_expected, r.m_x - r.m_xPrev ) ;
         }

      } while ( r.m_status == GSL_CONTINUE && r.m_iter < p.m_max_iter ) ;

      if ( r.m_status == GSL_SUCCESS )
      {
         r.m_converged = true ;
      }
   }

   r.m_strerror = gsl_strerror( r.m_status ) ;
}

template <class paramType>
void fdfSolver<paramType>::iterateBracketed( const intervalIterationInputs & p, intervalIterationResults & r )
{
   const double r_expected { m_params.expectedRoot() } ;

   r.m_xPrev      = p.m_xLo ;
   r.m_xLo        = p.m_xLo ;
   r.m_xHi        = p.m_xHi ;
   r.m_x          = p.m_xLo ;
   r.m_status     = gsl_root_fdfsolver_set( m_s, &m_F, r.m_xPrev ) ;
   r.m_solvername = gsl_root_fdfsolver_name( m_s ) ;

   if ( p.m_maxExpansionIterations )
   {
      increaseIntervalIfNotBracketed( m_params, r.m_xLo, r.m_xHi, p.m_maxExpansionIterations ) ;
   }

   if ( p.m_maxSubDivisions > 1 )
   {
      decreaseIntervalIfNotBracketed( m_params, r.m_xLo, r.m_xHi, p.m_maxSubDivisions ) ;
   }

   if ( p.m_verbose )
   {
      printf( "%5s [%9s, %9s] %9s %10s %9s\n",
              "iter", "lower", "upper", "root", "err", "err(est)" ) ;
   }

   if ( !r.m_status )
   {
      double fl { m_params( r.m_xLo ) } ;
      //double fh { m_params( r.m_xHi ) } ;

      do {

         r.m_iter++ ;

         r.m_status = gsl_root_fdfsolver_iterate( m_s ) ;
         if ( isGslStatusFatal( r.m_status ) )
         {
            break ;
         }

         r.m_xPrev = r.m_x ;
         r.m_x = gsl_root_fdfsolver_root( m_s ) ;
         if ( (r.m_x < r.m_xLo) || (r.m_x > r.m_xHi) )
         {
            // out of bounds for the zero crossing interval that we are working on.  Use bisection
            // instead.

            // compute an x* sitting at the midpoint:
            r.m_x = (r.m_xLo + r.m_xHi)/2.0 ;
            r.m_status = gsl_root_fdfsolver_set( m_s, &m_F, r.m_x ) ;
            if ( isGslStatusFatal( r.m_status ) )
            {
               break ;
            }
         }

         r.m_status = root_test_delta( r.m_x, r.m_xPrev, p.m_abserr, p.m_relerr ) ;
         if ( isGslStatusFatal( r.m_status ) )
         {
            break ;
         }

         // maintain the interval:
         double fr { m_params( r.m_x ) } ;

         if ( fr * fl < 0.0 )
         {
            // If the sign of the new f(x*) differs from f(x_0), then replace x_1 with x*.
            r.m_xHi = r.m_x ;
            //fh = fr ;
         }
         else
         {
            // otherwise replace x_0 with x*
            r.m_xLo = r.m_x ;
            fl = fr ;
         }

         if ( p.m_verbose )
         {
            printf( "%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
                    (int)r.m_iter, r.m_xLo, r.m_xHi, r.m_x, r.m_x - r_expected, r.m_xHi - r.m_xLo ) ;
         }

      } while ( r.m_status == GSL_CONTINUE && r.m_iter < p.m_max_iter ) ;

      if ( r.m_status == GSL_SUCCESS )
      {
         r.m_converged = true ;
      }
   }

   r.m_strerror = gsl_strerror( r.m_status ) ;
}

template <class paramType>
fSolver<paramType>::fSolver( const solver whichSolver ) : m_T( solverToMethod( whichSolver ) ), m_params{}
{
   m_F.function = paramType::function ;
   m_F.params = &m_params ;

   // turn off the print and abort on error behavior
   gsl_set_error_handler_off() ;

   m_s = gsl_root_fsolver_alloc( m_T ) ;
   if ( !m_s )
   {
      throw std::bad_alloc() ;
   }
}

template <class paramType>
fSolver<paramType>::~fSolver()
{
   gsl_root_fsolver_free( m_s ) ;
}

template <class paramType>
bool increaseIntervalIfNotBracketed( const paramType & f, double & x_min, double & x_max, const Uint max_iter )
{
   Uint iter = 0 ;
   bool foundOne = false ;
   double x1 = x_min ;
   double x2 = x_max ;

   // Brent's method (and probably the other interval methods) abort if
   // the root is not bracketed.  use the interval expansion method described
   // in the lectures if this is the case.
   //
   while ( iter < max_iter )
   {
      double f_min { f( x1 ) } ;
      double f_max { f( x2 ) } ;

      double s_min { signof( f_min ) } ;
      double s_max { signof( f_max ) } ;

      if ( s_min != s_max )
      {
         foundOne = true ;
         x_min = x1 ;
         x_max = x2 ;

         break ;
      }
      else
      {
         double a_min { fabs( f_min ) } ;
         double a_max { fabs( f_max ) } ;

         double width { x2 - x1 } ;

         if ( a_min < a_max )
         {
            x1 -= width/2 ;
         }
         else
         {
            x2 += width/2 ;
         }
      }

      iter++ ;
   }

   return foundOne ;
}

template <class paramType>
bool decreaseIntervalIfNotBracketed( const paramType & f, double & x_min, double & x_max, const Uint max_subdivisions )
{
   bool foundOne = false ;

   assert( max_subdivisions > 1 ) ;

   double f1 = f( x_min ) ;
   double s1 = signof( f1 ) ;
   double x1 = x_min ;
   double x2 = x_max ;
   double f2 = f( x2 ) ;
   double s2 = signof( f2 ) ;

   if ( s1 != s2 )
   {
      return true ;
   }

   const double w = (x_max - x_min)/max_subdivisions ;

   // This is a dumb search, and just plods through all the subdivisions serially, looking for the first
   // value of f(x) that changes sign.
   //
   for ( Uint i = 0 ; i < max_subdivisions ; i++ )
   {
      x2 = x1 + w ;
      f2 = f( x2 ) ;
      s2 = signof( f2 ) ;

      if ( s1 != s2 )
      {
         x_min = x1 ;
         x_max = x2 ;
         foundOne = true ;
         break ;
      }

      x1 = x2 ;
      f1 = f2 ;
   }

   return foundOne ;
}

template <class paramType>
void fSolver<paramType>::iterate( const intervalIterationInputs & p, intervalIterationResults & r )
{
   const double r_expected { m_params.expectedRoot() } ;

   r.m_xLo        = p.m_xLo ;
   r.m_xHi        = p.m_xHi ;
   r.m_x          = p.m_xLo ;

   if ( p.m_maxExpansionIterations )
   {
      increaseIntervalIfNotBracketed( m_params, r.m_xLo, r.m_xHi, p.m_maxExpansionIterations ) ;
   }

   if ( p.m_maxSubDivisions > 1 )
   {
      decreaseIntervalIfNotBracketed( m_params, r.m_xLo, r.m_xHi, p.m_maxSubDivisions ) ;
   }

   r.m_status     = gsl_root_fsolver_set( m_s, &m_F, r.m_xLo, r.m_xHi ) ;
   r.m_solvername = gsl_root_fsolver_name( m_s ) ;

   if ( !r.m_status )
   {
      if ( p.m_verbose )
      {
         printf( "%5s [%9s, %9s] %9s %10s %9s\n",
                 "iter", "lower", "upper", "root", "err", "err(est)" ) ;
      }

      do {
         r.m_iter++ ;

         r.m_status = gsl_root_fsolver_iterate( m_s ) ;
         if ( isGslStatusFatal( r.m_status ) )
         {
            break ;
         }

         r.m_x = gsl_root_fsolver_root( m_s ) ;

         r.m_xLo = gsl_root_fsolver_x_lower( m_s ) ;
         r.m_xHi = gsl_root_fsolver_x_upper( m_s ) ;

         // avoiding simulaneous absolute and relative error checks as with the fdf solver iteration
         // (see comments above)
         r.m_status = gsl_root_test_interval( r.m_xLo, r.m_xHi, 0.0, p.m_relerr ) ;
         if ( isGslStatusFatal( r.m_status ) )
         {
            break ;
         }
         else if ( r.m_status == GSL_SUCCESS )
         {
            r.m_status = gsl_root_test_interval( r.m_xLo, r.m_xHi, p.m_abserr, 0.0 ) ;
            if ( isGslStatusFatal( r.m_status ) )
            {
               break ;
            }
         }

         if ( p.m_verbose )
         {
            printf( "%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
                    (int)r.m_iter, r.m_xLo, r.m_xHi, r.m_x, r.m_x - r_expected, r.m_xHi - r.m_xLo ) ;
         }

      } while ( (r.m_status == GSL_CONTINUE) && (r.m_iter < p.m_max_iter) ) ;

      if ( r.m_status == GSL_SUCCESS )
      {
         r.m_converged = true ;
      }
   }

   r.m_strerror = gsl_strerror( r.m_status ) ;
}
