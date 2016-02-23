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
#include <limits>
#include "minimizer.h"
#include "stdoutfilestream.h"

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
     { "verbose",        0, NULL, 'v' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hm:f:n:cv", long_options, NULL ) ) )
      { 
         switch ( c )
         {
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

   if ( csv )
   {
      minimizerParameters p( mass ) ;

      double e = 0.01 ;

      for ( double x = e ; x < p.m_f.d - e ; x += p.m_f.d/numPoints )
      {
         out << x << ", " << p.m_f( x ) << std::endl ;
      }
   }
   else
   {
      constexpr auto massLowerBound = 0.0 ;
      constexpr auto massUpperBound = 0.5 ;
      double massDelta = (massUpperBound - massLowerBound)/(numMasses + 2) ;

      double m = massLowerBound + massDelta ;

      if ( !verbose )
      {
         out << "mass x\n" ;
      }

      for ( unsigned long i = 0 ; i < numMasses ; i++ )
      {
         if ( verbose )
         {
            out << "Mass:\t" << m << "\n" ;
         }

         minimizerParameters p( m ) ;
         minimizerResultsVec rv ;

         f_min_all( p, rv ) ;

         if ( verbose )
         {
            for ( const auto & r : rv )
            {
               out << "\tUsing " << r.m_solvername << " on: [ " << r.m_initial_a << ", " << r.m_initial_b << " ]\n"
                         << "\tIterations:\t" << r.m_iter << "\n"
                         << "\tConverged:\t" << r.m_converged << "\n"
                         << "\tStatus:\t" << r.m_status << " (" << r.m_strerror << ")" << "\n"
                         << "\tMin:\t" << r.m_min << " in [ " << r.m_a << ", " << r.m_b << "]\n"
                         << "\tF(Min):\t" << p.m_f(r.m_min) << "\n"
                         << "\tAbserr (bracket):\t" << r.m_b - r.m_a << "\n"
                         << std::endl ;
            }

            out << std::endl ;
         }
         else
         {
            constexpr double inf{ std::numeric_limits<double>::infinity() } ;
            double fmin{ -inf } ;
            double fmax{ inf } ;
            double xmin{} ;
            double xmax{} ;
            double diff{} ;
            bool successfulResult{false} ;

            assert( rv.size() <= 2 ) ;
            assert( rv.size() >= 1 ) ;

            for ( const auto & r : rv )
            {
               if ( !r.m_status )
               {
                  successfulResult = true ;

                  double f = p.m_f( r.m_min ) ;

                  if ( f > fmin )
                  {
                     xmin = r.m_min ;
                     fmin = f ;
                  }

                  if ( f < fmax )
                  {
                     xmax = r.m_min ;
                     fmax = f ;
                  }
               }
            }

            diff = fmax - fmin ;

            if ( successfulResult )
            {
               if ( verbose )
               {
                  std::cerr << m << ' ' << xmin << std::endl ;
                  std::cerr << m << ' ' << xmax << std::endl ;
               }
               out << m << ' ' << diff << std::endl ;
            }
         }

         m += massDelta ;
      }
   }

   return (int)RETURNCODES::SUCCESS ;
}
