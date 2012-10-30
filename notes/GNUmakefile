all :: myMathematica.html myrefs.bib

myMathematica.html : METADATA
	./METADATA -mathematica > $@

copyright : currentCopyright.latexPrologue currentBookCopyright.tex

currentCopyright.latexPrologue :
	~/bin/printCopyRight -what file -desc file -line='% ' > $@


l:
	find -name "*.tex" | grep -ve classicthesis -e /bak/ -e /junk/ -e revinfo/ -e /th/ > $@

myrefs.bib: myrefs.bib.in METADATA
	cat myrefs.bib.in > myrefs.bib
	./METADATA -bib >> myrefs.bib

clean::
	rm -f l currentBookCopyright.tex currentCopyright.latexPrologue myMathematica.html
