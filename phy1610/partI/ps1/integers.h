/**
   \file integers.h

   Some convienence definitions for integer types.
 */
#if !defined integers_h
#define integers_h

#include <cstdint>
#include <string>

/**
   Register sized unsigned integer type for loop counters and so forth.
 */
using Uint = std::uintptr_t ;

/**
   wrapper for stoul to match the type of Uint above.
 */
#if defined _WIN64
   #define strToUint std::stoull
#else
   #define strToUint std::stoul
#endif

/**
   Force a compilation error if size assumptions are invalid.
 */
inline void strToUintAssumptions()
{
#if defined _WIN64
   static_assert( sizeof(Uint) == sizeof(unsigned long long), "bad assumptions about sizeof uintptr_t, long long" ) ;
#else
   static_assert( sizeof(Uint) == sizeof(unsigned long), "bad assumptions about sizeof uintptr_t, long" ) ;
#endif
}

#endif
