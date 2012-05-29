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
ORIG_FILES += ../classicthesis.mine/classicthesis.sty
ORIG_FILES += ../classicthesis.mine/mycommon.sty

# straight from the classicthesis template:
ORIG_FRONTBACK_FILES += ../classicthesis/FrontBackmatter/Bibliography.tex
ORIG_FRONTBACK_FILES += ../classicthesis/FrontBackmatter/DirtyTitlepage.tex

# slightly modified from the classicthesis template:
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Contents.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Dedication.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Titleback.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Titlepage.tex

# like some of the above pages in the classicthesis template:
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/copyright.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Version.tex

LOCAL_FILES := $(notdir $(ORIG_FILES))
LOCAL_FRONTBACK_FILES := $(foreach e,$(notdir $(ORIG_FRONTBACK_FILES)),FrontBackmatter/$(e))

# ./ in these due to a bug in the .gitignore generation rule.
COPIED_FILES += ./peeters_macros.sty
COPIED_FILES += ./phy454.tex
COPIED_FILES += ./Bibliography.bib

PHY454 := $(filter-out $(STANDALONE), $(BOOKDEPENDENCIES))

GENERATED_PDFS := phy454.pdf
GENERATED_SOURCES := mathematica.tex 

PHY454_DEPS := $(PHY454) $(LOCAL_FILES) $(GENERATED_SOURCES) $(COPIED_FILES) $(LOCAL_FRONTBACK_FILES)

MAIN_TARGETS := $(GENERATED_PDFS) .gitignore

CLEAN_TARGETS := *.ilg *.ind *.idx *.ps *.dvi *.log *.aux *.bbl *.blg *.lof *.log *.lot *.out *.toc *.synctex.gz
CLEAN_TARGETS += $(MAIN_TARGETS) 
CLEAN_TARGETS += $(GENERATED_SOURCES)
CLEAN_TARGETS += $(LOCAL_FILES)
CLEAN_TARGETS += $(LOCAL_FRONTBACK_FILES)
CLEAN_TARGETS += $(COPIED_FILES)
CLEAN_TARGETS += $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.aux))

all :: $(MAIN_TARGETS)

# plainnat.bib (as used by classicthesis) doesn't like @webpage:
# http://tex.stackexchange.com/questions/56951/what-does-warning-entry-type-for-isnt-style-file-defined-mean/56954#56954
Bibliography.bib : ../myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

peeters_macros.sty : ../peeters_macros.tex
	cp $< $@

phy454.tex : ../classicthesis.mine/ClassicThesis.tex
	cp $< $@

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) $(COPIED_FILES) | tr ' ' '\n' | sed 's,.*/,notes/phy454/,' > $@
	echo $(LOCAL_FRONTBACK_FILES) $(GENERATED_SOURCES) | tr ' ' '\n' | sed 's,^,notes/phy454/,' >> $@

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

$(LOCAL_FRONTBACK_FILES) :
	cp $(filter %$@, $(ORIG_FRONTBACK_FILES)) $@

mathematica.tex : ../METADATA
	../METADATA -mathematica -latex -phy454 > mathematica.tex

phy454.pdf :: $(PHY454_DEPS)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex -nojustonce -file phy454.tex

clean ::
	rm -f $(CLEAN_TARGETS)
	rm -rf ./.revinfo
