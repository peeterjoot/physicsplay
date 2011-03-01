// FILE: dekker.c
// compile with "gcc dekker.c -o dekker"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define N 10000000

#define MFENCE \
   __asm__ __volatile__( "mfence" ::: "memory" ) 

#define SFENCE \
   __asm__ __volatile__( "sfence" ::: "memory" ) 

#define LFENCE \
   __asm__ __volatile__( "lfence" ::: "memory" ) 

#define SCHED_FENCE \
   __asm__ __volatile__( "" ::: "memory" ) 

#if defined USE_MFENCE

   #define FENCE MFENCE

#elif defined USE_SFENCE

   #define FENCE SFENCE

#elif defined USE_LFENCE

   #define FENCE LFENCE

#elif defined USE_SCHED_FENCE

   #define FENCE SCHED_FENCE

#else

   #define FENCE 0 /* no fence */

#endif

bool be_verbose = false ;

#if defined USE_ATOMIC || defined USE_SERIAL
   volatile unsigned foo = 0 ;

   inline void my_increment()
   {
      unsigned old_value ;
      unsigned add_value = 1 ;

      #if defined NO_LOCK
         #define LOCK_PREFIX ""
      #else
         // 
         // lock signal assertion is required for concurrent correctness.
         //
         #define LOCK_PREFIX "lock; "
      #endif

      __asm__ __volatile__( LOCK_PREFIX "xaddl %0,%1\n\t" : "=r"(old_value), "+m" (foo) : "0" (add_value) : "cc" ) ;
   }

   void my_lock( int tid_ignored )
   {
   }

   void my_unlock( int tid_ignored )
   {
   }
#else
   unsigned foo = 0 ;
   
   inline void my_increment()
   {
      foo++ ;
   }
   
   #if defined USE_XCHG_LOCK
   
      volatile char lock_word = 0 ;
   
      void my_lock( int tid_ignored )
      {
         char old_value ;
         char new_value = 1 ;
   
         do {
            // 
            // A dumb spinlock implementation, with no memory barriers.
            //
            __asm__ __volatile__( "xchgb  %0,%1\n\t" : "=r" (old_value), "+m" (lock_word) : "0" (new_value) : "cc" ) ;
   
         } while ( 1 == old_value ) ;
      }
   
      void my_unlock( int tid_ignored )
      {
         SCHED_FENCE ;
   
         lock_word = 0 ;
      }
   #else
   
      struct FLAG_STATE
      {
         volatile int flag ;
   
         char dummy[120] ; // cacheline separator.
      } ;
   
      FLAG_STATE g[2] ;
      volatile int turn = 0 ;
   
      #if defined USE_WIKI
      /* 
       * wikipedia implementation. p0
       *
           flag[0] := true
           while flag[1] = true {
               if turn . 0 {
                   flag[0] := false
                   while turn . 0 {
                   }
                   flag[0] := true
               }
           }
       
          // critical section
          ...
          turn := 1
          flag[0] := false
       */
      void my_lock( int tid )
      {
         int other = 1 - tid  ;
   
         g[tid].flag = true ; // I want in the CS.
   
         FENCE ;
   
         while ( true == g[other].flag )
         {
            // 
            // The other guy is in the CS or wants in.
            //
            if ( turn != tid )
            {
               // he said he wants it, but hasn't given me my turn yet.
               // 
               // let him have a chance.
               //
               g[tid].flag = false ;
   
               // wait till he gives me my turn
               while ( turn != tid )
               {
               }
   
               // he's about to give up his turn or has, so I can say I want it again.
               // 
               // I'll now spin on his flag changing (though I could miss it if unlucky and have
               // to start all over if he tries again fast).
               //
               g[tid].flag = true ;
            }
         }
      }
   
      void my_unlock( int tid )
      {
         int other = 1 - tid  ;
   
         turn = other ;
   
         //SFENCE ;
   
         g[tid].flag = false ;
      }
   
      #else
   
      void my_lock( int tid )
      {
         g[tid].flag = 1 ;
   
         //SFENCE ;
   
         turn = 1-tid ;
   
         FENCE ;
   
         //while( g[1-tid].flag && turn != tid ) ;
         while( g[1-tid].flag )
         {
            if ( turn == tid )
            {
               break ;
            }
         }
   
         // This would be the logical place for the lfence, to ensure that the lock data accesses don't 
         // start till we are in the critical section.
         //   LFENCE ;
      }
   
      void my_unlock( int tid )
      {
         // This would be the logical place for the lfence, to ensure that the lock data accesses are 
         // complete while we are in the critical section.
         //   SFENCE ;
   
         g[tid].flag = 0 ;
      }
      #endif // !USE_WIKI
   #endif // !USE_XCHG_LOCK
#endif // !USE_ATOMIC

#if defined __cplusplus 
   #define EXTERNC extern "C"
#endif

void do_work( int tid ) 
{
   int i ;
   int p = 0 ;

   for( i = 0 ; i < N ; i++ )
   {
      my_lock( tid ) ;

      my_increment() ;

      my_unlock( tid ) ;

      if ( be_verbose )
      {
         p++ ;

         if ( 0 == (p % 100000) )
         {
            printf( "%d: %d\n", tid, p ) ;
         }
      }
   }
}

EXTERNC
void *thread_0( void * ) 
{
   do_work( 0 ) ;
}

EXTERNC
void *thread_1( void * ) 
{
   do_work( 1 ) ;
}

double timeval_to_usec( const struct timeval * const pTv )
{
   double uSec = pTv->tv_sec * 1000000 ;

   uSec += pTv->tv_usec ;

   return uSec ;
}

int main( int argc, char *argv[] )
{
   pthread_t         h[2] ;
   struct timeval    t[2] ;
   double            elapsed ;

   gettimeofday( &t[0], NULL ) ;

#if defined USE_SERIAL
   pthread_create( &h[0], NULL, thread_0, NULL ) ;
   pthread_join( h[0], NULL ) ;

   pthread_create( &h[1], NULL, thread_1, NULL ) ;
   pthread_join( h[1], NULL ) ;
#else
   pthread_create( &h[0], NULL, thread_0, NULL ) ;
   pthread_create( &h[1], NULL, thread_1, NULL ) ;

   pthread_join( h[0], NULL ) ;
   pthread_join( h[1], NULL ) ;
#endif

   gettimeofday( &t[1], NULL ) ;

   elapsed = timeval_to_usec( &t[1] ) - timeval_to_usec( &t[0] ) ;

   printf( "variation, 2N, foo, 2N - foo, time (seconds)\n" ) ;

   printf( "%s,%u,%u,%u,%f\n", argv[0], 2*N, foo, 2*N - foo, elapsed/1000000.0 ) ;

   return 0 ;
}
