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

include ../make.rules

basicStatMechProblemSet1.pdf : basicStatMechProblemSet1Problem2.tex basicStatMechProblemSet1Problem1.tex
basicStatMechProblemSet1.pdf : $(PDF_DEPS)

basicStatMechProblemSet2.pdf : basicStatMechProblemSet2Problem2.tex basicStatMechProblemSet2Problem1.tex
basicStatMechProblemSet2.pdf : $(PDF_DEPS)

basicStatMechProblemSet3.pdf : basicStatMechProblemSet3Problem3.tex basicStatMechProblemSet3Problem2.tex basicStatMechProblemSet3Problem1.tex
basicStatMechProblemSet3.pdf : $(PDF_DEPS)

