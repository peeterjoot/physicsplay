// badly coupled:
#include "parseoptions.h"
#include "returncodes.h"

#include <assert.h>
#include <netcdf>
#include <cmath>
#include <vector>

#include "integers.h"
#include "physicsplay_build_version.h"

using namespace netCDF;
using namespace netCDF::exceptions;

constexpr int nx{ 20 }, ny{ 15 }, nz{ 3 };
using varType = double;

inline int point( int i, int j, int k ) {
    auto p = i + nx * (j + ny * k);
    assert( p < nx * ny * nz );

    return p;
}

// draw an ellipse.
void setData( varType* dataOut, const int v ) {
    double cx = ( nx - 1.0 ) / 2.0;
    double cy = ( ny - 1.0 ) / 2.0;
    double a = ( nx - 1.5 ) / 2.0;
    double b = ( ny - 1.5 ) / 2.0;

//#define PRINT_AS_MATHEMATICA
#ifdef PRINT_AS_MATHEMATICA
    const char * comma = "a = {";
#endif
    for ( int x = 0 ; x < a ; x++ ) {
        double theta = std::acos(x/a);
        double y = b * std::sin(theta);

        double pxp= std::floor(cx + x);
        double pxm= std::floor(cx - x);
        double pyp= std::floor(cy + y);
        double pym= std::floor(cy - y);

        for ( auto k{ 0 }; k < nz; k++ ) {
            auto p1 = point( pxp, pyp, k );
            auto p2 = point( pxp, pym, k );
            auto p3 = point( pxm, pyp, k );
            auto p4 = point( pxm, pym, k );

            dataOut[ p1 ] = 1.0;
            dataOut[ p2 ] = 1.0;
            dataOut[ p3 ] = 1.0;
            dataOut[ p4 ] = 1.0;

#ifdef PRINT_AS_MATHEMATICA
            printf("%s{%g,%g}, {%g,%g}, {%g,%g}, {%g,%g}\n", comma, pxp, pyp, pxp, pym, pxm, pyp, pxm, pym ); 
            comma = ",";
#endif
        }
    }
#ifdef PRINT_AS_MATHEMATICA
    printf( "};\n" );
#endif

#define PRINT_AS_ASCII_ART
#ifdef PRINT_AS_ASCII_ART
    int nl = 0;
    for ( auto i = 0 ; i < nx * ny * nz ; i++ ) {
        nl++;
        printf( "%c", dataOut[i] ? 'X' : ' ');

        if ( nl == nx ) {
            printf("\n");
            nl = 0;
        }
    }
    printf( "\n" );
#endif
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char** argv ) {
    parseOptions opt( argc, argv );

    try {
        varType dataOut[nx * ny * nz]{};

        // Create the netCDF file.
        NcFile dataFile( "first.netCDF.nc", NcFile::replace );

        // Create the dimensions.
        auto xDim = dataFile.addDim( "x", nx );
        auto yDim = dataFile.addDim( "y", ny );
        auto zDim = dataFile.addDim( "z", nz );

        std::vector<NcDim> dims{ xDim, yDim, zDim };

        // Create the data variable.
        auto data = dataFile.addVar( "data", ncDouble, dims );

        // Put the data in the file.
        std::vector<size_t> startp{ 0, 0, 0 };
        std::vector<size_t> countp{ nx, ny, nz };
        std::vector<ptrdiff_t> stridep{ 1, 1, 1 };
        std::vector<ptrdiff_t> imapp{ 1, nx, nx * ny };
//    auto p = i + nx * (j + ny * k);

        setData( dataOut, 0 );

        data.putVar( startp, countp, stridep, imapp, dataOut );

        // Add an attribute.
        dataFile.putAtt( "Version info:", PHYSICSPLAY_COMMIT_INFO );
    } catch ( NcException& e ) {
        std::cout << "caught: " << e.what() << "\n";
    }

    return (int)RETURNCODES::SUCCESS;
}
