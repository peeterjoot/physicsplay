files := $(shell ls *.ltx)
pdfs := $(files:.ltx=.pdf)

all : $(pdfs)

$(pdfs) : ../peeters_macros.tex

include ../make.rules
