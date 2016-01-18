/**
   \file quadradic.cc

   These functions are taken directly from the gsl documentation examples for the fsolver and fdfsolver interfaces.
 */
#include "quadratic.h"

double quadratic::function( double x, void * params )
{
   struct quadratic * p = (struct quadratic *) params ;
   double a = p->a ;
   double b = p->b ;
   double c = p->c ;
   return (a * x + b) * x + c ;
}

double quadratic::derivative( double x, void * params )
{
   struct quadratic * p = (struct quadratic *) params ;

   double a = p->a ;
   double b = p->b ;
   return 2.0 * a * x + b ;
}

void quadratic::functionAndDerivative( double x, void * params, double * y, double * dy )
{
   struct quadratic * p = (struct quadratic *) params ;

   double a = p->a ;
   double b = p->b ;
   double c = p->c ;

   *y = (a * x + b) * x + c ;
   *dy = 2.0 * a * x + b ;
}
