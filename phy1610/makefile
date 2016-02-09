PS3 += git.log
PS3 += inc/boosttest.h
PS3 += inc/integers.h
PS3 += inc/myrarray2.h
PS3 += inc/optticktock.h
PS3 += ps3/ants.cc
PS3 += ps3/ants_on_table.cc
PS3 += ps3/ants_on_table.h
PS3 += ps2/ants.out.default
PS3 += ps3/description.txt
PS3 += ps3/Doxyfile
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

TICKTOCK := $(HOME)/ticktock

all : ps3/ticktock.cc

ps4.tar.gz : $(PS3) makefile
	rm -f $@
	tar zcf $@ $(PS3) ants.batch.2016-02-04-*/*

git.log : 
	git log --stat inc ps2 ps3 > $@

$(TICKTOCK) : 
	(cd ; git clone https://github.com/vanzonr/ticktock.git)

ps3/ticktock.cc : $(TICKTOCK)/ticktock.cc
	cp $^ $@
