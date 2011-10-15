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
ORDERED += soln2.pdf
ORDERED += prob3.pdf
ORDERED += soln3.pdf
ORDERED += prob4.pdf
ORDERED += soln4.pdf
ORDERED += quiz1formulasheet.pdf
ORDERED += quiz1.pdf
ORDERED += quiz1solutions.pdf
ORDERED += prob5.pdf
ORDERED += soln5.pdf

sipe.pdf : $(ORDERED)
	pdftk $(ORDERED) cat output $@
