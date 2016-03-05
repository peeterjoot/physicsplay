/** \file stdoutfilestream.h
 */
#if !defined phy1610_stdoutfilestream_h_included
#define phy1610_stdoutfilestream_h_included

#include <iostream>
#include <fstream>
#include <string>

/**
   open a file for write, throwing an exception if the open fails.
 */
inline void openStreamForFile( std::ofstream &           stream,
                               const std::string &       filename,
                               std::ios_base::openmode   mode = std::ios_base::out | std::ios_base::trunc )
{
   // throw an exception if the open fails
   stream.exceptions( std::ios::failbit | std::ios::badbit ) ;

   stream.open( filename.c_str(), mode ) ;
}

/**
   Provide a method that returns a stream reference, either to a file
   stream or stdout.
 */
class stdoutOrFileStream
{
   std::ofstream  m_streamHandle ;     ///< file handle when appropriate.
   bool           m_useFileHandle ;    ///< do we use the ofstream or cout?
   
public:

   /**
      open a file if filename represents a non-null string (pathname)
    */
   stdoutOrFileStream( const std::string & filename )
      : m_streamHandle{},
        m_useFileHandle{false}
   {
      if ( filename.length() )
      {
         openStreamForFile( m_streamHandle, filename ) ;

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
