#include "iohandler.h"
#include "rangePartition.h"
#include "mpitask.h"
#include <string>

using itype = rangePartition::index_type ;

void initData( const itype m, const itype n, const itype j, float * const x, float * const rho, float * const rhoinit )
{
   for ( size_t i{m} ; i <= n ; i++ )
   {
      x[i] = (j + i)/10.0 ;
      rho[i] = j + i ;
      rhoinit[i] = rho[i] ;
   }
}

void evolveData( const itype m, const itype n, float * const rho )
{
   for ( size_t i{m} ; i <= n ; i++ )
   {
      rho[i] *= 1.5 ;
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

   using cfg = iohandler::cfg ;
   for ( auto c : { cfg::graphics, cfg::ascii, cfg::netcdf, cfg::noop } )
   {
      constexpr auto RANK_OF_MPI_TASK_TO_SHOW_GRAPHICS_ON{0} ;

      if ( (c == cfg::graphics) && (mpi.m_rank != RANK_OF_MPI_TASK_TO_SHOW_GRAPHICS_ON) )
      {
         c = cfg::noop ;
      }

      initData( r.first -1, r.second + 1, p.m_myFirstGlobalElementIndex - 1, x, rho, rhoinit ) ;

      iohandler io( c, "iotest", N, mpi.m_rank ) ;

      io.writeMeta( p.m_myFirstGlobalElementIndex -1, n, &x[1], &rhoinit[1] ) ;

      for ( int s{1} ; s < 5 ; s++ )
      {
         evolveData( r.first - 1, r.second + 1, rho ) ;

         io.writeData( s, p.m_myFirstGlobalElementIndex -1, n, &x[1], &rho[1] ) ;
      }
   }

   return 0 ;
}
