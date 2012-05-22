SOURCE_DIRS += .
SOURCE_DIRS += appendix
SOURCE_DIRS += elastic/displacements
SOURCE_DIRS += elastic/strain
SOURCE_DIRS += elastic/stress
SOURCE_DIRS += fluids
SOURCE_DIRS += fluids/bernoulli
SOURCE_DIRS += fluids/boundaryLayers
SOURCE_DIRS += fluids/hydrostatics
SOURCE_DIRS += fluids/navierStokes
SOURCE_DIRS += fluids/nondimensionalisation
SOURCE_DIRS += fluids/singularPertubation
SOURCE_DIRS += fluids/surfaces
SOURCE_DIRS += fluids/surfaceTension
SOURCE_DIRS += fluids/thermal
SOURCE_DIRS += FrontBackmatter
SOURCE_DIRS += intro
SOURCE_DIRS += solutions

# FIXME: move the figures into a figures dir to get them out of the way).
DEPENDENCYEXTENSIONS := mp4 pdf_tex png tex sty
BOOKDEPENDENCIES := $(foreach ext,$(DEPENDENCYEXTENSIONS),$(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.$(ext))))

PDFDEPENDENCIES := $(subst pdf_tex,pdf,$(filter %.pdf_tex,$(BOOKDEPENDENCIES)))
BOOKDEPENDENCIES += $(PDFDEPENDENCIES)

ORIG_FILES += ../myrefs.bib
#ORIG_FILES += ../abbrvurl.bst
#ORIG_FILES += ../alphaurl.bst
#ORIG_FILES += ../plainurl.bst
#ORIG_FILES += ../unsrturl.bst
#ORIG_FILES += ../eliblog.cls 
#ORIG_FILES += ../sourceaccess.tex 
ORIG_FILES += ../gitclone.ksh
ORIG_FILES += ../gitPull.ksh
ORIG_FILES += ../sampleBuildMake.ksh
ORIG_FILES += ../currentBookCopyright.tex

# this isn't part of my git repository.  It is the open-source StrobeMediaPlayback.swf from Adobe, hosted on SourceForge.net, and recommended by the media9 package maintainer, and 
# available here:
#
# http://sourceforge.net/projects/smp.adobe/files/
#
# I've downloaded that and placed the flash 10.1 version here:
# 
# note that the next version of media9 will bundle this directly, so requiring this external file for now is only temporary:
#
# http://tex.stackexchange.com/questions/1574/embedding-videos-and-animations/50370#comment104622_50370
#
#ORIG_FILES += ../strobe/StrobeMediaPlayback.swf

LOCAL_FILES := $(notdir $(ORIG_FILES))

PHY454 := $(filter-out $(STANDALONE), $(BOOKDEPENDENCIES))

GENERATED_PDFS := phy454.pdf

all :: $(GENERATED_PDFS) .gitignore

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/phy454/,' > $@

local : $(LOCAL_FILES) 

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

cronology.tex : ../METADATA
	../METADATA -phy454 > cronology.tex

mathematica.tex : ../METADATA
	../METADATA -mathematica -latex -phy454 > mathematica.tex

phy454.pdf :: $(PHY454) $(LOCAL_FILES) mathematica.tex
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex -nojustonce -file main.tex
	mv main.pdf phy454.pdf

clean ::
	rm -f *.ilg *.ind *.idx *.ps *.dvi $(GENERATED_PDFS) *.log *.aux *.bbl *.blg *.lof *.log *.lot *.out *.toc $(LOCAL_FILES) $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.aux))
