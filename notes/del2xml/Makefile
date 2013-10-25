CSV := $(wildcard *.csv)
XML := $(subst .csv,.xml,$(CSV))

all : $(XML)

%.xml : %.csv
	./del2xml < $^ > $@

sample2.xml : sample2.csv
	./del2xml -d '\$' < sample2.csv > sample2.xml
