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
#ORDERED += quiz1formulasheet.pdf
ORDERED += quiz1s.pdf
ORDERED += quiz1solutions.pdf
ORDERED += prob5.pdf
ORDERED += soln5.pdf
ORDERED += prob6.pdf
ORDERED += soln6.pdf
ORDERED += CorrectionWKB.pdf
#ORDERED += quiz2formulasheet.pdf
ORDERED += quiz2s.pdf
ORDERED += quiz2solutions.pdf
ORDERED += prob7.pdf
ORDERED += soln7.pdf
ORDERED += prob8.pdf
ORDERED += soln8.pdf
#ORDERED += quiz3formulasheet.pdf
ORDERED += prob9.pdf
ORDERED += soln9.pdf
ORDERED += prob10.pdf
ORDERED += soln10.pdf
ORDERED += quiz3s.pdf
ORDERED += quiz3solutions.pdf
ORDERED += prob11.pdf
ORDERED += soln11.pdf
ORDERED += prob12.pdf
ORDERED += soln12.pdf
#ORDERED += quiz4formulasheet.pdf
ORDERED += quiz4s.pdf
ORDERED += quiz4solutions.pdf
ORDERED += finalformulasheet.pdf
ORDERED += phy456h-d09s.pdf
ORDERED += phy456h-d10s.pdf
ORDERED += phy457h-d08s.pdf

all: sipe.pdf

quiz1s.pdf : quiz1.pdf
	pdftk $< cat 1-1 output $@

quiz2s.pdf : quiz2.pdf
	pdftk $< cat 1-1 output $@

quiz3s.pdf : quiz3.pdf
	pdftk $< cat 1-1 output $@

quiz4s.pdf : quiz4.pdf
	pdftk $< cat 1-2 output $@

phy456h-d09s.pdf : phy456h-d09.pdf
	pdftk $< cat 1-3 output $@

phy456h-d10s.pdf : phy456h-d10.pdf
	pdftk $< cat 1-3 output $@

phy457h-d08s.pdf : phy457h-d08.pdf
	pdftk $< cat 1-3 output $@

sipe.pdf : $(ORDERED) Makefile
	pdftk $(ORDERED) cat output $@
