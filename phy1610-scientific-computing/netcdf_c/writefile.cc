#include <netcdf.h>
#include <stdlib.h>

void handle_error( const int status )
{
   abort() ;
}

int main()
{
   int status, ncid, idX, idTime ;

   status = nc_create( "foo.nc", NC_CLOBBER, &ncid ) ;
   if (status != NC_NOERR)
      handle_error(status) ;

   status = nc_def_dim( ncid, "X", 40, &idX ) ;
   if (status != NC_NOERR)
      handle_error(status) ;

   status = nc_def_dim( ncid, "T", NC_UNLIMITED, &idTime ) ;
   if (status != NC_NOERR)
      handle_error(status) ;

   status = nc_close( ncid ) ;
   if (status != NC_NOERR)
      handle_error(status) ;

   return 0 ;
}
