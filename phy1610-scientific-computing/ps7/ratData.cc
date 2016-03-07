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
   std::string qualPath = fullyQualifyPathWithDirectory( ratPath, filename ) ;

   // open the file
   std::ifstream f{} ;

   openStreamForReadOrThrow( qualPath, f ) ;

   // read in the signal
   f >> m_times ;
   f >> m_signal ;
}

void ratData::writeToCsv( const std::string outFileName ) const
{
   // open an output file, throwing an exception on failure.
   std::ofstream f{} ;

   openStreamForWriteOrThrow( outFileName, f ) ;

   auto size = m_times.size() ;
   if ( size != m_signal.size() )
   {
      BOOST_THROW_EXCEPTION(
           array_size_error()
              << asize_info( size )
              << asize_info( m_signal.size() )
           ) ;
   }

   for ( decltype(size) i = 0 ; i < size ; i++ )
   {
      auto t = m_times[i] ;
      auto v = m_signal[i] ;

      f << t << "," << v.real() << "," << v.imag() << std::endl ;
   }
}
