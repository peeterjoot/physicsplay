#include <bitset>
#include <iostream>

#define WITHITER
#if defined WITHITER
template <int N>
struct iter ;

template <int N>
struct mybits : public std::bitset<N>
{
   using T = std::bitset<N> ;

   using T::T ;
   using T::size ;

   inline iter<N> begin( ) ;

   inline iter<N> end( ) ;
} ;

template <int N>
struct iter
{
   unsigned pos{} ;
   const mybits<N> & b ;

   iter( const mybits<N> & bits, unsigned p = {} ) : pos{p}, b{bits} {}

   const iter & operator++()
   {
      pos++ ;

      return *this ;
   }

   bool operator != ( const iter & i ) const
   {
      return pos != i.pos ;
   }

   int operator*() const
   {
      return b[ pos ] ;
   }
} ;

template <int N>
inline iter<N> mybits<N>::begin( )
{
   return iter<N>( *this ) ;
}

template <int N>
inline iter<N> mybits<N>::end( )
{
   return iter<N>( *this, size() ) ;
}

using b70 = mybits<70> ;
#else
using b70 = std::bitset<70> ;
#endif

void foo( b70 & v )
{
   v[3] = 1 ;
   v[13] = 1 ;
}

int main()
{
   b70 v ;

   foo( v ) ;

   std::cout << "foo: sizeof(v) = " << sizeof(b70) << '\n' ;

   for ( int i{} ; i < v.size() ; i++ )
   {
      char sep{ ' ' } ;
      if ( ((i+1) % 8) == 0 )
      {
         sep = '\n' ;
      }

      std::cout << v[i] << sep ;
   }
   std::cout << '\n' ;

   // also have a built in output method, and various conversion, utility and test functions (count, any, all, none, size, ...)
   std::cout << v << '\n' ;
   std::cout << v.to_string() << '\n' ;
   std::cout << "0x" << std::hex << v.to_ulong() << '\n' ;
   //std::cout << (~v).to_ulong() << '\n' ; // throws overflow_error

#if defined WITHITER
   for ( auto b : v )
   {
      std::cout << b << '\n' ;
   }
#endif

   return 0 ;
}
