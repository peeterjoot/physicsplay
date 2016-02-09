/**
   \file ants_on_table.h
 */
#if !defined phy1610_ps2_ants_on_table_h_included
#define phy1610_ps2_ants_on_table_h_included

#include "myrarray2.h"

/**
   Code that simulates ants walking on a table.
   The direction in which they walk, depends on where they are on the table, and they can fall of the edge.
   The simulation prints the number of ants left on the table after every time step.
 */
class ants_on_table
{
   size_t               m_table_grid_size ;  ///< table grid size.
   myrarray2            m_number_of_ants ;   ///< number of ants at each grid location after each timestep.
   myrarray2            m_velocity_of_ants ; ///< velocity of each ant at specified grid point.

   struct timerData
   {
      double m_init ;
      double m_core ;
      double m_update ;
      double m_totants ;

      timerData() :
         m_init{ 0.0 },
         m_core{ 0.0 },
         m_update{ 0.0 },
         m_totants{ 0.0 }
      {
      }
   } ;

   mutable timerData    m_timerData ;
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
      \retval The grid size that the simulation was initialized with.
    */
   inline size_t get_grid_size() const
   {
      return m_table_grid_size ;
   }

   /**
      \brief add the number of ants at each grid location.

      \retval The total number of ants.
    */
   float total_number_of_ants() const ;

   /**
      A simple forward iterator to drive the time stepping iterations.
     */
   class iterator
   {
      ants_on_table *   m_ants_p ;              ///< pointer to the simulation object modified by the iterator.
      int               m_timevalue ;           ///< The timestep value that the iterator is on.
      myrarray2         m_new_number_of_ants ;  ///< A temporary array used in each timestep.  Anchored here to avoid reallocation.

      // Allow ants_on_table::initialize() to construct a starting iterator, but nothing else.
      friend class ants_on_table ;

      /**
         An iterator object to be returned from ants_on_table::initialize()
       */
      explicit iterator( ants_on_table * p_ants ) ;

   public:

      /**
         A constructor to specify the end iteration.

         \param number_of_time_intervals [in]
            The number of times the ants walk around before we stop looking at them.
       */
      explicit iterator( const int number_of_time_intervals ) ;

      /**
         Perform one timestep operation.
       */
      iterator& operator++ () ; // Pre-increment

      /**
         Check against an end iterator to see if we've done the final timestep.
       */
      inline bool operator != ( iterator & rhs)
      {
         return m_timevalue != rhs.m_timevalue ;
      }

      /**
         Return the results of the last timestep operation (total number of ants on the table).
        */
      inline float operator* () const
      {
         return m_ants_p->total_number_of_ants() ;
      }

      /**
         Return the time step number that the iteration is on.
       */
      inline int operator()() const
      {
         return m_timevalue ;
      }
   } ;

   /**
      Reset the simulation, putting in a new number of total ants, and initial counts and velocities, and return
      an iterator that can be used for the subsequent timestep iterations.
    */
   iterator initialize( const int total_ants ) ;

   /**
      Perform one iteration of the ants walking on the table simulation.
    */
   void timestep( iterator & i ) ;
} ;

#endif
