#include "myexceptions.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include "stdoutfilestream.h"

template <typename streamType>
void openStream( std::string filename, streamType & stream, const decltype(std::ios_base::in) mode )
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

void openStreamForReadOrThrow( std::string filename, std::ifstream & stream )
{
   openStream<std::ifstream>( filename, stream, std::ios_base::in ) ;
}

void openStreamForWriteOrThrow( std::string filename, std::ofstream & stream )
{
   openStream<std::ofstream>( filename, stream, std::ios_base::out | std::ios_base::trunc ) ;
}
