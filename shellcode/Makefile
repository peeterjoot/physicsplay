myshell : exec.c driver.c setre.c
	rm -f $@
	cc -c exec.c
	cc -O2 -c driver.c
	cc -O2 -c setre.c
	cc -O2 exec.o driver.o setre.o -o $@

clean:
	rm -f *.o myshell
