#include "MyMatrix.h"
#include <stdexcept>

bool epred( const std::out_of_range & e ) { return true ; }

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"

//BOOST_AUTO_TEST_SUITE(testsM)

BOOST_AUTO_TEST_CASE( testsMat )
{
   MyMatrix a( 2,3 ) ;
   MyMatrix b( 2,2, 3.0 ) ;
   MyMatrix c ;

   BOOST_REQUIRE( a.get_rows() == 2 ) ;
   BOOST_REQUIRE( a.get_columns() == 3 ) ;
   BOOST_REQUIRE( b.get_rows() == 2 ) ;
   BOOST_REQUIRE( b.get_columns() == 2 ) ;

   a.set_element( 0, 0, 1.0 ) ;
   a.set_element( 0, 1, 2.0 ) ;
   a.set_element( 0, 2, 3.0 ) ;
   a.set_element( 1, 0, 4.0 ) ;
   a.set_element( 1, 1, 5.0 ) ;
   a.set_element( 1, 2, 6.0 ) ;

   BOOST_REQUIRE( a.get_element( 0, 0) == 1.0 ) ;
   BOOST_REQUIRE( a.get_element( 0, 1) == 2.0 ) ;
   BOOST_REQUIRE( a.get_element( 0, 2) == 3.0 ) ;
   BOOST_REQUIRE( a.get_element( 1, 0) == 4.0 ) ;
   BOOST_REQUIRE( a.get_element( 1, 1) == 5.0 ) ;
   BOOST_REQUIRE( a.get_element( 1, 2) == 6.0 ) ;

   BOOST_REQUIRE( b.get_element( 0, 0) == 3.0 ) ;
   BOOST_REQUIRE( b.get_element( 0, 1) == 3.0 ) ;
   BOOST_REQUIRE( b.get_element( 1, 0) == 3.0 ) ;
   BOOST_REQUIRE( b.get_element( 1, 1) == 3.0 ) ;

   BOOST_CHECK_EXCEPTION( a.set_element( 2, 0, 1.0, true ), std::out_of_range, epred );
   BOOST_CHECK_EXCEPTION( a.set_element( 0, 3, 1.0, true ), std::out_of_range, epred );

   a.output( "a.binary.dat", true ) ;
   b.input( "a.binary.dat", true ) ;
   BOOST_REQUIRE( b.get_rows() == 2 ) ;
   BOOST_REQUIRE( b.get_columns() == 3 ) ;
   BOOST_REQUIRE( b.get_element( 0, 0) == 1.0 ) ;
   BOOST_REQUIRE( b.get_element( 0, 1) == 2.0 ) ;
   BOOST_REQUIRE( b.get_element( 0, 2) == 3.0 ) ;
   BOOST_REQUIRE( b.get_element( 1, 0) == 4.0 ) ;
   BOOST_REQUIRE( b.get_element( 1, 1) == 5.0 ) ;
   BOOST_REQUIRE( b.get_element( 1, 2) == 6.0 ) ;

   a.output( "a.ascii.dat", false ) ;
   c.input( "a.ascii.dat", false ) ;
   BOOST_REQUIRE( c.get_rows() == 2 ) ;
   BOOST_REQUIRE( c.get_columns() == 3 ) ;
   BOOST_REQUIRE( c.get_element( 0, 0) == 1.0 ) ;
   BOOST_REQUIRE( c.get_element( 0, 1) == 2.0 ) ;
   BOOST_REQUIRE( c.get_element( 0, 2) == 3.0 ) ;
   BOOST_REQUIRE( c.get_element( 1, 0) == 4.0 ) ;
   BOOST_REQUIRE( c.get_element( 1, 1) == 5.0 ) ;
   BOOST_REQUIRE( c.get_element( 1, 2) == 6.0 ) ;
}
