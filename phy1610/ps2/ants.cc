#include "ants_on_table.h"

#define TABLE_GRID_SIZE 356
#define NUMBER_OF_TIME_INTERVALS 40
#define TOTAL_NUMBER_OF_ANTS 1010

int main()
{
   ants_on_table ants( TABLE_GRID_SIZE ) ;

   ants.initialize( TOTAL_NUMBER_OF_ANTS ) ;
   ants.simulation( NUMBER_OF_TIME_INTERVALS ) ;

	return 0 ;
}
