/**
   \file streamopen.cc

   Methods to open a file for read or for write (with truncate).  Throws an error with the filename
   if open fails.
 */
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include "myexceptions.h"
#include "stdoutfilestream.h"

/**
   Put the stream in a mode where an exception will be thrown on error, then open the file in the desired mode.

   If this fails, then throw an error detailing the filename, and propogate the exception message.
 */
template <typename streamType>
void openStream( const std::string &                  filename,
                 streamType &                         stream,
                 const decltype(std::ios_base::in)    mode )
{
   enableExceptionOnOpen( stream ) ;

   try {
      stream.open( filename, mode ) ;
   }
   catch ( std::ios_base::failure & e )
   {
      // rethrow with file/line/... attributes.
      BOOST_THROW_EXCEPTION(
            file_open_error()
               << open_info( e.what() )
               << name_info( filename ) ) ;
   }
}

void openStreamForReadOrThrow( const std::string &   filename,
                               std::ifstream &       stream )
{
   openStream<std::ifstream>( filename,
                              stream,
                              std::ios_base::in ) ;
}

void openStreamForWriteOrThrow( const std::string &   filename,
                                std::ofstream &       stream )
{
   openStream<std::ofstream>( filename,
                              stream,
                              std::ios_base::out | std::ios_base::trunc ) ;
}
