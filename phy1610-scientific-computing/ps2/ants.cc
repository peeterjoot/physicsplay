#include "ants_on_table.h"
#include "integers.h"
#include <iostream>
#include <getopt.h>
#include "optticktock.h"
#include "returncodes.h"

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: ants\n" 
      "\t[--gridsize=N|-g N]\n"
      "\t[--timeintervals=N|-t N]\n"
      "\t[--numberofants=N|-n N]\n"
      "\t[--help]" << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   size_t table_grid_size   { 356 } ;
   int num_time_intervals   { 40 } ;
   int total_number_of_ants { 1010 } ;
   int c{0} ;
   int line{0} ;
   TickTockOrNoOp timer ;
   float ioTime { 0.0 } ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "gridsize",       1, NULL, 'g' },
     { "timeintervals",  1, NULL, 't' },
     { "numberofants",   1, NULL, 'n' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hg:t:n:", long_options, NULL ) ) )
      { 
         switch ( c )
         {
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
            case 'n' :
            {
               line = __LINE__ ;
               total_number_of_ants = std::stod( optarg ) ;

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
   catch ( ... )
   {
      std::cerr 
         << __FILE__
         << ":"
         << line << ": uncaught exception (parse error)\n"
         << "option: -" << (char)c << '\n'
         << "argument: " << optarg << '\n'
         << std::endl ;

      std::exit( (int)RETURNCODES::PARSE_ERROR ) ;
   }

   ants_on_table ants( table_grid_size ) ;

   ants_on_table::iterator i = ants.initialize( total_number_of_ants ) ;
   ants_on_table::iterator end( num_time_intervals ) ;

   for ( ; i != end ; ++i )
   {
      float totants = i() ;

      timer.tick() ;

      std::cout << totants << " " << *i << std::endl ;

      ioTime += timer.silent_tock() ;
   }

   #if defined USE_TICK_TOCK
      std::cout << "io time: \t" << ioTime << std::endl ;
   #endif

   return (int)RETURNCODES::SUCCESS ;
}
