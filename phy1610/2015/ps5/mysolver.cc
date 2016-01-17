/**
   \file mysolver.cc
 */

#include <new>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include <stdio.h>
#include "integers.h"

#if 0
   #include "quadratic.h"

   #define FUNCTION_TO_SOLVE_F quadratic
   #define FUNCTION_TO_SOLVE_DF quadratic_deriv
   #define FUNCTION_TO_SOLVE_FDF quadratic_fdf

   #define FUNCTION_PARAM_STRUCT quadratic_params
   #define FUNCTION_PARAM_INIT { 1.0, 0.0, -5.0 }
   #define FUNCTION_EXPECTED_ROOT std::sqrt( 5.0 )
#else
   #include "ps5function.h"

   #define FUNCTION_TO_SOLVE_F ps5function
   #define FUNCTION_TO_SOLVE_DF ps5function_deriv
   #define FUNCTION_TO_SOLVE_FDF ps5function_fdf

   #define FUNCTION_PARAM_STRUCT ps5function_params
   #define FUNCTION_PARAM_INIT { }
   #define FUNCTION_EXPECTED_ROOT 1.0
#endif

static const void * solverMethod[] =
{
   nullptr,
   (const void *)gsl_root_fsolver_bisection,
   (const void *)gsl_root_fsolver_falsepos,
   (const void *)gsl_root_fsolver_brent,
   (const void *)gsl_root_fdfsolver_newton,
   (const void *)gsl_root_fdfsolver_secant,
   (const void *)gsl_root_fdfsolver_steffenson,
} ;

fdfSolver::fdfSolver( const solver whichSolver ) : T((const gsl_root_fdfsolver_type *)solverMethod[ (int)whichSolver ])
{
   F.f = FUNCTION_TO_SOLVE_F ;
   F.df = FUNCTION_TO_SOLVE_DF ;
   F.fdf = FUNCTION_TO_SOLVE_FDF ;

   // turn off the print and abort on error behavior
   gsl_set_error_handler_off() ;

   s = gsl_root_fdfsolver_alloc( T ) ;
   if ( !s )
   {
      throw std::bad_alloc() ;
   }
}

fdfSolver::~fdfSolver()
{
   gsl_root_fdfsolver_free( s ) ;
}

int fdfSolver::iterate( const double x0, const Uint max_iter, const double r_expected, const double err )
{
   int status ;
   double x ;
   double xPrev = x0 ;
   Uint iter = 0 ;
   FUNCTION_PARAM_STRUCT params = FUNCTION_PARAM_INIT ;

   F.params = &params ;
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
          printf ("Converged:\n") ;
      }

      printf( "%5d %10.7f %+10.7f %10.7f\n",
              (int)iter, x, x - r_expected, x - xPrev ) ;

   } while ( status == GSL_CONTINUE && iter < max_iter ) ;

   return status ;
}

fSolver::fSolver( const solver whichSolver ) : T((const gsl_root_fsolver_type *)solverMethod[ (int)whichSolver ])
{
   F.function = FUNCTION_TO_SOLVE_F ;

   // turn off the print and abort on error behavior
   gsl_set_error_handler_off() ;

   s = gsl_root_fsolver_alloc( T ) ;
   if ( !s )
   {
      throw std::bad_alloc() ;
   }
}

fSolver::~fSolver()
{
   gsl_root_fsolver_free( s ) ;
}

int fSolver::iterate( const double x_lo, const double x_hi, const Uint max_iter, const double r_expected, const double err )
{
   FUNCTION_PARAM_STRUCT params = FUNCTION_PARAM_INIT ;
   F.params = &params ;
   Uint iter = 0 ;
   double r ;
   double x_min = x_lo ;
   double x_max = x_hi ;

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
         }

         r = gsl_root_fsolver_root( s ) ;

         x_min = gsl_root_fsolver_x_lower( s ) ;
         x_max = gsl_root_fsolver_x_upper( s ) ;

         status = gsl_root_test_interval( x_min, x_max, 0, err ) ;
         if ( status == GSL_SUCCESS )
         {
             printf ("Converged:\n") ;
         }

         printf( "%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
                 (int)iter, x_min, x_max, r, r - r_expected, x_max - x_min ) ;

      } while ( status == GSL_CONTINUE && iter < max_iter ) ;
   }

   return status ;
}
