#include <netcdf.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <iostream>
#include "physicsplay_build_version.h"

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
   int status, ncid, idX, idTime, varid ;
   constexpr auto N{40} ;

   // also: nc_open for already existing only
   status = nc_create( "foo.nc",
                       NC_CLOBBER,
                       &ncid ) ;
   handle_error( status, "nc_create", __LINE__ ) ;

   status = nc_def_dim( ncid,
                        "X",
                        N,
                        &idX ) ;
   handle_error( status, "nc_def_dim", __LINE__ ) ;

   status = nc_def_dim( ncid,
                        "T",
                        NC_UNLIMITED,
                        &idTime ) ;
   handle_error( status, "nc_def_dim", __LINE__ ) ;

   int dims[2]{idTime, idX} ;

   status = nc_def_var( ncid, "R", NC_INT, 2, dims, &varid);
   handle_error( status, "nc_def_var", __LINE__ ) ;

   std::vector<int> R ;
   int i{0} ;
   for( int &v : R )
   {
      v += 2 * i ;

      i++ ;
   }

   status = nc_put_att_text( ncid,
                             NC_GLOBAL,
                             "commit",
                             strlen(PHYSICSPLAY_COMMIT_INFO),
                             PHYSICSPLAY_COMMIT_INFO ) ;
   handle_error( status, "nc_put_att_text", __LINE__ ) ;

   status = nc_enddef( ncid ) ;
   handle_error( status, "nc_enddef", __LINE__ ) ;

   size_t start{0} ;
   size_t count{1} ;
   status = nc_put_vara_int( ncid,
                             varid,
                             &start,
                             &count,
                             &R[0] );
   handle_error( status, "nc_put_var_int", __LINE__ ) ;

   status = nc_close( ncid ) ;
   handle_error( status, "nc_close", __LINE__ ) ;

   return 0 ;
}
