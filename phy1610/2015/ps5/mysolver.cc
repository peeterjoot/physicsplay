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

/**
   Test for any return code that isn't one of GSL_CONTINUE or GSL_SUCCESS.
 */
inline bool isGslStatusFatal( int status )
{
   return ( (status != GSL_CONTINUE) && (status != GSL_SUCCESS) ) ;
}

template <class paramType>
void fdfSolver<paramType>::iterate( const iterationParameters & p, iterationResults & r )
{
   const double r_expected { m_params.expectedRoot() } ;

   r.m_xPrev      = p.m_x0 ;
   r.m_converged  = false ;
   r.m_x          = p.m_x0 ;
   r.m_iter       = 0 ;
   r.m_status     = gsl_root_fdfsolver_set( m_s, &m_F, r.m_xPrev ) ;
   r.m_solvername = gsl_root_fdfsolver_name( m_s ) ;

   if ( p.m_verbose )
   {
      printf( "%5s %9s %10s %9s\n",
              "iter", "root", "err", "err(est)" ) ;
   }

   do {
      m_iter++ ;

      // Can return GSL_EBADFUNC, GSL_EZERODIV (singular value or divide by zero)
      r.m_status = gsl_root_fdfsolver_iterate( m_s ) ;
      if ( isGslStatusFatal( r.m_status ) )
      {
         break ;
      }

      r.m_xPrev = r.m_x ;
      r.m_x = gsl_root_fdfsolver_root( m_s ) ;

      //
      // gsl_root_test_delta deals with relative error in a smart way.  Such an error is
      // usually defined as: e_r = |x - x_0|/|x|, so we want |x - x_0|/|x| < e_r for a desired e_r.
      // That is problematic when the root is near zero.
      //
      // Instead this tests for relative error by checking that
      //    |x - x_0| < |x| e_r + e_a, where e_r is the desired relative error and e_a is the
      // desired absolute error, so if the root is near zero, only the absolute error check
      // will be relavant.
      //
      r.m_status = gsl_root_test_delta( r.m_x, r.m_xPrev, p.m_errabs, p.m_errrel ) ;
      if ( isGslStatusFatal( r.m_status ) )
      {
         break ;
      }

      if ( p.m_verbose )
      {
         printf( "%5d %10.7f %+10.7f %10.7f\n",
                 (int)r.m_iter, r.m_x, r.m_x - r_expected, r.m_x - r.m_xPrev ) ;
      }

   } while ( r.m_status == GSL_CONTINUE && m_iter < max_iter ) ;

   if ( r.m_status == GSL_SUCCESS )
   {
      r.m_converged = true ;
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
      double f_min { m_F.function( x_min, m_F.params ) } ;
      double f_max { m_F.function( x_max, m_F.params ) } ;

      double s_min { std::copysign( 1.0, f_min ) } ;
      double s_max { std::copysign( 1.0, f_max ) } ;

      if ( s_min != s_max )
      {
         foundOne = true ;
         break ;
      }
      else
      {
         double a_min { std::abs( f_min ) } ;
         double a_max { std::abs( f_max ) } ;

         double width { x_max - x_min } ;

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
   Uint iter { 0 } ;
   double r ;
   double x_min{ x_lo } ;
   double x_max{ x_hi } ;
   const double r_expected { m_params.expectedRoot() } ;

   increaseIntervalIfNotBracketed( x_min, x_max, max_iter ) ;

   int status { gsl_root_fsolver_set( m_s, &m_F, x_min, x_max ) } ;
   if ( status )
   {
      std::cout << std::string( gsl_strerror (status) ) << std::endl;
   }
   else
   {
      printf( "using %s method\n", gsl_root_fsolver_name( m_s ) ) ;

      printf( "%5s [%9s, %9s] %9s %10s %9s\n",
              "iter", "lower", "upper", "root", "err", "err(est)" ) ;

      do {
         iter++ ;

         status = gsl_root_fsolver_iterate( m_s ) ;
         if ( status )
         {
            std::cout << std::string( gsl_strerror (status) ) << std::endl;
            break ;
         }

         r = gsl_root_fsolver_root( m_s ) ;

         x_min = gsl_root_fsolver_x_lower( m_s ) ;
         x_max = gsl_root_fsolver_x_upper( m_s ) ;

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

template <class paramType>
void solverParams<paramType>::runSolver( const std::vector<solver> & howToSolve ) const
{
   auto xmin = m_x0 ;

   for ( auto method : howToSolve )
   {
      while ( xmin <= m_xUpper )
      {
         // Newton's method bounces around
         if ( isFdfSolver( method ) )
         {
            fdfSolver<paramType> s( method ) ;

            s.iterate( xmin, m_max_iter_deriv, m_err ) ;
         }
         else
         {
            fSolver<paramType> s( method ) ;

            s.iterate( m_intervalXMin, m_x0, m_max_iter, m_err ) ;
         }

         xmin += m_intervalStep ;
      }
   }
}
