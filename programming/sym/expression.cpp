#include "expression.h"
#include <sstream>

using namespace std ;

bool expression::isZero() const
{
   citerType i = m_summands.begin() ;

   if ( (*i).isZero() )
   {
      i++ ;

      if ( i == m_summands.end() )
      {
         return true ;
      }
   }

   return false ;
}

inline bool compareTerm( const term & a, const term & b )
{
   std::string aStr = a.toString( false ) ;
   std::string bStr = b.toString( false ) ;

   if ( aStr == bStr )
   {
      // want to sort the factors with higher weight than the cooefficients.
      return a.m_scalar > b.m_scalar ;
   }
   else
   {
      return aStr > bStr ;
   }
}

void expression::reduce()
{
   m_summands.sort( compareTerm ) ;

   std::string curStr ;
   iterType prev ;
   iterType i = m_summands.begin() ;

   while ( i != m_summands.end() && (TERM_ZERO_VALUE == (*i).getScale()) )
   {
      i = m_summands.erase( i ) ;
   }

   if ( i != m_summands.end() )
   {

      {
         term curValue = *i ;
         curValue.normalize() ;
         curStr = curValue.toString() ;
      }

      prev = i ;
      i++ ;
      while ( i != m_summands.end() )
      {
         std::string nextStr ;

         while ( i != m_summands.end() && (TERM_ZERO_VALUE == (*i).getScale()) )
         {
            i = m_summands.erase( i ) ;
         }

         if ( i == m_summands.end() )
         {
            break ;
         }

         {
            term next = *i ;
            next.normalize() ;
            nextStr = next.toString() ;
         }

         if ( nextStr == curStr )
         {
            (*prev).adjustScale( *i ) ;

            i = m_summands.erase( i ) ;
         }
         else
         {
            prev = i ;
            curStr = nextStr ;
            i++ ;
         }
      }
   }

   //
   // a final "dead code" elimination pass.
   //
   for ( i = m_summands.begin() ; i != m_summands.end() ; )
   {
      if ( TERM_ZERO_VALUE == (*i).getScale() )
      {
         i = m_summands.erase( i ) ;
      }
      else
      {
         i++ ;
      }
   }

   if ( !m_summands.size() )
   {
      m_summands.push_front( term( TERM_ZERO_VALUE ) ) ;
   }
}

std::string expression::toString() const
{
   std::ostringstream out ;

   bool wantSignPrefix = false ;

   contType::size_type size = m_summands.size() ;

   if ( size > 1 )
   {
      out << "( " ;
   }

   for ( citerType i = m_summands.begin() ; i != m_summands.end() ; i++ )
   {
      (*i).toStringStream( out, wantSignPrefix ) ;

      wantSignPrefix = true ;
   }

   if ( size > 1 )
   {
      out << " )" ;
   }

   return out.str() ;
}

