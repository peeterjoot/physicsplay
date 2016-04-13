/** \file asciiIO.cc */
#include "asciiIO.h"
#include "stdoutfilestream.h"

asciiIO::asciiIO( const std::string & fileBaseName )
{
   const std::string filename{ fileBaseName + ".out" } ;

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

      m_file << time << " : " << j << ", " << localXstart[i] << ", " << localRhoStart[i] << '\n' ;
   }
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

asciiIO::close( )
{
}

asciiIO::~asciiIO( )
{
   // member destructors will close the file if open.
}
