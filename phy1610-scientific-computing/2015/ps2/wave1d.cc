/**
   \file wave1d.cc

   Simulates a one-dimensional damped wave equation

   \author Ramses van Zon
 */

#include <iostream>
#include <cmath>
//#include <memory>
#include "wave1d.h"

wave1d::wave1d( const parameters & p_ ) :
   rho_prev(),
   rho(),
   rho_next(),
   x(),
   p(p_)
{
   rho_prev.resize( p.npnts, 0.0 ) ;
   rho.resize( p.npnts, 0.0 ) ;
   rho_next.resize( p.npnts, 0.0 ) ;
   x.resize( p.npnts, 0.0 ) ;
}

void wave1d::initializeAndExcite()
{
   // Initialize
   for ( Sint i = 0 ; i < p.npnts ; i++ )
   {
      x[i] = p.x1 + ((i-1)*(p.x2-p.x1))/p.ngrid ;

      // resize does this, since the fill value was specified.
      //rho[i] = 0.0 ;
      //rho_prev[i] = 0.0 ;
      //rho_next[i] = 0.0 ;
   }

   // Excite
   for ( Sint i = p.npnts/4 + 1 ; i < 3*p.npnts/4 ; i++ )
   {
      rho[i] = 0.25 - fabs(double(i-p.npnts/2)/double(p.npnts)) ;
      rho_prev[i] = rho[i] ;
   }
}

void wave1d::display( double time )
{
   std::cout << "# t = " << time << '\n' ;
   for ( Sint32 i = 1 ; i <= p.ngrid ; i++ ) 
   {
      std::cout << x[i] << " " << rho[i] << '\n' ;
   }  
}

void wave1d::compute()
{
   // Take timesteps
   for ( Sint32 s = 0 ; s < p.nsteps ; s++ )
   {

      // Set zero dirichlet boundary conditions
      rho[0] = 0.0 ;
      rho[p.ngrid+1] = 0.0 ;

      // Evolve
      for (Sint32 i = 1 ; i <= p.ngrid ; i++)
      {
         double laplacian = pow(p.c/p.dx,2)*(rho[i+1] + rho[i-1] - 2*rho[i]) ;
         double friction = (rho[i] - rho_prev[i])/p.tau ;
         rho_next[i] = 2*rho[i] - rho_prev[i] + p.dt*(laplacian*p.dt-friction) ;
      }

      // Rotate array pointers so t+1 becomes the new t etc.
      // Note that vector::swap doesn't touch the elements themselves, just
      // the vector metadata.
      std::vector<double> temp ;
      temp    .swap( rho_prev ) ;
      rho_prev.swap( rho ) ;
      rho     .swap( rho_next ) ;
      rho_next.swap( temp ) ;

      // Output density
      if ( ((s+1) % p.nper == 0) && p.verbose )
      {
         display( s * p.dt ) ;
      }
   }

//      if ( p.verbose )
//      {
//         display( (p.nsteps -1) * p.dt ) ;
//      }
}

/**
   Read the parameters file, and run the wave equation solving kernel.
 */
int main(int argc, char* argv[])
{
   parameters p( argc, argv ) ;

   wave1d w( p ) ;

   w.initializeAndExcite() ;

   if ( p.verbose )
   {
      // Output initial signal
      w.display( 0.0 ) ;
   }
   w.compute() ;

   return 0 ;
}
