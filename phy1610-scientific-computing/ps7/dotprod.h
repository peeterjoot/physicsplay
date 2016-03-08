/** \file dotprod.h
 */
#if !defined phy1610_dotprod_h_included
#define phy1610_dotprod_h_included

#include "rarray"
#include <cblas.h>

/**
   Compute the dot product of two real (double typed) vectors using cblas_ddot.
 */
double dotprod( const rarray<double, 1> & f, const rarray<double, 1> & g ) ;

#endif
