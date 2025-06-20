#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
//#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <string.h>
#include <iostream>
#include <format>

int main()
{
    const char * s = strerror_r( EINVAL, NULL, 0 );

    std::cout << std::format( "{}: {}\n", EINVAL, s );

    return 0;
}

// vim: et ts=4 sw=4
