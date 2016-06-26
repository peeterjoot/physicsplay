#include <iostream>

struct length
{
   double len {} ;

   constexpr length( double v ) : len{ v } {}

//   constexpr length( int v ) : len{ static_cast<double>(v) } {}
} ;

inline length operator + ( const length a, const length b )
{
   return length( a.len + b.len ) ;
}

inline length operator - ( const length a )
{
   return length( -a.len ) ;
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

constexpr length operator "" _m( unsigned long long v )
{
   return length{ static_cast<double>(v) } ;
}

constexpr length operator "" _dm( unsigned long long v )
{
   return length{ static_cast<double>(v/10.0) } ;
}

constexpr length operator "" _cm( unsigned long long v )
{
   return length{ static_cast<double>(v/100.0) } ;
}

constexpr length operator "" _mm( unsigned long long v )
{
   return length{ static_cast<double>(v/1000.0) } ;
}

int main()
{
   //length v = - ( 1._m + 2_dm + 3.0_cm + 5_mm ) ;
   length v = 1.0009_m + 3_dm + 5.0_cm + 7_mm ;

   std::cout << v.len << "\n" ;

   return 0 ;
}
