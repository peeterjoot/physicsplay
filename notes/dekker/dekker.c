// FILE: dekker.c
// compile with "gcc dekker.c -o dekker"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

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

struct FlagState
{
   volatile int flag ;

   char dummy[120] ; // cacheline separator.
} ;

FlagState g[2] ;
volatile int turn = 0 ;

#if defined USE_ATOMIC

volatile char lockWord = 0 ;

void my_lock( int tidIgnored )
{
   char oldValue ;
   char newValue = 1 ;

   do {
      // 
      // A dumb spinlock implementation, with no memory barriers.
      //
      __asm__ __volatile__( "xchgb  %0,%1\n\t" : "=r" (oldValue), "+m" (lockWord) : "0" (newValue) ) ;

   } while ( 1 == oldValue ) ;
}

void my_unlock( int tidIgnored )
{
   SCHED_FENCE ;

   lockWord = 0 ;
}
#elif defined USE_WIKI
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

   g[tid].flag = true ;

   FENCE ;

   while ( true == g[other].flag )
   {
      if ( turn != tid )
      {
         g[tid].flag = false ;

         while ( turn != tid )
         {
         }

         g[tid].flag = true ;
      }
   }
}

void my_unlock( int tid )
{
   int other = 1 - tid  ;

   turn = other ;
   g[tid].flag = false ;
}
#else
void my_lock(int tid)
{
    g[tid].flag = 1 ;
    turn = 1-tid ;

    FENCE ;

    while( g[1-tid].flag && turn != tid ) ;
}

void my_unlock(int tid)
{
    g[tid].flag = 0 ;
}
#endif

unsigned foo = 0 ;

#if defined __cplusplus 
#define EXTERNC extern "C"
#endif

EXTERNC
void *thread_0( void * ) 
{
    int i ;
    int p = 0 ;
    for( i=0; i<N; i++ ) {
        my_lock(0) ;
        foo++ ;
        my_unlock(0) ;

        p++ ;

        if ( 0 == (p % 100000) )
        {
           printf("0: %d\n", p) ;
        }
    }
}

EXTERNC
void *thread_1( void * ) 
{
    int i ;
    int p = 0 ;

    for( i=0; i<N; i++ ) {
        my_lock(1) ;
        foo++ ;
        my_unlock(1) ;

        p++ ;

        if ( 0 == (p % 100000) )
        {
           printf("1: %d\n", p) ;
        }
    }
}

int main(int argc, char *argv[])
{
    pthread_t t0, t1 ;
    double t = time(NULL) ;

    pthread_create(&t0, NULL, thread_0, NULL) ;
    pthread_create(&t1, NULL, thread_1, NULL) ;

    pthread_join(t0, NULL) ;
    pthread_join(t1, NULL) ;
    t = time(NULL) - t ;

    printf("2*N - foo  = %3u (foo = %u)\n\n", 2*N-foo, foo ) ;
    printf("time       = %3.0f seconds\n", t ) ;
    return 0 ;
}
