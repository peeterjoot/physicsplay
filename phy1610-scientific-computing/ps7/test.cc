#include "swapFileNameSuffix.h"
#include "myexceptions.h"
#include <boost/exception/get_error_info.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <iostream>
#include "stdoutfilestream.h"

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
}
