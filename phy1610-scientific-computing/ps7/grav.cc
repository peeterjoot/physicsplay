/** 
   \file grav.cc

   Main driver for the ps7 assignment.
 */
#include <iostream>
#include <string>
#include <getopt.h>
#include <fstream>
#include <cassert>
#include <utility>
#include <boost/exception/diagnostic_information.hpp>
#include "integers.h"
#include "returncodes.h"
#include "fftstate.h"
#include "stdoutfilestream.h"
#include "dotprod.h"
#include "ratData.h"

/**
   getopt handling helper function.
 */
void parseArgs( int argc, char ** argv, std::string & ratPath ) ;

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   std::string ratPath{RATPATH} ;

   try {
      ratData                    pred ;
      using                      results_pair = std::pair<std::string, double> ;
      std::vector<results_pair>  cvec ;
      ratData                    det ;

      // 1. Read the predicted GW signal from GWprediction.rat.
      pred.open( ratPath, "GWprediction.rat" ) ;

      // 3a. Compute the FFT of the two complex quantities, using FFTW.
      fftstate                   fft( pred.m_signalOrFFT ) ; 
      fft.execute( pred.m_signalOrFFT ) ;

      // 4a. Compute the power spectrum of both signals.
      pred.calculatePowerSpectrum() ;
      //pred.writeToCsv( "GWpredictionFFT.csv" ) ;
      //pred.writePowerSpectrumToFile( "GWpredictionFFTPower.txt" ) ;

      correlator                 correlation( pred.m_timesOrPower ) ;
      constexpr Uint             firstDetFileNumber{1} ;
      constexpr Uint             lastDetFileNumber{32} ;
      constexpr Uint             numberOfTopCorrelationsToDisplay{5} ;

      std::cout << "Correlations by detector filename\n\n" ;

      // 7. Repeat steps 2-to-6 for each of the signals in the observation set.
      for ( Uint i{ firstDetFileNumber } ; i <= lastDetFileNumber ; i++ )
      {
         char detFileName[32] ; 
         snprintf( detFileName, sizeof(detFileName), "detection%02d.rat", (int)i ) ;

         // 2. Read one of the GW signal from observations detection01.rat ...detection32.rat.
         det.open( ratPath, detFileName ) ;

         // 3b. Compute the FFT of the two complex quantities, using FFTW.
         fft.execute( det.m_signalOrFFT ) ;

         // 4b. Compute the power spectrum of both signals.
         det.calculatePowerSpectrum() ;
         //det.writeToCsv( "detection01FFT.csv" ) ;
         //det.writePowerSpectrumToFile( "detection01Power.txt" ) ;
         // break;

         // 5. Compute the correlation coefficient between the power spectra as defined in Eq. (1), using a ?dot BLAS call for the inner product from Eq. (3).
         double c{ correlation( det.m_timesOrPower ) } ;

         // 6. Output the correlation coefficient
         std::cout << detFileName << ' ' << c << std::endl ;

         cvec.push_back( std::make_pair( std::string(detFileName), c ) ) ;
      }

      // 8. Finally, determine the 5 most significant candidates (those with the 5 largest values of the correlation coefficient) from the observations set.

      // This is a c++14 style in-place sort, similar to a perl sort, where the sort function is also specified inline:
      // http://stackoverflow.com/a/279878/189270
      std::sort( cvec.begin(), cvec.end(), [](auto & left, auto & right) { return left.second > right.second ; } ) ;

      // With c++11, auto can't be used for the function parameter types, instead requiring:
      //std::sort( cvec.begin(), cvec.end(), [](results_pair & left, results_pair & right) { return left.second > right.second ; } ) ;

      std::cout << "\nTop " << numberOfTopCorrelationsToDisplay << " correlations\n\n" ;

      for ( Uint i{ 0 } ; i < numberOfTopCorrelationsToDisplay ; i++ )
      {
         std::cout << cvec[i].first << ' ' << cvec[i].second << std::endl ;
      }
   }
   catch (boost::exception & e)
   {
      auto s { boost::diagnostic_information( e ) } ;
      std::cout << s << std::endl ;

      return (int)RETURNCODES::EXCEPTION ;
   }

   return (int)RETURNCODES::SUCCESS ;
}

/**
   Print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: grav\n" 
      "\t[--ratpath=p|-r p]\n"
      "\t[--help]" << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

void parseArgs( int argc, char ** argv, std::string & ratPath )
{
   int c{0} ;
   int line{0} ;

   constexpr struct option longOptions[]{
     { "help",           0, NULL, 'h' },
     { "ratpath",        1, NULL, 'r' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hr:", longOptions, NULL ) ) )
      { 
         switch ( c )
         {
            case 'r' :
            {
               line = __LINE__ ;
               ratPath = optarg ;

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
}
