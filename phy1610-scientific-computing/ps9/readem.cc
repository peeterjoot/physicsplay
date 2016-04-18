/** \file readem.cc
 */
#include "readem.h"
#include <cstdlib>
#include <unistd.h>

void readem( const int fd, void * buf, const size_t bytes )
{
   ssize_t n = read( fd, buf, bytes ) ;

   if ( (size_t)n != bytes )
   {
      abort() ;
   }
}
