README.ps10.txt

   This file.

ps10.pdf

   Report.

ps10/GNUmakefile
make.rules
make.vars
make.vars.boosttest
make.vars.rarray

   makefiles for this assignment.

ps10/ticktock.h
ps10/inifile.h
ps10/ticktock.cc

   These are unchanged from the skeleton code supplied for this assignment.

ps10/setup

   Modified to use newer than gcc 4.8.1 compiler.  My code developed on a ubuntu VM doesn't compile with that older compiler.
   
inc/boosttest.h
inc/farray.h
inc/myexceptions.h

   Helper headers common with previous assignments.

ps10/waveparams.txt
   Modified for no graphics.   

ps10/waveparamsg.txt
   graphics only for rank=0 mpi task.

ps10/rangePartition.h
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

ps10/wave1d.cc

   Modifications to the supplied 1d solver skeleton code to partition the work into multiple MPI tasks.

ps10.git.log

   Git log for this assignment.

ps10/compareoutput.sh
   A script used to numerically compare the size=1 output for the zeroth timestep to that of size=2,5,10.
   Was also used to do the same for the pre-timestep local partitioning of the density (rho) and grid array (x).

ps10.sh

   qsub script used to test scaling.
