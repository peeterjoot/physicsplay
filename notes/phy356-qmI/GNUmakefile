THISDIR := phy356-qmI
THISBOOK := phy356

include ../latex/make.bookvars

FIGURES := ../../figures/$(THISBOOK)

SOURCE_DIRS += chapters
SOURCE_DIRS += $(FIGURES)

GENERATED_PDFS += desaiTypos.pdf
#GENERATED_PDFS += reproSaveSize.pdf

#ONCEFLAGS := -justonce

include ../latex/make.rules

desaiTypos.pdf :: desaiTyposInnards.tex
