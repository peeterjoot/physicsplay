#include <netcdf.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <iostream>

#define handle_error( status, what, line ) \
do { \
   if ( status ) \
   { \
      std::cout << __FILE__ << ':' << line << ':' << what << " failed with rc = " << status << ':' << nc_strerror( status ) << '\n' ; \
      abort() ; \
   } \
} while ( 0 ) 

int main()
{
   int status, ncid, XdimId, TdimId, idVarG, idVarA ;
   constexpr auto N{40} ;

   status = nc_open( "foo.nc", NC_NOWRITE, &ncid ) ;
   handle_error( status, "nc_create", __LINE__ ) ;

#if 0
   status = nc_def_dim( ncid,
                        "X",
                        N,
                        &XdimId ) ;
   handle_error( status, "nc_def_dim", __LINE__ ) ;

   status = nc_def_dim( ncid,
                        "T",
                        NC_UNLIMITED,
                        &TdimId ) ;
   handle_error( status, "nc_def_dim", __LINE__ ) ;

   int dimsA[2]{TdimId, XdimId} ;

   status = nc_def_var( ncid, "A", NC_INT, 2, dimsA, &idVarA);
   handle_error( status, "nc_def_var", __LINE__ ) ;

   int dimsG[2]{XdimId} ;

   status = nc_def_var( ncid, "G", NC_FLOAT, 1, dimsG, &idVarG);
   handle_error( status, "nc_def_var", __LINE__ ) ;
#endif

   status = nc_get_att_text( ncid,
                             NC_GLOBAL,
                             "commit",
                             strlen(PHYSICSPLAY_COMMIT_INFO),
                             PHYSICSPLAY_COMMIT_INFO ) ;
   handle_error( status, "nc_get_att_text", __LINE__ ) ;

   std::vector<int> vecA(N) ;
   std::vector<float> vecG(N) ;
   for( auto i{0} ; i < N ; i++ )
   {
      vecA[i] = i ;
      vecG[i] = i/10.0 ;
   }

   // Read in three timeslices of data:
   for ( size_t i{0} ; i < 3 ; i++ )
   {
      size_t startA[]{i, 0} ;
      size_t countA[]{1, N} ;
      status = nc_get_vara_int( ncid,
                                idVarA,
                                startA,
                                countA,
                                &vecA[0] );
      handle_error( status, "nc_get_var_int", __LINE__ ) ;
   }

   // Read in the grid-mesh values:
   size_t startG[]{0} ;
   size_t countG[]{N} ;
   status = nc_get_vara_float( ncid,
                               idVarG,
                               startG,
                               countG,
                               &vecG[0] );
   handle_error( status, "nc_get_var_float", __LINE__ ) ;

   status = nc_close( ncid ) ;
   handle_error( status, "nc_close", __LINE__ ) ;

   return 0 ;
}
