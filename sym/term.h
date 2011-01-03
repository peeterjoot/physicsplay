#if !defined term_header_included
#define term_header_included

/**
  \file term.h
  \brief A basic numeric expression with a numeric and symbolic portion.
 */

#include <string>
#include <map>
#include <sstream>

/**
   The literal.  The most basic expression (a string).
 */
typedef std::string literal ;

/**
   \brief A class representing one of the elements in a sum.

   logically this has the form:

   scalar [literal^exponent]*

   This is a scaling term (default of one).  This is followed by zero
   or more symbolic literals raised to integer powers (default of one).

   The implementation is a string indexed associative array (stl::map)
   of literals (strings), where
   the value in the array is the exponent of the literal.

   Each multiplication of a literal * literal increases the exponent.
   Multiplication by a new (different) literal creates a new element
   (ie: factor) in the array.

GINAC: Should be able to replace this with ginac::ex completely.  This doesn't
map exactly, and is kind of like product(s) of ginac::symbol(s), plus
a leading numeric factor (which is superfluous since ginac::ex can represent
the numeric coefficient).
 */
class term
{
   typedef std::map<literal, int> factorsType ;
   typedef factorsType::iterator iterType ;
   typedef factorsType::const_iterator citerType ;

   #define TERM_ZERO_VALUE 0.0
   #define TERM_ONE_VALUE 1.0

public:
   typedef float scalarType ;

private:
   factorsType m_factors ;
   scalarType m_scalar ;

public:
   /**
    * construct a scalar.
    */
   term( const scalarType & v ) : m_scalar(v)
   {
   }

   /**
    * construct term from a literal.
    */
   term( const literal & literal, const scalarType s = TERM_ONE_VALUE ) : m_scalar(s)
   {
      m_factors[ literal ] = 1 ;
   }

   /**
    * reset the scale factor to one.
    */
   void normalize()
   {
      m_scalar = TERM_ONE_VALUE ;
   }

#if 0
   void adjustScale( const scalarType s )
   {
      m_scalar += s ;
   }
#endif

   scalarType getScale() const
   {
      return m_scalar ;
   }

   /**
    * add to the scalar value for this set of factors using the scale factor from another (presumed equal term).
    */
   void adjustScale( const term & t )
   {
      m_scalar += t.m_scalar ;
   }

   /**
    * multiply term by a single literal.  If this shared any common factors with this term, that factors' exponent will be incremented.
    */
   term & operator *= ( const literal & v )
   {
      m_factors[ v ] ++ ;

      return *this ;
   }

   /**
    * multiply term by another term.  Any common factors will result in aggreggate exponentation.
    */
   term & operator *= ( const term & v )
   {
      for ( citerType i = v.m_factors.begin() ; i != v.m_factors.end() ; i++ )
      {
         m_factors[ i->first ] += i->second ;
      }
      m_scalar *= v.m_scalar ;

      return *this ;
   }

   /**
    * adjust the sign of the scalar factor for this term.
    */
   void negate()
   {
      m_scalar *= -TERM_ONE_VALUE ;
   }

   /**
    * convert term to a string.
    */
   inline std::string toString( const bool withScalar = true ) const ;

   void toStringStream( std::ostringstream & out, const bool useSignPrefix, const bool withScalar = true ) const ;

   /**
    * compare two terms for sort purposes.
    */
   friend bool compareTerm( const term & a, const term & b ) ;

   bool isZero() const
   {
      return ( TERM_ZERO_VALUE == m_scalar ) ;
   }
} ;

inline std::string term::toString( const bool withScalar ) const
{
   std::ostringstream out ;

   toStringStream( out, false, withScalar ) ;

// not working anymore?
//cout << "out.str(): " << out.str() << endl ;
   return out.str() ;
}

#endif
