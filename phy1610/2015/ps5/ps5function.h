/** \file ps5function.h
 */
#if !defined phy1610_ps5_ps5function_h_included
#define phy1610_ps5_ps5function_h_included

#include "externc.h"

struct ps5function_params
{
} ;

EXTERNC double ps5function( double x, void * params ) ;
EXTERNC double ps5function_deriv( double x, void * params ) ;
EXTERNC void ps5function_fdf( double x, void * params, double *y, double *dy ) ;

#endif
