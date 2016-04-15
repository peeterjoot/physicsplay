Results:

1) Times required for ASCII vs NETCDF:

Here's the timing data from a run on a 4x8 node queue submission:

   ascii 1  31.1333
   ascii 2  16.4453
   ascii 4  9.92022
   ascii 8  6.91076
   ascii 16 4.36198
   ascii 32 3.69546
   netcdf   1  3.20788
   netcdf   2  4.11547
   netcdf   4  4.20569
   netcdf   8  5.26298
   netcdf   16 218.35
   netcdf   32 419.811

As the number of nodes is increased the time required to do the IO in the
ascii configuration gets lower and lower.  This makes some sense since
each MPI task has to write considerably less data, and all such tasks
are writing to seperate files.

Observe that the netcdf time at 'mpirun -n 1' compared to the ascii time for
the same configuration is close to 10x faster.

The netcdf time is roughly maintained at the same levels while the MPI size <
8.  For the couple larger MPI size values measured, the time required goes off
the scale.  My guess is that we end up with cross machine file locking issues
with all the MPI tasks contending for some resource (perhaps a file lock) in
the netcdf stack.

2) File sizes:

From the same run, the ascii file size is 5.3x bigger:

   -rw-r--r-- 1 peeterj triverio 412629544 Apr 14 22:26 aggregate.out.1
   -rw-r--r-- 1 peeterj triverio  78232812 Apr 14 22:39 dataFilename.nc

This size difference is made worse by the particular form of the ascii IO that I used:

   0 1 -26 0
   0 2 -25.99 0
   0 3 -25.98 0
   0 4 -25.97 0
   0 5 -25.96 0
   0 6 -25.95 0
   ...

These are, respectively: timestep sequence number, global domain index,
x-value at that index, and rho-value at that index.  This format was chosen
so that with MPI sizes > 1, the ascii files could be cat'ted to recover an
equivalent to the MPI size=1 data.

Description of files in the ps11.tar.gz file:
======================================================================================
README.ps11.txt

   This file.

ps10/timeAsciiVsNetcdfIO

   This is a script that was used both for collecting the time data to compare
   the ascii vs. netcdf IO times, but also to check that the same results 
   were produced for the netcdfIO and asciiIO modes.

   Here's an example of check mode output:

      $ ./timeAsciiVsNetcdfIO -tmin 1 -tmax 2 -quick -check
      # rm -f dataFilename*out
      # mpirun -n 1 ./wave1d ./waveparamsPs10.txt 2>&1 | grep Walltime | sort -k3 -n | tail -1
      # cat dataFilename*out | grep -v '#' | sort -k1 -n -t' ' -k2 -n -t' ' > aggregate.out.1
      ascii,1,0.922104,5106344
      # rm -f dataFilename*out
      # mpirun -n 1
      # ./wave1d ./waveparamsPs10nc.txt 2>&1 | grep Walltime | sort -k3 -n | tail -1
      #  ./readwavenc -f dataFilename.nc > netcdf.out.1
      netcdf,1,0.528641,1095008
      # diff -up aggregate.out.1 netcdf.out.1
      # rm -f dataFilename*out
      # mpirun -n 2
      # ./wave1d ./waveparamsPs10.txt 2>&1 | grep Walltime | sort -k3 -n | tail -1
      # cat dataFilename*out | grep -v '#' | sort -k1 -n -t' ' -k2 -n -t' ' >
      # aggregate.out.2
      ascii,2,0.809912,5106344
      # rm -f dataFilename*out
      # mpirun -n 2
      # ./wave1d ./waveparamsPs10nc.txt 2>&1 | grep Walltime | sort -k3 -n | tail -1
      #  ./readwavenc -f dataFilename.nc > netcdf.out.2
      netcdf,2,0.651433,1094924
      # diff -up aggregate.out.2 netcdf.out.2

   A netcdf reader utility is used to dump the .nc file in the same format that the 
   ascii writer uses, and these can then be compared simply.  For mpi sizes > 1,
   the ascii IO data must be sorted to merge all the rows by the timestep sequence
   number (and then by the global index for the rho array).

ps11.git.log

   Git log for this assignment.

ps10/GNUmakefile
make.vars
make.vars.pnetcdf
make.vars.mpi
   makefiles for this assignment.

scinet.env.netcdf.mpi.gcc-520
scinet.env.netcdf.mpi.intel15
scinet.env.netcdf.serial.gcc-481
scinet.env.netcdf.serial.gcc-520
scinet.env.netcdf.serial.intel15
ps10/setup <<< link to scinet.env.netcdf.mpi.gcc-520

   Modified the original hw11/setup to use newer-than gcc-4.8.1 compiler.  My (ps10) code developed on a ubuntu VM (which also supported MPI to my suprise) doesn't compile with that older compiler.  For ps11 this has the modifications to allow allow parallel (+mpi) netcdf.
   
inc/myexceptions.h
   Auxmented relative to ps10 submission with netcdf error classes and throw based assert macros.

ps10/waveparams.txt
   Updated to match the supplied hw11 assignment skeleton.  Uses ascii IO.

ps10/waveparamsnc.txt
   Same as above but using netcdf (parallel) IO.

ps10/waveparamsPs10.txt
ps10/waveparamsPs10nc.txt
   The configuration originally in the hw10 skeleton code (changed in hw11 to output lots more.)

ps10/wave1d.cc

   On top of the ps10 modifications to the supplied 1d solver skeleton code to partition the work into multiple MPI tasks, this
   now also uses the iohandler class to deal with the specific requested IO configuration.

ps11.sh

   qsub script used to test ASCII vs NETCDF IO times for various MPI sizes.

netcdf_c/readfile.cc
netcdf_c/writefile.cc
netcdf_c/writefilep.cc
netcdf_c/GNUmakefile
netcdf_c/testwritep.sh
   Standalone code to read and write and (parallel) write stuff into a netcdf file.
   This writes data that's much like the wave1d data to be written (i.e.
   unlimited time dimension, fixed spatial dimension, 1d grid variables (x), and
   a data variable to be written at multiple timesteps.)

inc/mpitask.h
ps10/mpitask.cc
   A small OO wrapper for the MPI init/finalize calls that get the size/rank
   and free mpi resources before exit.

inc/physicsplay_build_version.h
   last commit into to write to an attribute (as recommended in previous
   scinet course where the C++ API was discussed).

ps10/readwavenc.cc
   This is a netcdf reading utility that reads the format that wave1d outputs (in netcdf mode),
   and spits it back out again in ascii format like wave1d outputs in ascii mode.

ps10/writefilep.cc
   This is a standalone test driver written to try to isolate the issue
   described in:
         https://support.scinet.utoronto.ca/education/go.php/218/forums/forum/view.php/fid/6/pid/336/
   The times array output was found to be the culprit.

ps10/iotest.cc
   This was a manual unit test driver to call iohandler in each of the
   possible modes (graphics, ascii, netcdf).  Invoke it using mpirun.

inc/returncodes.h
inc/stdoutfilestream.h
ps7/streamopen.cc
   Recycled from previous assignments unchanged.

ps10/iohandler.h
ps10/iohandler.cc
ps10/asciiIO.h
ps10/asciiIO.cc
ps10/graphicsIO.h
ps10/graphicsIO.cc
ps10/netcdfIO.h
ps10/netcdfIO.cc
   The iohandler class abstract the output performed by the original wave1d code (graphics vs. ascii).
   The speicific IO methods are handled by some virtual class implementations, with netcdfIO.h/.cc 
   providing parallel .nc writer capability.

#--------------------------------------
# stuff unchanged (or mostly unchanged) since ps10 submission:

make.rules
make.vars.boosttest
make.vars.rarray
   makefiles for this assignment.

ps10/ticktock.h
ps10/inifile.h
ps10/ticktock.cc

   These are unchanged from the skeleton code supplied for this assignment.

inc/boosttest.h
inc/farray.h
   Helper headers common with previous assignments.

ps10/waveparamsg.txt
   graphics only for rank=0 mpi task.  Used for debugging (where I varied which of the MPI rank local domain results got displayed).

inc/rangePartition.h
ps10/rangePartition.cc
ps10/test.cc

   A helper class (and boost tests) to divide up a global domain range of indexes in [1,N] into per-mpi task partitions.

   This includes a method to return the local domain index from a global domain index that falls into
   the range of this mpi tasks' partition.

   Includes a method to return the local domain subset of a global domain index range if any of that range
   falls into the mpi tasks' partition (or an empty set).

ps10/leftright.cc

   standalone mpi experimentation code.

ps10/nocycle.cc

   standalone mpi experimentation code.

ps10/sendAndRecieveGhostCells.h
ps10/sendAndRecieveGhostCells.cc

   Standalone function to send and recieve the ghost cells.


ps10/ghosts.cc
ps10/testsendrecvghosts.sh

   Test driver for sendAndRecieveGhostCells()

ps10/compareoutput.sh
   A script used to numerically compare the size=1 output for the zeroth timestep to that of size=2,5,10.
   Was also used to do the same for the pre-timestep local partitioning of the density (rho) and grid array (x).

ps10/timeem.csv
ps10/minTimeVsParallelism.csv
   Raw results from the qsub run.

ps10/plotem.jl
   Plot the .csv results above (in terms of time and in terms of scaling).

ps10/ps10.tex
   Scaling discussion source text.  See ps10.pdf

ps10/timeem.pl

   A small driver for running and collecting scaling data for various numbers of mpi tasks (up to 32, running on 4 nodes).

ps10/waveparamsnoio.txt
   d=0.01 but without graphics and IO enabled.  This was used for testing the ps10 qsub batch script before queuing it on the production nodes.

ps10/wavescalingtestparams.txt
   d=0.002 configurations (without graphics and without IO enabled).  This was used for the final ps10 scaling mesaurements submitted on a four node cluster.

ps10.sh

   qsub script used to test scaling.


