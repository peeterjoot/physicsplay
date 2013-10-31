#include <unistd.h>
#include <asm/unistd.h>

   //
   // doesn't work with -O2 when these are stack vars?
   //
   char x[] = "/bin/shXshX" ;
//             0123456789abcdef0123456789abcdef
   char * prog = &x[0] ;
   char * nargv[] = { 0, &x[0x8], 0 } ;
   char ** nenvp = &nargv[2] ;

   //char prog[] = "/bin/sh" ;
   //char * nargv[] = { 0, "sh", "-p", 0 } ;
   //char * nenvp[] = { "HOME=/", "PS1=# ", 0 } ;

int shellcode()
{
   int err ;

   x[0x7] = 0 ;
   x[0xa] = 0 ;

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
   __asm__ __volatile__ ( "xor  %%eax,%%eax\n\t"
                          "movb %4,%%al\n\t"
                          "syscall\n\t"
     /* outputs */     : "=a"( err )
     /* inputs  */     : "D"( prog ),
                         "S"( nargv ),
                         "d"( nenvp ),
                         "n" ( __NR_execve )
     /* clobbers */    : "cc", "rcx", "r11" ) ;
#endif

#if 0
   // without optimization at the syscall point:
(gdb) info registers
   rax            0x3b     59
   rbx            0x4005b0 4195760
   rcx            0x400590 4195728
   rdx            0x7fffffffd570   140737488344432
   rsi            0x7fffffffd590   140737488344464
   rdi            0x7fffffffd5b0   140737488344496
   rbp            0x7fffffffd5c0   0x7fffffffd5c0
   rsp            0x7fffffffd5c0   0x7fffffffd5c0
   r8             0x7ffff7dd9340   140737351881536
   r9             0x7ffff7dec640   140737351960128
   r10            0x7fffffffd420   140737488344096
   r11            0x246    582
   r12            0x400400 4195328
   r13            0x7fffffffd690   140737488344720

   (gdb) x/s $rdi
   0x7fffffffd5b0:  "/bin/bash"

   (gdb) p ((char **)$rsi)[0]
   $1 = 0x0
   (gdb) p ((char **)$rsi)[1]
   $2 = 0x400694 "bash"
   (gdb) p ((char **)$rsi)[2]
   $3 = 0x400699 "-p"
   (gdb) p ((char **)$rsi)[3]
   $4 = 0x0

   (gdb) p ((char **)$rdx)[0]
   $5 = 0x40069c "HOME=/"
   (gdb) p ((char **)$rdx)[1]
   $6 = 0x4006a3 "PS1=# "
   (gdb) p ((char **)$rdx)[2]
   $7 = 0x0
#endif

   return err ;
}
