/**
 \file springmodel.cc
 */
#include "integers.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <getopt.h>
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
         "\tWhen file is specified evaluate the minimization function at a\n"
         "\tset of points in the interval and output a csv format file with these points.\n"
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
   unsigned long num{1000} ;
   std::string filename{} ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "mass",           1, NULL, 'm' },
     { "file",           1, NULL, 'f' },
     { "num",            1, NULL, 'n' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hm:f:n:", long_options, NULL ) ) )
      { 
         switch ( c )
         {
#if 0 // copied from ps[234]/ants.cc
            case 'g' :
            {
               line = __LINE__ ;
               table_grid_size = strToUint( optarg ) ;

               break ;
            }
            case 't' :
            {
               line = __LINE__ ;
               num_time_intervals = std::stoi( optarg ) ;

               break ;
            }
#endif
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

   minimizerParameters p( mass ) ;
   minimizerResults r ;

   if ( filename.length() )
   {
      std::ofstream f( filename.c_str() ) ;

      double e = 0.01 ;

      for ( double x = e ; x < p.m_f.d - e ; x += p.m_f.d/num )
      {
         f << x << ", " << p.m_f( x ) << std::endl ;
      }
   }
   else
   {
      f_min_all( p, r ) ;

      std::cout << "Using " << r.m_solvername << " on: [ " << p.m_a << ", " << p.m_b << " ]\n"
                << "Iterations:\t" << r.m_iter << "\n"
                << "Converged:\t" << r.m_converged << "\n"
                << "Status:\t" << r.m_status << " (" << r.m_strerror << ")" << "\n"
                << "Min:\t" << r.m_min << "\n"
                << "F(Min):\t" << p.m_f(r.m_min) << "\n"
                << "Abserr (bracket):\t" << r.m_b - r.m_a << "\n"
                << std::endl ;
   }

   return (int)RETURNCODES::SUCCESS ;
}
