/** \file rangePartition.cc
 */
#include "rangePartition.h"
#include <cassert>
#include <algorithm>

rangePartition::rangePartition( const index_type numElements, const taskId numTasks, const taskId taskNumber )
{
   index_type batchSize = numElements / numTasks ;

   assert( taskNumber < numTasks ) ;
   assert( taskNumber >= 0 ) ;

   m_myFirstGlobalElementIndex = 1 + batchSize * taskNumber ;

   if ( (taskNumber + 1) == numTasks )
   {
      batchSize += (numElements % numTasks) ;
   }

   m_myLastGlobalElementIndex = m_myFirstGlobalElementIndex + batchSize - 1 ;

   assert( m_myFirstGlobalElementIndex >= 1 ) ;
   assert( m_myLastGlobalElementIndex <= numElements ) ;
}

rangePartition::index_type rangePartition::toLocalDomain( const index_type i ) const
{
   assert( i <= m_myLastGlobalElementIndex ) ;
   assert( i >= m_myFirstGlobalElementIndex ) ;

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
      r.first  = 1 ;
      r.second = 0 ;
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

   assert( sz > 0 ) ;

   return sz ;
}
