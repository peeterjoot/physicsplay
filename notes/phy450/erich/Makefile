ORDERED += RelEMp1-11.pdf

#RelEM12-26.pdf
ORDERED += RelEMpp12-24.pdf
ORDERED += pp.24.1-24.4.pdf
ORDERED += RelEMpp25-26.pdf
ORDERED += RelEM27-44.pdf
ORDERED += RelEMpp45-51.pdf

#RelEMpp52-56.pdf
ORDERED += RelEMpp52-53.pdf
ORDERED += RelEMp53.1.pdf
ORDERED += RelEMpp54-56.pdf
ORDERED += RelEMpp56.1-73.pdf
ORDERED += RelEMpp74-83.pdf
ORDERED += RelEMpp84-102.pdf
ORDERED += RelEMpp103-113.pdf
ORDERED += RelEMpp114-127.pdf
ORDERED += RelEMpp128-135.pdf
ORDERED += RelEMpp136-146.pdf
ORDERED += RelEMGF1-5.pdf
ORDERED += RelEMpp147-165.pdf

#RelEMpp166-180.pdf
ORDERED += RelEMpp166-176.pdf
ORDERED += RelEMpp177.pdf
ORDERED += RelEMpp178.pdf
ORDERED += RelEMpp179-180.pdf
ORDERED += RelEMpp181-195.pdf
ORDERED += RelEMpp196-200.pdf

ORDERED += 450hw1.pdf
ORDERED += PS1soln.pdf
ORDERED += 450hw2.pdf
ORDERED += PS2soln.pdf
ORDERED += 450hw3.pdf
ORDERED += PS3soln.pdf
ORDERED += 450midterm.pdf
ORDERED += 450hw4.pdf
ORDERED += PS4soln.pdf
ORDERED += 450hw5.pdf
ORDERED += PS5soln.pdf
ORDERED += 450hw6.pdf
ORDERED += PS6soln.pdf

GENERATED += RelEMpp12-24.pdf
GENERATED += RelEMpp166-176.pdf
GENERATED += RelEMpp177.pdf
GENERATED += RelEMpp178.pdf
GENERATED += RelEMpp179-180.pdf
GENERATED += RelEMpp25-26.pdf
GENERATED += RelEMpp52-53.pdf
GENERATED += RelEMpp54-56.pdf

SOURCES := $(filter-out $(GENERATED),$(ORDERED))
SOURCES += RelEM12-26.pdf
SOURCES += RelEMpp166-180.pdf
SOURCES += RelEMpp52-56.pdf

ORIGIN := http://www.physics.utoronto.ca/~poppitz/epoppitz/PHY450_files

poppitz450.pdf : $(ORDERED)
	pdftk $(ORDERED) cat output $@

$(SOURCES) :
	wget $(ORIGIN)/$@

# rules to split a couple of the pdfs to inject or reorder various pages.

RelEMpp12-24.pdf : RelEM12-26.pdf
	pdftk $< cat 1-13 output $@

RelEMpp25-26.pdf : RelEM12-26.pdf
	pdftk $< cat 14-15 output $@

RelEMpp52-53.pdf : RelEMpp52-56.pdf
	pdftk $< cat 1-2 output $@

RelEMpp54-56.pdf : RelEMpp52-56.pdf
	pdftk $< cat 3-5 output $@

RelEMpp166-176.pdf : RelEMpp166-180.pdf
	pdftk $< cat 1-12 output $@

RelEMpp177.pdf : RelEMpp166-180.pdf
	pdftk $< cat 14 output $@

RelEMpp178.pdf : RelEMpp166-180.pdf
	pdftk $< cat 13 output $@

RelEMpp179-180.pdf : RelEMpp166-180.pdf
	pdftk $< cat 15-16 output $@
