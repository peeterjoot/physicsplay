THISDIR := phy452

include ../make.vars

SOURCE_DIRS += appendix
# FIXME:
# 1) including this incorrectly adds figures/*pdf to the ./.gitignore file
# 2) also not seeing this result in figure dependencies. touch figures/etalonFig1.pdf
SOURCE_DIRS += figures
#SOURCE_DIRS += solutions

GENERATED_SOURCES += mathematica.tex 
#GENERATED_PDFS += basicStatMechProblemSet1.pdf
#GENERATED_PDFS += basicStatMechProblemSet2.pdf
#GENERATED_PDFS += basicStatMechProblemSet3.pdf
#GENERATED_PDFS += basicStatMechProblemSet4.pdf
#GENERATED_PDFS += basicStatMechProblemSet5.pdf
#GENERATED_PDFS += basicStatMechProblemSet6.pdf

PHY452_FIGURES += figures/huang93Fig3.pdf
PHY452_FIGURES += figures/huang93Fig4.pdf
PHY452_FIGURES += figures/huang93Fig2.pdf
PHY452_FIGURES += figures/huang93Fig6.pdf

phy452.pdf :: $(PHY452_FIGURES)

include ../make.rules

basicStatMechProblemSet1.pdf : basicStatMechProblemSet1Problem1.tex
basicStatMechProblemSet1.pdf : basicStatMechProblemSet1Problem2.tex

basicStatMechProblemSet2.pdf : basicStatMechProblemSet2Problem1.tex
basicStatMechProblemSet2.pdf : basicStatMechProblemSet2Problem2.tex

basicStatMechProblemSet3.pdf : basicStatMechProblemSet3Problem1.tex
basicStatMechProblemSet3.pdf : basicStatMechProblemSet3Problem2.tex
basicStatMechProblemSet3.pdf : basicStatMechProblemSet3Problem3.tex

basicStatMechProblemSet4.pdf : basicStatMechProblemSet4Problem1.tex
basicStatMechProblemSet4.pdf : basicStatMechProblemSet4Problem2.tex
basicStatMechProblemSet4.pdf : basicStatMechProblemSet4Problem3.tex

basicStatMechProblemSet5.pdf : basicStatMechProblemSet5Problem1.tex
basicStatMechProblemSet5.pdf : basicStatMechProblemSet5Problem2.tex
basicStatMechProblemSet5.pdf : basicStatMechProblemSet5Problem3.tex

basicStatMechProblemSet6.pdf : basicStatMechProblemSet6Problem1.tex
basicStatMechProblemSet6.pdf : basicStatMechProblemSet6Problem2.tex
basicStatMechProblemSet6.pdf : basicStatMechProblemSet6Problem3.tex
basicStatMechProblemSet6.pdf : basicStatMechProblemSet6Problem4.tex
#basicStatMechProblemSet6.pdf : basicStatMechProblemSet6Problem5.tex
#basicStatMechProblemSet6.pdf : basicStatMechProblemSet6Problem6.tex
#basicStatMechProblemSet6.pdf : basicStatMechProblemSet6Problem7.tex

basicStatMechProblemSet1.pdf : $(PDF_DEPS)
basicStatMechProblemSet2.pdf : $(PDF_DEPS)
basicStatMechProblemSet3.pdf : $(PDF_DEPS)
basicStatMechProblemSet4.pdf : $(PDF_DEPS)
basicStatMechProblemSet5.pdf : $(PDF_DEPS)
basicStatMechProblemSet6.pdf : $(PDF_DEPS)
