/**
   \file squareRootTwoFunction.cc
 */
#include "squareRootTwoFunction.h"
#include <cmath>

double squareRootTwoFunction::function( double x, void * params )
{
   return x * x - 2.0 ;
}

double squareRootTwoFunction::derivative( double x, void * params )
{
   return 2.0 * x ;
}

void squareRootTwoFunction::functionAndDerivative( double x, void * params, double *y, double *dy )
{
   *y = x * x - 2.0 ;
   *dy = 2.0 * x ;
}
