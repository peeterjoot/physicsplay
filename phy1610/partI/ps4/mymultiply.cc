//
// mymultiply.cc - example matrix multiplication, header file.
//
// Part of the "Profiling and optimization" assignment of the
// "Scientific Software Development" mini-course by SciNet.
//
// For instructional purpose only.  Don't use in production code.
//
// Ramses van Zon, January 2015
//

#include "mymultiply.h"
#include <cassert>

// Matrix-multiply matrix a and b into matrix c
// memory of c should already be allocates.

void multiply(MyMatrix &a, MyMatrix &b, MyMatrix &c, const Uint tilesize )
{
   // store dimensions of the arrays
   const Uint n = a.get_rows() ;
   const Uint m = a.get_columns() ;
   const Uint r = b.get_columns() ;
   const Uint s = b.get_rows() ;

   // ensure sizes are compatible
   assert( m == r ) ;
   assert( m == c.get_rows() ) ;
   assert( s == c.get_columns() ) ;

   if ( !tilesize )   
   {
      // compute the product element by element:
      // i is the row index of result matrix c, j is its column index.
      for ( Uint i = 0 ; i < n ; i++ )
      {
         for ( Uint j = 0 ; j < s ; j++ )
         {
            // initialize c[i][j] element to zero
            // accumulate result
            double acc = 0.0 ;
            for ( Uint j2 = 0 ; j2 < m ; j2 ++)
            {
               acc += a.get_element( i, j2 ) * b.get_element( j2, j ) ;
            }

            c.set_element( i, j, acc ) ;
         }
      }
   }
   else
   {
      assert( 0 == (m % tilesize) ) ;
      assert( 0 == (n % tilesize) ) ;
      assert( 0 == (r % tilesize) ) ;
      assert( 0 == (s % tilesize) ) ;

      // todo.
   }
}
