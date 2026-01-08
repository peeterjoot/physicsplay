#include <cstdint>

// sample: forward reference enum class with type:
enum class Bar : uint8_t;

bool foo( Bar b );

enum class Bar : uint8_t
{
    x,
    y,
    z
};

bool foo( Bar b )
{
    return b == Bar::x;
}
