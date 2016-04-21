#include "ants_on_table.h"
#include "integers.h"
#include <iostream>
#include <getopt.h>
#include "returncodes.h"

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: ants\n"
      "\t[--gridsize=N|-g N]\n"
      "\t[--timeintervals=N|-t N]\n"
      "\t[--numberofants=N|-n N]\n"
      "\t[--netcdf=filename|-f filename]\n"
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
   std::string netcdffilename{} ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "gridsize",       1, NULL, 'g' },
     { "timeintervals",  1, NULL, 't' },
     { "numberofants",   1, NULL, 'n' },
     { "netcdf",         1, NULL, 'f' },
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
            case 'f' :
            {
               line = __LINE__ ;
               netcdffilename = optarg ;

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
   ants.initialize( total_number_of_ants ) ;
   output( ants, num_time_intervals, netcdffilename ) ;

   return (int)RETURNCODES::SUCCESS ;
}
