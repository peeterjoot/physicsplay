#include <iostream>
#include <format>
#include <stdlib.h>

// like assert, but always on:
#define VERIFY1(c, d1) \
do { \
    if ( !(c) ) { \
        std::cerr << std::format( "{}:{}:({}): Verify {} failed. DATA: {}\n", __FILE__, __LINE__, __func__, #c, d1 ); \
        abort(); \
    } \
} while( 0 )

#define VERIFY2(c, d1, d2) \
do { \
    if ( !(c) ) { \
        std::cerr << std::format( "{}:{}:({}): Verify {} failed. DATA: {}, {}\n", __FILE__, __LINE__, __func__, #c, d1, d2 ); \
        abort(); \
    } \
} while( 0 )

int main( int argc, char ** argv )
{
    int i = 6;
    int j = 7;
    VERIFY1( i == 6, i );
    VERIFY2( i*j == 42, i, j );

    if ( argc == 1 )
    {
        std::cout << "VERIFY1: expect abort\n";
        VERIFY1( i == 5, i );
    }
    else
    {
        std::cout << "VERIFY2: expect abort\n";
        VERIFY2( i == 5, i, j );
    }

    return 0;
}
