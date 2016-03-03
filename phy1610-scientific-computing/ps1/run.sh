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
./lissajous --help 2>&1 | tee lissajous.help.txt
./lissajous -h

usage: lissajous [--number=n|-n n] [-lower=x1|-l x1] [--upper=x2|-u x2] [--help]
