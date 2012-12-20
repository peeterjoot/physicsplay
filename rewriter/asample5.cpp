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

int blah() ;

void infinite( int z, int y, int x = 0 )
{
   if ( 1 )
   {
      infinite( 5, y - 1, x + 1 ) ;
   }
   else
      infinite( 5, y + 1, x - 1 ) ;
}
#define SQLT_CFG 0
#define SQLT_cfgReadDcsDirectory 0
void sqlt_fnc_entry( int, int ) ;
void iicall( int z, int y, int x = 0 )
{
sqlt_fnc_entry( SQLT_CFG, SQLT_cfgReadDcsDirectory );

   if ( 1 )
   {
      infinite( 5, y - 1, x + 1 ) ;
   }
   else
      infinite( 5, y + 1, x - 1 ) ;
}


