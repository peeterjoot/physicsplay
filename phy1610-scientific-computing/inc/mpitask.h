/** \file mpitask.h
 */
#if !defined phy1610_mpitask_h_included
#define phy1610_mpitask_h_included

/**
   Run the mpi init/term functions and collect the size and rank.
 */
struct mpitask
{
   /** fake an mpi init call */
   mpitask( int rank, int size ) ;

   mpitask( int * argc, char *** argv ) ;

   ~mpitask() ;

   int   m_rank ;
   int   m_size ;
private:
   bool  m_initDone ;
} ;

#endif
