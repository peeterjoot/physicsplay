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

   /** set the default values for these parameters */
   solverParams() :
      m_x0{0.0},
      m_xUpper{10.0},
      m_intervalStep{0.5},
      m_max_iter{100},
      m_max_iter_deriv{15000},
      m_err{1e-4}
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
            // Newton's method bounces around
            if ( isFdfSolver( method ) )
            {
               fdfSolver<ps5function> s( method ) ;

               fdfSolver<ps5function>::inputs p( xmin, m_max_iter_deriv, m_err, m_err ) ;
               fdfSolver<ps5function>::results r ;

               s.iterate( p, r ) ;

               std::ostringstream out ;
               out << "Using " << r.m_solvername << " with x_0 = " << xmin << "\n"
                   << "Iterations:\t" << r.m_iter << "\n"
                   << "Converged:\t" << r.m_converged << "\n"
                   << "Status:\t" << r.m_status << " (" << r.m_strerror << ")" << "\n"
                   << "Root:\t" << r.m_x << "\n"
                   << "F(Root):\t" << f(r.m_x) << "\n"
                   << "Abserr:\t" << fabs(r.m_x - r.m_xPrev) << "\n" << std::endl ;

               if ( r.m_converged )
               {
                  std::cout << out.str() ;
               }
               else
               {
                  std::cerr << out.str() ;
               }
            }
            else
            {
               fSolver<ps5function> s( method ) ;

               fSolver<ps5function>::inputs p( m_x0, xmin, m_max_iter, m_err, m_err ) ;
               fSolver<ps5function>::results r ;

               s.iterate( p, r ) ;

               std::ostringstream out ;
               out << "Using " << r.m_solvername << " on: [ " << m_x0 << ", " << xmin << " ]\n"
                   << "Iterations:\t" << r.m_iter << "\n"
                   << "Converged:\t" << r.m_converged << "\n"
                   << "Status:\t" << r.m_status << " (" << r.m_strerror << ")" << "\n"
                   << "Root:\t" << r.m_r << "\n"
                   << "F(Root):\t" << f(r.m_r) << "\n"
                   << "Abserr:\t" << r.m_xHi - r.m_xLo << "\n" << std::endl ;

               if ( r.m_converged )
               {
                  std::cout << out.str() ;
               }
               else
               {
                  std::cerr << out.str() ;
               }
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
