/** \file ps5function.h
 */
#if !defined phy1610_ps5_ps5function_h_included
#define phy1610_ps5_ps5function_h_included

/**
   A gsl function parameter object, also supplying the function pointers for both the interval and 
   derivative solvers.
 */
struct ps5function
{
   /**
      Returns \f[ (\exp(1-x^2) -1) e^{\sin x} \f]
     */
   static double function( double x, void * params ) ;

   static double derivative( double x, void * params ) ;

   static void functionAndDerivative( double x, void * params, double * y, double * dy ) ;

   static inline double expectedRoot()
   {
      // -1.0 is also a root.
      return 1.0 ;
   }
} ;

#endif
