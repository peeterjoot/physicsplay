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

void multiply(MyMatrix &a, MyMatrix &b, MyMatrix &c)
{
    // store dimensions of the arrays
    const Uint n = a.get_rows() ;
    const Uint m = a.get_columns() ;
    const Uint k = c.get_columns() ;

    // ensure sizes are compatible
    assert(m == b.get_rows()) ;
    assert(a.get_rows() == c.get_rows()) ;
    assert(b.get_columns() == k) ;

    // compute the product element by element:
    // i is the row index of result matrix c, j is its column index.
    for ( Uint i = 0 ; i < n ; i++ )
    {
        for ( Uint j = 0 ; j < k ; j++ )
        {
            // initialize c[i][j] element to zero
            // accumulate result
            double acc = 0.0 ;
            for ( Uint j2 = 0 ; j2 < m ; j2 ++)
            {
                acc += a.get_element(i,j2) * b.get_element(j2,j) ;
            }
            c.set_element(i, j, acc) ;
        }
    }
}
