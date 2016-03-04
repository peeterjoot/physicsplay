#include "integers.h"
#include <iostream>
#include <string>
#include <getopt.h>
#include "returncodes.h"
#include "rarray"
#include "rarrayio"

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: grav\n" 
      "\t[--ratpath=p|-r p]\n"
      "\t[--detection=f|-d f]\n"
      "\t[--prediction=p|-p p]\n"
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
   std::string ratPath{RATPATH} ;
   std::string detectionFileName{"detection01.rat"} ;
   std::string predictionFileName{"GWprediction.rat"} ;

   constexpr struct option longOptions[]{
     { "help",           0, NULL, 'h' },
     { "ratpath",        1, NULL, 'r' },
     { "detection",      1, NULL, 'd' },
     { "prediction",     1, NULL, 'p' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hr:d:p:", longOptions, NULL ) ) )
      { 
         switch ( c )
         {
            case 'r' :
            {
               line = __LINE__ ;
               ratPath = optarg ;

               break ;
            }
            case 'd' :
            {
               line = __LINE__ ;
               detectionFileName = optarg ;

               break ;
            }
            case 'p' :
            {
               line = __LINE__ ;
               predictionFileName = optarg ;

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

   using crarray = rarray<std::complex<double>, 1> ;

   crarray predictionData ;
   crarray detectionData ;

   return (int)RETURNCODES::SUCCESS ;
}
