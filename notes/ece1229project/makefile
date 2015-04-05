FIGPATH := ../../figures/ece1229/project
FIGUREPATHS := $(wildcard $(FIGPATH)/*.png)
FIGURES := $(notdir $(FIGUREPATHS))
PDFLATEX := pdflatex -file-line-error -synctex=1 --max-print-line=1000 --c-style-errors --halt-on-error
DIST := /cygdrive/c/Users/IBM_ADMIN/Dropbox/ece1229-handouts/project/report

all : presentation.pdf

presentation.pdf : $(FIGURES) Bibliography.bib

$(FIGURES) : %.png: $(FIGPATH)/%.png
	cp $< $@

%.pdf :: %.tex
	$(PDFLATEX) $<
	bibtex $(basename $@)
	$(PDFLATEX) $<
	bibtex $(basename $@)
	$(PDFLATEX) $<
	bibtex $(basename $@)

dist : 
	cp make.sh *.png *.pdf Bibliography.bib *.tex $(DIST)

clean :
	rm -f *.snm *.aux *.out *.toc *.nav *.pdf *.synctex.gz *.log *.blg *.bbl

veryclean : clean
	rm -f *.png *.pdf *.bib

Bibliography.bib : ../myrefs.bib.in
	cp ../myrefs.bib.in myrefs.bib
	(cd .. ; ./METADATA -bib >> blogit/myrefs.bib)
	sed 's/@webpage/@manual/g' < myrefs.bib > Bibliography.bib
