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

DEPENDENCYEXTENSIONS := mp4 pdf_tex png tex sty
BOOKDEPENDENCIES := $(foreach ext,$(DEPENDENCYEXTENSIONS),$(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.$(ext))))

PDFDEPENDENCIES := $(subst pdf_tex,pdf,$(filter %.pdf_tex,$(BOOKDEPENDENCIES)))
BOOKDEPENDENCIES += $(PDFDEPENDENCIES)

ORIG_FILES += ../currentBookCopyright.tex
ORIG_FILES += ../myrefs.bib 

LOCAL_FILES := $(filter-out myrefs.bib,$(notdir $(ORIG_FILES)))
COPIED_FILES += ./peeters_macros.sty

PHY454 := $(filter-out $(STANDALONE), $(BOOKDEPENDENCIES))

GENERATED_PDFS := phy454.pdf

PHY454_DEPS := $(PHY454) $(LOCAL_FILES) mathematica.tex myrefs.bib $(COPIED_FILES)

all :: $(GENERATED_PDFS) .gitignore

# plainnat.bib (as used by classicthesis) doesn't like @webpage:
# http://tex.stackexchange.com/questions/56951/what-does-warning-entry-type-for-isnt-style-file-defined-mean/56954#56954
myrefs.bib : ../myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

peeters_macros.sty : ../peeters_macros.tex
	cp $< $@

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) $(COPIED_FILES) | tr ' ' '\n' | sed 's,.*/,notes/phy454/,' > $@

local : $(LOCAL_FILES) 

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

mathematica.tex : ../METADATA
	../METADATA -mathematica -latex -phy454 > mathematica.tex

phy454.pdf :: $(PHY454_DEPS)
#	echo deps: $(PHY454_DEPS)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex -nojustonce -file phy454.tex

clean ::
	rm -f *.ilg *.ind *.idx *.ps *.dvi $(GENERATED_PDFS) *.log *.aux *.bbl *.blg *.lof *.log *.lot *.out *.toc $(LOCAL_FILES) $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.aux))
