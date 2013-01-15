THISDIR := otherbook

include ../make.vars

ORIG_FIGURE_DIRS += ../classicalmechanics/figures
ORIG_FIGURE_DIRS += ../gabook/figures
ORIG_FIGURE_DIRS += ../calculus

LOCAL_FIGURE_FILES += hoopSpring.png
LOCAL_FIGURE_FILES += parallelogramArea.png
LOCAL_FIGURE_FILES += parameterizedSurface.png
LOCAL_FIGURE_FILES += polarAndSpherical.png
LOCAL_FIGURE_FILES += surface_area_element.png
LOCAL_FIGURE_FILES += volume_element.png

SOURCE_DIRS += appendix
# FIXME:
# 1) including this incorrectly adds figures/*pdf to the ./.gitignore file
# 2) also not seeing this result in figure dependencies. touch figures/etalonFig1.pdf
SOURCE_DIRS += figures
#SOURCE_DIRS += solutions

#GENERATED_SOURCES += mathematica.tex 

include ../make.rules

figures/%.png: %.png
	cp $< $@

vpath %.png $(ORIG_FIGURE_DIRS)

