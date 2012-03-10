ORDERED += class1.pdf

ORDERED += classnote12.pdf
ORDERED += hw1_31012012.pdf
ORDERED += hw2_09032012.pdf
ORDERED += phy459h-m09.pdf
ORDERED += phy459h-m10.pdf
ORDERED += phy454h-m11.pdf

all: kdas.pdf

kdas.pdf : $(ORDERED) Makefile
	pdftk $(ORDERED) cat output $@
