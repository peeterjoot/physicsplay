//
// diffring_timestep.h
//
// Time step module for 1d diffusion on a ring
//

#ifndef DIFFRINGTIMESTEPH
#define DIFFRINGTIMESTEPH

#include "darray.h"
#include "darray2.h"

/**
   This holds the time evolution matrix and what ever additional state is required to
   perform that evolution.
 */
class diffring_evolution
{
   const int   m_n ;       ///< size of the matrix, saved for convenience.
   darray      m_tmpvec ;  ///< temporary vector (i.e. allocate once.)
   darray2     m_F ;       ///< matrix that describes the time evolution

   /**
      Fill the matrix needed in perform_time_step.

      \internal
    */
   void fill_time_step_matrix( const double   D,
                               const double   dt,
                               const double   dx ) ;
public:

   /**
      Construct an object with the state required for timestep calculations

      \param N [in]
         Size of the density vector.

      \param D [in]
         The diffusion constant.

      \param dt [in]
         The time step to be used.

      \param dx [in]
         The spatial resolution.
     */
   diffring_evolution( const int      N,
                       const double   D,
                       const double   dt,
                       const double   dx ) ;

   /**
      Perform a single time step for the density field.

      \param P [in|out]
         The density
    */
   void perform_time_step( darray & P ) ;
} ;
#endif
