/** \file carray.h
 */
#if !defined phy1610_carray_h_included
#define phy1610_carray_h_included

#include "rarray"
#include <complex>

/**
   Helper typedef for a complex 1D signal array.
 */
using carray = rarray<std::complex<double>, 1> ;

#endif
