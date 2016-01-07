# default behaviour: print the [-2,2] 100 entry table:
./tanhTable

# with an override on the number of intervals:
./tanhTable -n 4
./tanhTable --number=4

# also overriding the range:
./tanhTable -n 4 -l 0 -u 2
./tanhTable -n 4 --lower=0 --upper=2

# FIXME: bug: this doens't look right:
./tanhTable -n 4 --lower=-3 --upper=-1

# test argument parse error codepath:
./tanhTable --number=ayala
./tanhTable -l g
./tanhTable -u h

# print help and exit:
./tanhTable --help
./tanhTable -h
