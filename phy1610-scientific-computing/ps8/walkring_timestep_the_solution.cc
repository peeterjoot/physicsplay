// 
// walkring_timestep.cc
//
// Time stepping module for 1d random walk on a ring
//

#include "walkring_timestep.h"
#include <random>

// perform a single time step for the random walkers
// Arguments:
//   pos: positions of the walkers
//   N:   number of grid points
//   p:   probablity to jump left. Same probability to go right.
void perform_time_step(rarray<int,1>& pos, int N, double p)
{
    static const int seed = 13;
    static std::mt19937 engine(seed);
    static std::uniform_real_distribution<> uniform;
    int Z = pos.size();
    // move all walkers
    for (int i = 0; i < Z; i++) {
        double r = uniform(engine); // draws a random number
        if (r < p) {
            // move to the right, respecting periodic boundaries
            pos[i]++;
            if (pos[i] == N)
                pos[i] = 0;
        } else if (r < 2*p) {
            // move to the left, respecting periodic boundaries
            if (pos[i] == 0)
                pos[i] = N-1;
            else
                pos[i]--;
        } else {
            // position remains unchanged
        }
    }
}


