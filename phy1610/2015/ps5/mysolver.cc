/**
   \file mysolver.cc
 */

#include <new>
#include <iostream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include <stdio.h>
#include <cmath>
#include "integers.h"
#include "mysolver.h"

template <class paramType>
fdfSolver<paramType>::fdfSolver( const solver whichSolver ) : T( solverToFdfMethod( whichSolver ) ), params{}
{
   F.f = paramType::function ;
   F.df = paramType::derivative ;
   F.fdf = paramType::functionAndDerivative ;
   F.params = &params ;

   // turn off the print and abort on error behavior
   gsl_set_error_handler_off() ;

   s = gsl_root_fdfsolver_alloc( T ) ;
   if ( !s )
   {
      throw std::bad_alloc() ;
   }
}

template <class paramType>
fdfSolver<paramType>::~fdfSolver()
{
   gsl_root_fdfsolver_free( s ) ;
}

template <class paramType>
int fdfSolver<paramType>::iterate( const double x0, const Uint max_iter, const double err )
{
   int status ;
   double x ;
   double xPrev = x0 ;
   Uint iter = 0 ;
   const double r_expected = params.expectedRoot() ;

   status = gsl_root_fdfsolver_set( s, &F, xPrev ) ;

   printf( "using %s method\n", gsl_root_fdfsolver_name( s ) ) ;

   printf( "%5s %9s %10s %9s\n",
           "iter", "root", "err", "err(est)" ) ;

   do {
      iter++ ;
      status = gsl_root_fdfsolver_iterate( s ) ;
      xPrev = x ;
      x = gsl_root_fdfsolver_root( s ) ;
      status = gsl_root_test_delta( x, xPrev, 0, err ) ;

      if (status == GSL_SUCCESS)
      {
         std::cout << "Converged:" << std::endl ;
      }

      printf( "%5d %10.7f %+10.7f %10.7f\n",
              (int)iter, x, x - r_expected, x - xPrev ) ;

   } while ( status == GSL_CONTINUE && iter < max_iter ) ;

   return status ;
}

template <class paramType>
fSolver<paramType>::fSolver( const solver whichSolver ) : T( solverToMethod( whichSolver ) ), params{}
{
   F.function = paramType::function ;
   F.params = &params ;

   // turn off the print and abort on error behavior
   gsl_set_error_handler_off() ;

   s = gsl_root_fsolver_alloc( T ) ;
   if ( !s )
   {
      throw std::bad_alloc() ;
   }
}

template <class paramType>
fSolver<paramType>::~fSolver()
{
   gsl_root_fsolver_free( s ) ;
}

template <class paramType>
bool fSolver<paramType>::increaseIntervalIfNotBracketed( double & x_min, double & x_max, const Uint max_iter )
{
   Uint iter = 0 ;
   bool foundOne = false ;

   // Brent's method (and probably the other interval methods) abort if
   // the root is not bracketed.  use the interval expansion method described
   // in the lectures if this is the case.
   //
   while ( iter < max_iter )
   {
      double f_min = F.function( x_min, F.params ) ;
      double f_max = F.function( x_max, F.params ) ;

      double s_min = std::copysign( 1.0, f_min ) ;
      double s_max = std::copysign( 1.0, f_max ) ;

      if ( s_min != s_max )
      {
         foundOne = true ;
         break ;
      }
      else
      {
         double a_min = std::abs( f_min ) ;
         double a_max = std::abs( f_max ) ;

         double width = x_max - x_min ;
         if ( a_min < a_max )
         {
            x_min -= width/2 ;
         }
         else
         {
            x_max += width/2 ;
         }
      }

      iter++ ;
   }

   return foundOne ;
}

template <class paramType>
int fSolver<paramType>::iterate( const double x_lo, const double x_hi, const Uint max_iter, const double err )
{
   Uint iter = 0 ;
   double r ;
   double x_min = x_lo ;
   double x_max = x_hi ;
   const double r_expected = params.expectedRoot() ;

   increaseIntervalIfNotBracketed( x_min, x_max, max_iter ) ;

   int status = gsl_root_fsolver_set( s, &F, x_min, x_max ) ;
   if ( status )
   {
      std::cout << std::string( gsl_strerror (status) ) << std::endl;
   }
   else
   {
      printf( "using %s method\n", gsl_root_fsolver_name( s ) ) ;

      printf( "%5s [%9s, %9s] %9s %10s %9s\n",
              "iter", "lower", "upper", "root", "err", "err(est)" ) ;

      do {
         iter++ ;

         status = gsl_root_fsolver_iterate( s ) ;
         if ( status )
         {
            std::cout << std::string( gsl_strerror (status) ) << std::endl;
            break ;
         }

         r = gsl_root_fsolver_root( s ) ;

         x_min = gsl_root_fsolver_x_lower( s ) ;
         x_max = gsl_root_fsolver_x_upper( s ) ;

         status = gsl_root_test_interval( x_min, x_max, 0, err ) ;
         if ( status == GSL_SUCCESS )
         {
             std::cout << "Converged:" << std::endl ;
         }

         printf( "%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
                 (int)iter, x_min, x_max, r, r - r_expected, x_max - x_min ) ;

      } while ( (status == GSL_CONTINUE) && (iter < max_iter) ) ;
   }

   return status ;
}
