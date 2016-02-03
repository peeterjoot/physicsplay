# FIXME: this makefile can probably now use:
# ../include/make.vars
# ../include/make.rules

RAWTEXFILES := $(shell ls *.tex)

TEXFILES := $(filter-out $(INCOMPLETE), $(RAWTEXFILES)) 

PDFS := $(TEXFILES:.tex=.pdf)

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: $(LOCAL_FILES)
#all :: $(PDFS)
all :: .gitignore
all :: Bibliography.bib
all :: peeters_macros.sty
all :: peeters_layout.sty
#all :: partEll.pdf
#all :: ans2.pdf
#all :: main.pdf
#all :: chapFigureMisplacement.pdf
#all :: problem3.pdf
#all :: index.pdf
#all :: problemWithFig.pdf
#all :: sectionColor.pdf
#all :: colors.pdf
#all :: problemChap.pdf
#all :: breqnTest.pdf
#all :: dmath.pdf
#all :: colorArticle.pdf

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/latex/,' > $@

video: $(VIDEO)

$(PDFS) : $(LOCAL_FILES)

local : $(LOCAL_FILES)

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

%.pdf : %.tex
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo > ./.revinfo/lastCommit.tex
	~/bin/mkRevInfo -date > ./.revinfo/gitCommitDate.tex
	~/bin/mkRevInfo -commit > ./.revinfo/gitCommitString.tex
	~/bin/mkRevInfo -repo > ./.revinfo/gitRepo.tex
	$(LATEXMK) $<

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f *.ilg *.idx *.ps *.dvi $(PDFS) *.aux *.log *.bbl *.blg *.brf *.toc *.stackdump *.bib
	rm -rf ./.revinfo/

peeters_layout.sty : ../peeters_layout.sty
	cp $^ $@

peeters_macros.sty : ../peeters_macros.sty
	cp $^ $@

Bibliography.bib : myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

# old style:
myrefs.bib: ../myrefs.bib.in ../METADATA
	cp ../myrefs.bib.in myrefs.bib
	../METADATA -bib >> myrefs.bib

localclean ::
	rm -f $(LOCAL_FILES)
