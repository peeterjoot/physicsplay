/**
   \file ants_on_table.cc
 */

#include "ants_on_table.h"
#include <cmath>
#include <iostream>

ants_on_table::iterator ants_on_table::initialize( const int total_ants )
{
   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
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
      for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
      {
         for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
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

   return iterator( this ) ;
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

   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
      {
         totants += m_number_of_ants[i][j] ;
      }
   }

   return totants ;
}

void ants_on_table::timestep( iterator & iter )
{
   static const double RADIUS_OF_POSITION_ADJUSTMENT { 1.9 } ;
   static const double NOT_WALKING_ANTS_FRACTION { 0.8 } ;
   static const double FALLEN_ANTS_FRACTION { 0.2 } ;

   iter.m_new_number_of_ants.fill( 0.0 ) ;

   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
      {
         int di = RADIUS_OF_POSITION_ADJUSTMENT * sin (m_velocity_of_ants[i][j]) ;
         int dj = RADIUS_OF_POSITION_ADJUSTMENT * cos (m_velocity_of_ants[i][j]) ;
         int i2 = (int)i + di ;
         int j2 = (int)j + dj ;

         // some ants do not walk
         iter.m_new_number_of_ants[i][j] += NOT_WALKING_ANTS_FRACTION * m_number_of_ants[i][j] ;

         // the rest of the ants walk, but some fall of the table
         if (i2 > 0 and i2 >= (int)m_table_grid_size and j2 < 0 and j2 >= (int)m_table_grid_size)
         {
            iter.m_new_number_of_ants[i2][j2] += FALLEN_ANTS_FRACTION * m_number_of_ants[i][j] ;
         }
      }
   }

   // removed the totants calculation (it was done at the top of the loop, but not used in
   // the timestep calculation itself).
   //
   // Note: could use the rarray deep copy here, but is that smart enough to avoid a reallocation
   // when the sizes are compatible?
   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
      {
         m_number_of_ants[i][j] = iter.m_new_number_of_ants[i][j] ;
      }
   }
}

ants_on_table::iterator::iterator( ants_on_table * p_ants )
   : m_ants_p( p_ants ),
     m_timevalue( 0 ),
     m_new_number_of_ants( p_ants->get_grid_size(), p_ants->get_grid_size() )
{
}

ants_on_table::iterator::iterator( const int n )
   : m_ants_p(nullptr), m_timevalue(n), m_new_number_of_ants()
{
}

ants_on_table::iterator& ants_on_table::iterator::operator++ ()
{
   m_ants_p->timestep( *this ) ;
   m_timevalue++ ;

   return *this;
}
