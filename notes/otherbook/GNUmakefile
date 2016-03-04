THISDIR := otherbook
THISBOOK := $(THISDIR)

include ../make.bookvars

FIGURES := ../../figures/$(THISBOOK)

ORIG_FIGURE_DIRS += ../../figures/classicalmechanics
ORIG_FIGURE_DIRS += ../../figures/gabook

#LOCAL_FIGURE_FILES += hoopSpring.png
#LOCAL_FIGURE_FILES += parallelogramArea.png

SOURCE_DIRS += appendix
SOURCE_DIRS += $(FIGURES)
#SOURCE_DIRS += solutions

#GENERATED_SOURCES += mathematica.tex 

include ../make.rules

figures/%.png: %.png
	cp $< $@

vpath %.png $(ORIG_FIGURE_DIRS)

