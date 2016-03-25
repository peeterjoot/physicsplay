// based on dartmouth.cc with error handling and just the raw calls without any attempt to make the data interesting.

#include "silo.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// hdfview fiveByThree.silo &
int main( int argc, char *argv[] )
{
   constexpr auto NX { 5 } ;
   constexpr auto NY { 3 } ;

   int dims[] = { NX, NY } ;
   int ndims = 2 ;
   float x[NX] { 0.1, 0.2, 0.3, 0.4, 0.5 } ;      
   float y[NY] { 1.1, 1.2, 1.3 } ;      
   float scalar[NX * NY] { 5.1, 5.2, 5.3, 5.4, 5.5,
                           7.1, 7.2, 7.3, 7.4, 7.5,
                           9.1, 9.2, 9.3, 9.4, 9.5 } ;
   float vector_x[NX * NY] { 50.1, 50.2, 50.3, 50.4, 50.5,
                             70.1, 70.2, 70.3, 70.4, 70.5,
                             90.1, 90.2, 90.3, 90.4, 90.5 } ;
   float vector_y[NX * NY] { 59.1, 59.2, 59.3, 59.4, 59.5,
                             79.1, 79.2, 79.3, 79.4, 79.5,
                             99.1, 99.2, 99.3, 99.4, 99.5 } ;

   float *coords[] = { x, y } ;
   float *vector[] = { vector_x, vector_y } ;
   char * varnames[]{ (char *)"v_x", (char *)"v_y" } ;

   DBfile * dbfile = DBCreate( "fiveByThree.silo", DB_CLOBBER, DB_LOCAL,
                               "some grid data", DB_HDF5 ) ;
   if ( dbfile == NULL )
   {
      // on error: could use: DBErrno, DBErrfuncname
      fprintf( stderr, "Could not create Silo file!\n" ) ;

      return -1 ;
   }

   int err ;

   err = DBPutQuadmesh( dbfile, "points", NULL, coords, dims, ndims, DB_FLOAT, DB_COLLINEAR, NULL ) ;
   if ( err )
   {
      fprintf( stderr, "mesh write failed\n" ) ;

      goto CLEANUP ;
   }
   err = DBPutQuadvar1( dbfile, "scalar", "quadmesh", scalar, dims, ndims, NULL, 0, DB_FLOAT, DB_NODECENT, NULL ) ;
   if ( err )
   {
      fprintf( stderr, "scalar write failed\n" ) ;

      goto CLEANUP ;
   }
   err = DBPutQuadvar( dbfile, "vector", "quadmesh", 2, varnames, vector, dims, ndims, NULL, 0, DB_FLOAT, DB_NODECENT, NULL ) ;
   if ( err )
   {
      fprintf( stderr, "mesh write failed\n" ) ;

      goto CLEANUP ;
   }

CLEANUP:
   err = DBClose( dbfile ) ;
   if ( err )
   {
      fprintf( stderr, "close failed\n" ) ;
   }

   return 0 ;
}
