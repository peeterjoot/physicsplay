#include "ants_on_table.h"
#include "optticktock.h"

void ants_on_table::timestep( )
{
   constexpr double WALKING_ANTS_PER_FALLEN { 4.0 } ;
   constexpr double FALLEN_ANTS_FRACTION { 0.2 } ;

   TickTockOrNoOp timer ; 

   timer.tick() ;
   m_new_number_of_ants.fill( 0.0 ) ;
   m_timerData.m_init += timer.silent_tock() ;

   timer.tick() ;
   for ( size_t i = 0 ; i < m_table_grid_size ; i++ )
   {
      for ( size_t j = 0 ; j < m_table_grid_size ; j++ )
      {
         float n = m_number_of_ants( i, j ) ;
         int di = m_velocity_y_of_ants( i, j ) ;
         int dj = m_velocity_x_of_ants( i, j ) ;

         int i2 = (int)i + di ;
         int j2 = (int)j + dj ;

         float fallen = FALLEN_ANTS_FRACTION * n ;

         // some ants do not walk
         m_new_number_of_ants.assign( i, j, WALKING_ANTS_PER_FALLEN * fallen ) ;

         // the rest of the ants walk, but some fall of the table
         if (i2 >= 0 and i2 < (int)m_table_grid_size and j2 >= 0 and j2 < (int)m_table_grid_size)
         {
            m_new_number_of_ants.add( i2, j2, fallen ) ;
         }
      }
   }
   m_timerData.m_core += timer.silent_tock() ;

   timer.tick() ;

   m_number_of_ants.swap( m_new_number_of_ants ) ;

   m_timerData.m_update += timer.silent_tock() ;
}
