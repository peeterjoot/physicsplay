#include <boost/regex.hpp>
#include <iostream>

using namespace boost ;
using namespace std ;

int main()
{
   string lines[] = 
   {
      string( "blah # sljfs" ),
      string( "" ),
      string( " " ),
      string( " # blah" ),
   } ;

   for ( unsigned i = 0 ; i < sizeof(lines)/sizeof(lines[0]) ; i++ )
   {
      const regex e("\\s*#.*$") ;
      const string & orig = lines[i] ;

      string out = regex_replace( orig, e, string("") ) ;

      cout << "orig: " << orig << endl ;
      cout << "out: " << out << endl ;

      cmatch what ;
      regex blank("^\\s*$") ;
      if ( regex_match( out.c_str(), what, blank ) )
      {
         cout << i << ":" << "'" << orig << "'" << " <<= blank\n" ;
      }
   }

   return 0 ;
}
