THISDIR := resume
THISBOOK := $(THISDIR)

include ../make.vars

all :: peeters_macros.sty
all :: peeters_layout.sty
all :: resume.pdf
resume.pdf :: resume.tex

peeters_layout.sty : ../peeters_layout.sty
	cp $^ $@

peeters_macros.sty : ../peeters_macros.sty
	cp $^ $@

include ../make.rules
