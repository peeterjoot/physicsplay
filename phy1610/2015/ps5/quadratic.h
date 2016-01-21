/** \file quadratic.h
 */
#if !defined phy1610_ps5_quadratic_h_included
#define phy1610_ps5_quadratic_h_included

#include <cmath>

/**
   A gsl function parameter object, also supplying the function pointers for both the interval and
   derivative solvers.

   These functions supply the quadradic function taken directly from the gsl documentation.
 */
struct quadratic
{
   double a ;
   double b ;
   double c ;

   quadratic() : a{1.0}, b{0.0}, c{-5.0} {}

   static double function( double x, void * params ) ;
   static double derivative( double x, void * params ) ;
   static void functionAndDerivative( double x, void * params, double * y, double * dy ) ;

   static inline double expectedRoot()
   {
      return std::sqrt( 5.0 ) ;
   }
} ;

#endif
