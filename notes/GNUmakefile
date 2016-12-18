# curious what my page count comes in as:
ALLPDF += blogit/dotBlade.pdf
ALLPDF += blogit/gaBasics.pdf
ALLPDF += blogit/gaMintro.pdf
#ALLPDF += blogit/kittelChapter3.pdf
ALLPDF += blogit/maxwellsFromGA.pdf
ALLPDF += blogit/pipeFlowConstPressureGradient.pdf
ALLPDF += blogit/qmTwoExamReflection.pdf
ALLPDF += blogit/qmTwoR1.pdf
ALLPDF += classicalmechanics/classicalmechanics.pdf
ALLPDF += dekker/dekker.pdf
ALLPDF += gabook/gabook.pdf
ALLPDF += miscphysics/miscphysics.pdf
#ALLPDF += otherbook/otherbook.pdf
ALLPDF += papers/gramSchmidtLorentz.pdf
#ALLPDF += papers/relwave.pdf
#ALLPDF += peterlue/AetherPhysics.pdf
#ALLPDF += peterlue/sampleArticle.pdf
ALLPDF += phy356/desaiTypos.pdf
ALLPDF += phy356/phy356.pdf
ALLPDF += phy450/phy450.pdf
#ALLPDF += phy452/basicStatMechProblemSet1.pdf
#ALLPDF += phy452/basicStatMechProblemSet2.pdf
ALLPDF += phy452/phy452.pdf
ALLPDF += phy454/phy454.pdf
ALLPDF += phy456/phy456.pdf
#ALLPDF += phy485/myFinalExamCheatSheet.pdf
ALLPDF += phy485/phy485.pdf

all :: myMathematica.html myrefs.bib

myMathematica.html : METADATA
	./METADATA -mathematica > $@

copyright : currentCopyright.latexPrologue currentBookCopyright.tex

currentCopyright.latexPrologue :
	printCopyRight -what file -desc file -line='% ' > $@

l:
	find . -name "*.tex" | grep -ve ./.latex/ -e ./latex/ -e /bak/ -e junk/ -e revinfo/ -e /th/ > $@

myrefs.bib: myrefs.bib.in METADATA
	cat myrefs.bib.in > myrefs.bib
	./METADATA -bib >> myrefs.bib

all.pdf : $(ALLPDF)
	pdftk $(ALLPDF) cat output $@

clean::
	rm -f l currentBookCopyright.tex currentCopyright.latexPrologue myMathematica.html

