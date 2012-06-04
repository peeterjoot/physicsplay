RAWTEXFILES := $(shell ls *.tex)

TEXFILES := $(filter-out $(INCOMPLETE), $(RAWTEXFILES)) 

PDFS := $(TEXFILES:.tex=.pdf)

# logically symlinks, but MikTex doesn't like those:
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../eliblog.cls 
ORIG_FILES += ../eliblogwidescreen.cls 
ORIG_FILES += ../myrefs.bib 
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../classicthesis.mine/mycommon.sty
ORIG_FILES += ../phy454/figures/couetteFlowFig1.png

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: $(LOCAL_FILES)
#all :: $(PDFS)
all :: .gitignore
all :: peeters_macros.sty
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
all :: colorArticle.pdf

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/blogit/,' > $@

video: $(VIDEO)

$(PDFS) : $(LOCAL_FILES)

local : $(LOCAL_FILES)

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

%.pdf : %.tex
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo > ./.revinfo/lastCommit.tex
	perl ../make_pdflatex -file $<

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f *.ilg *.idx *.ps *.dvi $(PDFS) *.aux *.log *.bbl *.blg *.brf *.toc *.stackdump *.bib

peeters_macros.sty : ../peeters_macros.tex
	cat ../peeters_macros.tex > $@

localclean ::
	rm -f $(LOCAL_FILES)
