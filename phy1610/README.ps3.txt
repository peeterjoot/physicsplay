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

   $ make clean test
   ...
   ./testdriver --report_level=detailed
   Running 1 test case...

   Test suite "test" passed with:
     10296 assertions out of 10296 passed
     1 test case out of 1 passed

     Test case "timestep" passed with:
       10296 assertions out of 10296 passed

-----------------------------------------
Part 3) (ps4)

The script:

   ps4.sh

was used to submit a job to run the ants profiling.  For this submission I ran
with increased numbers of ants and number of timesteps:

   ants -t 1000 -n 10000

(1000 timesteps, 10000 initial ants)

The outputs for that can be found in:

   ants.batch.2016-02-04-18:46:27/ants.out
   ants.batch.2016-02-04-18:46:27/profile.rednode.out

To compile on the gpc dev node I ran:

   . ./scinet.env.ps2_3

Then:

   (cd ps3 && make)

or for profiled output:

   (cd ps3 && PROFILED=1 make clean ants origants)

or for tick-tock output:

   (cd ps3 && USETICKTOCK=1 make clean ants origants)


