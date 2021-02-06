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

constexpr int nx{ 20 }, ny{ 15 };
using varType = double;

inline int point( int i, int j ) {
    auto p = i + nx * j;
    assert( p < nx * ny );

    return p;
}

// draw an ellipse.
void setData( varType* dataOut ) {
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

        auto p1 = point( pxp, pyp );
        auto p2 = point( pxp, pym );
        auto p3 = point( pxm, pyp );
        auto p4 = point( pxm, pym );

        dataOut[ p1 ] = 1.0;
        dataOut[ p2 ] = 1.0;
        dataOut[ p3 ] = 1.0;
        dataOut[ p4 ] = 1.0;

#ifdef PRINT_AS_MATHEMATICA
        printf("%s{%g,%g}, {%g,%g}, {%g,%g}, {%g,%g}\n", comma, pxp, pyp, pxp, pym, pxm, pyp, pxm, pym ); 
        comma = ",";
#endif
    }
#ifdef PRINT_AS_MATHEMATICA
    printf( "};\n" );
#endif

#define PRINT_AS_ASCII_ART
#ifdef PRINT_AS_ASCII_ART
    int nl = 0;
    for ( auto i = 0 ; i < nx * ny ; i++ ) {
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
        varType dataOut[nx * ny]{};

        // Create the netCDF file.
        NcFile dataFile( "first.netCDF.nc", NcFile::replace );

        // Create the dimensions.
        auto zDim = dataFile.addDim( "z" );
        auto xDim = dataFile.addDim( "x", nx );
        auto yDim = dataFile.addDim( "y", ny );

        std::vector<NcDim> dims{ zDim, xDim, yDim };

        // Create the data variable.
        auto data = dataFile.addVar( "data", ncDouble, dims );

        // Put the data in the file.
        std::vector<size_t> startp{ 0, 0, 0 };
        std::vector<size_t> countp{ 0, nx, ny };
        std::vector<ptrdiff_t> stridep{ 1, 1, 1 };
        std::vector<ptrdiff_t> imapp{ 1, 1, nx };
//    auto p = i + nx * (j + ny * k);

        const int nz{3};
        setData( dataOut );
        for ( auto k{ 0 }; k < nz; k++ ) {
            startp[0] = k;

            data.putVar( startp, countp, stridep, imapp, dataOut );
        }

        // Add an attribute.
        dataFile.putAtt( "Version info:", PHYSICSPLAY_COMMIT_INFO );
    } catch ( NcException& e ) {
        std::cout << "caught: " << e.what() << "\n";
    }

    return (int)RETURNCODES::SUCCESS;
}
