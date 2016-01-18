/** \file ps5function.h
 */
#if !defined phy1610_ps5_ps5function_h_included
#define phy1610_ps5_ps5function_h_included

struct ps5function
{
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
