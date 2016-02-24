/** \file stdoutfilestream.h
 */
#if !defined phy1610_stdoutfilestream_h_included
#define phy1610_stdoutfilestream_h_included

#include <iostream>
#include <fstream>
#include <string>

/**
   Provide a method that returns a stream reference, either to a file
   stream or stdout.
 */
class stdoutOrFileStream
{
   std::ofstream  f ;             ///< file handle when appropriate.
   bool           useFileHandle ; ///< do we use the ofstream or cout?
   
public:

   /**
      open a file if filename represents a non-null string (pathname)
    */
   stdoutOrFileStream( const std::string & filename ) : f{}, useFileHandle{false}
   {
      // throw an exception if the open fails
      f.exceptions(std::ios::failbit | std::ios::badbit);

      if ( filename.length() )
      {
         f.open( filename.c_str() ) ;

         useFileHandle = true ;
      }
   }

   /**
      Return either the ofstream object or cout
    */
   std::ostream & handle( ) 
   {
      if ( useFileHandle )
      {
         return f ;
      }
      else
      {
         return std::cout ;
      }
   }
} ;

#endif
