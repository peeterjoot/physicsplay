#if !defined sum_header_included
#define sum_header_included

/**
  \file sum.h
 */

#include "symbol.h"

/**
  This is a list of symbol/multivector pairs.  The sign(s) of each of
  the summands is built into the symbol themselves.

  A symbol has a multivector factor and a symbolic factor.

  GINAC: a replacement of the symbolic logic here should probably merge
this highest level class with the next lowest 'class symbol'.  make a list
of pair<ginac::ex, mv> instead.
 */
class sum
{
   typedef std::list<symbol> symbolSetType ;
   typedef symbolSetType::iterator iterType ;
   typedef symbolSetType::const_iterator citerType ;

   symbolSetType m_listOfSymbols ;

   /**
      \param sum [out]
         The result.  This is assumed to initially be zero/default constructed.
    */
   template <class mutate_op>
   static void multiply_op( sum & agg, const sum & l, const sum & r )
   {
      // assume zero constructed output

      for ( citerType i = l.m_listOfSymbols.begin() ; i != l.m_listOfSymbols.end() ; i++ )
      {
         for ( citerType j = r.m_listOfSymbols.begin() ; j != r.m_listOfSymbols.end() ; j++ )
         {
            symbol tmp ;

            mutate_op tmpEqualsItimesJ( tmp, *i, *j ) ;

            agg += tmp ;
         }
      }
   }

public:
   sum( ) {}

   sum( const symbol & i )
   {
      m_listOfSymbols.push_front( i ) ;
   }

   sum & operator += ( const symbol & more )
   {
      m_listOfSymbols.push_front( more ) ;

      return *this ;
   }

   sum & operator += ( const sum & s )
   {
      for ( citerType i = s.m_listOfSymbols.begin() ; i != s.m_listOfSymbols.end() ; i++ )
      {
         m_listOfSymbols.push_front( *i ) ;
      }

      return *this ;
   }

   sum & operator *= ( const symbol & scale )
   {
      for ( iterType i = m_listOfSymbols.begin() ; i != m_listOfSymbols.end() ; i++ )
      {
         (*i) *= scale ;
      }

      return *this ;
   }

#if 0 // not used.
   void reverseMe()
   {
      iterType i = m_listOfSymbols.begin() ;

      while ( i != m_listOfSymbols.end() )
      {
         (*i).reverseMe() ;

         i++ ;
      }
   }
#endif

   sum reverse() const
   {
      sum r(*this) ;

      for ( iterType i = r.m_listOfSymbols.begin() ; i != r.m_listOfSymbols.end() ; i++ )
      {
         (*i).reverseMe() ;
      }

      return r ;
   }

   sum & operator *= ( const sum & v )
   {
      sum t ;
      t.m_listOfSymbols.swap( m_listOfSymbols ) ;

      multiply_op< mutate_times >( *this, t, v ) ;

      return *this ;
   }

   friend sum operator * ( const sum & l, const sum & r )
   {
      sum agg ;

      multiply_op< mutate_times >( agg, l, r ) ;

      return agg ;
   }

   sum & operator ^= ( const sum & v )
   {
      sum t ;
      t.m_listOfSymbols.swap( m_listOfSymbols ) ;

      multiply_op< mutate_wedge >( *this, t, v ) ;

      return *this ;
   }

   friend sum operator ^ ( const sum & l, const sum & r )
   {
      sum agg ;

      multiply_op< mutate_wedge >( agg, l, r ) ;

      return agg ;
   }

   sum & operator <<= ( const sum & v )
   {
      sum t ;
      t.m_listOfSymbols.swap( m_listOfSymbols ) ;

      multiply_op< mutate_left_contract >( *this, t, v ) ;

      return *this ;
   }

   friend sum operator << ( const sum & l, const sum & r )
   {
      sum agg ;

      multiply_op< mutate_left_contract >( agg, l, r ) ;

      return agg ;
   }

   sum & operator >>= ( const sum & v )
   {
      sum t ;
      t.m_listOfSymbols.swap( m_listOfSymbols ) ;

      multiply_op< mutate_right_contract >( *this, t, v ) ;

      return *this ;
   }

   friend sum operator >> ( const sum & l, const sum & r )
   {
      sum agg ;

      multiply_op< mutate_right_contract >( agg, l, r ) ;

      return agg ;
   }

   void reduce( ) ;

   void dump(void) const ;

   void dump( const bool reduceFirst ) // NOT const.
   {
      if ( reduceFirst )
      {
         reduce() ;
      }

      dump() ;
   }

   friend sum dot( const sum & a, const mv & b ) ;

   void gradeFilter( const unsigned int mask )
   {
      for ( iterType i = m_listOfSymbols.begin() ; i != m_listOfSymbols.end() ; i++ )
      {
         (*i).gradeFilter( mask ) ;
      }
   }
} ;

#endif
