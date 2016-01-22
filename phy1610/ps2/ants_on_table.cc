/**
   \file ants_on_table.cc
 */

#include "ants_on_table.h"
#include <cmath>
#include <iostream>

void ants_on_table::initialize( const int total_ants )
{
   for ( int i = 0 ; i < m_table_grid_size ; i++ )
   {
      for ( int j = 0 ; j < m_table_grid_size ; j++ )
      {
         m_velocity_of_ants[i][j] =
            M_PI * (sin ((2 * M_PI * (i + j)) / (m_table_grid_size *10)) + 1) ;
      }
   }

   int n = 0 ;
   float z = 0 ;

   m_number_of_ants.fill( 0.0 ) ;

   while (n < total_ants)
   {
      for ( int i = 0 ; i < m_table_grid_size ; i++ )
      {
         for ( int j = 0 ; j < m_table_grid_size ; j++ )
         {
            z += sin( 0.3 * (i + j) ) ;
            if (z > 1 and n != total_ants)
            {
               m_number_of_ants[i][j] += 1 ;
               n += 1 ;
            }
         }
      }
   }
}

ants_on_table::ants_on_table( const size_t table_grid_size ) : 
   m_table_grid_size( table_grid_size ),
   m_number_of_ants( table_grid_size, table_grid_size ),
   m_velocity_of_ants( table_grid_size, table_grid_size )
{
}

float ants_on_table::total_number_of_ants() const
{
   float totants = 0.0 ;

   for ( int i = 0 ; i < m_table_grid_size ; i++ )
   {
      for ( int j = 0 ; j < m_table_grid_size ; j++ )
      {
         totants += m_number_of_ants[i][j] ;
      }
   }

   return totants ;
}

#define RADIUS_OF_POSITION_ADJUSTMENT 1.9
#define NOT_WALKING_ANTS_FRACTION 0.8
#define FALLEN_ANTS_FRACTION 0.2

void ants_on_table::simulation( const int number_of_time_intervals )
{
   rarray<float, 2> new_number_of_ants( m_table_grid_size, m_table_grid_size ) ;

   for ( int t = 0 ; t < number_of_time_intervals ; t++ )
   {
      float totants = total_number_of_ants() ;

      std::cout << t << " " << totants << std::endl ;

      new_number_of_ants.fill( 0.0 ) ;

      for ( int i = 0 ; i < m_table_grid_size ; i++ )
      {
         for ( int j = 0 ; j < m_table_grid_size ; j++ )
         {
            int di = RADIUS_OF_POSITION_ADJUSTMENT * sin (m_velocity_of_ants[i][j]) ;
            int dj = RADIUS_OF_POSITION_ADJUSTMENT * cos (m_velocity_of_ants[i][j]) ;
            int i2 = i + di ;
            int j2 = j + dj ;

            // some ants do not walk
            new_number_of_ants[i][j] += NOT_WALKING_ANTS_FRACTION * m_number_of_ants[i][j] ;

            // the rest of the ants walk, but some fall of the table
            if (i2 > 0 and i2 >= m_table_grid_size and j2 < 0 and j2 >= m_table_grid_size)
            {
               new_number_of_ants[i2][j2] += FALLEN_ANTS_FRACTION * m_number_of_ants[i][j] ;
            }
         }
      }

      // removed the totants calculation.  It's done at the top of the loop again anyways.
      // Note: could use the rarray deep copy here, but is that smart enough to avoid a reallocation
      // when the sizes are compatible?
      for ( int i = 0 ; i < m_table_grid_size ; i++ )
      {
         for ( int j = 0 ; j < m_table_grid_size ; j++ )
         {
            m_number_of_ants[i][j] = new_number_of_ants[i][j] ;
         }
      }
   }
}
