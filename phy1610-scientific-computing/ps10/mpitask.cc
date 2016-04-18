/** \file mpitask.cc
 */
#include <mpi.h>
#include "myexceptions.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include "mpitask.h"

mpitask::mpitask( int rank, int size )
   : m_rank( rank )
   , m_size( size )
   , m_initDone( false )
{
}

mpitask::mpitask( int * pargc, char *** pargv )
   : m_rank( -1 )
   , m_size( -1 )
   , m_initDone( false )
{
   int err = MPI_Init( pargc, pargv ) ;
   if ( err )
   {
      BOOST_THROW_EXCEPTION(
            mpiinitterm_error()
               << mpierr_info( err ) ) ;
   }

   m_initDone = true ;

   err = MPI_Comm_size( MPI_COMM_WORLD, &m_size ) ;
   if ( err )
   {
      BOOST_THROW_EXCEPTION(
            mpiinitterm_error()
               << mpierr_info( err ) ) ;
   }

   err = MPI_Comm_rank( MPI_COMM_WORLD, &m_rank ) ;
   if ( err )
   {
      BOOST_THROW_EXCEPTION(
            mpiinitterm_error()
               << mpierr_info( err ) ) ;
   }
}

mpitask::~mpitask()
{
   if ( !m_initDone )
      return ;

   int err = MPI_Finalize() ;
   if ( err )
   {
      // throwing in a destructure will cause std::terminate to be invoked.  Probably not unreasonable in this case.
      BOOST_THROW_EXCEPTION(
            mpiinitterm_error()
               << mpierr_info( err ) ) ;
   }
}
