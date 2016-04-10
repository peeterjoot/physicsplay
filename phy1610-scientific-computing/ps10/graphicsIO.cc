/** \file graphicsIO.cc */
#include <cpgplot.h>
#include "graphicsIO.h"

graphicsIO::graphicsIO( const std::string & fileBaseName, const size_t N )
   : m_rhoInitStart( nullptr )
{
   cpgbeg( 0, "/xwindow", 1, 1 ) ;
   cpgask( 0 ) ;
   m_red = 2 ; cpgscr( m_red, 1., 0., 0. ) ;
   m_grey = 3 ; cpgscr( m_grey, .2, .2, .2 ) ;
   m_white = 4 ; cpgscr( m_white, 1.0, 1.0, 1.0 ) ;
}

void graphicsIO::plot( const size_t          localN,
                       const float * const   x,
                       const float * const   rhoInit,
                       const float * const   rho )
{
   double localX1 = x[ 1 ] ;
   double localX2 = x[ localN ] ;

   cpgsls( 1 ) ;
   cpgslw( 6 ) ;
   cpgsci( m_white ) ;
   cpgslw( 2 ) ;
   cpgenv( localX1, localX2, 0., 0.25, 0, 0 ) ;
   cpglab( "x", "rho", "Wave test" ) ;
   cpgsls( 1 ) ;
   cpgslw( 6 ) ;
   cpgsci( m_white ) ;
   cpgline( localN + 2, x, rhoInit ) ;
   cpgsls( 2 ) ;
   cpgslw( 12 ) ;
   cpgsci( m_red ) ;
   cpgline( localN + 2, x, rho ) ;
}

void graphicsIO::writeData( const size_t          timeStepCount,
                            const size_t          globalOffset,
                            const size_t          localN,
                            const float * const   localXstart,
                            const float * const   localRhoStart )
{
   cpgbbuf( ) ;
   cpgeras( ) ;

   plot( localN,
         &localXstart[-1],
         m_rhoInitStart,
         &localRhoStart[-1] ) ;

   cpgebuf( ) ;
}

void graphicsIO::writeMeta( const size_t          globalOffset,
                            const size_t          localN,
                            const float * const   localXstart,
                            const float * const   localRhoStart )
{
   plot( localN,
         &localXstart[-1],
         &localRhoStart[-1],
         &localRhoStart[-1] ) ;

   m_rhoInitStart = localRhoStart ;
}

graphicsIO::~graphicsIO( )
{
   // member destructors will close the file.
}

