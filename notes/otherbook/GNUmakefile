include make.dep

ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../nonga/hoopSpring.png
ORIG_FILES += ../gabook/parallelogramArea.png
ORIG_FILES += ../calculus/parameterizedSurface.png
ORIG_FILES += ../calculus/polarAndSpherical.png
ORIG_FILES += ../calculus/surface_area_element.png
ORIG_FILES += ../calculus/volume_element.png

#ORIG_FILES += ../blogit/gaBasics.tex
#ORIG_FILES += ../blogit/dotBlade.tex
#ORIG_FILES += ../blogit/gaMintro.tex

LOCAL_FILES := $(notdir $(ORIG_FILES))

all : otherbook.pdf .gitignore

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/otherbook/,' > $@

local : $(LOCAL_FILES) 

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

otherbook.pdf :: $(BOOKDEPENDENCIES) $(LOCAL_FILES)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex main.tex
	mv main.pdf otherbook.pdf

cronology.tex : ../METADATA
	../METADATA -otherbook > cronology.tex

#%.pdf : %.tex
#	mkdir -p ./.revinfo/
#	~/bin/mkRevInfo > ./.revinfo/lastCommit.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)
