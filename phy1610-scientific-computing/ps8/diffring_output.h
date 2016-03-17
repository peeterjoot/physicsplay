// 
// diffring_output.h
//
// Module for output for 1d diffusion on a ring
//
#ifndef DIFFRINGOUTPUTH
#define DIFFRINGOUTPUTH

#include <fstream>
#include <rarray>

// Setup output into a file of file name datafilename.
// A header will be written to screen as well.
// Arguments:
//   file: the file object to use to open a file
//   datafilename: name of the file to open
void output_init(std::ofstream& file, std::string datafilename);

// Output into a file of file name datafilename. There will be other
// output to screen as well, such as a little graph of the density.
// Arguments:
//   file:        the file object to use
//   step:        number of the current time step
//   time:        current value of the time
//   P:           density array
//   outputcols:  width of the output graph.
void output(std::ofstream& file, int step, double time, const rarray<double,1> &P, int outputcols);

// Finalize output.
// Arguments:
//   file: the file object that was used
void output_finish(std::ofstream& file);

#endif

