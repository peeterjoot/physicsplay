#include <array>

using a10 = std::array<int, 10> ;

void foo( a10 & a )
{
   a[3] = 7 ;
   a[13] = 7 ;
#if 1
   a.at(13) = 7 ;
#endif
}

void bar( int * a )
{
   a[3] = 7 ;
   a[13] = 7 ;
}

int main()
{
   a10 a ;
   int b[10] {} ;

   foo( a ) ;
   bar( b ) ;

   return 0 ;
}
