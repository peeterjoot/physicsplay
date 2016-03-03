// compile with -E -dM to see if __STRICT_ANSI__ is coming from the compiler.

//#undef __STRICT_ANSI__
#include <stdio.h>

int main()
{
   #if defined __STRICT_ANSI__
      printf( "__STRICT_ANSI__\n" ) ;
   #else
      printf( "!__STRICT_ANSI__\n" ) ;
   #endif

   return 0 ;
}
