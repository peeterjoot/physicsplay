#if !defined symbol_header_included
#define symbol_header_included

/**
  \file symbol.h
 */

#include "expression.h"
//#include <common.h>
#include <e3ga.h>

using namespace e3ga ;

class sum ;
sum dot( const sum & a, const mv & b ) ;
//sum wedge( const sum & a, const mv & b ) ;

class symbol ;
bool compareSymbol (const symbol & first, const symbol & second) ;

/**
   A representation of a symbolic expression (polynomial like symbolic object)
   and an associated multivector factor.

   Here expression is a sum of terms, and a term is a product of factors (where
   one factor can be a scalar).  Factors in a term have a built in optional
   exponential scaling, so 'X' * 'X' isn't too factors (literals) but one
   with an exponent value of 2.

   This class is the first place in the hierarchy that a GA library
   dependency comes into play.

   GINAC: the expression use here could be completely replaced with ginac::ex.  However, with ginac able to represent all of the lower level symbolic parts
directly, this particular middleman is not required.
 */
class symbol
{
   expression m_symName ;
   typedef mv valueType ;
   valueType m_symNumeric ;

   friend class sum ;

public:
   symbol( const expression & name, const valueType & value ) : m_symName(name), m_symNumeric(value)
   {
   }

   symbol( const term & name, const valueType & value ) : m_symName(name), m_symNumeric(value)
   {
   }

   symbol( const literal & name, const valueType & value ) : m_symName(term(name)), m_symNumeric(value)
   {
   }

   symbol( const valueType & value ) : m_symName(term(1)), m_symNumeric(value)
   {
   }

   symbol( const literal & name ) : m_symName(term(name)), m_symNumeric(1)
   {
   }

   symbol( const term::scalarType scalar = TERM_ZERO_VALUE ) : m_symName(term(scalar)), m_symNumeric(1)
   {
   }

   symbol & operator *= ( const valueType & scale )
   {
      m_symNumeric *= scale ;

      return *this ;
   }

   symbol & operator *= ( const expression & scale )
   {
      m_symName *= scale ;

      return *this ;
   }

   symbol & operator *= ( const symbol & scale )
   {
      m_symName *= scale.m_symName ;
      m_symNumeric *= scale.m_symNumeric ;

      return *this ;
   }

   symbol & operator *= ( const term & scale )
   {
      m_symName *= scale ;

      return *this ;
   }

   symbol & operator ^= ( const symbol & scale )
   {
      m_symName *= scale.m_symName ;
      m_symNumeric ^= scale.m_symNumeric ;

      return *this ;
   }

   symbol & operator >>= ( const symbol & scale )
   {
      m_symName *= scale.m_symName ;
      m_symNumeric = ( scale.m_symNumeric << m_symNumeric ) ;

      return *this ;
   }

   symbol & operator <<= ( const symbol & scale )
   {
      m_symName *= scale.m_symName ;
      m_symNumeric <<= scale.m_symNumeric ;

      return *this ;
   }

   void reduce()
   {
      m_symName.reduce() ;
   }

   void reverseMe()
   {
      m_symNumeric = reverse( m_symNumeric ) ;
   }

   friend bool compareSymbol (const symbol & first, const symbol & second) ;
   friend sum dot( const sum & a, const mv & b ) ;
//   friend sum wedge( const sum & a, const sum & b ) ;

   void dump() const ;

   #define SYMBOL_SCALAR_PART    GRADE_0
   #define SYMBOL_VECTOR_PART    GRADE_1
   #define SYMBOL_BIVECTOR_PART  GRADE_2
   #define SYMBOL_TRIVECTOR_PART GRADE_3
   /**
      \param mask [in]
         One of SYMBOL_SCALAR_PART, SYMBOL_VECTOR_PART, SYMBOL_BIVECTOR_PART, or SYMBOL_TRIVECTOR_PART.
    */
   void gradeFilter( const unsigned int mask )
   {
      m_symNumeric.m_gu &= mask ;
   }

   /**
    * determine if a reduced symbol is zero (either a zero scalar value in the the one and only term of the expression,
    * or a zero as the coefficient of the mv value).
    */
   bool isZero() const ;
} ;

/*
   These pairs of classes aren't particularily intuitive, but
   are essentially macros to be passed to a template function.

   These are less sofisticated versions of <functional>, and it
   may be possible to use those and <algorithm> instead of the manual
   loops all over this code (ie: for_each template, ...).
 */
class mutate_times
{
   public:

   mutate_times( symbol & out, const symbol & l, const symbol & r )
   {
      out = l ;
      out *= r ;
   }
} ;

class mutate_wedge
{
   public:

   mutate_wedge( symbol & out, const symbol & l, const symbol & r )
   {
      out = l ;
      out ^= r ;
   }
} ;

class mutate_right_contract
{
   public:

   mutate_right_contract( symbol & out, const symbol & l, const symbol & r )
   {
      out = l ;
      out >>= r ;
   }
} ;

class mutate_left_contract
{
   public:

   mutate_left_contract( symbol & out, const symbol & l, const symbol & r )
   {
      out = l ;
      out <<= r ;
   }
} ;

int mv_bitmask( const mv & a ) ;

#endif
