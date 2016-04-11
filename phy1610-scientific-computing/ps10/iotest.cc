#include "iohandler.h"
#include "rangePartition.h"
#include "mpitask.h"
#include <string>
#include <cmath>

using itype = rangePartition::index_type ;

void initData( const itype m, const itype n, const itype j, float * const x, float * const rho, float * const rhoinit )
{
   for ( size_t i{m} ; i <= n ; i++ )
   {
      x[i] = (j + i)/10.0 ;
      rho[i] = (std::sin( j + i ) + 1)/8 ;
      rhoinit[i] = rho[i] ;
   }
}

void evolveData( const itype m, const itype n, float * const rho )
{
   for ( size_t i{m} ; i <= n ; i++ )
   {
      rho[i] *= 0.9 ;
   }
}

int main( int argc, char ** argv )
{
   mpitask mpi( &argc, &argv ) ;

   constexpr size_t N{40} ;
   rangePartition p( N, mpi.m_size, mpi.m_rank ) ;
   auto n{ p.localPartitionSize() } ;
   
   float x[ n + 2 ] ;
   float rho[ n + 2 ] ;
   float rhoinit[ n + 2 ] ;

   rangePartition::subrange r{ p.subsetOfGlobalRangeInThisPartition( 1, N ) } ;

   std::string fileBaseName{ "iotest" } ;

   using iocfg = iohandler::cfg ;
   for ( auto c : { iocfg::graphics, iocfg::ascii, iocfg::netcdf, iocfg::noop } )
   {
      constexpr auto RANK_OF_MPI_TASK_TO_SHOW_GRAPHICS_ON{0} ;

      if ( (c == iocfg::graphics) && (mpi.m_rank != RANK_OF_MPI_TASK_TO_SHOW_GRAPHICS_ON) )
      {
         c = iocfg::noop ;
      }

      initData( r.first -1,
                r.second + 1,
                p.m_myFirstGlobalElementIndex - 1,
                x,
                rho,
                rhoinit ) ;

      iohandler io( c, "iotest", N, mpi.m_rank ) ;
      io.setSleepTime( 1 ) ;

      io.writeMeta( p.m_myFirstGlobalElementIndex -1,
                    n,
                    &x[1],
                    &rhoinit[1] ) ;

      for ( int s{1} ; s < 5 ; s++ )
      {
         evolveData( r.first - 1,
                     r.second + 1,
                     rho ) ;

         io.writeData( s,
                       p.m_myFirstGlobalElementIndex -1,
                       n,
                       &x[1],
                       &rho[1] ) ;
      }
   }

   return 0 ;
}
