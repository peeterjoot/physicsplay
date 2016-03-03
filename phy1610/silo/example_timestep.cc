#include <silo.h>
#include <stdio.h>

/* SIMPLE SIMULATION SKELETON */
void write_vis_dump( int cycle )
{
   DBfile * dbfile = NULL ;

   /* Create a unique filename for the new Silo file*/
   char filename[100] ;
   sprintf( filename, "output%04d.silo", cycle ) ;

   /* Open the Silo file */
   dbfile = DBCreate( filename, DB_CLOBBER, DB_LOCAL,
                      "simulation time step", DB_HDF5 ) ;

   /* Add other Silo calls to write data here. */
   /* Close the Silo file. */
   DBClose( dbfile ) ;
}

int main( int, char ** )
{
   int c[]{1,2} ;

   for ( auto cycle : c )
   {
      //simulate_one_timestep () ;
      write_vis_dump( cycle ) ;
   }

   return 0 ;
}
