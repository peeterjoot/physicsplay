THISDIR := bb

#include ../make.vars
# this makefile fragment defines variables that are common to all the makefiles associated with my classic-thesis template
# based "books"

SOURCE_DIRS += .
SOURCE_DIRS += FrontBackmatter

DEPENDENCYEXTENSIONS += mp4 pdf_tex png tex sty

ORIG_FILES += ../currentBookCopyright.tex
ORIG_FILES += ../classicthesis/classicthesis.sty
ORIG_FILES += ../mycommon.sty

# straight from the classicthesis template:
#ORIG_FRONTBACK_FILES += ../classicthesis/FrontBackmatter/Bibliography.tex
#ORIG_FRONTBACK_FILES += ../classicthesis/FrontBackmatter/DirtyTitlepage.tex

# slightly modified from the classicthesis template:
#ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Contents.tex
#ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Dedication.tex
#ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Titleback.tex
#ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Titlepage.tex

# like some of the above pages in the classicthesis template:
#ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/copyright.tex
#ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Version.tex

# ./ in these due to a bug in the .gitignore generation rule.
COPIED_FILES += ./peeters_macros.sty
#COPIED_FILES += ./$(THISDIR).tex
COPIED_FILES += ./Bibliography.bib

GENERATED_PDFS += $(THISDIR).pdf

CLEAN_TARGETS += *.ilg *.ind *.idx *.ps *.dvi *.log *.aux *.bbl *.blg *.lof *.log *.lot *.out *.toc *.synctex.gz *.stackdump *.brf

#SOURCE_DIRS += appendix
#SOURCE_DIRS += solutions

GENERATED_SOURCES := mathematica.tex 

#include ../make.rules
BOOKDEPENDENCIES := $(foreach ext,$(DEPENDENCYEXTENSIONS),$(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.$(ext))))
BOOKDEPENDENCIES := $(foreach ext,$(DEPENDENCYEXTENSIONS),$(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.$(ext))))

PDFDEPENDENCIES := $(subst pdf_tex,pdf,$(filter %.pdf_tex,$(BOOKDEPENDENCIES)))
BOOKDEPENDENCIES += $(PDFDEPENDENCIES)

LOCAL_FILES := $(notdir $(ORIG_FILES))
LOCAL_FRONTBACK_FILES := $(foreach e,$(notdir $(ORIG_FRONTBACK_FILES)),FrontBackmatter/$(e))

JUSTBOOKDEPENDENCIES := $(filter-out $(STANDALONE), $(BOOKDEPENDENCIES))

THISBOOK_DEPS := $(JUSTBOOKDEPENDENCIES) $(LOCAL_FILES) $(GENERATED_SOURCES) $(COPIED_FILES) $(LOCAL_FRONTBACK_FILES) $(LOCAL_FIGURE_FILES)

MAIN_TARGETS += $(GENERATED_PDFS) .gitignore

CLEAN_TARGETS += $(MAIN_TARGETS) 
CLEAN_TARGETS += $(GENERATED_SOURCES)
CLEAN_TARGETS += $(LOCAL_FILES)
CLEAN_TARGETS += $(LOCAL_FRONTBACK_FILES)
CLEAN_TARGETS += $(LOCAL_FIGURE_FILES)
CLEAN_TARGETS += $(COPIED_FILES)
CLEAN_TARGETS += $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.aux))

all :: $(MAIN_TARGETS)

$(THISDIR).pdf :: $(THISBOOK_DEPS)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex -nojustonce -file $(THISDIR).tex

clean ::
	rm -f $(CLEAN_TARGETS)
	rm -rf ./.revinfo

#$(THISDIR).tex : ../classicthesis.mine/ClassicThesis.tex
#	cp $< $@

mathematica.tex : ../METADATA
	../METADATA -mathematica -latex -$(THISDIR) > mathematica.tex

# plainnat.bib (as used by classicthesis) doesn't like @webpage:
# http://tex.stackexchange.com/questions/56951/what-does-warning-entry-type-for-isnt-style-file-defined-mean/56954#56954
Bibliography.bib : ../myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) $(COPIED_FILES) | tr ' ' '\n' | sed 's,.*/,notes/$(THISDIR)/,' > $@
	echo $(LOCAL_FIGURE_FILES) $(LOCAL_FRONTBACK_FILES) $(GENERATED_SOURCES) | tr ' ' '\n' | sed 's,^,notes/$(THISDIR)/,' >> $@
ifneq ($(PDFDEPENDENCIES),)
	echo $(PDFDEPENDENCIES) | tr ' ' '\n' | sed 's,^,!notes/$(THISDIR)/,' >> $@
endif

cronology.tex : ../METADATA
	../METADATA -$(THISDIR) > cronology.tex

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

$(LOCAL_FRONTBACK_FILES) :
	cp $(filter %$@, $(ORIG_FRONTBACK_FILES)) $@

peeters_macros.sty : ../peeters_macros.tex $(THISDIR).sty
	cat ../peeters_macros.tex $(THISDIR).sty > $@
