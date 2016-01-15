# built with gcc 5.2.1, on ubuntu 15.10:
# g++ -std=c++11 -I../inc -Wall -Werror -D_GLIBCXX_USE_C99 -MMD -g    lissajous.cc   -o lissajous

# default behaviour: print the [-5,5] 100 entry table:
./lissajous | tee lissajous.txt

# with an override on the number of intervals:
./lissajous -n 4
./lissajous --number=4

# also overriding the range:
./lissajous -n 4 -l 0 -u 2
./lissajous -n 4 --lower=0 --upper=2
./lissajous -n 4 --lower=-3 --upper=-1

# test argument parse error codepath:
./lissajous --number=ayala
./lissajous -l g
./lissajous -u h

# print help and exit:
./lissajous --help
./lissajous -h
