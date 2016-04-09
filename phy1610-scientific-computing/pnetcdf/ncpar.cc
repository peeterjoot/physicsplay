#include <mpi.h>
#include "mpitask.h"
#include <netcdf_par.h>
#include <netcdf.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define NDIMS 2
#define DIMSIZE 24
#define QTR_DATA (DIMSIZE * DIMSIZE / 4)
#define ERR \
do { \
   std::cout << __FILE__ << ':' << __LINE__ << ": res=" << res << " (" << nc_strerror(res) << '\n' ; \
   abort() ; \
} while ( 0 )

#define FILE "tst_parallel.nc"

int main( int argc, char ** argv )
{
   mpitask mpi( &argc, &argv ) ;

   MPI_Comm comm = MPI_COMM_WORLD;
   MPI_Info info = MPI_INFO_NULL;

   int ncid, v1id, dimids[NDIMS];
   size_t start[NDIMS], count[NDIMS];

   int data[DIMSIZE * DIMSIZE], i, res;
   int slab_data[DIMSIZE * DIMSIZE / 4]; /* one slab */

   if (mpi.m_rank == 1)
      printf("\n*** tst_parallel testing very basic parallel access.\n");

   /* Create a parallel netcdf-4 file. */
   if ((res = nc_create_par(FILE, NC_NETCDF4|NC_MPIIO, comm, info, &ncid))) ERR;

   /* Create two dimensions. */
   if ((res = nc_def_dim(ncid, "d1", DIMSIZE, dimids))) ERR;
   if ((res = nc_def_dim(ncid, "d2", DIMSIZE, &dimids[1]))) ERR;

   /* Create one var. */
   if ((res = nc_def_var(ncid, "v1", NC_INT, NDIMS, dimids, &v1id))) ERR;

   if ((res = nc_enddef(ncid))) ERR;

   start[0] = mpi.m_rank * DIMSIZE/mpi.m_size ;
   start[1] = 0 ;
   /* Set up slab for this process. */
   count[0] = DIMSIZE/mpi.m_size ;
   count[1] = DIMSIZE ;

   /* Create phoney data. We're going to write a 24x24 array of ints,
      in 4 sets of 144. */
   for (i=mpi.m_rank*QTR_DATA; i < (mpi.m_rank+1)*QTR_DATA; i++)
      data[i] = mpi.m_rank;

   /*if ((res = nc_var_par_access(ncid, v1id, NC_COLLECTIVE)))
     ERR;*/
   if ((res = nc_var_par_access(ncid, v1id, NC_INDEPENDENT))) ERR;

   /* Write slabs of phoney data. */
   if ((res = nc_put_vara_int(ncid, v1id, start, count, &data[mpi.m_rank*QTR_DATA]))) ERR;

   /* Close the netcdf file. */
   if ((res = nc_close(ncid)))   ERR;
   
   return 0;
}
