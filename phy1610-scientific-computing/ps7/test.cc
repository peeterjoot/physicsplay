/**
   \file test.cc

   boost test driver for misc utility code.
 */
#include <boost/exception/get_error_info.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <iostream>
#include "swapFileNameSuffix.h"
#include "myexceptions.h"
#include "stdoutfilestream.h"
#include "dotprod.h"
#include "ratData.h"

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"

BOOST_AUTO_TEST_CASE( replaceFileSuffixTest )
{
   auto caughtRegexException { false } ;

   auto out { replaceFileSuffix( "foo.cc", "cc", "o" ) } ;
   BOOST_REQUIRE( out == "foo.o" ) ;

   try {
       // verify exception info is setup properly
       out = replaceFileSuffix( "foo.cc", "h", "o" ) ;
   } 
   catch (boost::exception & e)
   {
      auto s { boost::diagnostic_information( e ) } ;
      std::cout << s << std::endl ;

      caughtRegexException = true ;
   }

   BOOST_REQUIRE( true == caughtRegexException ) ;
}

BOOST_AUTO_TEST_CASE( openStreamNormal )
{
   {
      std::ofstream f ;

      openStreamForWriteOrThrow( "blah.out", f ) ;
      f << 3 ;
   }

   std::ifstream f ;
   int v ;

   openStreamForReadOrThrow( "blah.out", f ) ;
   f >> v ;

   BOOST_REQUIRE( 3 == v ) ;
}

// These two tests don't work on scinet nodes.  Don't see the boost exceptions with the info they are supposed to have
// and boost's test infrastructure appears to be intercepting the throw's (i.e. it reports these tests as failed
// even with the BOOST_REQUIRE's commented out).
BOOST_AUTO_TEST_CASE( openStreamWriteException )
{
   // These two aren't working on scinet:
   auto caughtWriteOpenFailure{ false } ;
   std::ofstream ofs ;

   try {
      openStreamForWriteOrThrow( "/dontcreatethispath/blah.out", ofs ) ;
   }
   catch (boost::exception & e)
   {
      auto s { boost::diagnostic_information( e ) } ;
      std::cout << s << std::endl ;

      caughtWriteOpenFailure = true ;
   }

   std::cout << caughtWriteOpenFailure << std::endl ;
   BOOST_REQUIRE( true == caughtWriteOpenFailure ) ;
}

BOOST_AUTO_TEST_CASE( openStreamReadException )
{
   auto caughtReadOpenFailure{ false } ;

   std::ifstream ifs ;
   try {
      openStreamForReadOrThrow( "/dontcreatethispath/blah.out", ifs ) ;
   }
   catch (boost::exception & e)
   {
      auto s { boost::diagnostic_information( e ) } ;
      std::cout << s << std::endl ;

      caughtReadOpenFailure = true ;
   }

   std::cout << caughtReadOpenFailure << std::endl ;
   BOOST_REQUIRE( true == caughtReadOpenFailure ) ;
}

BOOST_AUTO_TEST_CASE( dotproduct )
{
   constexpr auto size{5} ;
   constexpr auto v1{2} ;
   constexpr auto v2{3} ;
   darray f(5) ;
   f.fill( 2 ) ;
   f[0] = 1 ;

   darray g(5) ;
   g.fill( 3 ) ;

   auto d { dotprod( f, g ) } ;
   auto expected { (size -1)* v1 * v2 + g[0] } ;

   BOOST_REQUIRE( std::abs(d - expected) < 1e-8 ) ;
}
