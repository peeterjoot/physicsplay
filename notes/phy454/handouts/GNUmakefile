#ORDERED += class1.pdf
#ORDERED += classnote16.pdf
#ORDERED += hw1_31012012.pdf
#ORDERED += hw2_09032012.pdf
#ORDERED += hw3_21032012.pdf
#ORDERED += phy459h-m09.pdf
#ORDERED += phy459h-m10.pdf
ORDERED += phy459h-m09b.pdf
ORDERED += phy459h-m10b.pdf
ORDERED += phy454h-m11.pdf
ORDERED += formulaSheets459.pdf

all: oldexams.pdf

oldexams.pdf : $(ORDERED) Makefile
	pdftk $(ORDERED) cat output $@

phy459h-m09b.pdf : phy459h-m09.pdf
	pdftk $< cat 1-2 output $@

phy459h-m10b.pdf : phy459h-m10.pdf
	pdftk $< cat 1-2 output $@

formulaSheets459.pdf : phy459h-m10.pdf
	pdftk $< cat 3-6 output $@
