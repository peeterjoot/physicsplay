/** \file ticks.h
 */
#if !defined phy1610_ticks_h_included
#define phy1610_ticks_h_included

#include <chrono>
#include "cpplevel.h"

/**
   Wrapper for std::chrono::high_resolution_clock to make the long namespace names a bit more tractible.
 */
class ticks
{
   using clock      = std::chrono::high_resolution_clock ;
   using time_point = clock::time_point ;

   time_point m_sample ;
public:

   static inline ticks sample()
   {
      ticks t ;
      t.m_sample = clock::now() ;

      return t ;
   }

   using duration   = decltype( m_sample - m_sample ) ;

   friend duration operator -( const ticks & a, const ticks & b ) ;
} ;

inline ticks::duration operator -( const ticks & a, const ticks & b )
{
   return a.m_sample - b.m_sample ;
}

inline auto durationToMicroseconds( ticks::duration & diff )
#if !defined HAVE_CPLUSPLUS_14
-> decltype(std::chrono::duration_cast<std::chrono::microseconds>( diff ).count())
#endif
{
   return std::chrono::duration_cast<std::chrono::microseconds>( diff ).count() ;
}

inline auto durationToNanoseconds( ticks::duration & diff )
#if !defined HAVE_CPLUSPLUS_14
-> decltype(std::chrono::duration_cast<std::chrono::nanoseconds>( diff ).count())
#endif
{
   return std::chrono::duration_cast<std::chrono::nanoseconds>( diff ).count() ;
}

#endif
