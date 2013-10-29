EXE=.exe

del2xml$(EXE) : del2xml.cpp
	g++ -Wformat -g -o $@ $<
	# cl -Fedel2xml.exe /EHsc del2xml.cpp

clean:
	rm -f del2xml$(EXE)
