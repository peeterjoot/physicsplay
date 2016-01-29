#(cd ; git clone https://github.com/vanzonr/ticktock.git )

#make profile.mine.txt 
#make profile.orig.txt 
(time ./origants) 2>&1 | tail -3 | tee time.orig.out
(time ./ants) 2>&1 | tail -3 | tee time.mine.out
