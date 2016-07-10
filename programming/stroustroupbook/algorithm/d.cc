#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

int scan( const std::string & s, char v )
{
   auto i = find_if_not( s.begin(),
                         s.end(),
                         [ v ]( char c ){ return c == v ; }
                       ) ;

   if ( i == s.end() )
   {
      return 0 ;
   }
   else
   {
      std::cout << "diff: " << i - s.begin() << '\n' ;

      return ( v > *i ) ? 1 : -1 ;
   }
}

int scan2( const std::string & s, char v )
{
   auto p = s.begin() ;
   for ( auto c : s )
   {
      if ( c != v )
      {
         break ; 
      }

      p++ ;
   }

   if ( p == s.end() )
   {
      return 0 ;
   }
   else
   {
      std::cout << "diff: " << p - s.begin() << '\n' ;

      return ( v > *p ) ? 1 : -1 ;
   }
}

int scan3( const std::string & s, char v )
{
   auto p = s.begin() ;
   for ( ; p != s.end() ; p++ )
   {
      if ( *p != v )
      {
         break ; 
      }
   }

   if ( p == s.end() )
   {
      return 0 ;
   }
   else
   {
      std::cout << "diff: " << p - s.begin() << '\n' ;

      return ( v > *p ) ? 1 : -1 ;
   }
}

int main()
{
   std::vector< std::function< int( const std::string &, char ) > > v { scan, scan2, scan3 } ;

   for ( auto f : v )
   {
      int r0 = f( "nnnnn", 'n' ) ; 
      int rp = f( "nnnnnmmm", 'n' ) ; 
      int rn = f( "nnnnnpnn", 'n' ) ; 

      std::cout << r0 << '\n' ;
      std::cout << rp << '\n' ;
      std::cout << rn << '\n' ;
   }
   
   return 0 ;
} 
