/** \file myassert.h
 */
#if !defined phy1610_myassert_h_included
#define phy1610_myassert_h_included

#if defined USE_BOOST_REQUIRE_AS_ASSERT
   // If boosttest.h has been included (which includes the boost test headers), use that and not assert:
   #define myassert( predicate ) BOOST_REQUIRE( predicate )
#else
   #include <cassert>

   #define myassert( predicate ) assert( predicate )
#endif

#endif
