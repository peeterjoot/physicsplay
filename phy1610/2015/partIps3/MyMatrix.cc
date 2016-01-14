/**
   \file MyMatrix.cc

   implementation of non-inline methods for the MyMatrix class.
 */
#include "MyMatrix.h"
#include <string>
#include <fstream>
#include <stdexcept>
#if defined WITH_ARRAY
#include <algorithm>
#endif

inline void MyMatrix::check_cons_dimensions() const
{
   if ( 0 == r || 0 == c )
   {
      std::string s = std::string( "r = " ) + std::to_string( r )
                    + std::string( ", c = " ) + std::to_string( c ) ;

      throw std::out_of_range( s ) ;
   }
}

MyMatrix::MyMatrix( const Uint r_, const Uint c_ ) : elem(), r{r_}, c{c_}
{
   check_cons_dimensions() ;

#if defined WITH_ARRAY
   elem = new valueType[ r * c ] ;
#else
   elem.resize( r * c ) ;
#endif
}

MyMatrix::MyMatrix( const Uint r_, const Uint c_, const MyMatrix::valueType fill ) : elem(), r{r_}, c{c_}
{
   check_cons_dimensions() ;

#if defined WITH_ARRAY
   elem = new valueType[ r * c ] ;
   std::fill( elem, &elem[r * c], fill ) ;
#else
   elem.resize( r * c, fill ) ;
#endif
}

void MyMatrix::set_element_checked( const Uint i, const Uint j, const MyMatrix::valueType v )
{
   if ( i >= r || j >= c )
   {
      std::string s = 
                      std::string( "i = " ) + std::to_string( i )
                    + std::string( ", j = " ) + std::to_string( j )
                    + std::string( "; r = " ) + std::to_string( r )
                    + std::string( ", c = " ) + std::to_string( c ) ;

      throw std::out_of_range( s ) ;
   }

   set_element_unchecked( i, j, v ) ;
}

MyMatrix::valueType MyMatrix::get_element_checked( const Uint i, const Uint j ) const
{
   if ( i >= r || j >= c )
   {
      std::string s = 
                      std::string( "i = " ) + std::to_string( i )
                    + std::string( ", j = " ) + std::to_string( j )
                    + std::string( "; r = " ) + std::to_string( r )
                    + std::string( ", c = " ) + std::to_string( c ) ;

      throw std::out_of_range( s ) ;
   }

   return get_element_unchecked( i, j ) ;
}

void MyMatrix::output( const std::string filename, const bool binaryMode ) const
{
   std::ios_base::openmode mode = std::ios_base::trunc ;
   if ( binaryMode )
   {
      mode |= std::ios_base::binary ;
   }

   std::ofstream stream( filename, mode ) ;

   if ( binaryMode )
   {
      stream.write( (char *)&r, sizeof(r) ) ;
      stream.write( (char *)&c, sizeof(c) ) ;
      stream.write( (const char *)elem.data(), sizeof(valueType)*r*c ) ;
   }
   else
   {
      stream << r << " "
             << c << std::endl ;

      for ( Uint i = 0 ; i < r ; i++ )
      {
         for ( Uint j = 0 ; j < c ; j++ )
         {
            stream << elem[ pos( i, j ) ] << " " ;
         }

         stream << std::endl ;
      }
   }

   // destructor will close the file.
}

void MyMatrix::input( const std::string filename, const bool binaryMode )
{
   std::ios_base::openmode mode = std::ios_base::in ;
   if ( binaryMode )
   {
      mode = std::ios_base::binary ;
   }

   std::ifstream stream( filename, mode ) ;
   if ( binaryMode )
   {
      stream.read( (char *)&r, sizeof(r) ) ;
      stream.read( (char *)&c, sizeof(c) ) ;
   }
   else
   {
      stream >> r ;
      stream >> c ;
   }
   elem.resize( r * c ) ;

   if ( binaryMode )
   {
      stream.read( (char *)elem.data(), sizeof(valueType)*r*c ) ;
   }
   else
   {
      for ( Uint i = 0 ; i < r ; i++ )
      {
         for ( Uint j = 0 ; j < c ; j++ )
         {
            valueType tmp ;
            stream >> tmp ;
            elem[ pos( i, j ) ] = tmp ;
         }
      }
   }

   // destructor will close the file.
}
