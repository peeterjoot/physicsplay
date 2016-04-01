#source setup

export OMP_NUM_THREADS=1
./wave1d waveparams.txt
mv dataFilename.out dataFilename.out.1

export OMP_NUM_THREADS=8
./wave1d waveparams.txt
mv dataFilename.out dataFilename.out.8

diff -up dataFilename.out.1 dataFilename.out.8
