struct withConstructor
{
   int x ;

   withConstructor() : x(3) {}
} ;

struct noConstructor
{
   int x ;
} ;

struct withConsIndirectly
{
   int x ;
   int y ;
   int z ;

   withConstructor with ;
} ;

struct krcb
{
   noConstructor noneA ;
   noConstructor noneB ;
   noConstructor noneC ;
   noConstructor noneD ;
   noConstructor noneE ;
   int           noneF ;

   withConstructor directCons ;

   withConsIndirectly indirectCons ;
} ;

void foo()
{
   withConstructor local1 ;
   noConstructor local2 ;
}

#if 0
withConstructor global1 ;
noConstructor global2 ;
#endif

krcb k ;
