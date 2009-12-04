// FILE: dekker.c
// compile with "gcc dekker.c -o dekker"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10000000

volatile int flag[2][/*ignore*/4];
volatile int turn=0;

void my_lock(int tid)
{
    flag[tid][/*ignore*/0] = 1;
    turn = 1-tid;
    //__asm__ ("mfence"); 
    while( flag[1-tid][/*ignore*/0] && turn != tid )
        ;
}

void my_unlock(int tid)
{
    flag[tid][/*ignore*/0] = 0;
}

unsigned foo=0;
    
void *thread_0() 
{
    int i,j;
    for( i=0; i<N; i++ ) {
        my_lock(0);
        foo++;
        my_unlock(0);
    }
}

void *thread_1() 
{
    int i,j;
    for( i=0; i<N; i++ ) {
        my_lock(1);
        foo++;
        my_unlock(1);
    }
}

int main(int argc, char *argv[])
{
    pthread_t t0, t1;
    double t = time(NULL);

    pthread_create(&t0, NULL, thread_0, NULL); 
    pthread_create(&t1, NULL, thread_1, NULL); 

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    t = time(NULL) - t;

    printf("2*N - foo  = %3u (foo = %u)\n\n", 2*N-foo, foo );
    printf("time       = %3.0f seconds\n", t );
    return 0;
}

