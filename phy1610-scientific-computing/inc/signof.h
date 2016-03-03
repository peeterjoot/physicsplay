/** \file signof.h
 */
#if !defined phy1610_signof_h_included
#define phy1610_signof_h_included

#include <cmath>

/**
   cygwin's math.h doesn't put copysign in the std:: namespace, even with g++ 5.3.0 -std=c++11
 */
inline double signof( const double v )
{
   #if defined __CYGWIN__
      return copysign( 1.0, v ) ;
   #else
      return std::copysign( 1.0, v ) ;
   #endif
}

#endif
