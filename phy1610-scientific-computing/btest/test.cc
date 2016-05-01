#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <vector>

BOOST_AUTO_TEST_CASE( testExample )
{
   std::vector<int> v(3) ;

   BOOST_REQUIRE( 3 == v.size() ) ;
   BOOST_REQUIRE_MESSAGE( 3 == v.size(), "size: " + std::to_string( v.size() ) ) ;
}
