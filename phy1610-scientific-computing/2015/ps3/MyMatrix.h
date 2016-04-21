/** \file mymatrix.h
 */
#if !defined phy1610_ps3_mymatrix_h_included
#define phy1610_ps3_mymatrix_h_included

#include <vector>
#include <string>
#include "integers.h"

#if defined MYMATRIX_DO_RANGE_CHECKING
   #define MYMATRIX_RANGE_CHECKED_FLAG true
#else
   #define MYMATRIX_RANGE_CHECKED_FLAG false
#endif
/**
  A simple matrix class.
 */
class MyMatrix
{
   /// this class is generic with the exception of this float dependence
   typedef float valueType ;

   /// storage.
#if defined WITH_ARRAY
   valueType * elem ;
#else
   std::vector<valueType> elem ;
#endif
   Uint r ;    ///< rows
   Uint c ;    ///< columns

   /**
      return the storage location for the specified (i,j) location.

      This internal function does not range checking.

      \param i [in]
         row index.

      \param j [in]
         column index.
    */
   inline Uint pos( const Uint i, const Uint j ) const
   {
      return ( i*c + j ) ;
   }

   /** throws std::out_of_range if r == 0, or c == 0.  Called in all constructors.
    */
   inline void check_cons_dimensions() const ;

   /**
      no range checking exceptions.
    */
   inline valueType get_element_unchecked( const Uint i, const Uint j ) const
   {
      return elem[ pos( i, j ) ] ;
   }

   /**
      throws out_of_range exception if i,j exceed acceptible range.  Not inlined to firewall away the exception object creation code.
    */
   valueType get_element_checked( const Uint i, const Uint j ) const ;

   /**
      no range checking exceptions.
    */
   inline void set_element_unchecked( const Uint i, const Uint j, const valueType v )
   {
      elem[ pos( i, j ) ] = v ;
   }

   /**
      throws out_of_range exception if i,j exceed acceptible range.  Not inlined to firewall away the exception object creation code.
    */
   void set_element_checked( const Uint i, const Uint j, const valueType v ) ;
public:

   MyMatrix( ) : elem{}, r{0}, c{0} {} 

   /**
      Construct an uninitialized matrix with a specified size.

      \param r_ [in]
         number of rows

      \param c_ [in]
         number of columns
    */
   MyMatrix( const Uint r_, const Uint c_ ) ;

   /**
      construct a matrix element with a default value used for all elements.

      \param r_ [in]
         number of rows

      \param c_ [in]
         number of columns

      \param fill [in]
         initial value for the matrix elements.
    */
   MyMatrix( const Uint r_, const Uint c_, const valueType fill ) ;

   /**
      destructor.  nothing needed explicitly (vector cleans up after itself)
    */
   ~MyMatrix( )
   {
#if defined WITH_ARRAY
      if ( elem )
      {
         delete[] elem ;
      }
#endif
   }

   /**
      number of rows in the matrix.
    */
   inline Uint get_rows() const
   {
      return r ;
   }

   /**
      number of columns in the matrix.
    */
   inline Uint get_columns() const
   {
      return c ;
   }

   /**
      set the (i,j) matrix element to the value v.

      \param i [in]
         row index

      \param j [in]
         column index

      \param v [in]
         value to set

      \param checked [in]
         throw std::out_of_range if the i >= r, j >= c
    */
   inline void set_element( const Uint i, const Uint j, const valueType v, const bool checked = MYMATRIX_RANGE_CHECKED_FLAG )
   {
      if ( !checked )
      {
         // fast path (inlined) for performance.
         return set_element_unchecked( i, j, v ) ;
      }
      else
      {
         return set_element_checked( i, j, v ) ;
      }
   }

   /**
      get the (i,j) matrix element.

      \param i [in]
         row index

      \param j [in]
         column index
    */
   inline valueType get_element( const Uint i, const Uint j, const bool checked = MYMATRIX_RANGE_CHECKED_FLAG ) const
   {
      if ( !checked )
      {
         // fast path (inlined) for performance.
         return get_element_unchecked( i, j ) ;
      }
      else
      {
         // with range checking.
         return get_element_checked( i, j ) ;
      }
   }

   /**
      Write the matrix to a file

      \param filename [in]
         path to the file to write the data to.

      \param binaryMode [in]
         specify true for binary mode output.
    */
   void output( const std::string filename, const bool binaryMode = false ) const ;

   /**
      Read the matrix to a file

      \param filename [in]
         path to the file to write the data to.

      \param binaryMode [in]
         specify true for binary mode output.
    */
   void input( const std::string filename, const bool binaryMode = false ) ;
} ;

#endif
