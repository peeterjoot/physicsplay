// 
// walkring_timestep.cc
//
// Time stepping module for 1d random walk on a ring
//

#include "walkring_timestep.h"
#include <cassert>

walkring_evolution::walkring_evolution()
   : m_generator( 0, 1 )
{
}

// perform a single time step for the random walkers
// pos: the positions of Z walkers. Z=pos.size()
// N: the number of grid points. All positions should remain between 0
//    and N-1, with periodic boundary conditions
// p: the probability to jump to the left. Also the probability to jump right.
//    the probability to stay on the same spot is thus 1-2p.
void walkring_evolution::perform_time_step(rarray<int,1>& pos, int N, double p)
{
   auto Z = pos.size() ; 
   assert( p >= 0.0 ) ;
   assert( N > 0 ) ;
   assert( Z > 0 ) ;
   assert( 1 - 2 * p >= 0.0 ) ;

   for ( decltype(Z) i{0} ; i < Z ; i++ )
   {
      auto randomvar = m_generator.sample() ;

      if ( randomvar < p )
      {
         // move to the left (counterclockwise):
         pos[i] = (pos[i] - 1 + N) % N ;
      }
      else if ( randomvar < (2 * p) )
      {
         // move to the right (clockwise):
         pos[i] = (pos[i] + 1) % N ;
      }
      // else: no-op
   }
}
