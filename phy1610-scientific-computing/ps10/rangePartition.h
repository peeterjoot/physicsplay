/** \file rangePartition.h
 */
#if !defined phy1610_rangePartition_h_included
#define phy1610_rangePartition_h_included

#include <utility>

/**
   A class to help manage the translation between the global and local domain indexes.

   The global domain is a range [1,N) that is to be subdivided by a number of threads (or processes)
   indexed [0, numTasks), where numTasks is a positive non-zero count (i.e. the mpi size).

   The taskNumber is a value in that range (i.e. a mpi rank).
 */
class rangePartition
{
public:
   using taskId = int ;
   using size_type = size_t ;

   /** 
      A global domain sub-range that is appropriate for the assigned task.  See rangeForTask.
    */
   using subrange = std::pair<size_type, size_type> ;

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
   rangePartition( const size_type numElements, const taskId numTasks, const taskId taskNumber ) ;

   /** Given a global domain array index appropriate for the local partition, compute the local domain
       index in [1,p) where p is the size of the local domain partition.

       Zero indexed array elements are not used, to allow for the use of v[0] as the lower bound parition guard cell.
    */
   size_type toLocalDomain() const ;
      
   /** 
      Given a global range [lowerGlobalBound, upperGlobalBound) determine the appropriate subset of that range
      that belongs in the local domain.

      This can be used to translate a loop in the global domain, such as:

         for ( auto i{3}, i < 43 ; i++ )
         {
            v[i] = ...
         }

      onto one appropriate for local computation

         rangePartition p( ... ) ;
         auto r = p.rangeForTask( 3, 43 ) ;
         for ( auto i{r.first}, i < r.second ; i++ )
         {
            auto j = p.toLocalDomain( i ) ;

            v[j] = ...
         }
      
     */
   subrange rangeForTask( const size_type lowerGlobalBound, const size_type upperGlobalBound ) const ;

private:

//   size_type firstElementForTask ;
//   size_type lastElementForTask ;
} ;

#if 0
arrayIOwriter::writePartitionInfo::writePartitionInfo( const void * const   start,
                                                       const size_t         totalBytes,
                                                       const int            numTasks,
                                                       const int            threadnum )
   : m_batchSizeBytes{ totalBytes / numTasks }
   , m_startpos{nullptr}
{

   // give the last thread anything left over
   if ( (threadnum + 1) == numTasks )
   {
      m_batchSizeBytes += (totalBytes % numTasks) ;
   }

   assert( m_batchSizeBytes ) ; // these cases were implicitly handled before this function was called.

   m_startpos = (char *)start + m_batchSizeBytes * threadnum ;
}
#endif

#endif
