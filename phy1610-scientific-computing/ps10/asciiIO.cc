/** \file asciiIO.cc */
#include "asciiIO.h"
#include "stdoutfilestream.h"

asciiIO::asciiIO( const std::string & fileBaseName, const int rank )
   : iohandlerImplementation( rank )
{
   const std::string filename{ fileBaseName + "_" + std::to_string( rank ) + ".out" } ;

   openStreamForWriteOrThrow( filename, m_file ) ;
}

void asciiIO::writeData( const float           time,
                         const size_t          globalOffset,
                         const size_t          localN,
                         const float * const   localXstart,
                         const float * const   localRhoStart )
{
   // It's useful for testing ascii output to write out the ghost cells too:
   for ( int i{-1} ; i <= (int)localN ; i++ )
   {
      int j = i + 1 + globalOffset ;

      m_file << m_outStepCount << ", " << j << ", " << localXstart[i] << ", " << localRhoStart[i] << '\n' ;
   }

   m_times.push_back( time ) ;
   m_outStepCount++ ;
}

void asciiIO::writeMeta( const size_t          globalOffset,
                         const size_t          localN,
                         const float * const   localXstart,
                         const float * const   localRhoStart )
{
   writeData( 0,
              globalOffset,
              localN,
              localXstart,
              localRhoStart ) ;
}

void asciiIO::close( )
{
   if ( 0 == m_rank )
   {
      for ( size_t i{0} ; i < m_times.size() ; i++ )
      {
         m_file << "# " << i << ", " << m_times[i] << '\n' ;
      }
   }
}

asciiIO::~asciiIO( )
{
   // member destructors will close the file if open.
}
