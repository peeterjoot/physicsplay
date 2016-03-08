/** \file ratToCsv.cc

   Read in one .rat file and write out a .csv file for plotting.
  */
#include "integers.h"
#include <iostream>
#include <string>
#include <getopt.h>
#include "returncodes.h"
#include "rarray"
#include "rarrayio"
#include "fftstate.h"
#include <fstream>
#include <complex>
#include "stdoutfilestream.h"
#include "swapFileNameSuffix.h"
#include "ratData.h"
#include "myexceptions.h"
#include <boost/exception/diagnostic_information.hpp>

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: grav\n" 
      "\t[--ratpath=p|-r p]\n"
      "\t[--filename=f|-d f]\n"
      "\t[--help]" << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

void outputSignalForPlotting( const std::string & infile,
                              const ratData &     r )
{
   auto outFileName { replaceFileSuffix( infile, "rat", "csv" ) } ;

   r.writeToCsv( outFileName ) ;
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   int c{0} ;
   int line{0} ;
   std::string ratPath{RATPATH} ;
   std::string fileName{} ;

   constexpr struct option longOptions[]{
     { "help",           0, NULL, 'h' },
     { "ratpath",        1, NULL, 'r' },
     { "filename",       1, NULL, 'f' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hr:f:", longOptions, NULL ) ) )
      { 
         switch ( c )
         {
            case 'r' :
            {
               line = __LINE__ ;
               ratPath = optarg ;

               break ;
            }
            case 'f' :
            {
               line = __LINE__ ;
               fileName = std::string(optarg) ;

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
      ratData data ;

      data.open( ratPath, fileName ) ;

#if 0 
      assert( 
         ( (intptr_t)(&data.m_timesOrPower[0] & 0xF) == 0 ) &&
         ( (intptr_t)(&data.m_signalOrFFT[0] & 0xF) == 0 ) &&

std::cout << "pointers" << std::endl ;
std::cout << &data.m_timesOrPower[0] << std::endl ;
std::cout << &data.m_signalOrFFT[0] << std::endl ;
#endif

      outputSignalForPlotting( fileName, data ) ;
   } 
   catch (boost::exception & e)
   {
      auto s { boost::diagnostic_information( e ) } ;
      std::cout << s << std::endl ;

      return (int)RETURNCODES::EXCEPTION ;
   }

   return (int)RETURNCODES::SUCCESS ;
}
