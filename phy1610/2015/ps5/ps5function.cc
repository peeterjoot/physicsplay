#include "ps5function.h"
#include <cmath>

double ps5function::function( double x, void * params )
{
   double xSquared = x * x ;
   double eOneMinusXSquared = std::exp( 1.0 - xSquared ) ;
   double eSinX = std::exp( std::sin( x ) ) ;

   return (eOneMinusXSquared - 1.0) * eSinX ;
}

double ps5function::derivative( double x, void * params )
{
   double xSquared = x * x ;
   double eOneMinusXSquared = std::exp( 1.0 - xSquared ) ;
   double eSinX = std::exp( std::sin( x ) ) ;

   return -( 2 * x * eOneMinusXSquared + std::cos(x) ) * eSinX ;
}

void ps5function::functionAndDerivative( double x, void * params, double *y, double *dy )
{
   double xSquared = x * x ;
   double eOneMinusXSquared = std::exp( 1.0 - xSquared ) ;
   double eSinX = std::exp( std::sin( x ) ) ;
   double cosX = std::cos( x ) ) ;

   *y = (eOneMinusXSquared - 1.0) * eSinX ;
   *dy = -( (2 * x + cosX) * eOneMinusXSquared + cosX ) * eSinX ;
}
