/**
   \file ants_on_table.h
 */
#if !defined phy1610_ps2_ants_on_table_h_included
#define phy1610_ps2_ants_on_table_h_included

#include "rarray"

/**
   Code that simulates ants walking on a table.
   The direction in which they walk, depends on where they are on the table, and they can fall of the edge.
   The simulation prints the number of ants left on the table after every time step.
 */
class ants_on_table
{
   int                  m_table_grid_size ;
   rarray<float, 2>     m_number_of_ants ;
   rarray<float, 2>     m_velocity_of_ants ;

   /**
      \brief add the number of ants at each grid location.

      \retval The total number of ants.
    */
   float total_number_of_ants() const ;

public:

   /** 
      \brief Allocate the ant count matrix and the (average?) ant velocity per grid point.

      \param table_grid_size [in]
         Total number of grid intervals in each direction.
    */
   ants_on_table( const size_t table_grid_size ) ;

   /**
      Reset the simulation, putting in a new number of total ants, and initial counts and velocities.
    */
   void initialize( const int total_ants ) ;

   /**
      \brief ants walk on a table

      \param number_of_time_intervals [in]
         The number of times the ants walk around before we stop looking at them.
    */
   void simulation( const int number_of_time_intervals ) ;
} ;

#endif
