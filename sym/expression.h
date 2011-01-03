#if !defined expression_header_included
#define expression_header_included

/**
  \file expression.h
  \brief An expression class supporting addition and multiplication.
 */

#include "term.h"
#include <list>

/**
   A representation of a set (sum) of terms.
  
   Addition and subtraction are implemented.
   Multiplication (with distribution over all sums) is implemented.
  
   Addition and subtraction operations do not result in common expression elimination, and reduce() must be called
   explicitly if desired.

GINAC: Should be able to replace this and term ginac::ex completely.
 */
class expression
{
   typedef std::list<term> contType ;
   typedef contType::iterator iterType ;
   typedef contType::const_iterator citerType ;

   contType m_summands ;

   /**
    * multiply self by complete expression.  No
    */
   static void multiply( expression & r, const expression & a, const expression & b )
   {
      // TODO: assert that r.m_summands.size() == 0

      // c = \sum_i a_i b_i
      for ( citerType i = a.m_summands.begin() ; i != a.m_summands.end() ; i++ )
      {
         for ( citerType j = b.m_summands.begin() ; j != b.m_summands.end() ; j++ )
         {
            term tmp(*i) ;
            tmp *= (*j) ;

            r.m_summands.push_front(tmp) ;
         }
      }
   }

   // for operator *='s use of swap.  Likely no other uses for empty expressions.
   expression( )
   {
   }

public:

   expression( const term & t )
   {
      m_summands.push_front( t ) ;
   }

   /**
    * multiply all terms in self by factor.
    */
   expression & operator *= ( const term & factor )
   {
      for ( iterType i = m_summands.begin() ; i != m_summands.end() ; i++ )
      {
         (*i) *= factor ;
      }

      return *this ;
   }

   std::string toString() const ;

   expression & operator *= ( const expression & e )
   {
      //
      // need new storage for the result, but it doesn't make sense to
      // have to go through all the constructor/destructor gunk more than
      // we have to.  Move the initial *this to a temp var, and then multiply
      // it out.  On scope exit the initial contents of *this are then
      // destructed.
      //
      expression t ;
      t.m_summands.swap( m_summands ) ;

      multiply( *this, t, e ) ;

      return *this ;
   }

   /**
    * negate all terms in self.
    */
   void negate()
   {
      for ( iterType i = m_summands.begin() ; i != m_summands.end() ; i++ )
      {
         (*i).negate() ;
      }
   }

   /**
    * add a term from self.
    */
   expression & operator += ( const term & t )
   {
      m_summands.push_front( t ) ;

      return *this ;
   }

   /**
    * subtract a term from self.
    */
   expression & operator -= ( const term & t )
   {
      term n(t) ;
      n.negate() ;

      m_summands.push_front( n ) ;

      return *this ;
   }

   /**
    * add an expression from self.
    */
   expression & operator += ( const expression & e )
   {
      for ( citerType i = e.m_summands.begin() ; i != e.m_summands.end() ; i++ )
      {
         m_summands.push_front((*i)) ;
      }

      return *this ;
   }

   /**
    * subtract an expression from self.
    */
   expression & operator -= ( const expression & e )
   {
      for ( citerType i = e.m_summands.begin() ; i != e.m_summands.end() ; i++ )
      {
         term n((*i)) ;
         n.negate() ;
         m_summands.push_front(n) ;
      }

      return *this ;
   }

   /**
    * eliminate common expressions.
    */
   void reduce() ;

   /**
    * is an expression equal to zero.  Assumes that the expression is reduced.
    */
   bool isZero() const ;
} ;

#endif
