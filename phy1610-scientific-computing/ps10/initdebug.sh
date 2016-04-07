# with waveparamsid.txt::initdebug=1
./wave1d waveparamsid.txt | grep init | tee x1
mpirun -n 2 ./wave1d  waveparamsid.txt | grep init: | sort -k2 -n | tee x2
diff -up x1 x2
