#include <unistd.h>
#include <thread>
#include <atomic>
#include <iostream>
#include <format>

std::atomic<int> done{};

void poller( volatile int * v )
{
    int i{};

    while ( !done )
    {
        if ( 0 == (i % 100) )
        {
            int sample = *v;
            std::cout << std::format( "{}: {}\n", i, sample );
        }
        i++;
        usleep( 10000 );
    }
}

int main()
{
    int i{};
    std::thread t(poller, static_cast<volatile int *>(&i) );

    // ten seconds polling time, 10ms sleep per interval:
    for ( ; i < 1000 ; i++ )
    {
        usleep( 10000 );
    }
    done = 1;

    t.join();

    return 0;
}

// vim: et ts=4 sw=4
