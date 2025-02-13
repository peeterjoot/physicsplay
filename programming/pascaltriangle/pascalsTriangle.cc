/*
 * Print Pascal's triangle up to a given size.
 *
 * Usage: pascalsTriangle [n]
 *
 * n = 10 by default.
 *
 * Example:
 * ./pascalsTriangle 6
         1
        1  1
      1  2  1
     1  3  3  1
   1  4  6  4  1
  1  5 10 10  5  1
 */
#include <stdio.h>
#include <stdlib.h>

/** For the last row of Pascal's triangle that we will print, figure out how many digits is required for one of the central values.
 *
 * This function and printrow both use a recurrence relationship to compute the binomial coefficient:
 *
 * \binom{n,k} = \binom{n,k-1} (n - k + 1)/k
 *
 */
static int biggest( int n ) {
   int binom = 1;

   for ( int k = 1 ; k < n/2 ; k++ ) {
      binom *= (n - k + 1);
      binom /= k;
   }

   int len = snprintf( NULL, 0, "%d", binom );
   return len;
}

/// Print a row of Pascal's triangle
static void printrow( int n, int m, int spaces ) {
   int binom = 1;
   int leading = (m - n - 1) * spaces/2;

   printf( "%*s%*d", leading, "", spaces, 1 );

   for ( int k = 1 ; k < n ; k++ ) {
      binom *= (n - k + 1);
      binom /= k;

      printf( "%*d", spaces, binom );
   }

   if ( n > 0 ) {
      printf( "%*d", spaces, 1 );
   }
   printf( "\n" );
}

int main( int argc, char ** argv ) {
   int m = 10;

   if ( argc == 2 ) {
      m = atoi( argv[1] );
   }

   if ( m <= 0 ) {
      fprintf( stderr, "invalid size: %d\n", m );
      return 1;
   }

   int spaces = biggest( m ) + 1;

   for ( int n = 0 ; n < m ; n++ ) {
      printrow( n, m, spaces );
   }

   return 0;
}

// vim: et ts=3 sw=3
