#include <stdlib.h>

typedef struct foo                      
{
   unsigned char m;                        
   unsigned char n;                        
} foo;

typedef struct Foo
{
   unsigned char m[2][3];                        
   unsigned char n[2];
} bar;

typedef Foo moo ;

