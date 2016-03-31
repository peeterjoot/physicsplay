README.ps9.txt
   This file.

hw9/inifile.h
hw9/ticktock.h
hw9/ticktock.cc
   original supplied files.   

hw9/setup
   Tweaked to deal with malfunctioning default gdb

make.*
hw9/GNUmakefile
   Tweaked for consistency with my other phy1610 submissions.

hw9/wave1d.cc
   with parallization
   
hw9/waveparams.txt
   config parameters (modified to remove graphics)

hw9/waveparamsp.txt
   config file with parallel io enabled, graphics disabled.
   
hw9/part1.sh
   simple script for part1.  compare basic parallelization results.

hw9/oneThreadRegressionCheck.sh
   regression test: compare single-threaded output against results from that of ../hw9-dist/wave1d

hw9/part2.pl
   collect timings varing number of threads.
   
ps9.git.log
   git log for assignment changes.

ps9.sh
   qsub script to collect timing info.  Runs hw9/part2.pl a few times on a non-devel node.

TODO:
   Report: part2.ods:

   # without optimization:
   outtime=1 3.84x scaling
   outtime=10 5.98x scaling
   outtime=20 6.23x scaling

   # with optimization:
   3x max scaling without parallel IO.
