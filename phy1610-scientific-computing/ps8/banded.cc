/** \file banded.cc
 */

#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include "banded.h"
#include "myexceptions.h"

int getSquareMatrixDimensions( const darray2 & m )
{
   auto rows = m.extent( 0 ) ;
   auto columns = m.extent( 1 ) ;

   if ( rows != columns )
   {
      BOOST_THROW_EXCEPTION(
            array_not_square_error()
               << arows_info( rows )
               << acolumns_info( columns ) ) ;
   }

   return rows ;
}

void initializeBandedMatrix( darray2 &     m,
                             const double   subdiagonal,
                             const double   diagonal,
                             const double   superdiagonal,
                             const BANDING_TYPE how )
{
   auto rows = getSquareMatrixDimensions( m ) ;

   m.fill( 0.0 ) ;

   for ( decltype(rows) i { 0 } ; i < rows ; i++ )
   {
      auto iplusone{ (i+1)%rows } ;
      m[i][i]        = diagonal ;
      m[iplusone][i] = subdiagonal ;
      m[i][iplusone] = superdiagonal ;
   }

   // Now that we've entered the matrix, we have only two options:
   // ... Do we take the red pill or the blue pill?
   if ( how == BANDING_TYPE::TRIDIAGONAL )
   {
      m[0][rows-1] = 0.0 ;
      m[rows-1][0] = 0.0 ;
   }
}
