/** \file mymatrix.h
 */
#if !defined phy1610_ps3_mymatrix_h_included
#define phy1610_ps3_mymatrix_h_included

#include <vector>
#include <string>
#include "integers.h"

/**
  A simple matrix class.
 */
class MyMatrix
{
   std::vector<float> elem ; ///< storage.
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
public:

   /**
      construct a matrix element.

      \param r_ [in]
         number of rows

      \param c_ [in]
         number of columns
    */
   MyMatrix( const Uint r_, const Uint c_ ) ;

   /**
      destructor.  nothing needed explicitly (vector cleans up after itself)
    */
   ~MyMatrix( )
   {
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
    */
   void set_element( const Uint i, const Uint j, const float v ) ;

//   float get_element( const Uint i, const Uint j ) const ;

   /**
      Write the matrix to a file

      \param filename [in]
         path to the file to write the data to.
    */
   void output( const std::string filename ) const ;
} ;

#endif
