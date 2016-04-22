/** \file ghosts.cc

  A standalone mpi worker to get the ghost cell send/recv logic tested independently.
  */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/assert.hpp>
#include <mpi.h>
#include "sendAndRecieveGhostCells.h"

int main( int argc, char* argv[] )
{
   int rank ;
   int size ;
   int err ;

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

   std::vector<float> send{ rank * 2.0f, rank * 2.0f + 1 } ;
   std::vector<float> recieved(2) ;

#if 0
   MPI_Status rstatus ;
   constexpr int tag1{ 1 } ;
   constexpr int tag2{ 2 } ;

   // send right ghost cell right.
   // send left ghost cell left.
   // recieve right's left ghost cell.
   // recieve lefts's right ghost cell.
   int left{ rank - 1 } ;
   if ( rank == 0 )
   {
      left = MPI_PROC_NULL ;
   }

   int right{ rank + 1 } ;
   if ( right == size )
   {
      right = MPI_PROC_NULL ;
   }

   err = MPI_Sendrecv( &send[1], 1, MPI_FLOAT, right, tag1,
                       &recieved[0], 1, MPI_FLOAT, left, tag1,
                       MPI_COMM_WORLD, &rstatus ) ;
   if ( err )
   {
      printf( "sendrecv err = %d\n", err ) ;
      abort() ;
   }

   err = MPI_Sendrecv( &send[0], 1, MPI_FLOAT, left, tag2,
                       &recieved[1], 1, MPI_FLOAT, right, tag2,
                       MPI_COMM_WORLD, &rstatus ) ;
   if ( err )
   {
      printf( "sendrecv err = %d\n", err ) ;
      abort() ;
   }
#else
   sendAndRecieveGhostCells( send[0], send[1],
                             &recieved[1], &recieved[0],
                             size,
                             rank ) ;
#endif

   if ( rank )
   {
      // should have gotten left's rightmost ghostcell:
      BOOST_ASSERT( recieved[0] == send[0] - 1 ) ;
   }

   if ( rank != (size-1) )
   {
      // should have gotten right's leftmost ghostcell:
      BOOST_ASSERT( recieved[1] == send[1] + 1 ) ;
   }

   std::cout << rank << "( " << send[0] << ", " << send[1] << " ): " << recieved[0] << ", " << recieved[1] << '\n' ;

   err = MPI_Finalize() ;
   if ( err )
   {
      printf( "finalize err = %d\n", err ) ;
      abort() ;
   }

   return 0 ;
}
