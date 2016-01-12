/**
   \file MyMatrix.cc

   implementation of non-inline methods for the MyMatrix class.
 */
#include "MyMatrix.h"
#include <string>
#include <fstream>
#include <stdexcept>

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

   elem.resize( r * c ) ;
}

MyMatrix::MyMatrix( const Uint r_, const Uint c_, const float fill ) : elem(), r{r_}, c{c_}
{
   check_cons_dimensions() ;

   elem.resize( r * c, fill ) ;
}

void MyMatrix::set_element( const Uint i, const Uint j, const float v )
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

   // [ cccc
   //   cccc
   //   cccc ]
   elem[ pos(i, j) ] = v ;
}

float MyMatrix::get_element( const Uint i, const Uint j ) const
{
   if ( i >= r || j >= c )
   {
      std::string s = 
                      std::string( "i = " ) + std::to_string( i )
                    + std::string( ", j = " ) + std::to_string( j ),
                    + std::string( "; r = " ) + std::to_string( r )
                    + std::string( ", c = " ) + std::to_string( c ) ;

      throw std::out_of_range( s ) ;
   }

   return elem[ pos( i, j ) ] ;
}

void MyMatrix::output( const std::string filename ) const
{
   std::ofstream out( filename ) ;

   for ( Uint i = 0 ; i < r ; i++ )
   {
      for ( Uint j = 0 ; j < c ; j++ )
      {
         out << elem[ pos( i, j ) ] << " " ;
      }

      out << std::endl ;
   }

   // destructor will close the file.
}
