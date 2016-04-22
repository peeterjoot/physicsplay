/** \file metaToText.cc

   A hacky bit of debug code to read a binary non-metadata file (*000XX.out)
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
#include <boost/filesystem.hpp>

int main( int argc, char ** argv )
{
   IOmetaData meta ;

   assert( argc == 2 ) ;
//   std::cout << argv[1] << std::endl ;

   uintmax_t sz = boost::filesystem::file_size( argv[1] ) ;
   uintmax_t nElements = sz/sizeof(float) ;

   int fd = open( argv[1], O_RDONLY ) ;
   if ( -1 == fd )
   {
      abort() ;
   }

   std::vector<float> rho( nElements ) ;
   readem( fd, &rho[0], sizeof(rho[0]) * nElements ) ;

   for ( auto rv : rho )
   {
      std::cout << rv << '\n' ;
   }

   return 0 ;
}
