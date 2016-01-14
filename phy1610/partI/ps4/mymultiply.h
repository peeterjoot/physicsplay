//
// mymultiply.h - example matrix multiplication, header file.
//
// Part of the "Profiling and optimization" assignment of the
// "Scientific Software Development" mini-course by SciNet.
//
// For instructional purpose only.  Don't use in production code.
//
// Ramses van Zon, January 2015
//

#ifndef MYMULTIPLYH
#define MYMULTIPLYH

#include "MyMatrix.h"

// Matrix-multiply matrix a and b into matrix c
// memory of c should already be allocates.

void multiply(MyMatrix &a, MyMatrix &b, MyMatrix &c);

#endif
