/**
   \file MyMatrix.cc

   implementation of non-inline methods for the MyMatrix class.
 */
#include "MyMatrix.h"
#include <string>
#include <stdexcept>

MyMatrix::MyMatrix( const Uint r_, const Uint c_ ) : elem(), r{r_}, c{c_}
{
   if ( 0 == r || 0 == c )
   {
      std::string s = std::string( "r = " ) + std::to_string( r )
                    + std::string( ", c = " ) + std::to_string( c ) ;

      throw std::out_of_range( s ) ;
   }

   elem.resize( r * c ) ;
}

void MyMatrix::set_element( const Uint i, const Uint j, const float v )
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

void MyMatrix::output( const string filename ) const
{
   // fixme: output to file.
   for ( Uint i = 0 ; i < r ; i++ )
   {
      for ( Uint j = 0 ; j < c ; j++ )
      {
         std::cout << get_element( i, j ) << " " ;
      }
      std::cout << std::endl ;
   }
}
