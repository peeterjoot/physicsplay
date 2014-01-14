#THISDIR := resume
#
## fixme.  looks like these assume a classicthesis project.  want to avoid the COPIED_FILES stuff in make.vars
## clean rule is also busted and removes resume.tex
#
#include ../make.vars
#include ../make.rules


RAWTEXFILES := $(shell ls *.tex)

TEXFILES := $(filter-out $(INCOMPLETE), $(RAWTEXFILES)) 

PDFS := $(TEXFILES:.tex=.pdf)

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: $(PDFS)
#all :: $(LOCAL_FILES)
all :: .gitignore
all :: Bibliography.bib
all :: peeters_macros.sty
all :: peeters_layout.sty

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/latex/,' > $@

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
	perl ../make_pdflatex -nojustonce -file $<

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

myrefs.bib: ../myrefs.bib.in ../METADATA
	cp ../myrefs.bib.in myrefs.bib
	../METADATA -bib >> myrefs.bib

localclean ::
	rm -f $(LOCAL_FILES)
