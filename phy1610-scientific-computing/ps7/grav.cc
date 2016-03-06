#include "integers.h"
#include <iostream>
#include <string>
#include <getopt.h>
#include "returncodes.h"
#include "rarray"
#include "rarrayio"
#include <fstream>
#include <complex>
#include <cassert>
#include "stdoutfilestream.h"
#include "swapFileNameSuffix.h"
#include <boost/exception/diagnostic_information.hpp>

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

inline std::string fullyQualifyPathWithDirectory( const std::string directoryName, const std::string fileName )
{
   if ( (fileName[0] != '/') && (directoryName != "") )
   {
      return directoryName + "/" + fileName ;
   }
   else
   {
      return fileName ;
   }
}

void openRatFile( const std::string ratPath, const std::string filename, ratData & r )
{
   std::string qualPath = fullyQualifyPathWithDirectory( ratPath, filename ) ;

   // open the file
   std::ifstream f( qualPath ) ;

   // read in the signal
   f >> r.m_times ;
   f >> r.m_signal ;
}

void outputSignalForPlotting( const std::string infile, const ratData & r )
{
   // open an output file, throwing an exception on failure.
   std::ofstream f{} ;

   auto outFileName = replaceFileSuffix( infile, "rat", "csv" ) ;

   openStreamForFile( f, outFileName ) ;

   auto size = r.m_times.size() ;
   assert( size == r.m_signal.size() ) ;

   for ( decltype(size) i = 0 ; i < size ; i++ )
   {
      auto t = r.m_times[i] ;
      auto v = r.m_signal[i] ;

      f << t << "," << v.real() << "," << v.imag() << std::endl ;
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

   try {
      ratData predictionData ;
      ratData detectionData ;

      openRatFile( ratPath, detectionFileName, detectionData ) ;
      openRatFile( ratPath, predictionFileName, predictionData ) ;

      outputSignalForPlotting( detectionFileName, detectionData ) ;
      outputSignalForPlotting( predictionFileName, predictionData ) ;

      return (int)RETURNCODES::SUCCESS ;
   } 
   catch (boost::exception & e)
   {
      std::string s = boost::diagnostic_information( e ) ;
      std::cout << s << std::endl ;

      return (int)RETURNCODES::EXCEPTION ;
   }
}
