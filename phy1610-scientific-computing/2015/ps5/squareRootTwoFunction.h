/** \file squareRootTwoFunction.h
 */
#if !defined phy1610_ps5_squareRootTwoFunction_h_included
#define phy1610_ps5_squareRootTwoFunction_h_included

#include <cmath>

/**
   A gsl function parameter object, also supplying the function pointers for both the interval and
   derivative solvers.
 */
struct squareRootTwoFunction
{
   /**
      Returns \f[
                 f(x) = x^2
              \f]

      \param x [in]
        Point at which to evaluate \f[ f(x) \f]

      \param params [in]
         ununsed
     */
   static double function( double x, void * params ) ;

   /**
      Returns \f[
                 f'(x) = 2 x
              \f]

      \param x [in]
         Point at which to evaluate \f[ f(x) \f]

      \param params [in]
         ununsed
     */
   static double derivative( double x, void * params ) ;

   /**
      Return both the function and the derivative.

      \param x [in]
         Evaluation point.

      \param params [in]
         ununsed

      \param y [out]
         \f[ f(x) \f]

      \param y [out]
         \f[ f'(x) \f]
     */
   static void functionAndDerivative( double x, void * params, double * y, double * dy ) ;

   /**
      Convience method to evaluate the function at this point without explicitly using function pointers.
    */
   double operator() ( const double x ) const
   {
      // gsl functions take void *, not const void *, to this needs coersion:
      return function( x, const_cast<squareRootTwoFunction*>(this) ) ;
   }

   /**
      For verbose output loops to show how close we are to the expected root.
    */
   static inline double expectedRoot()
   {
      return std::sqrt(2.0);
   }
} ;

#endif
