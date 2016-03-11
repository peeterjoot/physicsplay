#include <boost/regex.hpp>
#include <boost/static_assert.hpp>
#include <iostream>

//using std::string ;
using boost::regex ;
//using std::iostream ;
using namespace std ;

int main()
{
   BOOST_STATIC_ASSERT(1 == 1) ;
//   BOOST_STATIC_ASSERT(0 == 1) ;

   string lines[] = 
   {
      string( "blah # sljfs" ),
      string( "" ),
      string( " " ),
   }

   string line1( "blah # sljfs" ) ;
   string line2( "blah # sljfs" ) ;

   const regex e("\\s*#.*$") ;

//   string out = regex_replace( line, e, string("BBB") ) ;
   string out = regex_replace( line, e, string("") ) ;

   cout << "orig: " << line << endl ;
   cout << "out: " << out << endl ;


   return 0 ;
}
