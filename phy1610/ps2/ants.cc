#include "ants_on_table.h"
#include <iostream>

int main()
{
   const size_t TABLE_GRID_SIZE        { 356 } ;
   const int NUMBER_OF_TIME_INTERVALS  { 40 } ;
   const int TOTAL_NUMBER_OF_ANTS      { 1010 } ;

   ants_on_table ants( TABLE_GRID_SIZE ) ;

   ants_on_table::iterator i = ants.initialize( TOTAL_NUMBER_OF_ANTS ) ;
   ants_on_table::iterator end( NUMBER_OF_TIME_INTERVALS ) ;

   for ( ; i != end ; ++i )
   {
      std::cout << i() << " " << *i << std::endl ;
   }

   return 0 ;
}
