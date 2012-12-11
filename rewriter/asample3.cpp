struct withConstructor
{
   int x ;

   withConstructor() : x(3) {}
} ;

struct noConstructor
{
   int x ;
} ;

void foo()
{
   withConstructor local1 ;
   noConstructor local2 ;
}

withConstructor global1 ;
noConstructor global2 ;
