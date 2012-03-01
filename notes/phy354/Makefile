include make.dep

ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst

LOCAL_FILES := $(notdir $(ORIG_FILES))

ORDERED += CMpp1-13.pdf
#ORDERED += CMpp13.1-27.pdf
ORDERED += CMpp13.1-20.pdf 
ORDERED += CMpp20.1-.2.pdf
ORDERED += CMpp21-27.pdf 
ORDERED += CMpp27.1-.3.pdf
ORDERED += CMpp28-57.pdf
ORDERED += CMppD1-86.3.pdf

# from the 2011 course.  Looks like replaced by CMppD1-86.3.pdf above.
#ORDERED += CMppC1-C5.pdf
#ORDERED += CMpp86.1-86.3.pdf

ORDERED += CMpp73-82.pdf
ORDERED += CMpp157-169.pdf
ORDERED += CMppA1-A8.pdf
ORDERED += CMpp106-122.pdf
ORDERED += CMpp123-131.pdf
ORDERED += CMpp131.1-.9%3A.14.pdf
ORDERED += CMpp132-139.pdf
ORDERED += CMpp144-150.pdf
ORDERED += CMp147.1.pdf
ORDERED += CMpp151-164new.pdf
ORDERED += CMpp144-156.pdf
ORDERED += 2011_354hw1.pdf
ORDERED += 354hw1.pdf
ORDERED += hw1p1.pdf
ORDERED += 2011_354hw2.pdf
ORDERED += 354hw2.pdf
ORDERED += cm_hw2_q1.pdf
ORDERED += 354hw3.pdf
ORDERED += hw3soltns.pdf
ORDERED += 354hw4.pdf
ORDERED += cm_hw4_q1.pdf
ORDERED += 354hw5.pdf
ORDERED += cm_hw5_q1.pdf
ORDERED += 354-6.pdf
ORDERED += 354midterm.pdf
ORDERED += cmmidterm11.pdf
ORDERED += oldfinals.pdf

ORIGIN := http://www.physics.utoronto.ca/~poppitz/epoppitz/PHY354_files

#SOURCES := $(filter-out $(GENERATED),$(ORDERED))
#SOURCES := $(ORDERED)

all :: phy354.pdf
all :: poppitz354.pdf

local : $(LOCAL_FILES) 

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

cronology.tex : ../METADATA
	../METADATA -phy354 > cronology.tex

phy354.pdf :: $(BOOKDEPENDENCIES) $(LOCAL_FILES)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex main.tex
	mv main.pdf phy354.pdf

# FIXME: don't want pdf's in here!
#clean ::
#	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)

poppitz354.pdf : $(ORDERED)
	pdftk $(ORDERED) cat output $@

#$(SOURCES) :
#	wget $(ORIGIN)/$@

CMpp13.1-20.pdf : CMpp13.1-27.pdf
	pdftk $< cat 1-11 output $@

CMpp21-27.pdf : CMpp13.1-27.pdf
	pdftk $< cat 12-18 output $@
