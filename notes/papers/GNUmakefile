#
# could consider moving: .././classicalmechanics/mine/multiPendulumSphericalMatrix.tex here too.
#
THISDIR := papers
THISBOOK := $(THISDIR)
BASEVER := 069daa3

include ../latex/make.vars

FIGURES := ../../figures/$(THISBOOK)
SOURCE_DIRS += $(FIGURES)

GENERATED_PDFS += gramSchmidtLorentz.pdf
GENERATED_PDFS += relwave.pdf

all :: myrefs.bib $(GENERATED_PDFS)

$(GENERATED_PDFS) :: $(JUSTBOOKDEPENDENCIES) $(LOCAL_FILES) $(GENERATED_SOURCES) $(COPIED_FILES) $(LOCAL_COPIED_FILES)

include ../latex/make.rules
