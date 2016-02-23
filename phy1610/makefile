SUBMAKES += $(shell find -name GNUmakefile)
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

PS5 += ps5.git.log
PS5 += inc/boosttest.h
PS5 += inc/integers.h
PS5 += ps5/description.txt
#PS5 += ps5/Doxyfile
PS5 += ps5/GNUmakefile
PS5 += $(wildcard ps5/*.cc ps5/*.h)
#PS5 += ps4.sh
#PS5 += README.ps5.txt
#PS5 += scinet.env.ps5

TICKTOCK := $(HOME)/ticktock

all : ps3/ticktock.cc

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

$(TICKTOCK) : 
	(cd ; git clone https://github.com/vanzonr/ticktock.git)

ps3/ticktock.cc : $(TICKTOCK)/ticktock.cc
	cp $^ $@

clean:
	$(foreach dir,$(SUBDIRS),make -C $(dir) clean;)

subdirs:
	$(foreach dir,$(SUBDIRS),make -C $(dir);)
