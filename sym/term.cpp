#include "term.h"

using namespace std ;

void term::toStringStream( std::ostringstream & out, const bool useSignPrefix, const bool withScalar ) const
{
   scalarType scalarValue ;

   if ( withScalar )
   {
      scalarValue = m_scalar ;
   }
   else
   {
      //
      // This is a hack for the compare sort function ... I was lazy and used this string logic to do the compare.
      // It's not efficient, which will make all the already inefficient reduce() functions worse.
      //
      scalarValue = TERM_ONE_VALUE ;
   }

   if ( useSignPrefix )
   {
      out << " " ;

      if ( scalarValue > TERM_ZERO_VALUE )
      {
         out << "+ " ;
      }
   }

   if ( m_factors.size() )
   {
      if ( scalarValue == -TERM_ONE_VALUE )
      {
         out << "- " ;
      }
      else if ( scalarValue != TERM_ONE_VALUE )
      {
         out << scalarValue ;
      }

      bool doneFirst = false ;

      for ( citerType i = m_factors.begin() ; i != m_factors.end() ; i++ )
      {
         if ( doneFirst )
         {
            out << " " ;
         }
         else
         {
            doneFirst = true ;
         }

         if ( 1 == i->second )
         {
            out << i->first ;
         }
         else
         {
            out << i->first << "^" << i->second ;
         }
      }
   }
}
