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

$ make origants
g++ -MMD -I../../rarray -I/home/peeterj/ticktock -DNDEBUG -O2 -pg -g -Wall -Werror -std=c++11 -c -o origants.o origants.cc
cp /home/peeterj/ticktock/ticktock.cc ticktock.cc
g++ -MMD -I../../rarray -I/home/peeterj/ticktock -DNDEBUG -O2 -pg -g -Wall -Werror -std=c++11 -c -o ticktock.o ticktock.cc
g++ -o origants origants.o ticktock.o -pg -g

$ make profile.orig.txt
rm -f gmon.out
./origants > orig.out
gprof --line --no-graph ./origants > profile.orig.txt



$ make ants
g++ -MMD -I../../rarray -I/home/peeterj/ticktock -DNDEBUG -O2 -pg -g -Wall -Werror -std=c++11 -c -o ants.o ants.cc
g++ -MMD -I../../rarray -I/home/peeterj/ticktock -DNDEBUG -O2 -pg -g -Wall -Werror -std=c++11 -c -o ticktock.o ticktock.cc
g++ -MMD -I../../rarray -I/home/peeterj/ticktock -DNDEBUG -O2 -pg -g -Wall -Werror -std=c++11 -c -o ants_on_table.o ants_on_table.cc
g++ -o ants ants.o ticktock.o ants_on_table.o -pg -g

$ make profile.mine.txt
rm -f gmon.out
./ants > mine.out
gprof --line --no-graph ./ants > profile.mine.txt


