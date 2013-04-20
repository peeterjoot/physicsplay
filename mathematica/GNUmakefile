PACKAGES := $(wildcard *.m)
PACKAGEDIR := /cygdrive/c/Users/Peeter

files := $(foreach file,$(PACKAGES),$(PACKAGEDIR)/$(file))

all : $(files)
# echo $(files)

$(PACKAGEDIR)/%.m : %.m
	cp $< $@
