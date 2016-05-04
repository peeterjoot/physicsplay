SUBMAKES += $(shell find . -name GNUmakefile)
SUBDIRS := $(subst /GNUmakefile,,$(SUBMAKES))

PS3 += ps3.git.log
PS3 += inc/boosttest.h
PS3 += inc/integers.h
PS3 += inc/myrarray2.h
PS3 += inc/optticktock.h
PS3 += ps3/ants.cc
PS3 += ps3/ants_on_table.cc
PS3 += ps3/ants_on_table.h
PS3 += ps2/ants.out.default
PS3 += ps3/description.txt
#PS3 += ps3/Doxyfile
PS3 += ps3/GNUmakefile
PS3 += ps3/initialize.cc
PS3 += ps3/origants.cc
PS3 += ps3/output.cc
PS3 += ps3/runreport.txt
PS3 += ps3/testdriver.cc
PS3 += ps3/tickSamples
PS3 += ps3/ticktock.cc
PS3 += ps3/timestep.cc
PS3 += ps4.sh
PS3 += README.ps3.txt
PS3 += scinet.env.ps2_3

PS5 += $(wildcard ps5/*.cc ps5/*.h ps5/*.jl ps5/*.pdf)
PS5 += ps5/GNUmakefile
PS5 += make.vars
PS5 += make.rules
PS5 += ps5/x.out
PS5 += inc/integers.h
PS5 += inc/stdoutfilestream.h
PS5 += inc/gslhelper.h
PS5 += README.ps5.txt
PS5 += ps5.git.log

PS7 += scinet.env.ps7
PS7 += README.ps7.txt
PS7 += ps7/GNUmakefile
PS7 += make.vars
PS7 += make.vars.*
PS7 += make.rules
PS7 += ps7/dotprod.cc
PS7 += ps7/fftstate.cc
PS7 += ps7/grav.cc
PS7 += inc/ticks.h
PS7 += inc/cpplevel.h
PS7 += inc/boosttest.h
PS7 += inc/integers.h
PS7 += inc/myexceptions.h
PS7 += inc/returncodes.h
PS7 += inc/stdoutfilestream.h
PS7 += inc/swapFileNameSuffix.h
PS7 += inc/carray.h
PS7 += inc/darray.h
PS7 += ps7/ratData.cc
PS7 += ps7/ratToCsv.cc
PS7 += ps7/streamopen.cc
PS7 += ps7/swapFileNameSuffix.cc
PS7 += ps7/test.cc
PS7 += ps7.sh
PS7 += $(wildcard ps7/*.h ps7/*.jl ps7/*.rat)
PS7 += ps7.git.log

PS8 += inc/boosttest.h
PS8 += inc/cpplevel.h
PS8 += inc/darray.h
PS8 += inc/myexceptions.h
PS8 += inc/ticks.h
PS8 += ps8/GNUmakefile
PS8 += make.rules
PS8 += make.vars
PS8 += make.vars.blas
PS8 += make.vars.boosttest
PS8 += make.vars.rarray
PS8 += ps8.git.log
PS8 += ps8.pdf
PS8 += README.ps8.txt
PS8 += $(wildcard ps8/*.h ps8/*.cc ps8/*.ini ps8/*.dat)

PS9 += $(wildcard ps9/*.h ps9/*.cc ps9/wave*.txt ps9/*.sh ps9/*.pl ps9/*.jl ps9/*.csv)
PS9 += make.rules
PS9 += make.vars
PS9 += make.vars.boosttest
PS9 += make.vars.rarray
PS9 += ps9.git.log
PS9 += README.ps9.txt
PS9 += ps9.sh
PS9 += ps9/setup
PS9 += ps9/GNUmakefile
PS9 += inc/boosttest.h
PS9 += inc/integers.h
PS9 += inc/myexceptions.h
PS9 += ps9.pdf

PS10 += $(wildcard ps10/*.h ps10/*.cc ps10/wave*.txt ps10/*.sh ps10/*.pl ps10/*.jl ps10/*.csv)
PS10 += $(wildcard netcdf_c/*.cc netcdf_c/GNUmakefile netcdf_c/*.sh)
PS10 += $(wildcard netcdf_c/*setup)
PS10 += $(wildcard scinet.env.netcdf*)
PS10 += README.ps11.txt
PS10 += ps10/setup
PS10 += inc/boosttest.h
PS10 += inc/farray.h
PS10 += inc/mpitask.h
PS10 += inc/myexceptions.h
PS10 += inc/physicsplay_build_version.h
PS10 += inc/rangePartition.h
PS10 += inc/returncodes.h
PS10 += inc/stdoutfilestream.h
PS10 += make.rules
PS10 += make.vars
PS10 += make.vars.boosttest
PS10 += make.vars.mpi
PS10 += make.vars.pnetcdf
PS10 += make.vars.rarray
PS10 += ps10.sh
PS10 += ps10/GNUmakefile
PS10 += ps11.git.log
PS10 += ps7/streamopen.cc
#PS10 += $(wildcard ps10/*.tex)
#PS10 += ps10.pdf

TICKTOCK := $(HOME)/ticktock

#all : ps3/ticktock.cc
all : ps11.tar.gz

ps10.pdf : ../notes/blogit/ps10.pdf
	cp ../notes/blogit/ps10.pdf .

ps8.pdf : ../notes/blogit/ps8.pdf
	cp ../notes/blogit/ps8.pdf .

ps9.pdf : ../notes/blogit/ps9.pdf
	cp ../notes/blogit/ps9.pdf .

ps11.tar.gz : $(PS10) makefile
	rm -f $@
	tar zcf $@ $(PS10)

ps10.tar.gz : $(PS10) makefile
	rm -f $@
	tar zcf $@ $(PS10)

ps9.tar.gz : $(PS9) makefile
	rm -f $@
	tar zcf $@ $(PS9)

ps8.tar.gz : $(PS8) makefile ps8.pdf
	rm -f $@
	tar zcf $@ $(PS8)

ps7.tar.gz : $(PS7) makefile
	rm -f $@
	tar zcf $@ $(PS7)

ps5.tar.gz : $(PS5) makefile
	rm -f $@
	tar zcf $@ $(PS5)

ps4.tar.gz : $(PS3) makefile
	rm -f $@
	tar zcf $@ $(PS3) ants.batch.2016-02-10-17*/* 

ps3.git.log : 
	git log --stat inc ps2 ps3 > $@

ps5.git.log : 
	git log --stat inc ps5 > $@

ps7.git.log : 
	git log --stat inc ps7 > $@

ps8.git.log : 
	git log --stat inc ps8 > $@

ps9.git.log : 
	git log --stat inc ps9 > $@

ps10.git.log : 
	git log --stat inc ps10 > $@

ps11.git.log : 
	git log --stat inc ps10 netcdf_c > $@

$(TICKTOCK) : 
	(cd ; git clone https://github.com/vanzonr/ticktock.git)

ps3/ticktock.cc : $(TICKTOCK)/ticktock.cc
	cp $^ $@

clean:
	$(foreach dir,$(SUBDIRS),make -C $(dir) clean;)

subdirs:
	$(foreach dir,$(SUBDIRS),echo $(dir) ; make -C $(dir);)
