#include <stdio.h>
#include "foo.h"

void f() ;
void g() ;
void h() ;

int main()
{
   f() ;
   g() ;
   h() ;

   return 0 ;
}

void f()
{
   T t = foo() ;

   printf("%f %s %d\n", std::get<0>(t), std::get<1>(t), std::get<2>(t) ) ;
}

void g()
{
   S t = bar() ;

   printf("%f %s %d\n", t.f, t.s, t.i ) ;
}

void h()
{
   float f ;
   const char * k ;
   int i ;

   std::tie( f, k, i ) = foo() ;

   printf("%f %s %d\n", f, k, i ) ;
}
