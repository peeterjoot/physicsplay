/** \file bassert.cc */
#include <boost/exception/diagnostic_information.hpp>
#include "myexceptions.h"
#include <iostream>

void foo( int x ) ;

int main( int argc, char ** argv )
try 
{
    auto expected{7} ;

    ASSERT_DATA_INT_INT( argc == expected, argc, expected ) ;

    foo( expected ) ;
    #if 0
    ::boost::exception_detail::throw_exception_(
    assert_error() 
        << intdata_info( argc ) 
        << intdata2_info( expected )
    ,__PRETTY_FUNCTION__,"bassert.cc",11) ;
    #endif

    return 0 ;
}
catch ( boost::exception & e )
{
    auto s { boost::diagnostic_information( e ) } ;
    std::cout << s << std::endl ;

    return 1 ;
}

void foo( int x ) {}
