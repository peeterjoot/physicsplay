#include <stdio.h>

int setrootid() ;
int shellcode() ;

int main(int argc, char **argv)
{
   setrootid() ;

   int rc = shellcode() ;

   printf( "exec Failed\n" ) ;

   return rc ;
}
