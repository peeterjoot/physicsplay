PS3 += inc/boosttest.h
PS3 += inc/myrarray2.h
PS3 += inc/optticktock.h
PS3 += ps2/ants.cc
PS3 += ps2/description.txt
PS3 += ps2/ants_on_table.h
PS3 += ps2/ants_on_table.cc
PS3 += ps2/GNUmakefile
PS3 += ps2/ants.out.default
PS3 += ps2/Doxyfile
PS3 += ps3/description.txt
PS3 += ps3/origants.cc
PS3 += ps3/GNUmakefile
PS3 += ps3/runreport.txt
PS3 += ps3/tickSamples
PS3 += ps3/ticktock.cc
PS3 += ps3/testdriver.cc
PS3 += README.ps3.txt
PS3 += git.log

TICKTOCK := $(HOME)/ticktock

all : ps3/ticktock.cc

ps3.tar.gz : $(PS3) makefile
	rm -f $@
	tar zcf $@ $(PS3)

git.log : 
	git log --stat inc ps2 ps3 > $@

$(TICKTOCK) : 
	(cd ; git clone https://github.com/vanzonr/ticktock.git)

ps3/ticktock.cc : $(TICKTOCK)/ticktock.cc
	cp $^ $@
