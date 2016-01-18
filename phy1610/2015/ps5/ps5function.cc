#include "ps5function.h"
#include <cmath>

double ps5function::function( double x, void * params )
{
   double xx = x * x ;
   double exx = std::exp( 1.0 - xx ) ;
   double es = std::exp( std::sin( x ) ) ;

   return (exx - 1.0) * es ;
}

double ps5function::derivative( double x, void * params )
{
   double xx = x * x ;
   double exx = std::exp( 1.0 - xx ) ;
   double es = std::exp( std::sin( x ) ) ;

   return -( 2 * x * exx + std::cos(x) ) * es ;
}

void ps5function::functionAndDerivative( double x, void * params, double *y, double *dy )
{
   double xx = x * x ;
   double exx = std::exp( 1.0 - xx ) ;
   double es = std::exp( std::sin( x ) ) ;

   *y = (exx - 1.0) * es ;
   *dy = -( 2 * x * exx + std::cos(x) ) * es ;
}
