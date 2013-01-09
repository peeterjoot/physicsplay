include make.dep

#ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../phy354/figures/hoopSpring.png
ORIG_FILES += ../gabook/figures/parallelogramArea.png
ORIG_FILES += ../calculus/parameterizedSurface.png
ORIG_FILES += ../calculus/polarAndSpherical.png
ORIG_FILES += ../calculus/surface_area_element.png
ORIG_FILES += ../calculus/volume_element.png

ORIG_FILE_DIRS += ../miscphysics/
ORIG_FILE_DIRS += ../gabook/figures/
ORIG_FILE_DIRS += ../calculus/

#ORIG_FILES += ../blogit/gaBasics.tex
#ORIG_FILES += ../blogit/dotBlade.tex
#ORIG_FILES += ../blogit/gaMintro.tex

LOCAL_FILES := $(notdir $(ORIG_FILES))

all : peeters_macros.sty peeters_layout.sty myrefs.bib otherbook.pdf .gitignore

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/otherbook/,' > $@

local : $(LOCAL_FILES) 

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

otherbook.pdf :: $(BOOKDEPENDENCIES) $(LOCAL_FILES)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex -file main.tex
	mv main.pdf otherbook.pdf

cronology.tex : ../METADATA
	../METADATA -otherbook > cronology.tex

#-------------------------------
# HACK: from ../make.rules:

# plainnat.bib (as used by classicthesis) doesn't like @webpage:
# http://tex.stackexchange.com/questions/56951/what-does-warning-entry-type-for-isnt-style-file-defined-mean/56954#56954
Bibliography.bib : myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

# old style:
myrefs.bib: ../myrefs.bib.in ../METADATA
	cp ../myrefs.bib.in myrefs.bib
	../METADATA -bib >> myrefs.bib

peeters_layout.sty : ../peeters_layout.sty
	cp $^ $@

peeters_macros.sty : ../peeters_macros.sty
	cp $^ $@
#-------------------------------


#%.pdf : %.tex
#	mkdir -p ./.revinfo/
#	~/bin/mkRevInfo > ./.revinfo/lastCommit.tex
#	../make_pdflatex -file $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)
