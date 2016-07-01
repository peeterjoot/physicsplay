#include <stdio.h>

struct x
{
   virtual void foo( int v ) ;
} ;

//#define T int
#define T long
struct y : public x
{
   void foo( T v ) override ;
} ;

void x::foo( int v )
{
   printf( "x::foo:%d\n", v ) ;
}

void y::foo( T v )
{ 
   printf( "y::foo:%d\n", (int)v ) ;
}

int main()
{
   y o ;
   x & r = o ;
   r.foo( 1 ) ;
   r.foo( 1L ) ;
   o.foo( 1 ) ;
   o.foo( 1L ) ;

   return 0 ;
}
