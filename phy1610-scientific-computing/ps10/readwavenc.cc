#include <netcdf.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <iostream>
#include <getopt.h>
#include "returncodes.h"

#define handle_error( status, what, line ) \
do { \
   if ( status ) \
   { \
      std::cout << __FILE__ << ':' << line << ':' << what << " failed with rc = " << status << ':' << nc_strerror( status ) << '\n' ; \
      abort() ; \
   } \
} while ( 0 ) 

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: readwavenc\n" 
                "\t[--filename=f|-f f]\n"
                "\t[--verbose|-v]\n"
                "\t[--times|-t]\n"
                "\t[--help]" << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   int c{0} ;
   bool verbose{false} ;
   bool showtimes{false} ;
   std::string fileName{} ;

   constexpr struct option longOptions[]{
     { "help",           0, NULL, 'h' },
     { "filename",       1, NULL, 'f' },
     { "verbose",        0, NULL, 'v' },
     { "times",          0, NULL, 't' },
     { NULL,             0, NULL, 0   }
   } ;

   while ( -1 != ( c = getopt_long( argc, argv, "hf:vt", longOptions, NULL ) ) )
   { 
      switch ( c )
      {
         case 'f' :
         {
            fileName = std::string(optarg) ;

            break ;
         }
         case 'v' :
         {
            verbose = true ;

            break ;
         }
         case 't' :
         {
            showtimes = true ;

            break ;
         }
         case 'h' :
         default:
         {
            showHelpAndExit() ;
         }
      } 
   } 

   int status, ncid, XdimId, TdimId, idVarX, idVarRho, idVarAtTimes ;
   size_t N, tLen ;

#if 0
   // We are reading a file with the following structure:
dimensions:
        X = 5200 ;
        T = UNLIMITED ; // (30001 currently)
variables:
        float RHO(T, X) ;
        float X(X) ;
        float ATTIMES(T) ;

// global attributes:
//                 :params = "#params    Revision https://github.com/peeterjoot/physicsplay commit 76a89aa6bf159d8807f22cb2d6802b3bcde2a7cd Apr/11/2016\n#c         1\n#tau       20\n#x1        -26\n#x2        26\n#runtime   150\n#dx        0.01\n#outtime   0.04\n#ngrid     5200\n#dt        0.005\n#nsteps    30000\n#nper      8\n#graphics  -1\n#asciiIO   0\n#netcdfIO  1\n#pgrid 5200\n#npnts 5202\n" ;
#endif

   status = nc_open( fileName.c_str(), NC_NOWRITE, &ncid ) ;
   handle_error( status, "nc_create", __LINE__ ) ;

   status = nc_inq_dimid( ncid, "X", &XdimId ) ;
   handle_error( status, "nc_inq_dimid", __LINE__ ) ;

   status = nc_inq_dimlen( ncid, XdimId, &N ) ;
   handle_error( status, "nc_inq_dimlen", __LINE__ ) ;

   if ( verbose )
   {
      std::cout << "X dim: " << N << '\n' ;
   }

   status = nc_inq_dimid( ncid, "T", &TdimId ) ;
   handle_error( status, "nc_inq_dimid", __LINE__ ) ;

   status = nc_inq_dimlen( ncid, TdimId, &tLen ) ;
   handle_error( status, "nc_inq_dimlen", __LINE__ ) ;

   if ( verbose )
   {
      std::cout << "T dim: " << tLen << '\n' ;
   }

   status = nc_inq_varid( ncid, "RHO", &idVarRho ) ;
   handle_error( status, "nc_inq_varid", __LINE__ ) ;

   status = nc_inq_varid( ncid, "X", &idVarX ) ;
   handle_error( status, "nc_inq_varid", __LINE__ ) ;

   if ( verbose )
   {
      size_t paramsStringLen ;
      status = nc_inq_attlen( ncid,
                              NC_GLOBAL,
                              "params",
                              &paramsStringLen ) ;

      char params[ paramsStringLen + 1 ] ;
      status = nc_get_att_text( ncid,
                                NC_GLOBAL,
                                "params",
                                params ) ;
      handle_error( status, "nc_get_att_text", __LINE__ ) ;
      params[paramsStringLen] = 0 ;
      std::cout << params ;
   }

   std::vector<float> vecRho( N ) ;
   std::vector<float> vecX( N ) ;

   // Read in the grid-mesh values:
   status = nc_get_var_float( ncid,
                              idVarX,
                              &vecX[0] );
   handle_error( status, "nc_get_var_float", __LINE__ ) ;

   // Read in the three timeslices of data:
   for ( size_t s{0} ; s < tLen ; s++ )
   {
      size_t startA[]{s, 0} ;
      size_t countA[]{1, N} ;
      status = nc_get_vara_float( ncid,
                                  idVarRho,
                                  startA,
                                  countA,
                                  &vecRho[0] );
      handle_error( status, "nc_get_vara_float", __LINE__ ) ;

      for ( size_t i{0} ; i < N ; i++ )
      {
         std::cout << s << ' ' << i+1 << ' ' << vecX[i] << ' ' << vecRho[i] << '\n' ;
      }
   }

   if ( showtimes )
   {
      status = nc_inq_varid( ncid, "ATTIMES", &idVarAtTimes ) ;
      handle_error( status, "nc_inq_varid", __LINE__ ) ;

      std::vector<float> vecT( tLen ) ;
      status = nc_get_var_float( ncid,
                                 idVarAtTimes,
                                 &vecT[0] );
      handle_error( status, "nc_get_var_float", __LINE__ ) ;

      // display the (s*dt) times at which the output was saved
      for ( size_t i{0} ; i < vecT.size() ; i++ )
      {
         std::cout << "# " << i << ' ' << vecT[i] << '\n' ;
      }
   }

   status = nc_close( ncid ) ;
   handle_error( status, "nc_close", __LINE__ ) ;

   return (int)RETURNCODES::SUCCESS ;
}
