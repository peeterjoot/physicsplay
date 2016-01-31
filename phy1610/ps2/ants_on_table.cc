/**
   \file ants_on_table.cc
 */

#include "ants_on_table.h"
#include "optticktock.h"
#include <cmath>
#include <iostream>
#include <cassert>

ants_on_table::iterator ants_on_table::initialize( const int total_ants )
{
   assert( total_ants ) ;

   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
      {
         float v = 
            M_PI * (sin ((2 * M_PI * (i + j)) / (m_table_grid_size *10)) + 1) ;

#if defined USE_MYRARRAY2
         m_velocity_of_ants.assign( i, j, v ) ;
#else
         m_velocity_of_ants[i][j] = v ;
#endif
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
#if defined USE_MYRARRAY2
               m_number_of_ants.add( i, j, 1 ) ;
#else
               m_number_of_ants[i][j] += 1 ;
#endif
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
   assert( table_grid_size ) ;
}

ants_on_table::~ants_on_table( )
{
   #if defined USE_TICK_TOCK
      std::cout << "totants time: \t" << m_timerData.m_totants << std::endl ;
      std::cout << "init time: \t"    << m_timerData.m_init    << std::endl ;
      std::cout << "core time: \t"    << m_timerData.m_core    << std::endl ;
      std::cout << "update time: \t"  << m_timerData.m_update  << std::endl ;
   #endif
}

float ants_on_table::total_number_of_ants() const
{
   float totants = 0.0 ;

   TickTockOrNoOp timer ; 

   timer.tick() ;
   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
#if defined USE_SUBRARRAY
      auto ai = m_number_of_ants[i] ;
#endif

      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
      {
#if defined USE_MYRARRAY2
         totants += m_number_of_ants( i, j ) ;
#elif defined USE_SUBRARRAY
         totants += ai[j] ;
#else
         totants += m_number_of_ants[i][j] ;
#endif
      }
   }

   m_timerData.m_totants += timer.silent_tock() ;

   return totants ;
}

void ants_on_table::timestep( iterator & iter )
{
   constexpr double RADIUS_OF_POSITION_ADJUSTMENT { 1.9 } ;
   constexpr double WALKING_ANTS_PER_FALLEN { 4.0 } ;
   constexpr double FALLEN_ANTS_FRACTION { 0.2 } ;

   TickTockOrNoOp timer ; 

   timer.tick() ;
   iter.m_new_number_of_ants.fill( 0.0 ) ;
   m_timerData.m_init += timer.silent_tock() ;

   timer.tick() ;
   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
#if defined USE_SUBRARRAY
      auto ai = m_number_of_ants[i] ;
      auto vi = m_velocity_of_ants[i] ;
#endif
      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
      {
#if defined USE_SUBRARRAY
         float v = vi[ j ] ;
#elif defined USE_MYRARRAY2
         float v = m_velocity_of_ants( i, j ) ;
#else
         float v = m_velocity_of_ants[i][j] ;
#endif
         int di = RADIUS_OF_POSITION_ADJUSTMENT * sin( v ) ;
         int dj = RADIUS_OF_POSITION_ADJUSTMENT * cos( v ) ;
         int i2 = (int)i + di ;
         int j2 = (int)j + dj ;

#if defined USE_SUBRARRAY
         float fallen = FALLEN_ANTS_FRACTION * ai[j] ;
#elif defined USE_MYRARRAY2
         float fallen = FALLEN_ANTS_FRACTION * m_number_of_ants( i, j ) ;
#else
         float fallen = FALLEN_ANTS_FRACTION * m_number_of_ants[i][j] ;
#endif

         // some ants do not walk
#if defined USE_MYRARRAY2
         iter.m_new_number_of_ants.assign( i, j, WALKING_ANTS_PER_FALLEN * fallen ) ;
#else
         iter.m_new_number_of_ants[i][j] += WALKING_ANTS_PER_FALLEN * fallen ;
#endif

         // the rest of the ants walk, but some fall of the table
         if (i2 >= 0 and i2 < (int)m_table_grid_size and j2 >= 0 and j2 < (int)m_table_grid_size)
         {
#if defined USE_MYRARRAY2
            iter.m_new_number_of_ants.add( i2, j2, fallen ) ;
#else
            iter.m_new_number_of_ants[i2][j2] += fallen ;
#endif
         }
      }
   }
   m_timerData.m_core += timer.silent_tock() ;

   timer.tick() ;
   // removed the totants calculation (it was done at the top of the loop, but not used in
   // the timestep calculation itself).
   //
   // Note: could use the rarray deep copy here, but is that smart enough to avoid a reallocation
   // when the sizes are compatible?
   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
#if defined USE_SUBRARRAY
      auto ni = iter.m_new_number_of_ants[i] ;
#endif
      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
      {
#if defined USE_SUBRARRAY
         m_number_of_ants[i][j] = ni[j] ;
#elif defined USE_MYRARRAY2
         m_number_of_ants.assign(i, j, iter.m_new_number_of_ants( i, j ) ) ;
#else
         m_number_of_ants[i][j] = iter.m_new_number_of_ants[i][j] ;
#endif
      }
   }
   m_timerData.m_update += timer.silent_tock() ;
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
   assert( n > 0 ) ;
}

ants_on_table::iterator& ants_on_table::iterator::operator++ ()
{
   m_ants_p->timestep( *this ) ;
   m_timevalue++ ;

   return *this;
}
