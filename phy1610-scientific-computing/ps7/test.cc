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
#include "rarrayio"

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"

BOOST_AUTO_TEST_CASE( replaceFileSuffixTest )
{
   auto out { replaceFileSuffix( "foo.cc", "cc", "o" ) } ;
   BOOST_REQUIRE( out == "foo.o" ) ;

   BOOST_CHECK_THROW( replaceFileSuffix( "foo.cc", "h", "o" ), regex_match_error ) ;
}

BOOST_AUTO_TEST_CASE( openStreamNormalTest )
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

// These two tests don't work on scinet nodes (using either BOOST_CHECK_THROW or manually).
// With manual, don't see the boost exceptions with the info they are supposed to have
// and boost's test infrastructure appears to be intercepting the throw's (i.e. it reports these
// tests as failed even with the BOOST_REQUIRE's commented out).
BOOST_AUTO_TEST_CASE( openStreamWriteExceptionTest )
{
   std::ofstream ofs ;

   BOOST_CHECK_THROW(
      openStreamForWriteOrThrow( "/dontcreatethispath/blah.out", ofs ),
      file_open_error) ;

#if 0
   auto caughtWriteOpenFailure{ false } ;
   try {
      openStreamForWriteOrThrow( "/dontcreatethispath/blah.out", ofs ),
   }
   catch ( boost::exception & e )
   {
      auto s { boost::diagnostic_information( e ) } ;
      std::cout << s << std::endl ;

      caughtWriteOpenFailure = true ;
   }

   std::cout << caughtWriteOpenFailure << std::endl ;
   BOOST_REQUIRE( true == caughtWriteOpenFailure ) ;
#endif
}

BOOST_AUTO_TEST_CASE( openStreamReadExceptionTest )
{
   std::ifstream ifs ;

   BOOST_CHECK_THROW(
      openStreamForReadOrThrow( "/dontcreatethispath/blah.out", ifs ),
      file_open_error) ;
}

constexpr auto tolerance{ 1e-8 } ;

BOOST_AUTO_TEST_CASE( dotproductTest )
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

   BOOST_REQUIRE( std::abs(d - expected) < tolerance ) ;
}

BOOST_AUTO_TEST_CASE( correlationTest )
{
   constexpr auto expected{ 0.9541159787234387 } ; // computed with correlator.jl
   darray x ;
   darray y ;

   std::ifstream f( "x.rat" ) ;
   std::ifstream g( "y.rat" ) ;

   f >> x ;
   g >> y ;

   correlator c( x ) ;

   double result{ c( y ) } ;

   BOOST_REQUIRE( std::abs(result - expected) < tolerance ) ;
}
