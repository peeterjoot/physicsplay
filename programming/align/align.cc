#include <stdlib.h>
#include <assert.h>

void foo( char * b ) ;

int main()
{
   char * b ;
   int rc = posix_memalign( (void **)&b, 64, 128 ) ;

   for ( int j = 0 ; j < 100000000 ; j++ )
   {
      for ( int i = 0 ; i < 64 ; i++ )
      {
         foo( b + i ) ;
      }
   }

   return 0 ;
}
