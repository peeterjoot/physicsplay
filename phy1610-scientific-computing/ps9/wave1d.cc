//
// wave1d.cc - Simulates a one-dimensional damped wave equation modified
// to use pgplot for runtime display of solution with 1 second between frames.  
// 
// SciNet - March 2015

#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include <rarray>
#include <cpgplot.h>
#include <time.h>
#include "ticktock.h"
#include "inifile.h"
#include <omp.h>
#include "arrayIOwriter.h"
#include "iometadata.h"

using farray = rarray<float, 1> ;

int main( int argc, char* argv[] )
{
    // Open inifile and parse (using Inifile class from inifile.h)
    Inifile parameter( argc==1 ? "default.txt" : argv[1] ) ;

    // Physical parameters
    const double  c             = parameter.get<double>( "c", 1.0 ) ;             // wave speed
    const double  tau           = parameter.get<double>( "tau", 20.0 ) ;          // damping time
    const double  x1            = parameter.get<double>( "x1", -26.0 ) ;          // left most x value
    const double  x2            = parameter.get<double>( "x2", +26.0 ) ;          // right most x value

    // Simulation parameters
    const double  runtime       = parameter.get<double>( "runtime", 50.0 ) ;      // how long should the simulation try to compute?
    const double  dx            = parameter.get<double>( "dx", 0.01 ) ;           // spatial grid size  //0.02

    // Output parameters
    const double  outtime       =  parameter.get<double>( "outtime", 1.0 ) ;      // how often should a snapshot of the wave be written out? 

    const bool    graphics      = parameter.get<bool>( "graphics", true ) ;      // output to graphics (with 1 sec delay)  or to a file?

    const std::string  outdir   = parameter.get<std::string>( "outdir", "./" ) ; // use multiple files, one for each thread per timestep
    const std::string  filebase = parameter.get<std::string>( "filename", "dataFilename" ) ; // use multiple files, one for each thread per timestep
    const bool    parallelIO    = parameter.get<bool>( "parallelIO", false ) ; // use multiple files, one for each thread per timestep
    const bool    threadedIO    = parameter.get<bool>( "threadedIO", false ) ; // use multiple threads for IO
    float timeVal{0.0} ;

    arrayIOwriter::IO_method ioHow = arrayIOwriter::IO_method::serial ;

    if ( threadedIO )
    {
        ioHow = arrayIOwriter::IO_method::threaded ;
    }
    else if ( parallelIO )
    {
        ioHow = arrayIOwriter::IO_method::multifile ;
    }

    // Output file name
    const std::string dataFileBaseName = outdir + filebase ;

    // Derived parameters
    const int     ngrid       = (x2-x1)/dx ; // number of x points
    const int     numPoints   = ngrid + 2 ;  // number of x points including boundary points
    const double  dt          = 0.5 * dx/c ; // time step size
    const int     nsteps      = runtime/dt ; // number of steps of that size to reach runtime
    const int     nper        = outtime/dt ; // how many step s between snapshots

    // write out the initial metadata
    IOmetaData meta( nper, numPoints ) ;
    arrayIOwriter ioManager( dataFileBaseName, ioHow ) ;
    ioManager.writeMetaData( &meta, sizeof(meta) ) ;

    // Report all the values.
    std::cout << "#c          " << c       << std::endl ;
    std::cout << "#tau        " << tau     << std::endl ;
    std::cout << "#x1         " << x1      << std::endl ;
    std::cout << "#x2         " << x2      << std::endl ;
    std::cout << "#runtime    " << runtime << std::endl ;
    std::cout << "#dx         " << dx      << std::endl ;
    std::cout << "#outtime    " << outtime << std::endl ;
    std::cout << "#ngrid      " << ngrid   << std::endl ;
    std::cout << "#dt         " << dt      << std::endl ;
    std::cout << "#nsteps     " << nsteps  << std::endl ;
    std::cout << "#nper       " << nper    << std::endl ;
    std::cout << "#graphics   " << int(graphics) << std::endl ;
    std::cout << "#parallelIO " << int(parallelIO) << std::endl ;
    std::cout << "#threadedIO " << int(threadedIO) << std::endl ;

    // Define and allocate arrays.
    farray rho_prev( numPoints ) ; // time step t-1
    farray rho( numPoints ) ;      // time step t
    farray rho_next( numPoints ) ; // time step t+1
    farray rho_init( numPoints ) ; // initial values
    farray x( numPoints ) ;        // x values
 
    // Initialize.
    for ( int i = 0 ; i < numPoints ; i++ )
    {
        x[i] = x1 + ((i-1)*(x2-x1))/ngrid ;
        rho[i] = 0.0 ;
        rho_prev[i] = 0.0 ;
        rho_next[i] = 0.0 ;
    }

    // Excite.
    for ( int i = numPoints/4 + 1 ; i < 3*numPoints/4 ; i++ )
    {
        rho[i] = 0.25 - fabs( float(i-numPoints/2 )/float(numPoints)) ;
        rho_prev[i] = rho[i] ;
        rho_init[i] = rho[i] ;
    }
       
    int red, grey, white ;

    if ( graphics ) {
        cpgbeg( 0, "/xwindow", 1, 1 ) ;
        cpgask( 0 ) ;
        red = 2 ; cpgscr( red,1.,0.,0. ) ;
        grey = 3 ; cpgscr( grey,.2,.2,.2 ) ;
        white = 4 ; cpgscr( white,1.0,1.0,1.0 ) ;
        cpgsls( 1 ) ; cpgslw( 6 ) ; cpgsci( white ) ;
        cpgslw( 2 ) ;
        cpgenv( x1, x2, 0., 0.25, 0, 0 ) ;
        cpglab( "x", "rho", "Wave Test" ) ;
        cpgsls( 1 ) ; cpgslw( 6 ) ; cpgsci( white ) ;
        cpgline( numPoints, x.data( ), rho.data() ) ;
        cpgsls( 2 ) ; cpgslw( 12 ) ; cpgsci( red ) ;
        cpgline( numPoints, x.data( ), &rho_init[0] ) ;
    } else {     
        ioManager.writeMetaData( &x[0], sizeof(x[0])*x.size() ) ;
        ioManager.writeMetaData( &timeVal, sizeof(timeVal) ) ;
        ioManager.writeData( &rho[0], sizeof(rho[0]), rho.size() ) ;
    }

    // measure time
    TickTock tt ;
    tt.tick() ;

    // Take timesteps
    for ( int s = 0 ; s < nsteps ; s++ )
    {
        timeVal = s * dt ;

        // Set zero dirichlet boundary conditions
        rho[0] = 0.0 ;
        rho[ngrid+1] = 0.0 ;

        // Evolve
        //#pragma omp parallel for default(none) shared(c,dx,rho,rho_next,rho_prev,dt,ngrid,tau)
        #pragma omp parallel for default(none) shared( rho, rho_next, rho_prev )
        for (int i = 1; i <= ngrid; i++)
        {
            const float laplacian = pow( c/dx, 2 ) * ( rho[i+1] + rho[i-1] - 2*rho[i] ) ;
            const float friction = ( rho[i] - rho_prev[i] )/tau ;

            rho_next[i] = 2 * rho[i] - rho_prev[i] + dt * ( laplacian * dt - friction ) ;
        }

        // Rotate array pointers so t+1 becomes the new t etc.
        farray temp ;
        temp     = rho_prev ;
        rho_prev = rho ;
        rho      = rho_next ;
        rho_next = temp ;
	
        //Output every nper
        if ( (s+1) % nper == 0 )
        {
            if ( graphics )
            {
                cpgbbuf( ) ;
                cpgeras( ) ;
                cpgsls( 1 ) ; cpgslw( 6 ) ; cpgsci( white ) ;
                cpgslw( 2 ) ;
                cpgenv( x1, x2, 0., 0.25, 0, 0 ) ;
                cpglab( "x", "rho", "Wave test" ) ; // t=s*dt
                cpgsls( 2 ) ; cpgslw( 12 ) ; cpgsci( red ) ;
                cpgline( numPoints, x.data( ), rho.data( ) ) ;
                cpgsls( 1 ) ; cpgslw( 6 ) ; cpgsci( white ) ;
                cpgline( numPoints, x.data( ), rho_init.data( ) ) ;
                cpgebuf( ) ;
                sleep( 1 ) ; // artificial delay! 
            }
            else
            {
                ioManager.writeMetaData( &timeVal, sizeof(timeVal) ) ;
                ioManager.writeData( &rho[0], sizeof(rho[0]), rho.size() ) ;
            } 
        }
    }
    
    // Output measured runtime.
    std::cout << "Walltime = " << tt.silent_tock() << " sec."  << std::endl ;

    return 0 ;
}
// vim: noai:ts=4:sw=4
