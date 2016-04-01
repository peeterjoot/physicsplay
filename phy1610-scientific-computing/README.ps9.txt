README.ps9.txt
   This file.

ps9.pdf
   Summary report and graphs.

ps9/inifile.h
ps9/ticktock.h
ps9/ticktock.cc
   original supplied files.   

ps9/setup
   Tweaked to deal with malfunctioning default gdb

make.rules
make.vars
make.vars.boosttest
make.vars.rarray
ps9/GNUmakefile
   Makefile for this assignment.  Not all the make.vars* files here are used for this assignment.

ps9/iometadata.h
   Data structure that describes the fixed part of the metadata layout.

ps9/arrayIOwriter.cc
ps9/arrayIOwriter.h

   Three IO methods are implemented, as specified in the assignment, but have been modified slightly:

   - The IO is split between a metadata file and timestep data file(s)
   - The IO is done in binary mode.
   
   1) IO_method::serial

      Serial IO to a metadata file and a timestep data file.

      The binary format used will contain all the data available in the original text output.  The metadata portion
      of the output contains

         struct metaData
         {
            int nper ;
            int numPoints ;
            float x[numPoints] ;
            float times[] ; 
         } ;

      and the data files are just

         float rho[] 

      values.

      Notes:
      - The original text format also wrote the x[] array each timestep iteration.

   2) IO_method::threaded

      Parallel IO using a single file, but multiple IO writer threads.

   3) IO_method::multifile

      Parallel IO using multiple files where each thread writes at most one array per file.
      These files will be indexed numerically so that the serial IO file data can be recovered
      by cat'ting all the files on the command line.


   these files implement a binary IO data writing 

ps9/readem.h
ps9/readem.cc
   A hacky binary read method that aborts on any error.  Just used for the
   meta-to-text and data-to-text utilities.

ps9/dataToText.cc
ps9/metaToText.cc
   debug utility code to read from the data and meta binary files and dump out text.

ps9/test.cc
   boost test driver for the binary file IO class.

ps9/wave1d.cc
   with parallization
   
ps9/waveparams.txt
   config parameters (modified to remove graphics)

ps9/waveparamst.txt
   config file with thread based parallel io to a single file enabled, graphics disabled.

ps9/waveparamsp.txt
   config file with multifile parallel io enabled, graphics disabled.
   
ps9/part1.sh
   simple script for part1.  compare basic parallelization results.

ps9/oneThreadRegressionCheck.sh
   regression test: compare single-threaded output against results from that of ../ps9-dist/wave1d
   This is no longer valid now that I've switched to binary IO.

ps9/timeem.pl
   collect timings varing number of threads using serial IO, parallel IO, and multifile parallel IO.
   
inc/boosttest.h

   platform helper stuff for boost unittest

inc/integers.h

   Some integer convienience types and macros.

inc/myexceptions.h

   Some boost exception classes and info tag classes for PD data collection.

ps9/part2pivotdata.csv
ps9/part5pivotdata.csv
ps9/plotpart2.jl
ps9/plotpart5m.jl
ps9/plotpart5s.jl
ps9/plotpart5t.jl

   data and scripts for the report plots.

ps9.git.log
   git log for assignment changes.

ps9.sh
   qsub script to collect timing info.  Runs ps9/part2.pl a few times on a non-devel node.

TODO:
   Report: part2.ods:

   # without optimization:
   outtime=1 3.84x scaling
   outtime=10 5.98x scaling
   outtime=20 6.23x scaling

   # with optimization:
   3x max scaling without parallel IO.
