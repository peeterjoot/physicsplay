/**
   \file dotprod.cc

   Implementation of cblas based dot product and correlation methods.
 */
#include "dotprod.h"
#include "myexceptions.h"

double dotprod( const darray & f, const darray & g )
{
   // cblas_ddot can skip elements if desired (not desired here).
   constexpr auto stride{ 1 } ;

   if ( f.size() != g.size() )
   {
      BOOST_THROW_EXCEPTION(
            array_size_error()
               << asize_info( f.size() )
               << asize_info( g.size() )
            ) ;
   }

   // double cblas_ddot(const int N, const double *X, const int incX, const double *Y, const int incY);
   auto dot{ cblas_ddot( f.size(), &f[0], stride, &g[0], stride ) } ;

   return dot ;
}

correlator::correlator( const darray & pred )
   : m_pred( pred ),
     m_dotff( dotprod( m_pred, m_pred ) )
{
}

double correlator::operator()( const darray & det ) const
{
   auto dotfg { dotprod( m_pred, det ) } ;
   auto dotgg { dotprod( det, det ) } ;

   return dotfg / std::sqrt( m_dotff * dotgg ) ;
}
