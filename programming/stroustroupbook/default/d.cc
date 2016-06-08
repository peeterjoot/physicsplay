#include <iostream>

extern bool g ;

inline int foo( bool internalOverrideOfGlobalForTesting = g )
{
   if ( internalOverrideOfGlobalForTesting )
   { 
      return 1 ;
   }
   else
   { 
      return 2 ;
   }
}

bool g = true ;

int main()
{
   int v = foo() ;
   int w = foo( true ) ;
   int z = foo( false ) ;

   std::cout << v << '\n' ;
   std::cout << w << '\n' ;
   std::cout << z << '\n' ;

   return 0 ;
}
