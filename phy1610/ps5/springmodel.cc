/**
 \file springmodel.cc
 */
#include "integers.h"
#include <fstream>
#include <cassert>
#include <string>
#include <iostream>
#include <cstdio>
#include <getopt.h>
#include "minimizer.h"
#include "stdoutfilestream.h"
#include "springfunction.h"

/**
   return codes for this exe.
 */
enum class RETURNCODES : int
{
   SUCCESS,      ///< exit code for successful exectution
   HELP,         ///< exit code when -help (or bad option is supplied)
   PARSE_ERROR,  ///< exit code if there's a parse error */

   LAST
} ;

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   static_assert( (int)RETURNCODES::LAST <= 256, "exit code doesn't fit in waitpid waitstatus byte." ) ;

   std::cerr
      << "usage: springmodel\n"
         "\t[--mass=m|-m m]\n"
         "\t[--file=p|-f p]\n"
         "\t  The path to an output filename when appropriate.\n"
         "\t[--csv|-c]\n"
         "\t  Evaluate the minimization function at a\n"
         "\t  set of points in the interval and output a csv format file with these points for plotting.\n"
         "\t[--help]"
      << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

extern template
void f_min_all<gsl_spring_min_function>( const gsl_spring_min_function &   f,
                                         const minimizerParameters &       p,
                                         minimizerResults &                results ) ;

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   int c{0} ;
   int line{0} ;
   double mass{0.1} ;
   unsigned long numMasses{ 25 } ;
   bool verbose{false} ;
   bool showXmin{true} ;
   bool showXmax{false} ;
   bool showFmin{false} ;
   bool showFmax{false} ;
   bool showDiff{false} ;

   // csv related options:
   bool csv{false} ;
   unsigned long numPoints{1000} ;
   std::string filename{} ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "mass",           1, NULL, 'm' },
     { "num",            1, NULL, 'n' },
     { "file",           1, NULL, 'f' },
     { "csv",            0, NULL, 'c' },
     { "xmin",           0, NULL, 'M' },
     { "xmax",           0, NULL, 'N' },
     { "fmin",           0, NULL, 'F' },
     { "fmax",           0, NULL, 'X' },
     { "diff",           0, NULL, 'd' },
     { "verbose",        0, NULL, 'v' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hm:f:n:cvMNFdX", long_options, NULL ) ) )
      {
         switch ( c )
         {
            case 'M' :
            {
               showXmin = true ;

               break ;
            }
            case 'N' :
            {
               showXmax = true ;

               break ;
            }
            case 'F' :
            {
               showFmin = true ;

               break ;
            }
            case 'X' :
            {
               showFmax = true ;

               break ;
            }
            case 'd' :
            {
               showDiff = true ;

               break ;
            }
            case 'v' :
            {
               verbose = true ;

               break ;
            }
            case 'c' :
            {
               csv = true ;

               break ;
            }
            case 'f' :
            {
               line = __LINE__ ;
               filename = std::string( optarg ) ;

               break ;
            }
            case 'm' :
            {
               line = __LINE__ ;
               mass = std::stod( optarg ) ;

               break ;
            }
            case 'n' :
            {
               line = __LINE__ ;
               if ( csv )
               {
                  numPoints = std::stoul( optarg ) ;
               }
               else
               {
                  numMasses = std::stoul( optarg ) ;
               }

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

      std::exit( (int)RETURNCODES::PARSE_ERROR ) ;
   }

   stdoutOrFileStream fstream( filename ) ;
   std::ostream & out{ fstream.handle() } ;
   gsl_spring_min_function f ;

   if ( csv )
   {
      f.setMass( mass ) ;
      minimizerParameters p( f.start(), f.end() ) ;

      double delta = ( f.end() - f.start() ) / numPoints ;

      for ( double x = f.start() ; x < f.end() ; x += delta )
      {
         out << x << ", " << f( x ) << std::endl ;
      }
   }
   else
   {
      constexpr auto massLowerBound = 0.0 ;
      constexpr auto massUpperBound = 0.5 ;
      double massDelta = (massUpperBound - massLowerBound)/(numMasses + 2) ;

      double m = massLowerBound + massDelta ;
      minimizerParameters params( f.start(), f.end() ) ;

      if ( showDiff )
      {
         out << "mass diff\n" ;
      }
      else if ( showFmin )
      {
         out << "mass fmin\n" ;
      }
      else if ( showFmax )
      {
         out << "mass fmax\n" ;
      }
      else if ( showXmax )
      {
         out << "mass xmax\n" ;
      }
      else if ( showXmin )
      {
         out << "mass xmin\n" ;
      }

      for ( unsigned long i = 0 ; i < numMasses ; i++ )
      {
         minimizerResults results ;
         f.setMass( m ) ;
         f_min_all( f, params, results ) ;

         if ( verbose )
         {
            out << "Mass:\t" << m << "\n" ;

            for ( const auto & r : results.m_rv )
            {
               out << "\tUsing " << r.m_solvername << " on: [ " << r.m_initial_a << ", " << r.m_initial_b << " ]\n"
                   << "\tIterations:\t" << r.m_iter << "\n"
                   << "\tConverged:\t" << r.m_converged << "\n"
                   << "\tStatus:\t" << r.m_status << " (" << r.m_strerror << ")" << "\n"
                   << "\tMin:\t" << r.m_xmin << " in [ " << r.m_a << ", " << r.m_b << "]\n"
                   << "\tF(Min):\t" << r.m_fmin << "\n"
                   << "\tAbserr (bracket):\t" << r.m_b - r.m_a << "\n"
                   << std::endl ;
            }

            out << std::endl ;
         }
         else
         {
            double v{} ;

            if ( showDiff )
            {
               v = results.diff() ;
            }
            else if ( showFmin )
            {
               v = results.fmin() ;
            }
            else if ( showFmax )
            {
               v = results.fmax() ;
            }
            else if ( showXmax )
            {
               v = results.xmax() ;
            }
            else if ( showXmin )
            {
               v = results.xmin() ;
            }

            out << m << ' ' << v << std::endl ;
         }

         m += massDelta ;
      }
   }

   return (int)RETURNCODES::SUCCESS ;
}
