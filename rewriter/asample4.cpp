struct withConstructor
{
   int x ;

   withConstructor() : x(3) {}
} ;

struct noConstructor
{
   int x ;
} ;

struct krcb
{
   noConstructor     noCons ;
   withConstructor   withCons;
} ;

krcb k ;
