#include <stdio.h>
#include "foo.h"

int main()
{
   float f ;
   const char * k ;
   int i ;

   T t = foo() ;
   std::tie( f, k, i ) = foo() ;

   printf("%f %s %d\n", std::get<0>(t), std::get<1>(t), std::get<2>(t) ) ;
   printf("%f %s %d\n", f, k, i ) ;

   return 0 ;
}
