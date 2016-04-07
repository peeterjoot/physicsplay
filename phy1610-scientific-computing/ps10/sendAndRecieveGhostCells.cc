/** \file sendAndRecieveGhostCells.cc
 */

#include <mpi.h>
#include "myexceptions.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include "sendAndRecieveGhostCells.h"

void sendAndRecieveGhostCells( const float   myLeftGhostCell,
                               const float   myRightGhostCell,
                               float *       pLeftGhostCellFromRight,
                               float *       pRightGhostCellFromLeft,
                               const int     size,
                               const int     rank )
{
   int err ;
   MPI_Status rstatus ;
   constexpr int tag1 = 1 ;
   constexpr int tag2 = 2 ;

   int left = rank - 1 ;
   if ( rank == 0 )
   {
      left = MPI_PROC_NULL ;
   }

   int right = rank + 1 ;
   if ( right == size )
   {
      right = MPI_PROC_NULL ;
   }

   err = MPI_Sendrecv( const_cast<float *>(&myRightGhostCell), 1, MPI_FLOAT, right, tag1,
                       pRightGhostCellFromLeft, 1, MPI_FLOAT, left, tag1,
                       MPI_COMM_WORLD, &rstatus ) ;
   if ( err )
   {
      BOOST_THROW_EXCEPTION(
            sendrecv_error()
               << mpirank_info( rank )
               << mpileft_info( left )
               << mpiright_info( right )
               << mpitag_info( tag1 )
               << mpierr_info( err ) ) ;
   }

   err = MPI_Sendrecv( const_cast<float *>(&myLeftGhostCell), 1, MPI_FLOAT, left, tag2,
                       pLeftGhostCellFromRight, 1, MPI_FLOAT, right, tag2,
                       MPI_COMM_WORLD, &rstatus ) ;
   if ( err )
   {
      BOOST_THROW_EXCEPTION(
            sendrecv_error()
               << mpirank_info( rank )
               << mpileft_info( left )
               << mpiright_info( right )
               << mpitag_info( tag2 )
               << mpierr_info( err ) ) ;
   }
}
