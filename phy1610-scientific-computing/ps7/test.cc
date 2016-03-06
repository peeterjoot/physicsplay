#include "swapFileNameSuffix.h"
#include "myexceptions.h"
#include <boost/exception/get_error_info.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <iostream>

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"

BOOST_AUTO_TEST_CASE( timestep )
{
   bool caughtIt = false ;

   std::string out = replaceFileSuffix( "foo.cc", "cc", "o" ) ;
   BOOST_REQUIRE( out == "foo.o" ) ;

   try {
       // verify exception info is setup properly
       out = replaceFileSuffix( "foo.cc", "h", "o" ) ;
   } 
   catch (boost::exception & e)
   {
      std::string s = boost::diagnostic_information( e ) ;
      std::cout << s << std::endl ;

      caughtIt = true ;
   }

   BOOST_REQUIRE( true == caughtIt ) ;


   // FIXME: test boost::exception codepath of open read/write wrapper functions.
}
