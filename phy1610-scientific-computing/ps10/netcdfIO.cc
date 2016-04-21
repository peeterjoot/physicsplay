#include "netcdfIO.h"
#include "myexceptions.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <mpi.h>
#include <netcdf_par.h>
#include "rangePartition.h"

// This is a macro instead of inline to retain __LINE__ info in the BOOST_THROW_EXCEPTION call
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

/**
 don't know if this is actually an invalid value for netcdf (file, dimension, variable) handles, but at least give these a
 non-random value.
 */
static const constexpr int INVALID_NETCDF_ID{-1} ;

netcdfIO::netcdfIO( const std::string &   fileBaseName,
                    const size_t          N,
                    const int             size,
                    const int             rank,
                    const bool            writeTimes,
                    const std::string &   params )
   : iohandlerImplementation( size, rank, writeTimes )
   , m_opened( false )
   , m_ncid{ INVALID_NETCDF_ID }
   , m_xDimId{ INVALID_NETCDF_ID }
   , m_tDimId{ INVALID_NETCDF_ID }
   , m_rhoVarId{ INVALID_NETCDF_ID }
   , m_xVarId{ INVALID_NETCDF_ID }
   , m_timesVarId{ INVALID_NETCDF_ID }
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

   int atTimesDims[]{ m_tDimId } ;
   status = nc_def_var( m_ncid, "TIMES", NC_FLOAT, 1, atTimesDims, &m_timesVarId) ;
   handle_error( status ) ;

   status = nc_put_att_text( m_ncid,
                             NC_GLOBAL,
                             "params",
                             params.length(),
                             params.c_str() ) ;
   handle_error( status ) ;

   status = nc_enddef( m_ncid ) ;
   handle_error( status ) ;

   status = nc_var_par_access( m_ncid, m_rhoVarId, NC_COLLECTIVE ) ;
   handle_error( status ) ;

   status = nc_var_par_access( m_ncid, m_xVarId, NC_COLLECTIVE ) ;
   handle_error( status ) ;

   if ( 1 )
   {
      status = nc_var_par_access( m_ncid, m_timesVarId, NC_COLLECTIVE ) ;
   }
   else
   {
      status = nc_var_par_access( m_ncid, m_timesVarId, NC_INDEPENDENT ) ;
   }
   handle_error( status ) ;
}

void netcdfIO::writeData( const float           time,
                          const size_t          globalOffset,
                          const size_t          localN,
                          const float * const   localXstartIgnored,
                          const float * const   localRhoStart )
{
   size_t startRho[]{ m_outStepCount, globalOffset } ;
   size_t countRho[]{ 1, localN } ;
   int status = nc_put_vara_float( m_ncid,
                                   m_rhoVarId,
                                   startRho,
                                   countRho,
                                   localRhoStart ) ;
   handle_error( status ) ;

   m_times.push_back( time ) ;
   m_outStepCount++ ;
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

   writeData( 0.0,
              globalOffset,
              localN,
              nullptr,
              localRhoStart ) ;
}

void netcdfIO::internalClose( const bool isErrorCodePath )
{
   if ( m_opened )
   {
      if ( isErrorCodePath )
      {
         // We are either serivicing an exception, or somebody didn't call close() explicitly
         // before the destructor triggered.
         (void) nc_close( m_ncid ) ;
      }
      else
      {
         int status ;

         // HACK.  Need to be able to deal with (unanswered) issue raised here:
         //
         // https://support.scinet.utoronto.ca/education/go.php/218/forums/forum/view.php/fid/6/pid/336/
         //
         if ( (0 == m_rank) && m_withTimes )
         {
            auto tsize{ m_times.size() } ;

            size_t start[]{ 0 } ;
            size_t count[]{ tsize } ;

            status = nc_put_vara_float( m_ncid,
                                        m_timesVarId,
                                        start,
                                        count,
                                        &m_times[ 0 ] ) ;
            handle_error( status ) ;
         }

         if ( 0 ) // didn't help
         {
            status = MPI_Barrier( MPI_COMM_WORLD ) ;
            handle_error( status ) ;
         }

         status = nc_close( m_ncid ) ;

         if ( status )
         {
            BOOST_THROW_EXCEPTION(
                  netcdf_error()
                     << netcdf_errno_info( status )
                     << netcdf_strerror_info( nc_strerror( status ) )
                     ) ;
         }
      }

      m_opened = false ;
   }
}

void netcdfIO::close( )
{
   internalClose( false ) ;
}

netcdfIO::~netcdfIO( )
{
   internalClose( true ) ;
}
