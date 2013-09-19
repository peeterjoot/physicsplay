#include <stdio.h>
#include <math.h>

/** 
   Compute the Madelung constant for a cubic NaCl geometry with Cl- at the center.

   This would be a poor way to compute if the calculation is already done for a m-1 sided cube.
 */
double NaClMadelungRect( const double m )
{
   double madelung = 0.0 ;

   for ( int i = 0 ; i <= m ; i++ )
   {
      for ( int j = 0 ; j <= m ; j++ )
      {
         for ( int k = 0 ; k <= m ; k++ )
         {
            if ( i != 0 && j != 0 && k != 0 )
            {
               double t = 1.0 / sqrt( i^2 + j^2 + k^2 ) ;

               if ( 0 == ((i + j + k) % 2) )
               {
                  t *= -1 ;
               }

               madelung += t ;
            }
         }   
      }   
   }   

   return madelung ;
}

int main()
{
   for ( int i = 1 ; i <= 5 ; i++ )
   {
      double m = NaClMadelungRect( i ) ;

      printf( "%d: %f\n", i, m ) ;
   }

   return 0 ;
}
