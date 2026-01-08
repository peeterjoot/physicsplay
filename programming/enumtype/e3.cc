#include <cstdint>

// sample: forward reference enum class (without type -- didn't know that worked)
enum class Bar;

bool foo( Bar b );

enum class Bar
{
    x,
    y,
    z
};

bool foo( Bar b )
{
    return b == Bar::x;
}
