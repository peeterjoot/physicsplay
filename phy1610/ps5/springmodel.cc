/**
 \file springmodel.cc
 */
#include "integers.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <getopt.h>
#include <limits>
#include "minimizer.h"

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
   bool verbose{false} ;

   // csv related options:
   bool csv{false} ;
   unsigned long num{1000} ;
   std::string filename{} ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "mass",           1, NULL, 'm' },
     { "file",           1, NULL, 'f' },
     { "csv",            0, NULL, 'c' },
     { "verbose",        0, NULL, 'v' },
     { "num",            1, NULL, 'n' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hm:f:n:cv", long_options, NULL ) ) )
      { 
         switch ( c )
         {
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
               num = std::stoul( optarg ) ;

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

   if ( csv && filename.length() )
   {
      minimizerParameters p( mass ) ;
      std::ofstream f( filename.c_str() ) ;

      double e = 0.01 ;

      for ( double x = e ; x < p.m_f.d - e ; x += p.m_f.d/num )
      {
         f << x << ", " << p.m_f( x ) << std::endl ;
      }
   }
   else
   {
      constexpr auto massLowerBound = 0.0 ;
      constexpr auto massUpperBound = 0.5 ;
      constexpr auto numMasses = 25 ;
      constexpr auto massDelta = (massUpperBound - massLowerBound)/(numMasses + 2) ;

      double m = massLowerBound + massDelta ;

      if ( !verbose )
      {
         std::cout << "mass x\n" ;
      }

      for ( int i = 0 ; i < numMasses ; i++ )
      {
         if ( verbose )
         {
            std::cout << "Mass:\t" << m << "\n" ;
         }

         minimizerParameters p( m ) ;
         minimizerResultsVec rv ;

         f_min_all( p, rv ) ;

         if ( verbose )
         {
            for ( const auto & r : rv )
            {
               std::cout << "\tUsing " << r.m_solvername << " on: [ " << r.m_initial_a << ", " << r.m_initial_b << " ]\n"
                         << "\tIterations:\t" << r.m_iter << "\n"
                         << "\tConverged:\t" << r.m_converged << "\n"
                         << "\tStatus:\t" << r.m_status << " (" << r.m_strerror << ")" << "\n"
                         << "\tMin:\t" << r.m_min << " in [ " << r.m_a << ", " << r.m_b << "]\n"
                         << "\tF(Min):\t" << p.m_f(r.m_min) << "\n"
                         << "\tAbserr (bracket):\t" << r.m_b - r.m_a << "\n"
                         << std::endl ;
            }

            std::cout << std::endl ;
         }
         else
         {
            double min{ -std::numeric_limits<double>::infinity() } ;
            double xmin{} ;
            bool foundGlobalMin{false} ;

            for ( const auto & r : rv )
            {
               if ( !r.m_status )
               {
                  double f = p.m_f( r.m_min ) ;

                  if ( f > min )
                  {
                     xmin = r.m_min ;
                     min = f ;
                     foundGlobalMin = true ;
                  }
               }
            }

            if ( foundGlobalMin )
            {
               std::cout << m << ' ' << xmin << std::endl ;
            }
         }

         m += massDelta ;
      }
   }

   return (int)RETURNCODES::SUCCESS ;
}
