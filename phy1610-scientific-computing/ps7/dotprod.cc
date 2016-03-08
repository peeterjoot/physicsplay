/**
   \file dotprod.cc
 */
#include "dotprod.h"
#include "myexceptions.h"

double dotprod( const rarray<double, 1> & f, const rarray<double, 1> & g )
{
   // cblas_ddot can skip elements if desired (not desired here).
   constexpr auto stride { 1 } ;

   if ( f.size() != g.size() )
   {
      BOOST_THROW_EXCEPTION(
            array_size_error()
               << asize_info( f.size() )
               << asize_info( g.size() )
            ) ;
   }

   // double cblas_ddot(const int N, const double *X, const int incX, const double *Y, const int incY);
   auto dot { cblas_ddot( f.size(), &f[0], stride, &g[0], stride ) } ;

   return dot ;
}
