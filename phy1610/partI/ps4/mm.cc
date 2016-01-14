//
// mm.cc - matrix multiplication example
//
// Part of the "Profiling and optimization" assignment of the
// "Scientific Software Development" mini-course by SciNet.
//
// Ramses van Zon, January 2015
//

#include "MyMatrix.h"
#include "mymultiply.h"
#include "ticktock.h"

// Function that initializes the matrix a with values increasing
// number from x up to and including x+1.
// (It should be obvious that this is a somewhat arbitrary fill to
// make the computation below non-trivial).

void initialize(MyMatrix& a, double x)
{
    // need total number of elements to know the per-element increment
    const int nelements = a.get_rows()*a.get_columns();
    // y will hold the next value to be inserted.
    double y = x;

    // loop over rows (i) and columns (j)
    for (Uint i=0; i<a.get_rows(); i++) {
        for (Uint j=0; j<a.get_columns(); j++) {
            a.set_element(i, j, y);
            // increment y such that the last set element is x+1
            y += 1.0/(nelements-1);  
        }
    }
}

// Main routine: sets up matrices, multiplies that, writes them to files.

int main()
{
    // start a timer
    TickTock timer;
    timer.tick(); 

    // construct the matrices a,b, and c to be of size n x n, where n = 500
    const int n = 500;
    MyMatrix a(n, n);
    MyMatrix b(n, n);
    MyMatrix c(n, n);

    // initialize a and b
    initialize(a, 0);
    initialize(b, 1);

    // preform multiplication
    multiply(a, b, c);

    // write out both the input matrices a and b, and the result matrix c.
    a.output("a.dat");
    b.output("b.dat");
    c.output("c.dat");

    // measure how long this took.
    timer.tock("Total time:");

    // done, all is well
    return 0;
}
