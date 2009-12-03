files := $(shell ls *.ltx)
pdfs := $(files:.ltx=.pdf)

all : $(pdfs)

m: maxwellVacuum.pdf

$(pdfs) : ../peeters_macros.tex

include ../make.rules
