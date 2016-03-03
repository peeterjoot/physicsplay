THISDIR := phy452-basicstatmech

include ../make.bookvars

FIGURES := ../../figures/$(THISDIR)

SOURCE_DIRS += appendix
SOURCE_DIRS += $(FIGURES)
#SOURCE_DIRS += solutions

GENERATED_SOURCES += mathematica.tex 
#GENERATED_PDFS += basicStatMechProblemSet1.pdf
#GENERATED_PDFS += basicStatMechProblemSet2.pdf
#GENERATED_PDFS += basicStatMechProblemSet3.pdf
#GENERATED_PDFS += basicStatMechProblemSet4.pdf
#GENERATED_PDFS += basicStatMechProblemSet5.pdf
#GENERATED_PDFS += basicStatMechProblemSet6.pdf
#GENERATED_PDFS += basicStatMechProblemSet7.pdf
#GENERATED_PDFS += huang93.pdf

HUANG93_DEPS += $(FIGURES)/huang93Fig3.pdf
HUANG93_DEPS += $(FIGURES)/huang93Fig4.pdf
HUANG93_DEPS += $(FIGURES)/huang93Fig2.pdf
HUANG93_DEPS += $(FIGURES)/huang93Fig6.pdf

#THISBOOK_DEPS += $(HUANG93_DEPS)
THISBOOK_DEPS += $(FIGURES)/stirlingErrorFig3.pdf

EPS_FILES := $(wildcard $(FIGURES)/*.eps)
PDFS_FROM_EPS := $(subst eps,pdf,$(EPS_FILES))

THISBOOK_DEPS += $(PDFS_FROM_EPS)

include ../make.rules

basicStatMechProblemSet1.pdf :: basicStatMechProblemSet1Problem1.tex
basicStatMechProblemSet1.pdf :: basicStatMechProblemSet1Problem2.tex

basicStatMechProblemSet2.pdf :: basicStatMechProblemSet2Problem1.tex
basicStatMechProblemSet2.pdf :: basicStatMechProblemSet2Problem2.tex

basicStatMechProblemSet3.pdf :: basicStatMechProblemSet3Problem1.tex
basicStatMechProblemSet3.pdf :: basicStatMechProblemSet3Problem2.tex
basicStatMechProblemSet3.pdf :: basicStatMechProblemSet3Problem3.tex

basicStatMechProblemSet4.pdf :: basicStatMechProblemSet4Problem1.tex
basicStatMechProblemSet4.pdf :: basicStatMechProblemSet4Problem2.tex
basicStatMechProblemSet4.pdf :: basicStatMechProblemSet4Problem3.tex

basicStatMechProblemSet5.pdf :: basicStatMechProblemSet5Problem1.tex
basicStatMechProblemSet5.pdf :: basicStatMechProblemSet5Problem2.tex
basicStatMechProblemSet5.pdf :: basicStatMechProblemSet5Problem3.tex

basicStatMechProblemSet6.pdf :: basicStatMechProblemSet6Problem1.tex
basicStatMechProblemSet6.pdf :: basicStatMechProblemSet6Problem2.tex
basicStatMechProblemSet6.pdf :: basicStatMechProblemSet6Problem3.tex
basicStatMechProblemSet6.pdf :: basicStatMechProblemSet6Problem4.tex
#basicStatMechProblemSet6.pdf :: basicStatMechProblemSet6Problem6.tex
#basicStatMechProblemSet6.pdf :: basicStatMechProblemSet6Problem7.tex

huang93.pdf :: basicStatMechProblemSet6Problem5.tex
huang93.pdf :: $(HUANG93_DEPS)

basicStatMechProblemSet7.pdf :: basicStatMechProblemSet7Problem1.tex
basicStatMechProblemSet7.pdf :: basicStatMechProblemSet7Problem2.tex
basicStatMechProblemSet7.pdf :: basicStatMechProblemSet7Problem3.tex

basicStatMechProblemSet1.pdf :: $(PDF_DEPS)
basicStatMechProblemSet2.pdf :: $(PDF_DEPS)
basicStatMechProblemSet3.pdf :: $(PDF_DEPS)
basicStatMechProblemSet4.pdf :: $(PDF_DEPS)
basicStatMechProblemSet5.pdf :: $(PDF_DEPS)
basicStatMechProblemSet6.pdf :: $(PDF_DEPS)
basicStatMechProblemSet7.pdf :: $(PDF_DEPS)
