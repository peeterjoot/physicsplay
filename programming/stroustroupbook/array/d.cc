#include <array>
#include <iostream>

using a10 = std::array<int, 10> ;

void foo_nothrow( a10 & a )
{
   a[3] = 7 ;
   a[13] = 7 ;
}

void bar( int * a )
{
   a[3] = 7 ;
   a[13] = 7 ;
}

void foo_throw( a10 & a )
{
   a[3] = 7 ;
   a.at(13) = 7 ;
}

void blah( a10 & a )
{
   a[0] = 1 ;

   for ( int i{1} ; i < a.size() ; i++ )
   {
      a[i] = 2 * a[i-1] ;
   }
}

int main()
{
   a10 a ;
   int b[10] {} ;

   foo_nothrow( a ) ;
   std::cout << "foo_nothrow\n" ; for ( auto v : a ) { std::cout << v << '\n' ; }
   bar( b ) ;
   std::cout << "bar\n" ; for ( auto v : b ) { std::cout << v << '\n' ; }
   blah( a ) ;
   std::cout << "blah\n" ; for ( auto v : a ) { std::cout << v << '\n' ; }
   foo_throw( a ) ;
   std::cout << "foo_throw\n" ; for ( auto v : a ) { std::cout << v << '\n' ; }

   return 0 ;
}
