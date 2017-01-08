THISDIR := resume
THISBOOK := $(THISDIR)
BASEVER := 069daa3

include ../latex/make.vars

all :: peeters_macros.sty
all :: peeters_layout.sty
all :: resume.pdf
resume.pdf :: resume.tex

peeters_layout.sty : ../latex/peeters_layout.sty
	cp $^ $@

peeters_macros.sty : ../latex/peeters_macros.sty
	cp $^ $@

include ../latex/make.rules
