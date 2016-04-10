README.ps11.txt

   This file.

ps11.git.log

   Git log for this assignment.

ps10/GNUmakefile
make.rules
make.vars
make.vars.boosttest
make.vars.rarray
make.vars.pnetcdf
make.vars.mpi

   makefiles for this assignment.

ps10/ticktock.h
ps10/inifile.h
ps10/ticktock.cc

   These are unchanged from the skeleton code supplied for this assignment.

scinet.env.netcdf.mpi.gcc-520

   Modified the original hw11/setup to use newer than gcc 4.8.1 compiler.  My (ps10) code developed on a ubuntu VM (which also supported MPI to my suprise) doesn't compile with that older compiler.  For ps11 this has the modifications to allow allow parallel (+mpi) netcdf.
   
inc/boosttest.h
inc/farray.h
inc/myexceptions.h

   Helper headers common with previous assignments.

ps10/waveparams.txt
   Modified for no graphics.   

ps10/waveparamsg.txt
   graphics only for rank=0 mpi task.  Used for debugging (where I varied which of the MPI rank local domain results got displayed).

ps10/waveparamsnoio.txt
   d=0.01 but without graphics and IO enabled.  This was used for testing the qsub batch script before queuing it on the production nodes.

ps10/wavescalingtestparams.txt
   d=0.002 configurations (without graphics and without IO enabled).  This was used for the final scaling mesaurements submitted on a four node cluster.

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

ps10/wave1d.cc

   Modifications to the supplied 1d solver skeleton code to partition the work into multiple MPI tasks.

ps10.sh

   qsub script used to test scaling.

#--------------------------------------
# stuff that was strictly for ps10:

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

