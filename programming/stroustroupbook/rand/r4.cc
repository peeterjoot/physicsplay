#include <random>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <stdio.h>

/** bind uniform_int_distribution */
template <unsigned long a, unsigned long b>
class RandomIntegersUL {
    decltype( std::default_random_engine() ) m_device{
        std::default_random_engine()};
    std::mt19937 m_engine;
    std::uniform_int_distribution<unsigned long> m_uniform{a, b};

   public:
    /** constuct a uniform random number generator for the specified range */
    RandomIntegersUL() : m_engine( m_device() ) {
    }

    unsigned long operator()() {
        return m_uniform( m_engine );
    }
};

/** bind uniform_int_distribution */
template <int a, int b>
class RandomIntegersI {
    decltype( std::default_random_engine() ) m_device{
        std::default_random_engine()};
    std::mt19937 m_engine;
    std::uniform_int_distribution<int> m_uniform{a, b};

   public:
    /** constuct a uniform random number generator for the specified range */
    RandomIntegersI() : m_engine( m_device() ) {
    }

    int operator()() {
        return m_uniform( m_engine );
    }
};

#define DOUBLE_TYPE_MANTISSA_BITS 56
#define DOUBLE_TYPE_EXP_BITS 7

#define MIN_DOUBLE_EXP 1
#define MAX_DOUBLE_EXP ( ( 1 << DOUBLE_TYPE_EXP_BITS ) - 1 )

#define MIN_DOUBLE_MANTISSA 1ul
#define MAX_DOUBLE_MANTISSA ( ( 1ul << DOUBLE_TYPE_MANTISSA_BITS ) - 1 )

#define NUM_EXP 10
#define NUM_MANT 20

int main() {
    RandomIntegersI<MAX_DOUBLE_EXP/2 - 5, MAX_DOUBLE_EXP/2 + 5> re;
    RandomIntegersUL<MIN_DOUBLE_MANTISSA, MAX_DOUBLE_MANTISSA> rm;

    std::vector<unsigned long> exponents;
    std::vector<unsigned long> mantissas;

    exponents.reserve( NUM_EXP );
    mantissas.reserve( NUM_MANT );

    for ( int i = 0; i < NUM_EXP; i++ ) {
        unsigned long v = re();

        exponents.push_back( v );

//        printf( "e: 0x%02lX\n", v );
    }

    for ( int i = 0; i < NUM_MANT; i++ ) {
        unsigned long v = rm();

        mantissas.push_back( v );

//        printf( "m: 0x%016lX\n", v );
    }

    for ( unsigned long s = 0; s < 2; s++ ) {
        unsigned long signbit = s << ( DOUBLE_TYPE_EXP_BITS + DOUBLE_TYPE_MANTISSA_BITS );

        for ( auto e : exponents ) {
            unsigned long sign_and_exp = signbit | (e << DOUBLE_TYPE_MANTISSA_BITS);

            for ( auto m : mantissas ) {

                printf( "   ,0x%016lXuLL\n", sign_and_exp | m );
            }
        }
    }

    return 0;
}
