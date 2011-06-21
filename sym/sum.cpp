#include "sum.h"
#include <iostream>

using namespace std ;

// FIXME: this appears to be hacked from: double mv::largestCoordinate() const.
// What was I doing with it?
int mv_largestCoordinateIndex( const mv & v )
{
   int nc = e3ga_mvSize[v.gu()] ;
   int i ;
   int m = -1 ;
   float maxC = -1.0 ;

   for (i = 0; i < nc; i++)
   {
      float C = fabs( v.m_c[i] ) ;

      if ( C > maxC )
      {
         maxC = C ;
         m = i ;
      }
   }

   return m ;
}

void sum::reduce( )
{
   // Scale everything
   for ( iterType i = m_listOfSymbols.begin() ; i != m_listOfSymbols.end() ; i++ )
   {
      symbol & cur = (*i) ;

      int m = mv_largestCoordinateIndex( cur.m_symNumeric ) ;
      float s = cur.m_symNumeric.m_c[ m ] ;

      cur.m_symNumeric *= 1.0/s ;
      cur.m_symName *= term( s ) ;
   }

   // sort to aggreggate any equal mv components.
   m_listOfSymbols.sort( compareSymbol ) ;

   for ( iterType i = m_listOfSymbols.begin() ; i != m_listOfSymbols.end() ; )
   {
      symbol & cur = (*i) ;
      int curMask = mv_bitmask( cur.m_symNumeric ) ;

      iterType j = i ;
      j++ ;

      while ( j != m_listOfSymbols.end() )
      {
         const symbol & next = (*j) ;
         int nextMask = mv_bitmask( next.m_symNumeric ) ;

         if ( nextMask == curMask )
         {
            cur.m_symName += next.m_symName ;

            j = m_listOfSymbols.erase(j) ;
         }
         else
         {
            break ;
         }
      }

      i = j ;
   }

   // Final pass, now that all the common multivector factors have been accumlated, reduce the symbols.
   for ( iterType i = m_listOfSymbols.begin() ; i != m_listOfSymbols.end() ; )
   {
      (*i).reduce() ;

      if ( (*i).isZero() )
      {
         i = m_listOfSymbols.erase( i ) ;
      }
      else
      {
         i++ ;
      }
   }
}

void sum::dump(void) const
{
   bool first = true ;
   bool zero = true ;

   for ( citerType i = m_listOfSymbols.begin() ; i != m_listOfSymbols.end() ; i++ )
   {
      if ( first )
      {
         cout << endl ;
      }
      else
      {
         cout << "+ " ;
      }

      zero = false ;
      cout << (*i).m_symName.toString()
           << " ( "
           << toString((*i).m_symNumeric)
           << " )"
           << endl ;

      first = false ;
   }

   if ( zero )
   {
      cout << "0" << endl ;
   }
   else
   {
      cout << endl ;
   }
}

// FIXME: shouldn't call dot but left-or-right contract.
sum dot( const sum & a, const mv & b )
{
   sum r ;

   for ( sum::citerType i = a.m_listOfSymbols.begin() ; i != a.m_listOfSymbols.end() ; i++ )
   {
      symbol t(*i) ;

      t.m_symNumeric = b << t.m_symNumeric ;
// try:
//      t.m_symNumeric >>= b ;

      r.m_listOfSymbols.push_front( t ) ;
   }

   return r ;
}
