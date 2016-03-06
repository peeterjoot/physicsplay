/** \file myexception.h
 */
#if !defined phy1610_myexception_h_included
#define phy1610_myexception_h_included

#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <string>

struct error : virtual std::exception, virtual boost::exception { } ;
struct regex_match_error : virtual error { } ;

struct tag_match_input ;
typedef boost::error_info<tag_match_input,std::string> match_info ;

struct tag_match_re ;
typedef boost::error_info<tag_match_re,std::string> re_info ;

#endif
