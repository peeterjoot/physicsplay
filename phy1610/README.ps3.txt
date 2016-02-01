-----------------------------------------
Setup:

All commands should be run from ./ps3/.

It has been assumed that the following has been run as prep for build:

   (cd ; git clone git@github.com:vanzonr/rarray ; git clone https://github.com/vanzonr/ticktock.git)

-----------------------------------------
Part 1)

   See: ps3/runreport.txt for results from time, tick-tock, and gprof runs.

   a) For no tick-tock and no gprof instrumentation run:

      make clean origants ants

   b) tick-tocks:

      USETICKTOCK=1 make clean origants ants
      ./tickSamples

      to get tick/tock results and a comparision of times spent in each of the interesting looking timestep codepaths.

      Note that USETICKTOCK=1 sets the number of timesteps to 400 instead of 40.

   b) For gprof run:

      PROFILED=1 make clean profile.orig.txt profile.mine.txt

      Note that PROFILED=1, like USETICKTOCK=1, sets the number of timesteps to 400 instead of 40 for a better distributed
      set of profile sampling points.

-----------------------------------------
Part 2)
