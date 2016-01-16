/** \file boosttest.h
 */
#if !defined phy1610_boosttest_h_included
#define phy1610_boosttest_h_included

#if defined USE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK
   #include <boost/test/included/unit_test.hpp>
#else
   #define BOOST_TEST_DYN_LINK
   #include <stdlib.h> // HACK: need putenv, mkstemp in global namespace for this include w/ cygwin
   #include <boost/test/unit_test.hpp>
#endif

#endif
