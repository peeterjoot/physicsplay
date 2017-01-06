THISDIR := ece1236-microwaves
THISBOOK := ece1236

include ../latex/make.bookvars

#ONCEFLAGS := -justonce

SOURCE_DIRS += appendix
FIGURES := ../../figures/$(THISBOOK)
SOURCE_DIRS += $(FIGURES)

# also toggle redacted classicthesis-config.tex
# FIXME: changing this flag should be a dependency of matlab.tex 
#REDACTED := -redacted

GENERATED_SOURCES += matlab.tex 
GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += julia.tex 

EPS_FILES := $(wildcard $(FIGURES)/*.eps)
PDFS_FROM_EPS := $(subst eps,pdf,$(EPS_FILES))

THISBOOK_DEPS += $(PDFS_FROM_EPS)
#THISBOOK_DEPS += macros_mathematica.sty

include ../latex/make.rules

julia.tex : ../../julia/METADATA
mathematica.tex : ../../mathematica/METADATA
matlab.tex : ../../matlab/METADATA

#uwaves4TransmissionLines.pdf : ../ece1236/uwaves4TransmissionLinesCore.tex
#uwavesDeck5SmithChart.pdf :: ../ece1236/uwavesDeck5SmithChartCore.tex
#uwavesDeck7MultisectionTransformers.pdf : ../ece1236/uwavesDeck7MultisectionTransformersCore.tex

#problemSets :: uwavesproblemSet1.pdf
#
#ps7mathematica.tex : ../METADATA ../../mathematica/METADATA
#	(cd .. ; ./METADATA -mathematica -latex -ece1236 -filter ece1236/ps7/ ) > $@
#
#ps8mathematica.tex : ../METADATA ../../mathematica/METADATA
#	(cd .. ; ./METADATA -mathematica -latex -ece1236 -filter ece1236/ps8/ ) > $@
