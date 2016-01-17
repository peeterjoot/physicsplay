#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include "mysolver.h"

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

int main( int argc, char * argv[] )
{
   solver whichSolver = solver::undefined ;

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

   // FIXME: parameterize iteration interval, max_iter, and precis.
   double x0 = 0.5 ;
   while ( x0 <= 10.0 )
   {
      #define MAX_ITER 100
      #define ERROR_PRECISION 1e-4

      // Newton's method bounces around
      if ( isFdfSolver( whichSolver ) )
      {
         fdfSolver s( whichSolver ) ;

         s.iterate( x0, MAX_ITER, FUNCTION_EXPECTED_ROOT, ERROR_PRECISION ) ;
      }
      else
      {
         fSolver s( whichSolver ) ;

         s.iterate( 0.0, x0, MAX_ITER, FUNCTION_EXPECTED_ROOT, ERROR_PRECISION ) ;
      }

      x0 += 0.5 ;
   }

   return 0 ;
}
