#include <iostream>
#include <vector>
#include <string>

template <unsigned r, unsigned c>
class m
{
    std::vector<double> mat ;

public:
    class bad_init {} ;
    
    m() : mat(r*c) {}

    m( std::initializer_list<double> i ) : mat( r * c ) 
    {
        if ( i.size() > ( r * c ) )
        {
            throw bad_init() ;
        }

        int p{} ;
        for ( auto v : i )
        {
            mat[ p++ ] = v ;
        }
    }

    void dump( const std::string & n ) const
    {
        const char * sep = ": " ;
        std::cout << n ;

        for ( auto v : mat )
        {
            std::cout << sep << v ;
            sep = ", " ;
        }

        std::cout << '\n' ;
    }
} ;

int main()
{
    m< 3, 2 > v1 ;
    m< 3, 2 > v2{ 0., 1., 2., 3., 4. } ;

    v1.dump( "v1" ) ;
    v2.dump( "v2" ) ;

    m< 3, 2 > v3{ 0., 1., 2., 3., 4., 5., 6., 7. } ;

    return 0 ;
}