#A particle in one dimension
ORDERED += 1dreview.pdf

#The 1D harmonic oscillator
ORDERED += horeview.pdf

#Composite systems
ORDERED += comreview.pdf

#A particle in three dimensions
ORDERED += 3dreview.pdf

#Two particle systems
ORDERED += 2psreview.pdf

#Spherical harmonics
ORDERED += shreview.pdf

#The hydrogen atom
ORDERED += hreview.pdf

#Problem Sets
ORDERED += prob1.pdf
ORDERED += soln1.pdf
ORDERED += prob2.pdf

sipe.pdf : $(ORDERED)
	pdftk $(ORDERED) cat output $@
