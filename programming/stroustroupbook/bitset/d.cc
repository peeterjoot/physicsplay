#include <bitset>
#include <iostream>

using b70 = std::bitset<70> ;

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

   return 0 ;
}
