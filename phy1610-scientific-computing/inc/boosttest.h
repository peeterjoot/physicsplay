/** \file boosttest.h

   Deal with cygwin quirks if we attempt to use boost test there.
 */
#if !defined phy1610_boosttest_h_included
#define phy1610_boosttest_h_included

#if defined USE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK
   #include <boost/test/included/unit_test.hpp>

   #if defined __STRICT_ANSI__
      #error cygwin boost/test/unit_test.hpp requires putenv and mkstemp in the global namespace.  Add -U__STRICT_ANSI__
   #endif
#else
   #define BOOST_TEST_DYN_LINK

   #include <boost/test/unit_test.hpp>
#endif

#define USE_BOOST_REQUIRE_AS_ASSERT

#endif
