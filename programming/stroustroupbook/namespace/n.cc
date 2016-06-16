#include <stdio.h>

namespace {
   void foo() { printf( "ns:foo\n" ) ;
   }
}

int main() 
{
   foo() ;

   return 0 ;
}
