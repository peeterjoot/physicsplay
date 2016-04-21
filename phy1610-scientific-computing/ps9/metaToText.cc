/** \file metaToText.cc
  
   A hacky bit of debug code to read a binary metadata file (*00000.out)
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <vector>
#include <stdlib.h>
#include "iometadata.h"
#include <iostream>
#include "readem.h"
//#include <boost/filesystem.hpp>

// read one float at a time, count how many were read, and exit when done.
//
// would be better to batch using file_size calculation (subtracting the other stuff in the file to get at the number of
// time output events processed).
//
//uintmax_t sz = boost::filesystem::file_size(argv[1]) << '\n' ;
void readandprintfloat( const int fd )
{
   float f ;
   static int numtimes{ 0 } ;
   ssize_t n = read( fd, &f, sizeof(f) ) ;

   if ( (size_t)n == sizeof(f) )
   {
      std::cout << f << '\n' ;
      numtimes++ ;
   }
   else
   {
      std::cout << "ntimes: "      << numtimes << '\n' ;

      exit(0) ;
   }
}

int main( int argc, char ** argv )
{
   IOmetaData meta ;

   assert( argc == 2 ) ;
//   std::cout << argv[1] << std::endl ;

   int fd = open( argv[1], O_RDONLY ) ;
   if ( -1 == fd )
   {
      abort() ;
   }

   readem( fd, &meta, sizeof(meta) ) ;

   std::cout << "nper: "      << meta.nper      << '\n' ;
   std::cout << "numPoints: " << meta.numPoints << '\n' ;
   std::cout << "x:\n" ;

   std::vector<float> x( meta.numPoints ) ;
   readem( fd, &x[0], sizeof(float)* meta.numPoints ) ;

   for ( auto xv : x )
   {
      std::cout << xv << '\n' ;
   }

   std::cout << "times:\n" ;
   while ( true )
   {
      readandprintfloat( fd ) ;
   }

   return 0 ;
}
