#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include "integers.h"

#if 0
   #include "quadratic.h"

   #define FUNCTION_TO_SOLVE_F quadratic
   #define FUNCTION_TO_SOLVE_DF quadratic_deriv
   #define FUNCTION_TO_SOLVE_FDF quadratic_fdf

   #define FUNCTION_PARAM_STRUCT quadratic_params
   #define FUNCTION_PARAM_INIT { 1.0, 0.0, -5.0 }
#else
   #include "ps5function.h"

   #define FUNCTION_TO_SOLVE_F ps5function
   #define FUNCTION_TO_SOLVE_DF ps5function_deriv
   #define FUNCTION_TO_SOLVE_FDF ps5function_fdf

   #define FUNCTION_PARAM_STRUCT ps5function_params
   #define FUNCTION_PARAM_INIT { }
#endif

/** exit code for successful exectution */
#define RC_SUCCESS      0
/** exit code when -help (or bad option is supplied) */
#define RC_HELP         1
/** exit code if there's a parse error */
#define RC_PARSE_ERROR  2

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: findroot\n"
                "\t{[--bisection|-i] [--falsepos|-f] [--brent|-b]"
                "\t [--newton|-n] [--secant|-s] [--steffenson|-S]}"
                "\t[--help]" << std::endl ;

   std::exit( RC_HELP ) ;
}

enum class solver
{
   undefined,
   bisection,
   falsepos,
   brent,
   newton,
   secant,
   steffenson
} ;

const void * solverMethod[] =
{
   nullptr,
   (const void *)gsl_root_fsolver_bisection,
   (const void *)gsl_root_fsolver_falsepos,
   (const void *)gsl_root_fsolver_brent,
   (const void *)gsl_root_fdfsolver_newton,
   (const void *)gsl_root_fdfsolver_secant,
   (const void *)gsl_root_fdfsolver_steffenson,
} ;

inline bool isFdfSolver( solver s )
{
   return s >= solver::newton ;
}

int main( int argc, char * argv[] )
{
   int status ;
   int iter = 0, max_iter = 100 ;
   solver whichSolver = solver::undefined ;
   double r = 0, r_expected = sqrt( 5.0 ) ;

   FUNCTION_PARAM_STRUCT params = FUNCTION_PARAM_INIT ;

   int c{0} ;
   int line{0} ;

   const struct option long_options[] = {
     { "help",       0, NULL, 'h' },
     { "bisection",  0, NULL, 'i' },
     { "falsepos",   0, NULL, 'f' },
     { "brent",      0, NULL, 'b' },
     { "newton",     0, NULL, 'n' },
     { "secant",     0, NULL, 's' },
     { "steffenson", 0, NULL, 'S' },
     { NULL,         0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hifbnsS", long_options, NULL ) ) )
      { 
         switch ( c )
         {
            case 'i' :
            {
               line = __LINE__ ;
               whichSolver = solver::bisection ;

               break ;
            }
            case 'f' :
            {
               line = __LINE__ ;
               whichSolver = solver::falsepos ;

               break ;
            }
            case 'b' :
            {
               line = __LINE__ ;
               whichSolver = solver::brent ;

               break ;
            }
            case 'n' :
            {
               line = __LINE__ ;
               whichSolver = solver::newton ;

               break ;
            }
            case 's' :
            {
               line = __LINE__ ;
               whichSolver = solver::secant ;

               break ;
            }
            case 'S' :
            {
               line = __LINE__ ;
               whichSolver = solver::steffenson ;

               break ;
            }
            case 'h' :
            default:
            {
               showHelpAndExit() ;
            }
         } 
      }
   }
   catch (...)
   {
      std::cerr 
         << __FILE__
         << ":"
         << line << ": uncaught exception (parse error)\n"
         << "option: -" << (char)c << "\n"
         << "argument: " << optarg << "\n"
         << std::endl ;

      std::exit( RC_PARSE_ERROR ) ;
   }

   if ( whichSolver == solver::undefined )
   {
      std::cerr << "solver unspecified" << std::endl ;
      showHelpAndExit() ;
   }

   if ( isFdfSolver( whichSolver ) )
   {
      const gsl_root_fdfsolver_type *T = (const gsl_root_fdfsolver_type *)solverMethod[ (int)whichSolver ] ;
      gsl_root_fdfsolver *s ;
      gsl_function_fdf F ;

      double x, x0 = 5.0 ;

      F.f = FUNCTION_TO_SOLVE_F ;
      F.df = FUNCTION_TO_SOLVE_DF ;
      F.fdf = FUNCTION_TO_SOLVE_FDF ;
      F.params = &params ;
      s = gsl_root_fdfsolver_alloc( T ) ;
      gsl_root_fdfsolver_set( s, &F, x0 ) ;

      printf( "using %s method\n", gsl_root_fdfsolver_name( s ) ) ;

      printf( "%5s [%9s, %9s] %9s %10s %9s\n",
              "iter", "lower", "upper", "root", "err", "err(est)" ) ;

      do {
         iter++ ;
         status = gsl_root_fdfsolver_iterate( s ) ;
         x0 = x ;
         x = gsl_root_fdfsolver_root( s ) ;
         status = gsl_root_test_delta( x, x0, 0, 1e-3 ) ;

         if (status == GSL_SUCCESS)
           printf ("Converged:\n") ;

         printf( "%5d %10.7f %+10.7f %10.7f\n",
                 iter, x, x - r_expected, x - x0 ) ;

      } while ( status == GSL_CONTINUE && iter < max_iter ) ;

      gsl_root_fdfsolver_free( s ) ;
   }
   else
   {
      double x_lo = 0.0, x_hi = 5.0 ;

      const gsl_root_fsolver_type *T = (const gsl_root_fsolver_type *)solverMethod[ (int)whichSolver ] ;
      gsl_root_fsolver *s ;
      gsl_function F ;

      F.function = FUNCTION_TO_SOLVE_F ;
      F.params = &params ;

      s = gsl_root_fsolver_alloc( T ) ;
      gsl_root_fsolver_set( s, &F, x_lo, x_hi ) ;
      printf( "using %s method\n", gsl_root_fsolver_name( s ) ) ;

      printf( "%5s [%9s, %9s] %9s %10s %9s\n",
              "iter", "lower", "upper", "root", "err", "err(est)" ) ;

      do {
         iter++ ;
         status = gsl_root_fsolver_iterate( s ) ;
         r = gsl_root_fsolver_root( s ) ;
         x_lo = gsl_root_fsolver_x_lower( s ) ;
         x_hi = gsl_root_fsolver_x_upper( s ) ;
         status = gsl_root_test_interval( x_lo, x_hi, 0, 0.001 ) ;
         if ( status == GSL_SUCCESS )
         {
             printf ("Converged:\n") ;
         }

         printf( "%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
                 iter, x_lo, x_hi, r, r - r_expected, x_hi - x_lo ) ;

      } while ( status == GSL_CONTINUE && iter < max_iter ) ;

      gsl_root_fsolver_free( s ) ;
   }

   return status ;
}
