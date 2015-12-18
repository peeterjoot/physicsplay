THISDIR := phy1520

include ../make.bookvars

#ONCEFLAGS := -justonce

SOURCE_DIRS += appendix
FIGURES := ../../figures/$(THISDIR)
SOURCE_DIRS += $(FIGURES)

# also toggle redacted classicthesis-config.tex
# FIXME: changing this flag should be a dependency of mathematica.tex 
REDACTED := -redacted

GENERATED_SOURCES += julia.tex 
GENERATED_SOURCES += mathematica.tex 

PHY1520TEX := $(notdir $(wildcard ../$(THISDIR)/*.tex))
PHY1520TEX += FrontBackmatter/preface.tex
PHY1520STY := thisbook.sty
PHY1520STY := phy1520.sty

THISBOOK_DEPS += $(GENERATED_SOURCES)
THISBOOK_DEPS += $(PHY1520TEX)
THISBOOK_DEPS += $(PHY1520STY)
THISBOOK_DEPS += $(PDFS_FROM_EPS)

include ../make.rules

LATEXMK := ../make_pdflatex --oldscript -filename

$(PHY1520TEX) : %.tex : ../$(THISDIR)/%.tex
	mkdir -p $(dir $@)
	cp $< $@

$(PHY1520STY) : %.sty : ../$(THISDIR)/%.sty
	cp $< $@

clean ::
	rm -f $(PHY1520TEX) $(PHY1520STY)

myrefs.bib : 
	(cd ../phy1520 ; make myrefs.bib)
	cp ../phy1520/myrefs.bib .
