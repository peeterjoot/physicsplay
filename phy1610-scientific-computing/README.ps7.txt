- Please submit:

(a)   All source, header and make files:

   README.ps7.txt

      This file.

   scinet.env.ps7

      module load and fftw3 env hacking to run this code on a scinet node.

   ps7/GNUmakefile
   make.vars
   make.rules

      Makefiles.

   ps7/x.rat
   ps7/y.rat
   ps7/correlator.jl

      generate unit test result data for correlator boost unit test.

   ps7/darray.h
   ps7/carray.h
   ps7/dotprod.h
   ps7/ratData.h
   ps7/fftstate.h

      Headers specific to this assignment.

   inc/cpplevel.h
   inc/boosttest.h
   inc/integers.h
   inc/myexceptions.h
   inc/returncodes.h
   inc/stdoutfilestream.h
   inc/swapFileNameSuffix.h
   inc/ticks.h

      Headers common to this assignment and others (or standalone cblas, fft, ... test code not included).

   ps7/dotprod.cc
   ps7/fftstate.cc
   ps7/ratData.cc
   ps7/streamopen.cc
   ps7/swapFileNameSuffix.cc
   ps7/grav.cc

      Sources for the assignment driver.

   ps7/ratToCsv.cc
      
      To output .csv file representations of the .rat files for plotting.

   ps7/test.cc
      
      Boost tests for new utility code.

   ps7/plotem.jl
   ps7/plotpower.jl

      Some (Julia language) plotting scripts used in develoment.  Note that the frequency domain output of detection01.rat and the predicted
      signals look rect() like (i.e. perhaps sinc() like time domain signal once the noise is stripped away).

   ps7.sh

      scinet batch script.

(b)
   ps7.git.log

      The output of 'git log' from the development of your codes.

(*)

   Note that I put the data files here for easy multimachine access (i.e. my ubuntu VM and/or scinet)

      git@github.com:peeterjoot/gravitationalwaves.git

   and cloned that to ~/gravitationalwaves/.  The ps7/grad driver once built uses that path by default, but an alterate path may be supplied:

      $ ps7/grav --help
      usage: grav
              [--ratpath=p|-r p] Specify the path for the input .rat files
              [--time|-t] Show elapsed times for component calculations
              [--help]


(c)
The output of your code, ie. the correlation between the predicted waveform and each of the waveforms from the observations set, including 
the results of your analysis, i.e. which are the 5 most significant candidates (those with the 5 largest values of the correlation coefficient) from the observations set.

================================
Correlations by detector filename

detection01.rat 0.939055
detection02.rat 0.887038
detection03.rat 0.749303
detection04.rat 0.612952
detection05.rat 0.552329
detection06.rat 0.433699
detection07.rat 0.340906
detection08.rat 0.287609
detection09.rat 0.324875
detection10.rat 0.432781
detection11.rat 0.527679
detection12.rat 0.639159
detection13.rat 0.744845
detection14.rat 0.859163
detection15.rat 0.967221
detection16.rat 0.071921
detection17.rat 0.896847
detection18.rat 0.87365
detection19.rat 0.727012
detection20.rat 0.99222
detection21.rat 0.529308
detection22.rat 0.406748
detection23.rat 0.335255
detection24.rat 0.27105
detection25.rat 0.345294
detection26.rat 0.436053
detection27.rat 0.528535
detection28.rat 0.629183
detection29.rat 0.730712
detection30.rat 0.652491
detection31.rat 0.435728
detection32.rat 0.320668

Top 5 correlations

detection20.rat 0.99222
detection15.rat 0.967221
detection01.rat 0.939055
detection17.rat 0.896847
detection02.rat 0.887038
================================
With --time (from a scinet batch run)

IO time for .rat reads:                 32382340 (us).
FFT time:                               946092 (us).
Power spectrum calculation time:        141668 (us).
Correlation calculation time:           13910 (us).
