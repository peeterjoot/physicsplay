#include "symbol.h"
#include <iostream>

using namespace std ;

/**
 * return a bitmask with a bit set for each unique basis element in the algebra.
 * Look in the mv internals ... this operation very likely already exists.
 */
int mv_bitmask( const mv & a )
{
   int m = 0 ;
   int k = 0 ;
   int b = 0 ;
   for ( int i = 0 ; i <= e3ga_spaceDim ; i++ )
   {
      if ( a.gu() & (1 << i) )
      {
         for ( int j = 0 ; j < e3ga_groupSize[i] ; j++ )
         {
            if ( a.m_c[k] )
            {
               m |= (1 << b) ;
            }

            k++ ;
            b++ ;
         }
      }
      else
      {
         b += e3ga_groupSize[i] ;
      }
   }

   return m ;
}

bool symbol::isZero() const
{
   if ( m_symName.isZero() || ( 0 == mv_bitmask( m_symNumeric ) ) )
   {
      return true ;
   }
   else
   {
      return false ;
   }
}

void symbol::dump() const
{
   cout << m_symName.toString()
        << " ( "
        << toString(m_symNumeric)
        << " )"
        << endl ;
}


bool compareSymbol (const symbol & first, const symbol & second)
{
   const mv & a = first.m_symNumeric ;
   const mv & b = second.m_symNumeric ;

   if ( a.gu() > b.gu() )
   {
      return false ;
   }
   else if ( a.gu() < b.gu() )
   {
      return true ;
   }
   else
   {
      int la = mv_bitmask( a )  ;
      int lb = mv_bitmask( b )  ;

      return la > lb ;
   }
}
