/** \file rangePartition.cc
 */
#include "rangePartition.h"
#include <algorithm>
#include "myexceptions.h"

rangePartition::rangePartition( const index_type numElements, const taskId numTasks, const taskId taskNumber )
{
   ASSERT_DATA_INT( numTasks > 0, numTasks ) ;
   index_type batchSize = numElements / numTasks ;

   ASSERT_DATA_INT_INT( taskNumber < numTasks, taskNumber, numTasks ) ;
   ASSERT_DATA_INT( taskNumber >= 0, taskNumber ) ;

   m_myFirstGlobalElementIndex = 1 + batchSize * taskNumber ;

   if ( (taskNumber + 1) == numTasks )
   {
      batchSize += (numElements % numTasks) ;
   }

   m_myLastGlobalElementIndex = m_myFirstGlobalElementIndex + batchSize - 1 ;

   ASSERT_DATA_INT( m_myFirstGlobalElementIndex >= 1, m_myFirstGlobalElementIndex ) ;
   ASSERT_DATA_INT_INT( m_myLastGlobalElementIndex <= numElements, m_myLastGlobalElementIndex, numElements ) ;
}

rangePartition::index_type rangePartition::toLocalDomain( const index_type i ) const
{
   ASSERT_DATA_INT_INT( i <= (m_myLastGlobalElementIndex+1), i, m_myLastGlobalElementIndex + 1 ) ;
   ASSERT_DATA_INT_INT( i >= (m_myFirstGlobalElementIndex-1), i, m_myFirstGlobalElementIndex - 1 ) ;

   index_type j = i - m_myFirstGlobalElementIndex + 1 ;

   return j ;
}

rangePartition::subrange rangePartition::subsetOfGlobalRangeInThisPartition( const index_type l, const index_type u ) const
{
   subrange r ;

   // return an empty iteration range, if the local domain is a completely disjoint set from the one that
   // is passed in.  i.e.:
   // 
   // [m,n] = [m_myFirstGlobalElementIndex,m_myLastGlobalElementIndex]
   //
   // | 1 ... [l,u] ... [m,n] ... N |
   // | 1 ... [m,n] ... [l,u] ... N |
   if ( (u < m_myFirstGlobalElementIndex) ||
        (m_myLastGlobalElementIndex < l) )
   {
      r = emptySubRange() ;
   }
   else
   {
      r.first  = std::max( l, m_myFirstGlobalElementIndex ) ;
      r.second = std::min( u, m_myLastGlobalElementIndex ) ;
   }

   return r ;
}

rangePartition::index_type rangePartition::localPartitionSize( ) const
{
   index_type sz = m_myLastGlobalElementIndex - m_myFirstGlobalElementIndex + 1 ;

   ASSERT_DATA_INT( sz > 0, sz ) ;

   return sz ;
}
