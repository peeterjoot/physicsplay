#include <netcdf.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <iostream>

#define handle_error( status, what )         \
do {                                         \
   if ( status )                             \
   {                                         \
      std::cout                              \
         << __FILE__                         \
         << ':'                              \
         << __LINE__                         \
         << ':'                              \
         << what                             \
         << " failed with rc = "             \
         << status                           \
         << ':'                              \
         << nc_strerror( status )            \
         << '\n' ;                           \
      abort() ;                              \
   }                                         \
} while ( 0 )

int main()
{
   int status, ncid, XdimId, TdimId, idVarG, idVarA ;
   size_t N, tLen ;

   status = nc_open( "foo.nc",
                     NC_NOWRITE,
                     &ncid ) ;
   handle_error( status, "nc_create" ) ;

   status = nc_inq_dimid( ncid,
                          "X",
                          &XdimId ) ;
   handle_error( status, "nc_inq_dimid" ) ;

   status = nc_inq_dimlen( ncid,
                           XdimId,
                           &N ) ;
   handle_error( status, "nc_inq_dimlen" ) ;

   std::cout << "X dim: " << N << '\n' ;

   status = nc_inq_dimid( ncid,
                          "T",
                          &TdimId ) ;
   handle_error( status, "nc_inq_dimid" ) ;

   status = nc_inq_dimlen( ncid,
                           TdimId,
                           &tLen ) ;
   handle_error( status, "nc_inq_dimlen" ) ;

   std::cout << "T dim: " << tLen << '\n' ;

   status = nc_inq_varid( ncid,
                          "A",
                          &idVarA ) ;
   handle_error( status, "nc_inq_varid" ) ;

   status = nc_inq_varid( ncid,
                          "G",
                          &idVarG ) ;
   handle_error( status, "nc_inq_varid" ) ;

   size_t commitStringLen ;
   status = nc_inq_attlen( ncid,
                           NC_GLOBAL,
                           "commit",
                           &commitStringLen ) ;

   char commit[ commitStringLen + 1 ] ;
   status = nc_get_att_text( ncid,
                             NC_GLOBAL,
                             "commit",
                             commit ) ;
   handle_error( status, "nc_get_att_text" ) ;
   std::cout << "commit: " << commit << '\n' ;

   std::vector<int> vecA(N) ;
   std::vector<float> vecG(N) ;

   // Read in the grid-mesh values:
   status = nc_get_var_float( ncid,
                              idVarG,
                              &vecG[0] ) ;
   handle_error( status, "nc_get_var_float" ) ;

   for ( size_t i{0} ; i < N ; i++ )
   {
      std::cout << "x[" << i << "] = " << vecG[i] << '\n' ;
   }

   // Read in the three timeslices of data:
   for ( size_t s{0} ; s < tLen ; s++ )
   {
      size_t startA[]{s, 0} ;
      size_t countA[]{1, N} ;
      status = nc_get_vara_int( ncid,
                                idVarA,
                                startA,
                                countA,
                                &vecA[0] ) ;
      handle_error( status, "nc_get_vara_int" ) ;

      for ( size_t i{0} ; i < N ; i++ )
      {
         std::cout << s << ": y[" << i << "] = " << vecA[i] << '\n' ;
      }
   }

   status = nc_close( ncid ) ;
   handle_error( status, "nc_close" ) ;

   return 0 ;
}
