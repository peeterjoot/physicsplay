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
#include "ticks.h"

/**
   getopt handling.
 */
struct parseArgs
{
   std::string m_ratPath{RATPATH} ;
   bool        m_showTimes{false} ;

   parseArgs( int argc, char ** argv ) ;
} ;

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   parseArgs a( argc, argv ) ;

   try {
      ratData                    pred ;
      using                      results_pair = std::pair<std::string, double> ;
      std::vector<results_pair>  cvec ;
      ratData                    det ;

      // 1. Read the predicted GW signal from GWprediction.rat.
      pred.open( a.m_ratPath, "GWprediction.rat" ) ;

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
      ticks::duration iotime{} ;
      ticks::duration ffttime{} ;
      ticks::duration pstime{} ;
      ticks::duration cortime{} ;

      std::cout << "Correlations by detector filename\n\n" ;

      // 7. Repeat steps 2-to-6 for each of the signals in the observation set.
      for ( Uint i{ firstDetFileNumber } ; i <= lastDetFileNumber ; i++ )
      {
         char detFileName[32] ; 
         snprintf( detFileName, sizeof(detFileName), "detection%02d.rat", (int)i ) ;

         ticks t1 = ticks::sample() ;
         // 2. Read one of the GW signal from observations detection01.rat ...detection32.rat.
         det.open( a.m_ratPath, detFileName ) ;

         ticks t2 = ticks::sample() ;
         // 3b. Compute the FFT of the two complex quantities, using FFTW.
         fft.execute( det.m_signalOrFFT ) ;

         ticks t3 = ticks::sample() ;
         // 4b. Compute the power spectrum of both signals.
         det.calculatePowerSpectrum() ;
         //det.writeToCsv( "detection01FFT.csv" ) ;
         //det.writePowerSpectrumToFile( "detection01Power.txt" ) ;
         // break;
         ticks t4 = ticks::sample() ;

         // 5. Compute the correlation coefficient between the power spectra as defined in Eq. (1), using a ?dot BLAS call for the inner product from Eq. (3).
         double c{ correlation( det.m_timesOrPower ) } ;

         ticks t5 = ticks::sample() ;

         iotime  += (t2 - t1) ;
         ffttime += (t3 - t2) ;
         pstime  += (t4 - t3) ;
         cortime += (t5 - t4) ;

         // 6. Output the correlation coefficient
         std::cout << detFileName << ' ' << c << std::endl ;

         cvec.push_back( std::make_pair( std::string(detFileName), c ) ) ;
      }

      // 8. Finally, determine the 5 most significant candidates (those with the 5 largest values of the correlation coefficient) from the observations set.

      // This is a c++14 style in-place sort, similar to a perl sort, where the sort function is also specified inline:
      // http://stackoverflow.com/a/279878/189270
      std::sort( cvec.begin(), cvec.end(), [](auto & left, auto & right) { return left.second > right.second ; } ) ;
      // With c++11, auto can't be used for the function parameter types, instead requiring:
      //std::sort( cvec.begin(), cvec.end(), [](const results_pair & left, const results_pair & right) { return left.second > right.second ; } ) ;

      std::cout << "\nTop " << numberOfTopCorrelationsToDisplay << " correlations\n\n" ;

      for ( Uint i{ 0 } ; i < numberOfTopCorrelationsToDisplay ; i++ )
      {
         std::cout << cvec[i].first << ' ' << cvec[i].second << std::endl ;
      }

      if ( a.m_showTimes )
      {
         std::cout << "\nIO time for .rat reads:         \t" << durationToMicroseconds( iotime )  << " (us).\n" ;
         std::cout <<   "FFT time:                       \t" << durationToMicroseconds( ffttime ) << " (us).\n" ;
         std::cout <<   "Power spectrum calculation time:\t" << durationToMicroseconds( pstime )  << " (us).\n" ;
         std::cout <<   "Correlation calculation time:   \t" << durationToMicroseconds( cortime ) << " (us).\n" ;
      }
   }
   catch (boost::exception & e)
   {
      auto s{ boost::diagnostic_information( e ) } ;
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
      "\t[--ratpath=p|-r p] Specify the path for the input .rat files.\n"
      "\t[--time|-t] Show elapsed times for component calculations.\n"
      "\t[--help]" << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

parseArgs::parseArgs( int argc, char ** argv )
{
   int c{0} ;
   int line{0} ;

   constexpr struct option longOptions[]{
     { "help",           0, NULL, 'h' },
     { "ratpath",        1, NULL, 'r' },
     { "time",           0, NULL, 't' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hr:t", longOptions, NULL ) ) )
      { 
         switch ( c )
         {
            case 'r' :
            {
               line = __LINE__ ;
               m_ratPath = optarg ;

               break ;
            }
            case 't' :
            {
               m_showTimes = true ;

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
