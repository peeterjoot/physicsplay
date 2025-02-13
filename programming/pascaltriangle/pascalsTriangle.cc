#include <stdio.h>
#include <string>

int m = 10;

void printrow( int n, int spaces ) {
   int binom = 1;
   int leading = (m - n) * spaces/2;

   printf( "%*s%*d", leading, "", spaces, 1 );

   for ( int k = 1 ; k < n ; k++ ) {
      binom *= (n - k + 1);
      binom /= k;

      printf( "%*d", spaces, binom );
   }

   if ( n > 0 ) {
      printf( "%*d\n", spaces, 1 );
   } else {
      printf( "\n" );
   }
}

int main( int argc, char ** argv ) {
   if ( argc == 2 ) {
      m = std::stoi( argv[1] );
   } 

   int spaces = 1;
   if ( m >= 5 ) {
      spaces++;
   }
   if ( m >= 9 ) {
      spaces += 2;
   }
   if ( m >= 14 ) {
      spaces += 2;
   }

   for ( int n = 0 ; n < m ; n++ ) {
      printrow( n, spaces ); 
   }

   return 0;
}

// vim: et ts=3 sw=3
