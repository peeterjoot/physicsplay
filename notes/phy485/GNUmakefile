SOURCE_DIRS += .
SOURCE_DIRS += appendix
SOURCE_DIRS += FrontBackmatter
#SOURCE_DIRS += solutions

DEPENDENCYEXTENSIONS := mp4 pdf_tex png tex sty
BOOKDEPENDENCIES := $(foreach ext,$(DEPENDENCYEXTENSIONS),$(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.$(ext))))

PDFDEPENDENCIES := $(subst pdf_tex,pdf,$(filter %.pdf_tex,$(BOOKDEPENDENCIES)))
BOOKDEPENDENCIES += $(PDFDEPENDENCIES)

ORIG_FILES += ../currentBookCopyright.tex
ORIG_FILES += ../myrefs.bib 
ORIG_FILES += ../classicthesis.mine/classicthesis.sty
ORIG_FILES += ../classicthesis.mine/mycommon.sty

ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Bibliography.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Contents.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Dedication.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/DirtyTitlepage.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Titleback.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Titlepage.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Contents.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/copyright.tex
ORIG_FRONTBACK_FILES += ../classicthesis.mine/FrontBackmatter/Version.tex

LOCAL_FILES := $(filter-out myrefs.bib,$(notdir $(ORIG_FILES)))
LOCAL_FRONTBACK_FILES := $(foreach e,$(notdir $(ORIG_FRONTBACK_FILES)),FrontBackmatter/$(e))

# ./ in these due to a bug in the .gitignore generation rule.
COPIED_FILES += ./peeters_macros.sty
COPIED_FILES += ./phy485.tex

PHY485 := $(filter-out $(STANDALONE), $(BOOKDEPENDENCIES))

GENERATED_PDFS := phy485.pdf

PHY485_DEPS := $(PHY485) $(LOCAL_FILES) mathematica.tex myrefs.bib $(COPIED_FILES) $(LOCAL_FRONTBACK_FILES)

MAIN_TARGETS := $(GENERATED_PDFS) .gitignore

CLEAN_TARGETS := *.ilg *.ind *.idx *.ps *.dvi *.log *.aux *.bbl *.blg *.lof *.log *.lot *.out *.toc 
CLEAN_TARGETS += $(MAIN_TARGETS) 
CLEAN_TARGETS += $(LOCAL_FILES) $(LOCAL_FRONTBACK_FILES) $(COPIED_FILES)
CLEAN_TARGETS += $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.aux))

all :: $(MAIN_TARGETS)

# plainnat.bib (as used by classicthesis) doesn't like @webpage:
# http://tex.stackexchange.com/questions/56951/what-does-warning-entry-type-for-isnt-style-file-defined-mean/56954#56954
myrefs.bib : ../myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

peeters_macros.sty : ../peeters_macros.tex
	cp $< $@

phy485.tex : ../classicthesis.mine/ClassicThesis.tex
	cp $< $@

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) $(COPIED_FILES) | tr ' ' '\n' | sed 's,.*/,notes/phy485/,' > $@
	echo $(LOCAL_FRONTBACK_FILES) | tr ' ' '\n' | sed 's,^,notes/phy485/,' >> $@

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

$(LOCAL_FRONTBACK_FILES) :
	cp $(filter %$@, $(ORIG_FRONTBACK_FILES)) $@

mathematica.tex : ../METADATA
	../METADATA -mathematica -latex -phy485 > mathematica.tex

phy485.pdf :: $(PHY485_DEPS)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex -nojustonce -file phy485.tex

clean ::
	rm -f $(CLEAN_TARGETS)
