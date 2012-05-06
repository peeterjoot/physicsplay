include make.dep

ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../eliblog.cls 
ORIG_FILES += ../sourceaccess.tex 
ORIG_FILES += ../gitclone.ksh
ORIG_FILES += ../gitPull.ksh
ORIG_FILES += ../sampleBuildMake.ksh
ORIG_FILES += ../currentBookCopyright.tex
ORIG_FILES += ../strobe/StrobeMediaPlayback.swf

LOCAL_FILES := $(notdir $(ORIG_FILES))

PHY485 := $(filter-out $(STANDALONE), $(BOOKDEPENDENCIES))
#PHY485 += mathematica.tex

GENERATED_PDFS := phy485.pdf

all :: $(GENERATED_PDFS) .gitignore

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/phy485/,' > $@

local : $(LOCAL_FILES) 

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

cronology.tex : ../METADATA
	../METADATA -phy485 > cronology.tex

mathematica.tex : ../METADATA
	../METADATA -mathematica -latex -phy485 > mathematica.tex

phy485.pdf :: $(PHY485) $(LOCAL_FILES)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex main.tex
	mv main.pdf phy485.pdf

clean ::
	rm -f *.ps *.dvi $(GENERATED_PDFS) *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)
