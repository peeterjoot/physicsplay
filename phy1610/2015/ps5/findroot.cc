#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include "ps5function.h"
#include "mysolver.cc" // for template instantiations

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
                "\t{[--bisection|-i] [--falsepos|-f] [--brent|-b]\n"
                "\t [--newton|-n] [--secant|-s] [--steffenson|-S]}\n"
                "\t[--xlower=x0|-x x0] [--xupper=x1|-X x1] [--interval=w|-w w]\n"
                "\t[--maxiter=m|-m m] [--derivmaxiter=m|-d m] [--err=e|-e e]\n"
                "\t[--help]\n"
                "\n"
                "- At least one of --bisection, --falsepos, --brent, --newton, --secant, --steffenson must be specified\n"
                "- A root search will be performed in [x0,x1] with step size of w,\n"
                "  defaulting to [0,10,0.5]\n"
                "- maxiter for interval root methods defaults to 100.\n"
                "- derivmaxiter for derivative root methods defaults to 1000.\n"
                << std::endl ;

   std::exit( RC_HELP ) ;
}

/**
   Parse arguments and run the selected root solver.
 */
int main( int argc, char * argv[] )
{
   solver whichSolver{solver::undefined} ;
   double x0{0.5} ;
   double xUpper{10.0} ;
   double intervalStep{0.5} ;
   Uint   max_iter{100} ;
   Uint   max_iter_deriv{1000} ;
   double err{1e-4} ;
   double intervalXMin{0.0} ;
   int    c{0} ;
   int    line{0} ;

   const struct option long_options[]{
     { "help",          0, NULL, 'h' },
     { "bisection",     0, NULL, 'i' },
     { "falsepos",      0, NULL, 'f' },
     { "brent",         0, NULL, 'b' },
     { "newton",        0, NULL, 'n' },
     { "secant",        0, NULL, 's' },
     { "steffenson",    0, NULL, 'S' },
     { "xlower",        1, NULL, 'x' },
     { "xupper",        1, NULL, 'X' },
     { "interval",      1, NULL, 'w' },
     { "maxiter",       1, NULL, 'm' },
     { "derivmaxiter",  1, NULL, 'd' },
     { "err",           1, NULL, 'e' },
     { NULL,            0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hifbnsSx:X:w:m:d:e:", long_options, NULL ) ) )
      {
         switch ( c )
         {
            case 'x' :
            {
               line = __LINE__ ; 
               x0 = std::stod( optarg ) ;
               break ;
            }
            case 'X' :
            {
               line = __LINE__ ; 
               xUpper = std::stod( optarg ) ;
               break ;
            }
            case 'w' :
            {
               line = __LINE__ ; 
               intervalStep = std::stod( optarg ) ;
               break ;
            }
            case 'm' :
            {
               line = __LINE__ ; 
               max_iter = strToUint( optarg ) ;
               break ;
            }
            case 'd' :
            {
               line = __LINE__ ; 
               max_iter_deriv = strToUint( optarg ) ;
               break ;
            }
            case 'e' :
            {
               line = __LINE__ ; 
               err = std::stod( optarg ) ;
               break ;
            }
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

   while ( x0 <= xUpper )
   {
      // Newton's method bounces around
      if ( isFdfSolver( whichSolver ) )
      {
         fdfSolver<ps5function> s( whichSolver ) ;

         s.iterate( x0, max_iter_deriv, err ) ;
      }
      else
      {
         fSolver<ps5function> s( whichSolver ) ;

         s.iterate( intervalXMin, x0, max_iter, err ) ;
      }

      x0 += intervalStep ;
   }

   return 0 ;
}
