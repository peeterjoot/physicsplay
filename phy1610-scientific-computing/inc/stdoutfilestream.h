/** \file stdoutfilestream.h

   Some basic IO related methods, for opening files or throwing errors, and a class
   that supplies a stdout-or-fileStream ostream handle.
 */
#if !defined phy1610_stdoutfilestream_h_included
#define phy1610_stdoutfilestream_h_included

#include <iostream>
#include <fstream>
#include <string>

/**
   set the exception state so that an open error throws.
 */
template <typename S>
inline void enableExceptionOnOpen( S & stream )
{
   stream.exceptions( std::ios::failbit | std::ios::badbit ) ;
}

/** open file for read, or throw boost::exception */
void openStreamForReadOrThrow( const std::string & filename, std::ifstream & stream ) ;

/** open file for write with truncate, or throw boost::exception */
void openStreamForWriteOrThrow( const std::string & filename, std::ofstream & stream ) ;

/**
   Provide a method that returns a stream reference, either to a file
   stream or stdout.
 */
class stdoutOrFileStream
{
   std::ofstream  m_streamHandle{} ;     ///< file handle when appropriate.
   bool           m_useFileHandle{} ;    ///< do we use the ofstream or cout?

public:

   /**
      open a file if filename represents a non-null string (pathname)
    */
   stdoutOrFileStream( const std::string & filename )
   {
      if ( filename.length() )
      {
         openStreamForWriteOrThrow( filename, m_streamHandle ) ;

         m_useFileHandle = true ;
      }
   }

   /**
      Return either the ofstream object or cout
    */
   std::ostream & handle( )
   {
      if ( m_useFileHandle )
      {
         return m_streamHandle ;
      }
      else
      {
         return std::cout ;
      }
   }
} ;

#endif
