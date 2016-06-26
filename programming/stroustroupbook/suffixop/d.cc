#include <iostream>

struct length
{
   double len {} ;

   constexpr length( double v ) : len{ v } {}

   constexpr length( int v ) : len{ static_cast<double>(v) } {}
} ;

inline length operator + ( const length a, const length b )
{
   return length( a.len + b.len ) ;
}

constexpr length operator "" _m( long double v )
{
   return length{ static_cast<double>(v) } ;
}

constexpr length operator "" _dm( long double v )
{
   return length{ static_cast<double>(v/10.0) } ;
}

constexpr length operator "" _cm( long double v )
{
   return length{ static_cast<double>(v/100.0) } ;
}

constexpr length operator "" _mm( long double v )
{
   return length{ static_cast<double>(v/1000.0) } ;
}

#if 0
constexpr length operator "" _m(int v)
{
   return length{ static_cast<double>(v) } ;
}

constexpr length operator "" _dm(int v)
{
   return length{ static_cast<double>(v/10.0) } ;
}

constexpr length operator "" _cm(int v)
{
   return length{ static_cast<double>(v/100.0) } ;
}

constexpr length operator "" _mm(int v)
{
   return length{ static_cast<double>(v/1000.0) } ;
}
#endif

int main()
{
   //length v = 1._m + 2_dm + 1.0_cm + 1.0_mm ;
   length v = 1._m + 2._dm + 3._cm + 4._mm ;

   std::cout << v.len << "\n" ;

   return 0 ;
}
