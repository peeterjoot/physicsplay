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
    const int n = a.get_rows();
    const int m = a.get_columns();
    const int k = c.get_columns();

    // ensure sizes are compatible
    assert(a.get_columns() == b.get_rows());
    assert(a.get_rows() == c.get_rows());
    assert(b.get_columns() == c.get_columns());

    // compute the product element by element: 
    // i is the row index of result matrix c, j is its column index.
    for (int i=0; i<n; i++) {     
        for (int j=0; j<k; j++) {  
            // initialize c[i][j] element to zero
            c.set_element(i, j, 0.0);
            for (int j2=0; j2<m; j2++) {
                // accumulate result
                double newvalue = c.get_element(i,j) + a.get_element(i,j2)*b.get_element(j2,j);
                c.set_element(i, j, newvalue);
            }
        }
    }
}


