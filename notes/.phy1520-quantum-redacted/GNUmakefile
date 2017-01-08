THISDIR := phy1520-quantum-redacted
THISBOOK := phy1520
ORIGDIR := phy1520-quantum

include ../latex/make.bookvars

#ONCEFLAGS := -justonce

SOURCE_DIRS += appendix
FIGURES := ../../figures/$(THISBOOK)
SOURCE_DIRS += $(FIGURES)

# also toggle redacted classicthesis-config.tex
# FIXME: changing this flag should be a dependency of mathematica.tex 
REDACTED := -redacted

GENERATED_SOURCES += julia.tex 
GENERATED_SOURCES += mathematica.tex 

PHY1520TEX := $(notdir $(wildcard ../$(ORIGDIR)/*.tex))
PHY1520TEX += FrontBackmatter/preface.tex
PHY1520STY += thisbook.sty
PHY1520STY += phy1520.sty

THISBOOK_DEPS += $(GENERATED_SOURCES)
THISBOOK_DEPS += $(PHY1520TEX)
THISBOOK_DEPS += $(PHY1520STY)
THISBOOK_DEPS += $(PDFS_FROM_EPS)

include ../latex/make.rules

LATEXMK := ../make_pdflatex --oldscript -filename

$(PHY1520TEX) : %.tex : ../$(ORIGDIR)/%.tex
	mkdir -p $(dir $@)
	cp $< $@

$(PHY1520STY) : %.sty : ../$(ORIGDIR)/%.sty
	cp $< $@

clean ::
	rm -f $(PHY1520TEX) $(PHY1520STY)

myrefs.bib : 
	(cd ../$(ORIGDIR) ; make myrefs.bib)
	cp ../$(ORIGDIR)/myrefs.bib .
