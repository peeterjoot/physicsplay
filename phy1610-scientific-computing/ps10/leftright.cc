/** \file leftright.cc 
   simple mpi experimentation code (cyclic send)
 */
#include <stdio.h>
#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
   int rank ;
   int size ;
   int err ;
   double msgsent, msgrcvd ;
   MPI_Status rstatus ;
   int tag = 1 ;

   err = MPI_Init( &argc, &argv ) ;
   if ( err )
   {
      printf( "init err: %d\n", err ) ;
      abort() ;
   }
   err = MPI_Comm_size( MPI_COMM_WORLD, &size ) ;
   if ( err )
   {
      printf( "size err: %d\n", err ) ;
      abort() ;
   }
   err = MPI_Comm_rank( MPI_COMM_WORLD, &rank ) ;
   if ( err )
   {
      printf( "rank err: %d\n", err ) ;
      abort() ;
   }

   msgsent = rank * rank ;
   msgrcvd = -999. ;

   int left = (rank - 1 + size) % size ;
   int right = (rank + 1) % size ;

   err = MPI_Sendrecv( &msgsent, 1, MPI_DOUBLE, right, tag,
                       &msgrcvd, 1, MPI_DOUBLE, left, tag,
                       MPI_COMM_WORLD, &rstatus ) ;
   if ( err )
   {
      printf( "sendrecv err = %d\n", err ) ;
      abort() ;
   }

   std::cout << "Hello from task.  Rank = " << rank << ", size = " << size << " world.  msgsent = " << msgsent << ", msgrcvd = " << msgrcvd << '\n' ;
 
   err = MPI_Finalize() ;
   if ( err )
   {
      printf( "finalize err = %d\n", err ) ;
      abort() ;
   }

   return 0 ;
}
