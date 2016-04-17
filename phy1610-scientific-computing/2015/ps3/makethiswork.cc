// HW3 Assignment
//
// Compile, link, then run this code with
//     "./makethiswork 100 100 filename"
// to generate a file with a 100x100 array that is filled
// with a gaussian signal.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "MyMatrix.h"

int main(int argc, char* argv[])
{
    if ( argc > 3 )
    {
        // read command line arguments
        int r = atoi(argv[1]) ;
        int c = atoi(argv[2]) ;
        char* filename = argv[3] ;

        // create the 2d array
        std::cout << "Generating a 2d array of " << r << "x" << c << std::endl ;
        MyMatrix a(r,c) ;

        // fill the 2d array
        for ( Uint i{0} ; i < a.get_rows(); i++ )
        {
            for ( Uint j{ 0 } ; j < a.get_columns(); j++ )
            {
                double x = i/float(a.get_rows())-0.5 ;
                double y = j/float(a.get_columns())-0.5; // corrected version: this said "i/float(....) before

                a.set_element(i,j,exp(-(x*x+y*y)/8.0)) ;
            }
        }

        // write the 2d array to file
        a.output(filename) ;

        return 0 ;

    } else {

        // warning message if not enough arguments
        std::cerr << "Not enough arguments. Usage: " << argv[0] << " rows columns filename" << std::endl ;
        return 1 ;

    }
}
