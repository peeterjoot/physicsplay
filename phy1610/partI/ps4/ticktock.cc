// ticktock.cc
//
// Supplies implementation of the class TickTock to measure wall-time
//
// Ramses van Zon, January 2015
//

#include "ticktock.h"
#include <iostream>
#include <iomanip>
#include <sys/time.h>

static void print(const char* prefix, const double dt)
{
    // helper function to print elapsed time	
    if (prefix!=0)
        std::cout << prefix << "\t" << std::setprecision(4) << dt << " sec\n";
    else
        std::cout << "    \t" << std::setprecision(4) << dt << " sec\n";
}

static double elapsed_time()
{
   struct timeval t;
   gettimeofday(&t, 0);
   return t.tv_sec + 0.000001 * t.tv_usec;
}

void TickTock::tick()
{
    // start measuring time
    tick_ = elapsed_time();
}

void TickTock::tock(const char* prefix) const
{
    // done measuring time; print elapsed seconds
    print(prefix, silent_tock()); 
}

double TickTock::silent_tock() const
{
    // done measuring time; give elapsed seconds
    double tock = elapsed_time();
    double dt = tock-tick_;
    return dt;
}

