EXE=.exe

del2xml$(EXE) : del2xml.cpp
	g++ -Wformat -g -o $@ $<

clean:
	rm -f del2xml$(EXE)

build.bat : Makefile
	rm -f build.bat
	echo cl -c ../getopt/getopt.c -I../getopt > build.bat
	echo cl -c ../getopt/getopt1.c -I../getopt >> build.bat
	echo cl -Fedel2xml.exe /EHsc del2xml.cpp getopt.obj getopt1.obj -I../getopt >> build.bat
