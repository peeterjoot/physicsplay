#(cd ; git clone https://github.com/vanzonr/ticktock.git )

#make profile.mine.txt 
#make profile.orig.txt 
(time ./origants) 2>&1 | tail -3 | tee time.orig.out
(time ./ants) 2>&1 | tail -3 | tee time.mine.out


# mine (mine is probably a bit faster since there's a double counting of totants in the original)
real	0m0.716s
user	0m0.696s
sys	0m0.000s

# orig
real	0m0.726s
user	0m0.692s
sys	0m0.000s
