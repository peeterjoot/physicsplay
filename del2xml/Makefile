EXE=.exe

del2xml$(EXE) : del2xml.cpp commit.c
	g++ -Wformat -g -o $@ $<

commit.c: del2xml.cpp
	echo 'char commitString[] = "'`~/bin/mkRevInfo -commit`'" ;' > $@

clean:
	rm -f del2xml$(EXE)

build.bat : Makefile commit.c
	rm -f build.bat
	echo cl -c ../getopt/getopt.c -I../getopt > build.bat
	echo cl -c ../getopt/getopt1.c -I../getopt >> build.bat
	echo cl -c commit.c >> build.bat
	echo cl -Fedel2xml.exe /EHsc del2xml.cpp getopt.obj getopt1.obj -I../getopt >> build.bat
