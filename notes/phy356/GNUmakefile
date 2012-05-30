SOURCE_DIRS += .
SOURCE_DIRS += appendix
SOURCE_DIRS += FrontBackmatter
#SOURCE_DIRS += solutions

DEPENDENCYEXTENSIONS := mp4 pdf_tex png tex sty
BOOKDEPENDENCIES := $(foreach ext,$(DEPENDENCYEXTENSIONS),$(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.$(ext))))

PDFDEPENDENCIES := $(subst pdf_tex,pdf,$(filter %.pdf_tex,$(BOOKDEPENDENCIES)))
BOOKDEPENDENCIES += $(PDFDEPENDENCIES)

ORIG_FILES += ../currentBookCopyright.tex
ORIG_FILES += ../classicthesis.mine/classicthesis.sty
ORIG_FILES += ../classicthesis.mine/mycommon.sty
ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../eliblog.cls

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
COPIED_FILES += ./phy356.tex
COPIED_FILES += ./Bibliography.bib

PHY356 := $(filter-out $(STANDALONE), $(BOOKDEPENDENCIES))

GENERATED_PDFS += phy356.pdf
GENERATED_PDFS += desaiTypos.pdf
#GENERATED_SOURCES := mathematica.tex 

PHY356_DEPS := $(PHY356) $(LOCAL_FILES) $(GENERATED_SOURCES) $(COPIED_FILES) $(LOCAL_FRONTBACK_FILES)

MAIN_TARGETS := $(GENERATED_PDFS) .gitignore

CLEAN_TARGETS := *.ilg *.ind *.idx *.ps *.dvi *.log *.aux *.bbl *.blg *.lof *.log *.lot *.out *.toc *.synctex.gz *.stackdump *.brf
CLEAN_TARGETS += $(MAIN_TARGETS) 
CLEAN_TARGETS += $(GENERATED_SOURCES)
CLEAN_TARGETS += $(LOCAL_FILES)
CLEAN_TARGETS += $(LOCAL_FRONTBACK_FILES)
CLEAN_TARGETS += $(COPIED_FILES)
CLEAN_TARGETS += $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.aux))

all :: $(MAIN_TARGETS)

desaiTypos.pdf :: desaiTypos.tex
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo > ./.revinfo/lastCommit.tex
	../make_pdflatex -file $<

# plainnat.bib (as used by classicthesis) doesn't like @webpage:
# http://tex.stackexchange.com/questions/56951/what-does-warning-entry-type-for-isnt-style-file-defined-mean/56954#56954
Bibliography.bib : ../myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

peeters_macros.sty : ../peeters_macros.tex phy356.sty
	cat ../peeters_macros.tex phy356.sty > $@

phy356.tex : ../classicthesis.mine/ClassicThesis.tex
	cp $< $@

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) $(COPIED_FILES) | tr ' ' '\n' | sed 's,.*/,notes/phy356/,' > $@
	echo $(LOCAL_FRONTBACK_FILES) $(GENERATED_SOURCES) | tr ' ' '\n' | sed 's,^,notes/phy356/,' >> $@

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

$(LOCAL_FRONTBACK_FILES) :
	cp $(filter %$@, $(ORIG_FRONTBACK_FILES)) $@

mathematica.tex : ../METADATA
	../METADATA -mathematica -latex -phy356 > mathematica.tex

phy356.pdf :: $(PHY356_DEPS)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex -nojustonce -file phy356.tex

clean ::
	rm -f $(CLEAN_TARGETS)
	rm -rf ./.revinfo
