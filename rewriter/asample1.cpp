#include <stddef.h>
#include <stdlib.h>
#include "asample1.h"

struct blah
{
   char z ;
} ;

typedef blah moo ;
#define Moo blah

// forward declaration
class qq ;

union uu
{
   int ui ;
   char uc ;
#if defined foodef
   long ul ;
#endif
#if defined bardef && (bardef == 2)
   long long ull ;
#endif
#if defined NOTDEFINED
   notdef bvlah ;
#endif
} ;

class qq 
{ 
   public:
      int x ;
} ;

struct Test
{
   int a, b ;

   moo c ;
   Moo d ;

   int * e ;
   Moo * f ;
   float * ffp ;
   float ff ;

   uu umember ;

   blah bb[ 3 ] ;
} ;

class bar : public foo
{
   public:
   char w ;

   Test t ;
} ;

