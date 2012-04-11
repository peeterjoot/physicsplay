all : myMathematica.html

myMathematica.html : METADATA
	./METADATA -mathematica > $@

copyright : currentCopyright.latexPrologue currentBookCopyright.tex

currentCopyright.latexPrologue :
	~/bin/printCopyRight -what file -desc file -line='% ' > $@

currentBookCopyright.tex :
	~/bin/printCopyRight -latex > $@
