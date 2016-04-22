#include <mpi.h>
#include <netcdf_par.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <iostream>
#include "physicsplay_build_version.h"
#include "mpitask.h"
#include "rangePartition.h"

#define handle_error( status, what )   \
do {                                   \
   if ( status )                       \
   {                                   \
      std::cout                        \
         << __FILE__                   \
         << ':'                        \
         << __LINE__                   \
         << ':'                        \
         << what                       \
         << " failed with rc = "       \
         << status                     \
         << ':'                        \
         << nc_strerror( status )      \
         << '\n' ;                     \
      abort() ;                        \
   }                                   \
} while ( 0 )

int main( int argc, char ** argv )
{
   mpitask mpi( &argc, &argv ) ;

   int status, ncid, XdimId, TdimId, idVarG, idVarA ;
   constexpr int N{40} ;
   rangePartition p( N, mpi.m_size, mpi.m_rank ) ;

   // also: nc_open for already existing only
   status = nc_create_par( "foo.nc",
                           NC_NETCDF4 | NC_MPIIO,
                           MPI_COMM_WORLD,
                           MPI_INFO_NULL,
                           &ncid ) ;
   handle_error( status, "nc_create" ) ;

   status = nc_def_dim( ncid,
                        "X",
                        N,
                        &XdimId ) ;
   handle_error( status, "nc_def_dim" ) ;

   status = nc_def_dim( ncid,
                        "T",
                        NC_UNLIMITED,
                        &TdimId ) ;
   handle_error( status, "nc_def_dim" ) ;

   int dimsA[2]{TdimId, XdimId} ;

   status = nc_def_var( ncid, "A", NC_INT, 2, dimsA, &idVarA) ;
   handle_error( status, "nc_def_var" ) ;

   int dimsG[2]{XdimId} ;

   status = nc_def_var( ncid, "G", NC_FLOAT, 1, dimsG, &idVarG) ;
   handle_error( status, "nc_def_var" ) ;

   status = nc_put_att_text( ncid,
                             NC_GLOBAL,
                             "commit",
                             strlen(PHYSICSPLAY_COMMIT_INFO),
                             PHYSICSPLAY_COMMIT_INFO ) ;
   handle_error( status, "nc_put_att_text" ) ;

   status = nc_enddef( ncid ) ;
   handle_error( status, "nc_enddef" ) ;


#if 1
   std::vector<int> vecA( p.localPartitionSize() ) ;
   std::vector<float> vecG( p.localPartitionSize() ) ;
   rangePartition::subrange r{ p.subsetOfGlobalRangeInThisPartition( 1, N ) } ;
   for( auto j{r.first-1} ; j < r.second ; j++ )
   {
      int i = p.toLocalDomain( j ) ;

      vecA[i] = j ;
      vecG[i] = j/10.0 ;
   }

   status = nc_var_par_access( ncid, idVarA, NC_COLLECTIVE ) ;
   handle_error( status, "nc_var_par_access" ) ;

   status = nc_var_par_access( ncid, idVarG, NC_COLLECTIVE ) ;
   handle_error( status, "nc_var_par_access" ) ;

   // Write out the grid-mesh values:
   size_t startG[]{p.m_myFirstGlobalElementIndex -1} ;
   size_t countG[]{p.localPartitionSize()} ;
   status = nc_put_vara_float( ncid,
                               idVarG,
                               startG,
                               countG,
                               &vecG[0] ) ;
   handle_error( status, "nc_put_var_float" ) ;

   // Write out three timeslices of data:
   for ( size_t s{0} ; s < 3 ; s++ )
   {
      size_t startA[]{s, p.m_myFirstGlobalElementIndex -1} ;
      size_t countA[]{1, p.localPartitionSize()} ;
      status = nc_put_vara_int( ncid,
                                idVarA,
                                startA,
                                countA,
                                &vecA[0] ) ;
      handle_error( status, "nc_put_var_int" ) ;

      for( auto j{r.first-1} ; j < r.second ; j++ )
      {
         int i = p.toLocalDomain( j ) ;

         vecA[i] ++ ;
      }
   }

#else
   std::vector<int> vecA( N ) ;
   std::vector<float> vecG( N ) ;
   for( auto i{0} ; i < N ; i++ )
   {
      vecA[i] = j ;
      vecG[i] = j/10.0 ;
   }

   status = nc_var_par_access( ncid, idVarA, NC_INDEPENDENT ) ;
   handle_error( status, "nc_var_par_access" ) ;

   status = nc_var_par_access( ncid, idVarG, NC_INDEPENDENT ) ;
   handle_error( status, "nc_var_par_access" ) ;

   // Write out three timeslices of data:
   for ( size_t s{0} ; s < 3 ; s++ )
   {
      size_t startA[]{s, 0} ;
      size_t countA[]{1, N} ;
      status = nc_put_vara_int( ncid,
                                idVarA,
                                startA,
                                countA,
                                &vecA[0] ) ;
      handle_error( status, "nc_put_var_int" ) ;

      // timestep:
      for( auto i{0} ; i < N ; i++ )
      {
         vecA[i] ++ ;
      }
   }

   // Write out the grid-mesh values:
   size_t startG[]{0} ;
   size_t countG[]{N} ;
   status = nc_put_vara_float( ncid,
                               idVarG,
                               startG,
                               countG,
                               &vecG[0] ) ;
   handle_error( status, "nc_put_var_float" ) ;
#endif

   status = nc_close( ncid ) ;
   handle_error( status, "nc_close" ) ;

   return 0 ;
}
