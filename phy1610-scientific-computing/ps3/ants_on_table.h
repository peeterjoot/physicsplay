/**
   \file ants_on_table.h
 */
#if !defined phy1610_ps2_ants_on_table_h_included
#define phy1610_ps2_ants_on_table_h_included

#include "myrarray2.h"
#include <string>

/**
   Code that simulates ants walking on a table.
   The direction in which they walk, depends on where they are on the table, and they can fall of the edge.
   The simulation prints the number of ants left on the table after every time step.
 */
class ants_on_table
{
   size_t               m_table_grid_size{} ;  ///< table grid size.
   myrarray2<float>     m_number_of_ants ;     ///< number of ants at each grid location after each timestep.
   myrarray2<int>       m_velocity_x_of_ants ; ///< x velocity of each ant at specified grid point.
   myrarray2<int>       m_velocity_y_of_ants ; ///< y velocity of each ant at specified grid point.

   struct timerData
   {
       double m_init{ 0.0 } ;
       double m_core{ 0.0 } ;
       double m_update{ 0.0 } ;
       double m_totants{ 0.0 } ;
   } ;

   /// Tick-tock state
   mutable timerData    m_timerData ;

   /// timestep state
   myrarray2<float>  m_new_number_of_ants ;
public:

   /**
      \brief Allocate the ant count matrix and the ant velocity per grid point.

      \param table_grid_size [in]
         Total number of grid intervals in each direction.
    */
   ants_on_table( const size_t table_grid_size ) ;

   /**
      (implicit) deallocation of member data, and if tick-tocks are enabled, print out of the timer-data.
    */
   ~ants_on_table( ) ;

   /**
      Reset the simulation, putting in a new number of total ants, and initial counts and velocities.
    */
   void initialize( const int total_ants ) ;

   /**
      \brief add the number of ants at each grid location.

      \retval The total number of ants.
    */
   float total_number_of_ants() const ;

   /**
      Perform one iteration of the ants walking on the table simulation.
    */
   void timestep( ) ;

   float table_grid_size() const
   {
      return m_table_grid_size ;
   }

   using ants_storage_type = myrarray2<float>::storageValueType ;

   /** for netcdf writer */
   ants_storage_type antsBackingArray() const
   {
      return m_number_of_ants.storageLocation() ;
   }
} ;

/**
   Run the timestep function the specified number of times and output the results
 */
void output( ants_on_table & a, const int num_time_intervals, const std::string netcdfFileName = "" ) ;

#endif
