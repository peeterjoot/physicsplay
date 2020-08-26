#include <chrono>
#include <thread>
#include <string>
 
int main( int argc, char ** argv ) {
    using namespace std;
    using namespace std::chrono_literals;

    if ( argc == 2 ) {
        int milli = stoi( argv[1] );
        auto d = std::chrono::milliseconds(milli);
        //auto d = 2s;
        this_thread::sleep_for( d );
    }

    return 0;
}
