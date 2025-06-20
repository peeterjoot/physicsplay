#include <unistd.h>
#include <thread>
#include <atomic>
#include <iostream>
#include <format>

std::atomic<int> done{};

void poller()
{
    int i{};

    while ( !done )
    {
        if ( 0 == (i % 100) )
        {
            std::cout << std::format( "{}\n", i );
        }
        i++;
        usleep( 10000 );
    }
}

int main()
{
    std::thread t(poller);

    // ten seconds polling time, 10ms sleep per interval:
    for ( int i = 0 ; i < 1000 ; i++ )
    {
        usleep( 10000 );
    }
    done = 1;

    t.join();

    return 0;
}

// vim: et ts=4 sw=4
