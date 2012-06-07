ORDERED += 1530hw1.pdf
ORDERED += 1530hw2.pdf
ORDERED += 1530hw3.pdf
ORDERED += 1530hw4.pdf
ORDERED += 1530final.pdf
ORDERED += 1530final_1.pdf
#ORDERED += 1530hw1-solutions.pdf
#ORDERED += 1530hw2-corrns.pdf
#ORDERED += 1530hw2-solutions.pdf
#ORDERED += 1530hw3soltns.pdf
#ORDERED += 1530hw3-soltns1.pdf

SOURCES := $(filter-out $(GENERATED),$(ORDERED))

all :: poppitz1530.pdf .gitignore

.gitignore : GNUmakefile
	rm -f .gitignore
	touch $@

poppitz1530.pdf : $(ORDERED)
	pdftk $(ORDERED) cat output $@
