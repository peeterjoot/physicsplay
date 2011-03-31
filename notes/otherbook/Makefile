include make.dep

ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../nonga/gridSummation.png
ORIG_FILES += ../nonga/hoopSpring.png
ORIG_FILES += ../gabook/parallelogramArea.png
ORIG_FILES += ../calculus/parameterizedSurface.png
ORIG_FILES += ../calculus/polarAndSpherical.png
ORIG_FILES += ../calculus/surface_area_element.png
ORIG_FILES += ../calculus/volume_element.png

ORIG_FILES += ../blogit/gaBasics.tex
ORIG_FILES += ../blogit/dotBlade.tex
ORIG_FILES += ../blogit/gaMintro.tex

LOCAL_FILES := $(notdir $(ORIG_FILES))

all : otherbook.pdf

local : $(LOCAL_FILES) 

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

otherbook.pdf :: $(TEXFILES) $(LOCAL_FILES)
	../make_pdflatex main.tex
	mv main.pdf otherbook.pdf

cronology.tex : ../METADATA
	../METADATA -otherbook > cronology.tex

#%.pdf : %.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)
