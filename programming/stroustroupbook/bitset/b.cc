#include <vector>
#include <iostream>

using vb = std::vector<bool> ;

void foo( vb & v )
{
   v[3] = 1 ;
   v[13] = 1 ;
}

int main()
{
   vb v(15) ;

   foo( v ) ;

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

   v.resize( 70 ) ;

   for ( auto b : v )
   {
      std::cout << b << '\n' ;
   }

   return 0 ;
}
