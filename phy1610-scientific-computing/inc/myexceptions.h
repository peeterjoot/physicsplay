/** \file myexception.h

   Define some boost exception tags and exception types.
 */
#if !defined phy1610_myexception_h_included
#define phy1610_myexception_h_included

#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <string>
#include <unistd.h> // ssize_t

struct error : virtual std::exception, virtual boost::exception { } ;
struct regex_match_error : virtual error { } ;
struct file_open_error : virtual error { } ;
struct file_close_error : virtual error { } ;
struct file_write_error : virtual error { } ;
struct plan_create_error : virtual error { } ;
struct array_size_error : virtual error { } ;
struct array_not_square_error : virtual error { } ;

struct tag_match_input ;
typedef boost::error_info<tag_match_input,std::string> match_info ;

struct tag_match_re ;
typedef boost::error_info<tag_match_re,std::string> re_info ;

struct tag_open_error ;
typedef boost::error_info<tag_open_error,const char *> open_info ;

struct tag_file_descriptor ;
typedef boost::error_info<tag_file_descriptor,int> file_descriptor_info ;

struct tag_open_error_origin ;
typedef boost::error_info<tag_open_error_origin,std::string> name_info ;

struct tag_array_size_mismatch ;
typedef boost::error_info<tag_array_size_mismatch,size_t> asize_info ;

struct tag_write_size ;
typedef boost::error_info<tag_write_size,size_t> write_info ;

struct tag_write_offset ;
typedef boost::error_info<tag_write_offset,off_t> write_offset_info ;

struct tag_write_addr ;
typedef boost::error_info<tag_write_addr,const void *> write_addr_info ;

struct tag_write_result ;
typedef boost::error_info<tag_write_result,ssize_t> write_res_info ;

struct tag_array_numrows ;
typedef boost::error_info<tag_array_numrows,size_t> arows_info ;

struct tag_array_numcolumns ;
typedef boost::error_info<tag_array_numcolumns,size_t> acolumns_info ;

#endif
