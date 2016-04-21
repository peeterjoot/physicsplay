#include <cmath>
#include <iostream>
#include "optticktock.h"

void compute()
{
    int totalGridSize = 356 ;

    // ants walk on a table
    float number_of_ants[totalGridSize][totalGridSize] ;
    float new_number_of_ants[totalGridSize][totalGridSize] ;
    float velocity_of_ants[totalGridSize][totalGridSize] ;
    const int total_ants = 1010; // initial number of ants
    // initialize
    for (int i=0;i<totalGridSize;i++) {
        for (int j=0;j<totalGridSize;j++) {
            velocity_of_ants[i][j] = M_PI*(sin((2*M_PI*(i+j))/(totalGridSize *10))+1) ;
        }
    }
    int n = 0 ;
    float z = 0 ;
    for (int i=0;i<totalGridSize;i++) {
        for (int j=0;j<totalGridSize;j++) {
            number_of_ants[i][j] = 0.0 ;
        }
    }
    while (n < total_ants) {
        for (int i=0;i<totalGridSize;i++) {
            for (int j=0;j<totalGridSize;j++) {
                z += sin(0.3*(i+j)) ;
                if (z>1 and n!=total_ants) {
                    number_of_ants[i][j] += 1 ;
                    n += 1 ;
                }
            }
        }
    }

    TickTockOrNoOp timer ;

    double s_io { 0 } ;
    double s_totants { 0 } ;
    double s_init { 0.0 } ;
    double s_core { 0.0 } ;
    double s_update { 0.0 } ;

#if !defined NUMBER_OF_TIME_INTERVALS
   constexpr int NUMBER_OF_TIME_INTERVALS { 40 } ;
#endif

    // run simulation
    for (int t = 0; t < NUMBER_OF_TIME_INTERVALS; t++) {
timer.tick() ;
        float totants = 0.0 ;
        for (int i=0;i<totalGridSize;i++) {
            for (int j=0;j<totalGridSize;j++) {
                totants += number_of_ants[i][j] ;
            }
        }
s_totants += timer.silent_tock() ;

timer.tick() ;
        std::cout << t<< " " << totants << std::endl ;
s_io += timer.silent_tock() ;

timer.tick() ;
        for (int i=0;i<totalGridSize;i++) {
            for (int j=0;j<totalGridSize;j++) {
                new_number_of_ants[i][j] = 0.0 ;
            }
        }
s_init += timer.silent_tock() ;
timer.tick() ;
        for (int i=0;i<totalGridSize;i++) {
            for (int j=0;j<totalGridSize;j++) {
                int di = 1.9*sin(velocity_of_ants[i][j]) ;
                int dj = 1.9*cos(velocity_of_ants[i][j]) ;
                int i2 = i + di ;
                int j2 = j + dj ;
                // some ants do not walk
                new_number_of_ants[i][j]+=0.8*number_of_ants[i][j] ;
                // the rest of the ants walk, but some fall of the table
                if (i2>=0 and i2<totalGridSize and j2>=0 and j2<totalGridSize) {
                    new_number_of_ants[i2][j2]+=0.2*number_of_ants[i][j] ;
                }
            }
        }
s_core += timer.silent_tock() ;
timer.tick() ;
        for (int i=0;i<totalGridSize;i++) {
            for (int j=0;j<totalGridSize;j++) {
                number_of_ants[i][j] = new_number_of_ants[i][j] ;
                totants += number_of_ants[i][j] ;
            }
        }
s_update += timer.silent_tock() ;
    }

#if defined USE_TICK_TOCK
std::cout << "io time: \t" << s_io << std::endl ;
std::cout << "totants time: \t" << s_totants << std::endl ;
std::cout << "init time: \t" << s_init << std::endl ;
std::cout << "core time: \t" << s_core << std::endl ;
std::cout << "update time: \t" << s_update << std::endl ;
#endif
}

int main()
{
    compute() ;

    return 0 ;
}
