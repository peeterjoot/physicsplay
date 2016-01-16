/** \file boosttest.h
 */
#if !defined phy1610_boosttest_h_included
#define phy1610_boosttest_h_included

#if defined USE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK
   #include <boost/test/included/unit_test.hpp>
#else
   #define BOOST_TEST_DYN_LINK

   #if defined __STRICT_ANSI__
      #error cygwin boost/test/unit_test.hpp requires putenv and mkstemp in the global namespace.  Add -U__STRICT_ANSI__
   #endif

   #include <boost/test/unit_test.hpp>
#endif

#endif
