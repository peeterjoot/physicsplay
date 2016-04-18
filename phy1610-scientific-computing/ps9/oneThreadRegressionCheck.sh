#git clone /scinet/course/scientific_computing/2016/hw9
#cd hw9
#source setup
#make

export OMP_NUM_THREADS=1

../hw9-dist/wave1d waveparams.txt
mv dataFilename.out dataFilename.out.1.dist

./wave1d waveparams.txt
mv dataFilename.out dataFilename.out.1.mine

diff -up dataFilename.out.1.dist dataFilename.out.1.mine
