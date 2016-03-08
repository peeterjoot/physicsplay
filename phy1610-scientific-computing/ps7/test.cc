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

BOOST_AUTO_TEST_CASE( timestep )
{
   auto caughtIt { false } ;

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

      caughtIt = true ;
   }

   BOOST_REQUIRE( true == caughtIt ) ;

   {
      std::ofstream f ;

      openStreamForWriteOrThrow( "blah.out", f ) ;
      f << 3 ;
   }
   {
      std::ifstream f ;
      int v ;

      openStreamForReadOrThrow( "blah.out", f ) ;
      f >> v ;

      BOOST_REQUIRE( 3 == v ) ;
   }

   auto caughtWriteOpenFailure{ false } ;
   auto caughtReadOpenFailure{ false } ;
   {
      std::ifstream ifs ;
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

      try {
         openStreamForReadOrThrow( "/dontcreatethispath/blah.out", ifs ) ;
      }
      catch (boost::exception & e)
      {
         auto s { boost::diagnostic_information( e ) } ;
         std::cout << s << std::endl ;

         caughtReadOpenFailure = true ;
      }
   }
   BOOST_REQUIRE( true == caughtWriteOpenFailure ) ;
   BOOST_REQUIRE( true == caughtReadOpenFailure ) ;

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
}
