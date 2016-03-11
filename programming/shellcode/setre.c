#include <unistd.h>
#include <asm/unistd.h>

int setrootid()
{
   int err ;

#if 0
   syscall( __NR_setreuid, 0, 0 ) ;
   syscall( __NR_setregid, 0, 0 ) ;
#elif 0
   sys_setreuid( 0, 0 ) ;
   sys_setregid( 0, 0 ) ;
#elif 0
   setreuid( 0, 0 ) ;
   setregid( 0, 0 ) ;
#else
   __asm__ __volatile__ ( "xor  %%edi,%%edi\n\t"
                          "xor  %%esi,%%esi\n\t"
                          "xor  %%eax,%%eax\n\t"
                          "movb %1,%%al\n\t"
                          "syscall\n\t"
                          "xor  %%eax,%%eax\n\t"
                          "movb %2,%%al\n\t"
                          "syscall\n\t"
     /* outputs */     : "=a"(err)
     /* inputs  */     : "n" ( __NR_setreuid ),
                         "n" ( __NR_setregid )
     /* clobbers */    : "cc", "edi", "esi", "rcx", "r11" ) ;
#endif

   return err ;
}
