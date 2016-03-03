#include <type_traits>
#include <iostream>

using namespace std ;

int main()
{
   float p[1][1] ;
   float p2[1] ;

   // Can I do this?

   if ( is_pointer<*(&p[0][0])>() )
   {
      cout << "pointer\n" ;
   }

   if ( is_pointer<*(&p2[0])>() )
   {
      cout << "pointer\n" ;
   }

   return 0 ;
}
