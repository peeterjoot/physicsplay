#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "ps5solver.h"

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
                "\t[--bracketed|-r]\n"
                "\t[--help]\n"
                "\n"
                "- At least one of --bisection, --falsepos, --brent, --newton, --secant, --steffenson must be specified\n"
                "- A root search will be performed in [x0,x1] with step size of w,\n"
                "  defaulting to [0,10,0.5]\n"
                "- maxiter for interval root methods defaults to 100.\n"
                "- derivmaxiter for derivative root methods defaults to 1000.\n"
                "- specify bracketed to use safe derivative iteration.\n"
                << std::endl ;

   std::exit( RC_HELP ) ;
}

/**
   Parameters for running the solver as specified in the problem:
   - varying initial values x0 for x, or for varying starting intervals [0.0,x0], where x0 ranges from 0 to 10 in steps of 0.5.
 */
struct solverParams
{
   double m_x0 ;                 ///< initial upper bound for the first interval (fsolver) or root guess (fdfsolver)
   double m_xUpper ;             ///< upper bound for all the intervals (i.e. 10)
   double m_intervalStep ;       ///< step size
   Uint   m_max_iter ;           ///< max number of iterations when running a fsolver method
   Uint   m_max_iter_deriv ;     ///< max number of iterations when running an fdfsolver method
   double m_err ;                ///< desired error for convergence
   bool   m_bracketed ;          ///< use interval method for derivative solvers.

   /** set the default values for these parameters */
   solverParams() :
      m_x0{0.0},
      m_xUpper{10.0},
      m_intervalStep{0.5},
      m_max_iter{100},
      m_max_iter_deriv{15000},
      m_err{1e-4},
      m_bracketed{false}
   {
   }

   void runSolver( const std::vector<solver> & howToSolve ) const
   {
      ps5function f ;

      for ( auto method : howToSolve )
      {
         auto xmin = m_x0 + m_intervalStep ;

         while ( xmin <= m_xUpper )
         {
            bool converged = false ;
            bool bracketedResult = false ;
            std::ostringstream out ;

            intervalIterationInputs pi( m_x0, xmin, m_max_iter, m_err, m_err ) ;
            intervalIterationResults ri ;

            derivativeIterationInputs pd( xmin, m_max_iter_deriv, m_err, m_err ) ;
            derivativeIterationResults rd ;

            // Newton's method bounces around
            if ( isFdfSolver( method ) && m_bracketed )
            {
               bracketedResult = true ;
               fdfSolver<ps5function> s( method ) ;

               s.iterateBracketed( pi, ri ) ;
            }
            else if ( isFdfSolver( method ) )
            {
               fdfSolver<ps5function> s( method ) ;

               s.iterate( pd, rd ) ;
            }
            else
            {
               fSolver<ps5function> s( method ) ;
               bracketedResult = true ;

               s.iterate( pi, ri ) ;
            }

            if ( bracketedResult )
            {
               converged = ri.m_converged ;

               out << "Using " << ri.m_solvername << " on: [ " << m_x0 << ", " << xmin << " ]\n"
                   << "Iterations:\t" << ri.m_iter << "\n" ;

               if ( isFdfSolver( method ) )
               {
                  out << "Bisection Corrections:\t" << ri.m_numBisections << "\n" ;
               }

               out << "Converged:\t" << ri.m_converged << "\n"
                   << "Status:\t" << ri.m_status << " (" << ri.m_strerror << ")" << "\n"
                   << "Root:\t" << ri.m_x << "\n"
                   << "F(Root):\t" << f(ri.m_x) << "\n"
                   << "Abserr (bracket):\t" << ri.m_xHi - ri.m_xLo << "\n" << std::endl ;
            }
            else
            {
               converged = rd.m_converged ;

               out << "Using " << rd.m_solvername << " with x_0 = " << xmin << "\n"
                   << "Iterations:\t" << rd.m_iter << "\n"
                   << "Converged:\t" << rd.m_converged << "\n"
                   << "Status:\t" << rd.m_status << " (" << rd.m_strerror << ")" << "\n"
                   << "Root:\t" << rd.m_x << "\n"
                   << "F(Root):\t" << f(rd.m_x) << "\n"
                   << "Abserr:\t" << fabs(rd.m_x - rd.m_xPrev) << "\n" << std::endl ;
            }

            if ( converged )
            {
               std::cout << out.str() ;
            }
            else
            {
               std::cerr << out.str() ;
            }

            xmin += m_intervalStep ;
         }
      }
   }
} ;

/**
   Parse arguments and run the selected root solver.
 */
int main( int argc, char * argv[] )
{
   std::vector<solver> howToSolve ;
   solverParams p ;
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
     { "bracketed",     0, NULL, 'r' },
     { NULL,            0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hifbnsSx:X:w:m:d:e:r", long_options, NULL ) ) )
      {
         switch ( c )
         {
            case 'r' :
            {
               line = __LINE__ ;
               p.m_bracketed = true ;
               break ;
            }
            case 'x' :
            {
               line = __LINE__ ;
               p.m_x0 = std::stod( optarg ) ;
               break ;
            }
            case 'X' :
            {
               line = __LINE__ ;
               p.m_xUpper = std::stod( optarg ) ;
               break ;
            }
            case 'w' :
            {
               line = __LINE__ ;
               p.m_intervalStep = std::stod( optarg ) ;
               break ;
            }
            case 'm' :
            {
               line = __LINE__ ;
               p.m_max_iter = strToUint( optarg ) ;
               break ;
            }
            case 'd' :
            {
               line = __LINE__ ;
               p.m_max_iter_deriv = strToUint( optarg ) ;
               break ;
            }
            case 'e' :
            {
               line = __LINE__ ;
               p.m_err = std::stod( optarg ) ;
               break ;
            }
            case 'i' :
            {
               line = __LINE__ ;
               howToSolve.push_back( solver::bisection ) ;

               break ;
            }
            case 'f' :
            {
               line = __LINE__ ;
               howToSolve.push_back( solver::falsepos ) ;

               break ;
            }
            case 'b' :
            {
               line = __LINE__ ;
               howToSolve.push_back( solver::brent ) ;

               break ;
            }
            case 'n' :
            {
               line = __LINE__ ;
               howToSolve.push_back( solver::newton ) ;

               break ;
            }
            case 's' :
            {
               line = __LINE__ ;
               howToSolve.push_back( solver::secant ) ;

               break ;
            }
            case 'S' :
            {
               line = __LINE__ ;
               howToSolve.push_back( solver::steffenson ) ;

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

   if ( 0 == howToSolve.size() )
   {
      std::cerr << "solver unspecified" << std::endl ;
      showHelpAndExit() ;
   }

   p.runSolver( howToSolve ) ;

   return 0 ;
}
