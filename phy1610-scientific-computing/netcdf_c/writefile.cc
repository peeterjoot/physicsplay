#include <netcdf.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <iostream>
#include "physicsplay_build_version.h"

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

int main()
{
   int status, ncid, XdimId, TdimId, idVarG, idVarA ;
   constexpr auto N{40} ;

   // also: nc_open for already existing only
   status = nc_create( "foo.nc",
                       NC_CLOBBER,
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

   std::vector<int> vecA(N) ;
   std::vector<float> vecG(N) ;
   for( auto i{0} ; i < N ; i++ )
   {
      vecA[i] = i ;
      vecG[i] = i/10.0 ;
   }

   status = nc_put_att_text( ncid,
                             NC_GLOBAL,
                             "commit",
                             strlen(PHYSICSPLAY_COMMIT_INFO),
                             PHYSICSPLAY_COMMIT_INFO ) ;
   handle_error( status, "nc_put_att_text" ) ;

   status = nc_enddef( ncid ) ;
   handle_error( status, "nc_enddef" ) ;

   // Write out three timeslices of data:
   for ( size_t i{0} ; i < 3 ; i++ )
   {
      size_t startA[]{i, 0} ;
      size_t countA[]{1, N} ;
      status = nc_put_vara_int( ncid,
                                idVarA,
                                startA,
                                countA,
                                &vecA[0] ) ;
      handle_error( status, "nc_put_var_int" ) ;

      // timestep:
      for( auto j{0} ; j < N ; j++ )
      {
         vecA[j] ++ ;
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

   status = nc_close( ncid ) ;
   handle_error( status, "nc_close" ) ;

   return 0 ;
}
