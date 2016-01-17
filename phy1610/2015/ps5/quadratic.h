/** \file quadratic.h
 */
#if !defined phy1610_ps5_quadratic_h_included
#define phy1610_ps5_quadratic_h_included

#include "externc.h"

struct quadratic_params
{
    double a, b, c ;
} ;

EXTERNC double quadratic( double x, void * params ) ;
EXTERNC double quadratic_deriv( double x, void * params ) ;
EXTERNC void quadratic_fdf( double x, void * params, double *y, double *dy ) ;

#endif
