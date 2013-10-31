#include <unistd.h>
#include <asm/unistd.h>

int shellcode()
{
   int err ;

   char prog[] = "/bin/bash" ;
   char * nargv[] = { 0, "bash", "-p", 0 } ;
   char * nenvp[] = { "HOME=/", "PS1=# ", 0 } ;

#if 0
   syscall( __NR_execve, prog, nargv, nenvp ) ;

   err = errno ;
#elif 0
   execve( prog, nargv, nenvp ) ;

   err = errno ;
#else

// http://stackoverflow.com/questions/2535989/what-are-the-calling-conventions-for-unix-linux-system-calls-on-x86-64
// http://stackoverflow.com/questions/9506353/how-to-invoke-a-system-call-via-sysenter-in-inline-assembly-x86-amd64-linux
// http://www.x86-64.org/documentation/abi.pdf
//
   // kernel param passing in: %rdi, %rsi, %rdx, %r10, %r8 and %r9.  rcx, r11 destroyed
   //
   // doesn't work with -O2 ?
   //
   __asm__ __volatile__ ( "xor  %%eax,%%eax\n\t"
                          "movb %4,%%al\n\t"
                          "syscall\n\t"
     /* outputs */     : "=a"( err )
     /* inputs  */     : "D"( prog ),
                         "S"( nargv ),
                         "d"( nenvp ),
                         "n" ( __NR_execve )
     /* clobbers */    : "cc", "rcx", "r11" ) ;


//   (gdb) x/20c $rdi
//      0x40076a:       47 '/'  98 'b'  105 'i' 110 'n' 47 '/'  98 'b'  97 'a'  115 's'
//      0x400772:       104 'h' 0 '\000'        1 '\001'        27 '\033'       3 '\003'        59 ';'  48 '0'  0 '\000'
//      0x40077a:       0 '\000'        0 '\000'        5 '\005'        0 '\000'

   // 0x3b = 59
//   => 0x00007ffff7b0f2c0 <+0>:     mov    $0x3b,%eax 
//         0x00007ffff7b0f2c5 <+5>:     syscall
#endif

   return err ;
}
