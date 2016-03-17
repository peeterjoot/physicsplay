// 
// walkring_output.h
//
// Module for output for 1d random walk on a ring
//
#ifndef WALKRINGOUTPUTH
#define WALKRINGOUTPUTH

#include <fstream>
#include <rarray>

// Setup output into a file of file name datafilename.
// A header will be written to screen as well.
// Arguments:
//   file: the file object to use to open a file
//   datafilename: name of the file to open
void output_init(std::ofstream& file, std::string datafilename);

// Output into a file of file name datafilename. There will be other
// output to screen as well, such as a little histogram of where the
// walkers are.
// Arguments:
//   file:        the file object to use
//   step:        number of the current time step
//   time:        current value of the time
//   N:           number of grid points
//   w:           position of the walkers
//   outputcols:  width of the output graph.
void output(std::ofstream& file, int step, double time, int N, const rarray<int,1> &w, int outputcols);

// Finalize output.
// Arguments:
//   file: the file object that was used
void output_finish(std::ofstream& file);

#endif

