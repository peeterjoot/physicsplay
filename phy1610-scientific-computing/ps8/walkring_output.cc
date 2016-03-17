// 
// walkring_output.cc
//
// Module for output for 1d random walk on a ring
//

#include "walkring_output.h"
#include <iostream>
#include <iomanip>
#include <rarrayio>
#include "ticktock.h"
#include "sparkline.h"

static TickTock tt;

void output_init(std::ofstream& file, std::string datafilename)
{
  // Setup output into a file of file name datafilename.
  // A header will be written to screen as well.
  // Arguments:
  //   file: the file object to use to open a file
  //   datafilename: name of the file to open

  file.open(datafilename);
  // Start measuring elapsed time
  tt.tick();
  // Some initial output to screen
  std::cout << "   Step   Time    Walltime(s) Profile"  << std::endl;
}

void output(std::ofstream& file, int step, double time, int N, const rarray<int,1> &w, int outputcols)
{
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

  // First, write the rarray to file
  file << time << "\n" << w << " \n\n";
  // report to screen too
  std::cout << std::fixed << std::setw(7) << step  << " "
            << std::fixed << std::setprecision(4) << std::setw(8) << time << "   "
            << std::fixed << std::setprecision(4) << std::setw(8) << tt.silent_tock() << "   "
            << sparkhist(0, N, w, outputcols, true) << std::endl;
}

// Finalize output
// Arguments:
//   file: the file object that was used
void output_finish(std::ofstream& file)
{
  // Close file
  file.close();
}

