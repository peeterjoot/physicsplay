// based on http://stackoverflow.com/a/11788476/189270

#include <pthread.h>
#include <signal.h>
#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <string.h>
#include <errno.h>

enum {
   DR7_BREAK_ON_EXEC  = 0,
   DR7_BREAK_ON_WRITE = 1,
   DR7_BREAK_ON_RW   = 3
};

enum drLen {
   DR7_LEN_INVALID = -1,
   DR7_LEN_1 = 0,
   DR7_LEN_2 = 1,
   DR7_LEN_4 = 3,
   DR7_LEN_8 = 2
};

drLen lenBySize[] = 
{
   DR7_LEN_INVALID,
   DR7_LEN_1,
   DR7_LEN_2,
   DR7_LEN_4, /* 3 bytes: trace 4 */
   DR7_LEN_4,
   DR7_LEN_8, /* 5 bytes: trace 8 */
   DR7_LEN_8, /* 6 bytes: trace 8 */
   DR7_LEN_8, /* 7 bytes: trace 8 */
   DR7_LEN_8
} ;

typedef struct {
   char l0:1;
   char g0:1;
   char l1:1;
   char g1:1;
   char l2:1;
   char g2:1;
   char l3:1;
   char g3:1;
   char le:1;
   char ge:1;
   char pad1:3;
   char gd:1;
   char pad2:2;
   char rw0:2;
   char len0:2;
   char rw1:2;
   char len1:2;
   char rw2:2;
   char len2:2;
   char rw3:2;
   char len3:2;
} dr7_t;

#if defined __cplusplus
extern "C"
#endif
{
   typedef void sigHandler(int, siginfo_t*, void*);
#if defined __cplusplus
}
#endif

int setHandler(sigHandler handler)
{
   struct sigaction trap_action;

   sigaction(SIGTRAP, NULL, &trap_action);
   trap_action.sa_sigaction = handler;
   trap_action.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
   sigaction(SIGTRAP, &trap_action, NULL);

   return 0;
}

struct watchData
{
   pid_t   who ;
   void *  addr ;
   drLen   len ;
   int     err ;
} ;

void * watchpoint( void * argV )
{
   int retval = 0;

   watchData * w = (watchData *)argV ;

   dr7_t dr7 = {0};
   dr7.l0 = 1;
   dr7.rw0 = DR7_BREAK_ON_WRITE;
   dr7.len0 = w->len;

   if (ptrace(PTRACE_ATTACH, w->who, NULL, NULL))
   {
      retval = errno ;
      w->err = 1 ;

      goto DONE ;
   }

   sleep(1);

   if (ptrace(PTRACE_POKEUSER, w->who, offsetof(struct user, u_debugreg[0]), w->addr))
   {
      retval = errno;

      w->err = 2 ;
   }
   else
   {
      if (ptrace(PTRACE_POKEUSER, w->who, offsetof(struct user, u_debugreg[7]), dr7))
      {
         retval = errno;

         w->err = 3 ;
      }
   }

   if (ptrace(PTRACE_DETACH, w->who, NULL, NULL))
   {
      if ( !retval )
      {
         retval = errno;

         w->err = 4 ;
      }
   }

DONE:
   return (void *)retval ;
}

int forkAndWatch( watchData * w )
{
#if 1
   pid_t child;
   int child_stat = 0;

   child = fork() ;
   if ( child == 0 )
   {
      watchpoint( w ) ;

      exit(0);
   }
   else if ( child != -1 )
   {
      waitpid(child, &child_stat, 0);

      if (WEXITSTATUS(child_stat))
      {
         printf("child exit !0\n");

         return 1;
      }
   }
#else
   // doesn't work:
   pthread_t tid ;
   int rc ;
   pthread_attr_t attr ;

   rc = pthread_attr_init( &attr ) ;
   if ( rc )
   {
      printf( "error: pthread_attr_init: %d (%s)\n", rc, strerror(rc) ) ;

      return rc ;
   }

   rc = pthread_attr_setscope( &attr, PTHREAD_SCOPE_SYSTEM ) ;
   if ( rc )
   {
      printf( "error: pthread_attr_setscope: %d (%s)\n", rc, strerror(rc) ) ;

      return rc ;
   }

   rc = pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE ) ;
   if ( rc )
   {
      printf( "error: pthread_attr_setdetachstate: %d (%s)\n", rc, strerror(rc) ) ;

      return rc ;
   }

   rc = pthread_create( &tid, &attr, watchpoint, w ) ;
   if ( rc )
   {
      printf( "error: pthread_create: %d (%s)\n", rc, strerror(rc) ) ;
   }
   else
   {
      void * ret = 0 ;
      rc = pthread_join( tid, &ret ) ;

      if ( rc )
      {
         printf( "error: pthread_join: %d (%s)\n", rc, strerror(rc) ) ;
      }
      else
      {
         printf( "watchpoint thread done: %ld: %d\n", (long)ret, w->err ) ;
      }
   }
#endif

   return 0;
}

long var;

void trap(int sig, siginfo_t* info, void* context)
{
   printf("new value: %d\n", var);
}

int main(int argc, char * argv[])
{
   long i;
   struct watchData w ;
   //w.who = getpid() ;
   w.who = syscall( SYS_gettid );
   w.addr = &var ;
   w.len = lenBySize[sizeof(var)] ;

   printf("init value: %d\n", var);

   setHandler(trap);

   forkAndWatch( &w ) ;

   for (i = 0; i < 100; i++) {
      var++;
      sleep(1);
   }

   return 0;
}
