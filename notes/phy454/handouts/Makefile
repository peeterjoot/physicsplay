ORDERED += class1.pdf

# strain tensor
#ORDERED += classnote2.pdf

# strain and stress tensors.  Appears to have all the content of note2.
#ORDERED += classnote3.pdf
#ORDERED += classnote4.pdf
#ORDERED += classnote5.pdf
#ORDERED += classnote6.pdf
#ORDERED += classnote7.pdf
#ORDERED += classnote8.pdf
#ORDERED += classnote10.pdf
ORDERED += classnote11.pdf
ORDERED += hw1_31012012.pdf
ORDERED += phy459h-m09.pdf
ORDERED += phy459h-m10.pdf
ORDERED += phy454h-m11.pdf

all: kdas.pdf

kdas.pdf : $(ORDERED) Makefile
	pdftk $(ORDERED) cat output $@
