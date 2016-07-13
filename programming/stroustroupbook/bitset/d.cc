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

   // also have a built in output method, and various conversion, utility and test functions (count, any, all, none, size, ...)
   std::cout << v << '\n' ;
   std::cout << v.to_string() << '\n' ;

   return 0 ;
}
