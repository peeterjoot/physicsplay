THISDIR := ece1254

include ../make.bookvars

INCOMPLETE += multiphysicsProblemSet1Problem1.tex
INCOMPLETE += multiphysicsProblemSet1Problem2.tex
INCOMPLETE += multiphysicsProblemSet1Problem3.tex
INCOMPLETE += multiphysicsProblemSet2aProblem1.tex

#ONCEFLAGS := -justonce

SOURCE_DIRS += appendix
# FIXME:
# 1) including this incorrectly adds figures/*pdf to the ./.gitignore file
# 2) also not seeing this result in figure dependencies. touch figures/etalonFig1.pdf
FIGURES := ../../figures/$(THISDIR)
SOURCE_DIRS += $(FIGURES)

COPIED_FILES += ./macros_bm.sty

# also toggle redacted classicthesis-config.tex
# FIXME: changing this flag should be a dependency of mathematica.tex 
#REDACTED := -redacted

GENERATED_SOURCES += mathematica.tex 

EPS_FILES := $(wildcard $(FIGURES)/*.eps)
PDFS_FROM_EPS := $(subst eps,pdf,$(EPS_FILES))

THISBOOK_DEPS += $(PDFS_FROM_EPS)

include ../make.rules

multiphysicsProblemSet1.pdf :: multiphysicsProblemSet1Problem1.tex
multiphysicsProblemSet1.pdf :: multiphysicsProblemSet1Problem2.tex
multiphysicsProblemSet1.pdf :: multiphysicsProblemSet1Problem3.tex

multiphysicsProblemSet2a.pdf : multiphysicsProblemSet2aProblem1.tex
multiphysicsProblemSet2a.pdf : ../ece1254/conjugateGradientAlgorithm.tex
multiphysicsProblemSet2a.pdf : ../ece1254/simpleNortonEquivalents.tex

multiphysicsProblemSet1.pdf :: $(PDF_DEPS)
