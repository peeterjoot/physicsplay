THISDIR := phy356-qmI

include ../make.bookvars

FIGURES := ../../figures/$(THISDIR)

SOURCE_DIRS += chapters
SOURCE_DIRS += $(FIGURES)

GENERATED_PDFS += desaiTypos.pdf
#GENERATED_PDFS += reproSaveSize.pdf

#ONCEFLAGS := -justonce

include ../make.rules

desaiTypos.pdf :: desaiTyposInnards.tex
