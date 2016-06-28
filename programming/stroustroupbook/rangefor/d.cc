#include <iostream>

class bititer
{
   unsigned bset ;
   int cur{} ;
 
public:

   bititer( const unsigned b )
      : bset{ b }
   {
   }

   bititer & operator++()
   {
      bset >>= 1 ;
      cur++ ;

      return *this ;
   }

   unsigned operator*()
   {
      unsigned v{} ;

      if ( bset & 1 )
      {
         v = ( 1 << cur ) ;
      } 

      return v ;
   }

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
   for ( auto v : bitset{ 0b10101010 } )
   {
      std::cout << v << "\n" ;
   }

   return 0 ;
}
