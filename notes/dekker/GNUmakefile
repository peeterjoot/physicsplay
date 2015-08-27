MUTEX += dekker dekker_mfence dekker_lfence dekker_sfence dekker_sched
MUTEX += dekker_wiki dekker_mfence_wiki dekker_lfence_wiki dekker_sfence_wiki dekker_sched_wiki 
MUTEX += dekker_xchg dekker_atomic dekker_serial_atomic dekker_serial_nolock

#all :: $(MUTEX)

files := $(shell ls *.tex)
pdfs := $(files:.tex=.pdf)

PDF_GENERATED_DEPS += peeters_macros.sty peeters_layout.sty Bibliography.bib myrefs.bib

include ../make.latexmk

all :: $(pdfs) .gitignore

.gitignore : GNUmakefile
	rm -f .gitignore
	touch $@

$(pdfs) : $(PDF_GENERATED_DEPS)

peeters_layout.sty : ../peeters_layout.sty
	cp $^ $@

peeters_macros.sty : ../peeters_macros.sty
	cp $^ $@

# plainnat.bib (as used by classicthesis) doesn't like @webpage:
# http://tex.stackexchange.com/questions/56951/what-does-warning-entry-type-for-isnt-style-file-defined-mean/56954#56954
Bibliography.bib : myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

# old style: don't think I have any direct uses anymore, but am generating Bibliography.bib from this.
myrefs.bib: ../myrefs.bib.in ../METADATA
	cp ../myrefs.bib.in myrefs.bib
	../METADATA -bib >> myrefs.bib

%.pdf : %.tex
	$(LATEXMK) $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log $(PDF_GENERATED_DEPS) *.o $(MUTEX)

dekker: dekker.c
	g++ dekker.c -o $@ -lpthread

dekker_atomic: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_ATOMIC

dekker_serial_atomic: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_SERIAL

dekker_serial_nolock: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_SERIAL -DNO_LOCK

dekker_xchg: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_XCHG_LOCK

dekker_mfence: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_MFENCE

dekker_sfence: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_SFENCE

dekker_lfence: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_LFENCE

dekker_sched: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_SCHED_FENCE



dekker_wiki: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_WIKI

dekker_mfence_wiki: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_MFENCE -DUSE_WIKI

dekker_sfence_wiki: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_SFENCE -DUSE_WIKI

dekker_lfence_wiki: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_LFENCE -DUSE_WIKI

dekker_sched_wiki: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_SCHED_FENCE -DUSE_WIKI
