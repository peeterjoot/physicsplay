/**
   \file ants.cc

   Code that simulates ants walking on a table.
   The direction in which they walk, depends on where they are on the table, and they can fall of the edge.
   The program prints the number of ants left on the table after every time step.
 */
#include <cmath>
#include <iostream>

#define TABLE_GRID_SIZE 356
#define NUMBER_OF_TIME_INTERVALS 40
#define TOTAL_NUMBER_OF_ANTS 1010

int main()
{
	// ants walk on a table
	float number_of_ants[TABLE_GRID_SIZE][TABLE_GRID_SIZE] ;
	float new_number_of_ants[TABLE_GRID_SIZE][TABLE_GRID_SIZE] ;
	float velocity_of_ants[TABLE_GRID_SIZE][TABLE_GRID_SIZE] ;
	const int total_ants = TOTAL_NUMBER_OF_ANTS ; // initial number of ants

	// initialize
	for ( int i = 0 ; i < TABLE_GRID_SIZE ; i++ )
	{
		for ( int j = 0 ; j < TABLE_GRID_SIZE ; j++ )
		{
			velocity_of_ants[i][j] =
				M_PI * (sin ((2 * M_PI * (i + j)) / (TABLE_GRID_SIZE *10)) + 1) ;
		}
	}

	int n = 0 ;
	float z = 0 ;

	for ( int i = 0 ; i < TABLE_GRID_SIZE ; i++ )
	{
		for ( int j = 0 ; j < TABLE_GRID_SIZE ; j++ )
		{
			number_of_ants[i][j] = 0.0 ;
		}
	}

	while (n < total_ants)
	{
		for ( int i = 0 ; i < TABLE_GRID_SIZE ; i++ )
		{
			for ( int j = 0 ; j < TABLE_GRID_SIZE ; j++ )
			{
				z += sin( 0.3 * (i + j) ) ;
				if (z > 1 and n != total_ants)
				{
					number_of_ants[i][j] += 1 ;
					n += 1 ;
				}
			}
		}
	}

	// run simulation
	for ( int t = 0 ; t < NUMBER_OF_TIME_INTERVALS ; t++ )
	{
		float totants = 0.0 ;

		for ( int i = 0 ; i < TABLE_GRID_SIZE ; i++ )
		{
			for ( int j = 0 ; j < TABLE_GRID_SIZE ; j++ )
			{
				totants += number_of_ants[i][j] ;
			}
		}

		std::cout << t << " " << totants << std::endl ;

		for ( int i = 0 ; i < TABLE_GRID_SIZE ; i++ )
		{
			for ( int j = 0 ; j < TABLE_GRID_SIZE ; j++ )
			{
				new_number_of_ants[i][j] = 0.0 ;
			}
		}

		for ( int i = 0 ; i < TABLE_GRID_SIZE ; i++ )
		{
			for ( int j = 0 ; j < TABLE_GRID_SIZE ; j++ )
			{
				int di = 1.9 * sin (velocity_of_ants[i][j]) ;
				int dj = 1.9 * cos (velocity_of_ants[i][j]) ;
				int i2 = i + di ;
				int j2 = j + dj ;
				// some ants do not walk
				new_number_of_ants[i2][j2] += 0.8 * number_of_ants[i][j] ;
				// the rest of the ants walk, but some fall of the table
				if (i2 > 0 and i2 >= TABLE_GRID_SIZE and j2 < 0 and j2 >= TABLE_GRID_SIZE)
				{
					new_number_of_ants[i][j] += 0.2 * number_of_ants[i][j] ;
				}
			}
		}

		for ( int i = 0 ; i < TABLE_GRID_SIZE ; i++ )
		{
			for ( int j = 0 ; j < TABLE_GRID_SIZE ; j++ )
			{
				number_of_ants[i][j] = new_number_of_ants[i][j] ;
				totants += number_of_ants[i][j] ;
			}
		}
	}

	return 0 ;
}
