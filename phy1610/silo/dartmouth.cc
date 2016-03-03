// https://www.dartmouth.edu/~rc/classes/visit/import_data_silo.html
#include "silo.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Program to make a silo file from the wind temperature and velocity data from OpenDX.
int main(int argc, char *argv[])
{
   #define NX 144
   #define NY 73

   #define MAXLINE 1024
   char line[MAXLINE] ;
   int i, j ;
   //int index = 0 ;
   int dims[] = { NX, NY } ;
   int ndims = 2 ;
   //int nvars = 2 ;
   //int vardims[] = { 1, 3 } ;
   //int centering[] = { 1, 1 } ;
   char * varnames[] = { (char *)"velocity_x", (char *)"velocity_y" } ;
   float temp[NY][NX], vel_x[NY][NX], vel_y[NY][NX] ;
   float *velocity[2] ;
   float *temperature ;
   float x[NX], y[NY] ;
   float *coords[] = { x, y } ;

   velocity[0] = (float *) malloc(sizeof(float) * NX * NY) ;
   velocity[1] = (float *) malloc(sizeof(float) * NX * NY) ;
   temperature = (float *) malloc(sizeof(float) * NX * NY) ;
   FILE *fp1 ;
   if ((fp1 = fopen("temp.dat", "r")) == 0)
   {
      fprintf(stderr, "Error opening temperature data file. exiting ... \n") ;
      exit(-1) ;
   }
   /* read in the temerpature data */

   for (j = 0 ; j < NX; ++j)
      for (i = 0 ; i < NY; ++i)
      {
         fgets(line, MAXLINE, fp1) ;
         sscanf(line, "%f", &temp[i][j]) ;
      }

   fclose(fp1) ;

   if ((fp1 = fopen("wind_vel.dat", "r")) == 0)
   {
      fprintf(stderr,
              "Error opening wind velocity data file. exiting ... \n") ;
      exit(-1) ;
   }
   /* read in wind velocity data */
   for (j = 0 ; j < NX; ++j)
      for (i = 0 ; i < NY; ++i)
      {
         fgets(line, MAXLINE, fp1) ;
         sscanf(line, "%f %f", &vel_x[i][j], &vel_y[i][j]) ;
      }
   fclose(fp1) ;

   for (i = 0 ; i < NY; ++i)
      for (j = 0 ; j < NX; ++j)
      {
         temperature[i * NX + j] = temp[i][j] ;
         velocity[0][i * NX + j] = vel_x[i][j] ;
         velocity[1][i * NX + j] = vel_y[i][j] ;
      }
   // create x axis coordinates
   for (i = 0 ; i < NX; i++)
      x[i] = -178.75 + 2.5 * i ;

   // create y axis coordinates
   for (i = 0 ; i < NY; i++)
      y[i] = -90 + 2.5 * i ;

   DBfile *dbfile = NULL ;
   /* Open the Silo file */
   dbfile = DBCreate("wind_temp.silo", DB_CLOBBER, DB_LOCAL,
                     "2D wind temperature and velocity data", DB_HDF5) ;
   if (dbfile == NULL)
   {
      fprintf(stderr, "Could not create Silo file!\n") ;
      return -1 ;
   }

   /* write a 2D rectilinear mesh  */
   DBPutQuadmesh(dbfile, "quadmesh", NULL, coords, dims, ndims, DB_FLOAT,
                 DB_COLLINEAR, NULL) ;
   DBPutQuadvar1(dbfile, "temp", "quadmesh", temperature, dims, ndims, NULL,
                 0, DB_FLOAT, DB_NODECENT, NULL) ;
   DBPutQuadvar(dbfile, "velocity", "quadmesh", 2, varnames, velocity, dims,
                ndims, NULL, 0, DB_FLOAT, DB_NODECENT, NULL) ;
   DBClose(dbfile) ;

   return 0 ;
}
