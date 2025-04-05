#include <stdio.h>

long mfpvr()
{
   long v = 0 ;

   __asm__ ( "mfpvr %0\n\t" : "=r"(v) ) ;

   return v ;
}

int main()
{
   printf( "0x%lX\n", mfpvr() ) ;

   return 0 ;
}
