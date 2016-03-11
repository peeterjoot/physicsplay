#include <cstdio>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <cctype>

using namespace std ;

static void map( const string & s )
{
   size_t l = s.length() ;

   string t ;
   const char * sv = s.c_str() ;

   for ( size_t i = 0 ; i < l ; i++ )
   {
      t.push_back( isprint( sv[i] ) ? sv[i] : ' ' ) ;
   }

   if ( t != s )
   {
      fprintf( stderr, "non-printable characters found in string '%s'.  Converted to '%s'\n", s.c_str(), t.c_str() ) ;
   }
}

int main()
{
   for ( int i = 1 ; i < 255 ; i++ )
   {
      char s[2] ;
      s[0] = i ;
      s[1] = 0 ;

      string str( s ) ;      

      map( str ) ;
   }

   return 0 ;
}
