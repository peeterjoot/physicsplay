#include <iostream>

class bititer
{
   unsigned bset ;
   int cur{} ;
 
   unsigned value() const
   {
      unsigned v{} ;

      if ( bset & 1 )
      {
         v = ( 1 << cur ) ;
      } 

      return v ;
   }

   void increment()
   {
      bset >>= 1 ;
      cur++ ;
   }
  
public:

   bititer( const unsigned b )
      : bset{ b }
   {
   }

#if 0
   unsigned next( )
   {
      unsigned v = value() ;

      increment() ;

      return v ;
   }
#endif

   bititer & operator++()
   {
      increment() ;

      return *this ;
   }

   unsigned operator*()
   {
      return value() ;
   }

#if 0
   operator bool() { return bset != 0 ; }
#endif

   bool operator !=( const bititer & b )
   {
      return ( bset != b.bset ) ;
   }
} ;

struct bitset
{
   unsigned bits ;

   bititer begin()
   {
      return bititer{ bits } ;
   }

   bititer end()
   {
      return bititer{ 0 } ;
   }
} ;

int main()
{
#if 0
   bititer i{ 0b1011 } ;

   while ( i )
   {
      unsigned v = *i ;
      ++i ;

      std::cout << v << "\n" ;
   }
#endif

   for ( auto v : bitset{ 0b1100 } )
   {
      std::cout << v << "\n" ;
   }

   return 0 ;
}
