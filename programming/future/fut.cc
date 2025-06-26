#include <future>
#include <iostream>
#include <format>
#include <stdint.h>

uint32_t producer( int v )
{
    return 42 + v;
}

int main()
{
    std::future<uint32_t> fut[2];
    uint32_t v[2];
    uint32_t i{};
    for ( auto & f : fut )
    {
        f = std::async( std::launch::async, producer, i );
        i++;
    }

    i = 0;
    for ( auto & f : fut )
    {
        v[i] = f.get();
        i++;
    }
    std::cout << std::format( "Results: {}, {}\n", v[0], v[1] );

    return 0;
}

