/** \file banded.cc
 */

#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include "banded.h"
#include "myexceptions.h"

void initializeBandedMatrix( darray2 &     m,
                             const double   subdiagonal,
                             const double   diagonal,
                             const double   superdiagonal,
                             const BANDING_TYPE how )
{
   auto rows = m.extent( 0 ) ; 
   auto columns = m.extent( 1 ) ; 

   m.fill( 0.0 ) ;

   if ( rows != columns )
   {
      BOOST_THROW_EXCEPTION(
            array_not_square_error()
               << arows_info( rows )
               << acolumns_info( columns ) ) ;
   }

   for ( decltype(rows) i = 0 ; i < rows ; i++ )
   {
      m[i][i] = diagonal ;
      m[(i+1)%rows][i] = subdiagonal ;
      m[i][(i+1)%rows] = superdiagonal ;
   }

   if ( how == BANDING_TYPE::TRIDIAGONAL )
   {
      m[0][rows-1] = 0.0 ;
      m[rows-1][0] = 0.0 ;
   }
}
