#include "integers.h"
#include <iostream>
#include <string>
#include <getopt.h>
#include "returncodes.h"
#include "rarray"
#include "rarrayio"
#include <fstream>
#include <complex>

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

using carray = rarray<std::complex<double>, 1> ;
using darray = rarray<double, 1> ;

struct ratData
{
   darray   m_times ;
   carray   m_signal ;
} ;

void openRatFile( const std::string filename, ratData & r )
{
   // open the file
   std::ifstream f( filename ) ;

   // read in the signal
   f >> r.m_times ;
   f >> r.m_signal ;
}

inline std::string fullyQualifyPathWithDirectory( const std::string directoryName, const std::string fileName )
{
   if ( fileName[0] != '/' )
   {
      return directoryName + "/" + fileName ;
   }
   else
   {
      return fileName ;
   }
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
               detectionFileName = ratPath + "/" + std::string(optarg) ;

               break ;
            }
            case 'p' :
            {
               line = __LINE__ ;
               predictionFileName = ratPath + "/" + std::string(optarg) ;

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

   predictionFileName = fullyQualifyPathWithDirectory( ratPath, predictionFileName ) ;
   detectionFileName = fullyQualifyPathWithDirectory( ratPath, detectionFileName ) ;

   ratData predictionData ;
   ratData detectionData ;

   openRatFile( detectionFileName, detectionData ) ;
   openRatFile( predictionFileName, predictionData ) ;

   return (int)RETURNCODES::SUCCESS ;
}
