/** \file ratData.cc */
#include "stdoutfilestream.h"
#include "ratData.h"
#include "rarrayio"
#include "myexceptions.h"

/**
   helper function to fully qualify a file given a directory and the filename within that dir.

   restrictions: This function is Unix specific.
 */
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

void ratData::open( const std::string ratPath, const std::string filename )
{
   auto qualPath { fullyQualifyPathWithDirectory( ratPath, filename ) } ;

   // open the file
   std::ifstream f{} ;

   openStreamForReadOrThrow( qualPath, f ) ;

   // read in the signal
   f >> m_timesOrPower ;
   f >> m_signalOrFFT ;
}

void ratData::writeToCsv( const std::string outFileName ) const
{
   // open an output file, throwing an exception on failure.
   std::ofstream f{} ;

   openStreamForWriteOrThrow( outFileName, f ) ;

   auto size { m_timesOrPower.size() } ;
   if ( size != m_signalOrFFT.size() )
   {
      BOOST_THROW_EXCEPTION(
           array_size_error()
              << asize_info( size )
              << asize_info( m_signalOrFFT.size() )
           ) ;
   }

   for ( decltype(size) i{0} ; i < size ; i++ )
   {
      auto t { m_timesOrPower[i] } ;
      auto v { m_signalOrFFT[i] } ;

      f << t << "," << v.real() << "," << v.imag() << std::endl ;
   }
}

void ratData::writePowerSpectrumToFile( const std::string outFileName ) const
{
   // open an output file, throwing an exception on failure.
   std::ofstream f{} ;

   openStreamForWriteOrThrow( outFileName, f ) ;

   auto size { m_timesOrPower.size() } ;

   for ( decltype(size) i{0} ; i < size ; i++ )
   {
      f << m_timesOrPower[i] << std::endl ;
   }
}

void ratData::calculatePowerSpectrum()
{
   // Is there a BLAS method that can be used for this?
   auto size{ m_signalOrFFT.size() } ;

   for ( decltype(size) i{0} ; i < size ; i++ )
   {
      m_timesOrPower[i] = std::norm( m_signalOrFFT[i] ) ;
   }
}
