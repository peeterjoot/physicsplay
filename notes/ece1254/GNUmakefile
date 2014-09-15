THISDIR := ece1254

include ../make.bookvars

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

#condensedMatterProblemSet1.pdf :: condensedMatterProblemSet1Problem1.tex
#condensedMatterProblemSet1.pdf :: condensedMatterProblemSet1Problem2.tex
#condensedMatterProblemSet1.pdf :: condensedMatterProblemSet1Problem3.tex
#
#condensedMatterProblemSet1.pdf :: $(PDF_DEPS)
