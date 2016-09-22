THISDIR := ece1228-electromagnetic-theory
THISBOOK := ece1228

include ../make.bookvars

#ONCEFLAGS := -justonce

SOURCE_DIRS += appendix
FIGURES := ../../figures/$(THISBOOK)
SOURCE_DIRS += $(FIGURES)

# also toggle redacted classicthesis-config.tex
# FIXME: changing this flag should be a dependency of matlab.tex 
#REDACTED := -redacted

#GENERATED_SOURCES += matlab.tex 
#GENERATED_SOURCES += mathematica.tex 
#GENERATED_SOURCES += julia.tex 

EPS_FILES := $(wildcard $(FIGURES)/*.eps)
PDFS_FROM_EPS := $(subst eps,pdf,$(EPS_FILES))

THISBOOK_DEPS += $(PDFS_FROM_EPS)
#THISBOOK_DEPS += macros_mathematica.sty

include ../make.rules

l1 : emtLecture1.pdf
l2 : emtLecture2.pdf
l3 : emtLecture3.pdf

julia.tex : ../../julia/METADATA
mathematica.tex : ../../mathematica/METADATA
matlab.tex : ../../matlab/METADATA
