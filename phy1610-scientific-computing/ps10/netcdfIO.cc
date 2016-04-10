#include "netcdfIO.h"
#include "myexceptions.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include "physicsplay_build_version.h"
#include <mpi.h>
#include <netcdf_par.h>

// macro to retain __LINE__ info in the BOOST_THROW_EXCEPTION macro
#define handle_error( status )                                       \
do {                                                                 \
   if ( status )                                                     \
   {                                                                 \
      BOOST_THROW_EXCEPTION(                                         \
            netcdf_error()                                           \
               << netcdf_errno_info( status )                        \
               << netcdf_strerror_info( nc_strerror( status ) )      \
               ) ;                                                   \
   }                                                                 \
} while ( 0 )

netcdfIO::netcdfIO( const std::string & fileBaseName, const size_t N )
   : m_opened( false )
{
   int status ;
   const std::string filename{ fileBaseName + ".nc" } ;

   status = nc_create_par( filename.c_str(),
                           NC_NETCDF4 | NC_MPIIO,
                           MPI_COMM_WORLD,
                           MPI_INFO_NULL,
                           &m_ncid ) ;
   if ( status )
   {
      BOOST_THROW_EXCEPTION(
            file_open_error()
               << name_info( filename )
               << netcdf_errno_info( status )
               << netcdf_strerror_info( nc_strerror( status ) )
               ) ;
   }
   m_opened = true ;

   status = nc_def_dim( m_ncid,
                        "X",
                        N,
                        &m_xDimId ) ;
   handle_error( status ) ;

   status = nc_def_dim( m_ncid,
                        "T",
                        NC_UNLIMITED,
                        &m_tDimId ) ;
   handle_error( status ) ;

   int rhoVarDims[]{ m_tDimId, m_xDimId } ;

   status = nc_def_var( m_ncid, "RHO", NC_FLOAT, 2, rhoVarDims, &m_rhoVarId ) ;
   handle_error( status ) ;

   int xVarDims[]{ m_xDimId } ;

   status = nc_def_var( m_ncid, "X", NC_FLOAT, 1, xVarDims, &m_xVarId) ;
   handle_error( status ) ;

   status = nc_put_att_text( m_ncid,
                             NC_GLOBAL,
                             "commit",
                             strlen(PHYSICSPLAY_COMMIT_INFO),
                             PHYSICSPLAY_COMMIT_INFO ) ;
   handle_error( status ) ;

   status = nc_enddef( m_ncid ) ;
   handle_error( status ) ;

   status = nc_var_par_access( m_ncid, m_rhoVarId, NC_COLLECTIVE ) ;
   handle_error( status ) ;

   status = nc_var_par_access( m_ncid, m_xVarId, NC_COLLECTIVE ) ;
   handle_error( status ) ;
}

netcdfIO::~netcdfIO( )
{
   int status = nc_close( m_ncid ) ;

   if ( status )
   {
      BOOST_THROW_EXCEPTION(
            netcdf_error()
               << netcdf_errno_info( status )
               << netcdf_strerror_info( nc_strerror( status ) )
               ) ;
   }
}

void netcdfIO::writeData( const size_t          timeStepCount,
                          const size_t          globalOffset,
                          const size_t          localN,
                          const float * const   localRhoStart )
{
   size_t startRho[]{ timeStepCount, globalOffset } ;
   size_t countRho[]{ 1, localN } ;
   int status = nc_put_vara_float( m_ncid,
                                   m_rhoVarId,
                                   startRho,
                                   countRho,
                                   localRhoStart ) ;
   handle_error( status ) ;
}

void netcdfIO::writeMeta( const size_t          globalOffset,
                          const size_t          localN,
                          const float * const   localXstart,
                          const float * const   localRhoStart )
{
   size_t startX[]{ globalOffset } ;
   size_t countX[]{ localN } ;

   int status = nc_put_vara_float( m_ncid,
                                   m_xVarId,
                                   startX,
                                   countX,
                                   localXstart ) ;
   handle_error( status ) ;

   writeData( 0, globalOffset, localN, localRhoStart ) ;
}
