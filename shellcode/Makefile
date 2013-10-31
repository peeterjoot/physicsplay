#CFLAGS += -g
OPTFLAGS += -O2

myshell : exec.c driver.c setre.c Makefile
	rm -f $@
	cc -O2 $(CFLAGS) -c exec.c
	#cc $(CFLAGS) -c exec.c
	cc $(CFLAGS) $(OPTFLAGS) -c driver.c
	cc $(CFLAGS) $(OPTFLAGS) -c setre.c
	cc $(OPTFLAGS) exec.o driver.o setre.o -o $@

clean:
	rm -f *.o myshell
