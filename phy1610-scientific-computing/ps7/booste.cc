/**
   \file booste.cc

   Experiment with boost exceptions.
 */
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <regex>
#include <iostream>

struct error : virtual std::exception, virtual boost::exception { } ;
struct regex_match_error : virtual error { } ;

struct tag_match_input ;
typedef boost::error_info<tag_match_input,std::string> match_info ;

struct tag_match_re ;
typedef boost::error_info<tag_match_re,std::string> re_info ;

int main()
{
   try {
       std::string s{"alja"} ;
       std::regex r{"blah"} ;

       BOOST_THROW_EXCEPTION(
            regex_match_error() 
               << match_info( s )
               << re_info( "blah" )
            ) ;
   } 
   catch ( boost::exception & e )
   {
      if ( auto * i { boost::get_error_info<match_info>(e) } ) 
      {
         std::cout << "match pattern: " << *i << std::endl ;
      }

      if ( auto * i { boost::get_error_info<re_info>(e) } ) 
      {
         std::cout << "match re: " << *i << std::endl ;
      }

      auto s { boost::diagnostic_information( e ) } ;
      std::cout << s << std::endl ;
   }

   return 0 ;
}
