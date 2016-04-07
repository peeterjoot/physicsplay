/** \file rangePartition.h
 */
#if !defined phy1610_rangePartition_h_included
#define phy1610_rangePartition_h_included

#include <utility>
#include <cstddef>

/**
   A class to help manage the translation between the global and local domain indexes.

   The global domain is a range [1,N] that is to be subdivided by a number of threads (or processes)
   indexed [0, numTasks), where numTasks is a positive non-zero count (i.e. the mpi size).

   The taskNumber is a value in that range (i.e. a mpi rank).
 */
class rangePartition
{
public:
   using taskId = int ;
   using index_type = size_t ;

   /** 
      A global domain sub-range that is appropriate for the assigned task.  See subsetOfGlobalRangeInThisPartition.
    */
   using subrange = std::pair<index_type, index_type> ;

   /**
      \param numElements [in]
         The number of elements in the array to be partitioned.

      \param numTasks [in]
         A non-zero positive number representing the number of threads or number of mpi processes assigned to a partition of the work.
         i.e. mpi size.

      \param taskNumber [in]
         A value in the range [0,numTasks)
         i.e. mpi rank.
    */
   rangePartition( const index_type numElements, const taskId numTasks, const taskId taskNumber ) ;

   /** Given a global domain array index appropriate for the local partition, compute the local domain
       index in [1,p] where p is the size of the local domain partition.

       Zero indexed array elements are not used, to allow for the use of v[0] as the lower bound parition guard cell.
    */
   index_type toLocalDomain( const index_type i ) const ;
      
   /** 
      Given a global range [lowerGlobalBound, upperGlobalBound] determine the appropriate subset of that range
      that belongs in the current partition.

      This can be used to translate a loop in the global domain, such as:

         vector<T> v(43 + 1, 0.0) ;
         for ( auto i{3}, i <= 43 ; i++ )
         {
            v[i] = ...
         }

      onto one that can (indirectly) be used for local computation

         rangePartition p( 43, ... ) ;
         vector<T> v( p.localPartitionSize() + 1, 0.0 ) ;

         auto r = p.subsetOfGlobalRangeInThisPartition( 3, 43 ) ;
         for ( auto i{r.first}, i <= r.second ; i++ )
         {
            auto j { p.toLocalDomain( i ) } ;

            v[j] = ...
         }

      \retval
         The subset of the specified range that falls into this partition, or an empty range (such as {1,0})
     */
   subrange subsetOfGlobalRangeInThisPartition( const index_type lowerGlobalBound, const index_type upperGlobalBound ) const ;

   index_type localPartitionSize( ) const ;

private:

   index_type     m_myFirstGlobalElementIndex ; ///< lower bound for: global domain index for this threads' partition.
   index_type     m_myLastGlobalElementIndex ;  ///< upper bound for: global domain index for this threads' partition.
} ;

#endif
