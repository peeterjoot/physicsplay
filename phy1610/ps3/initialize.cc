/**
   \file initialize.cc
 */
#include "ants_on_table.h"
#include <cassert>

void ants_on_table::initialize( const int total_ants )
{
   assert( total_ants ) ;

   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
      {
         float v = 
            M_PI * (sin ((2 * M_PI * (i + j)) / (m_table_grid_size *10)) + 1) ;

         m_velocity_of_ants.assign( i, j, v ) ;
      }
   }

   int n = 0 ;
   float z = 0 ;

   m_number_of_ants.fill( 0.0 ) ;

   while (n < total_ants)
   {
      for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
      {
         for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
         {
            z += sin( 0.3 * (i + j) ) ;
            if (z > 1 and n != total_ants)
            {
               m_number_of_ants.add( i, j, 1 ) ;
               n += 1 ;
            }
         }
      }
   }
}
