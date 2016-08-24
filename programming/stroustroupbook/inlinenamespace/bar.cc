#include "foo.h"

void blah(void)
{
   using namespace myproject::V1 ;

   struct X x ;
   
   foo( x ) ;
} 

void usedefault(void)
{
   using namespace myproject ;

   struct X x ;
   
   foo( x ) ;
} 

int main()
{
   blah() ;
   usedefault() ;
   return 0 ;
} 
