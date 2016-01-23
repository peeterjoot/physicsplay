#include "ants_on_table.h"
#include <iostream>

#define TABLE_GRID_SIZE 356
#define NUMBER_OF_TIME_INTERVALS 40
#define TOTAL_NUMBER_OF_ANTS 1010

int main()
{
   ants_on_table ants( TABLE_GRID_SIZE ) ;

   ants_on_table::iterator i = ants.initialize( TOTAL_NUMBER_OF_ANTS ) ;
   ants_on_table::iterator end( NUMBER_OF_TIME_INTERVALS ) ;

   for ( ; i != end ; ++i )
   {
      std::cout << i() << " " << *i << std::endl ;
   }

   return 0 ;
}
