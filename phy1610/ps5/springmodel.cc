/**
 \file springmodel.cc
 */
#include "integers.h"
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

   std::cerr << "usage: springmodel\n" 
//      "\t[--gridsize=N|-g N]\n"
//      "\t[--timeintervals=N|-t N]\n"
      "\t[--help]" << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   int c{0} ;
   int line{0} ;
   double mass{0.25} ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "mass",           1, NULL, 'm' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hm:", long_options, NULL ) ) )
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
            case 'm' :
            {
               line = __LINE__ ;
               mass = std::stod( optarg ) ;

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

   for ( double x = 0.01 ; x < 0.5 ; x += 0.01 )
   {
      printf( "%f, %f\n", x, p.m_f( x ) ) ;
   }
#if 0
   f_min_all( p, r ) ;

   std::cout << "Using " << r.m_solvername << " on: [ " << p.m_a << ", " << p.m_b << " ]\n"
             << "Iterations:\t" << r.m_iter << "\n"
             << "Converged:\t" << r.m_converged << "\n"
             << "Status:\t" << r.m_status << " (" << r.m_strerror << ")" << "\n"
             << "Min:\t" << r.m_min << "\n"
             << "F(Root):\t" << p.m_f(r.m_min) << "\n"
             << "Abserr (bracket):\t" << r.m_b - r.m_a << "\n"
             << std::endl ;
#endif

   return (int)RETURNCODES::SUCCESS ;
}
