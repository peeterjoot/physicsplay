/** \file myexception.h

   Define some boost exception tags and exception types.
 */
#if !defined phy1610_myexception_h_included
#define phy1610_myexception_h_included

#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <string>

struct error : virtual std::exception, virtual boost::exception { } ;
struct regex_match_error : virtual error { } ;
struct file_open_error : virtual error { } ;
struct plan_create_error : virtual error { } ;
struct array_size_error : virtual error { } ;

struct tag_match_input ;
typedef boost::error_info<tag_match_input,std::string> match_info ;

struct tag_match_re ;
typedef boost::error_info<tag_match_re,std::string> re_info ;

struct tag_open_error ;
typedef boost::error_info<tag_open_error,const char *> open_info ;

struct tag_open_error_origin ;
typedef boost::error_info<tag_open_error_origin,std::string> name_info ;

struct tag_array_size_mismatch ;
typedef boost::error_info<tag_array_size_mismatch,size_t> asize_info ;

#endif
