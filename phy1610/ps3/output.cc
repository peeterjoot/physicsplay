/**
   \file output.cc
 */
#include "ants_on_table.h"
#include "optticktock.h"
#include <iostream>

void output( ants_on_table & a, const int num_time_intervals )
{
   TickTockOrNoOp timer ;
   float ioTime { 0.0 } ;

   for ( int i = 0 ; i < num_time_intervals ; i++ )
   {
      float totants = a.total_number_of_ants() ;

      timer.tick() ;

      std::cout << totants << " " << i << std::endl ;

      ioTime += timer.silent_tock() ;

      a.timestep() ;
   }

   #if defined USE_TICK_TOCK
      std::cout << "io time: \t"      << ioTime << std::endl ;
   #endif
}
