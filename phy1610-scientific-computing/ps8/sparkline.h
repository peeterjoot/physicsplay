// 
// sparkline.h
//
// write 1d rarray as a sparkline
//

#ifndef MYSPARKLINEH
#define MYSPARKLINEH

#include <rarray>
#include <string>

// The sparkline functions produce a one-line string with a graph made
// up of (unicode) block characters whose height represents the value
// of the array.  For long arrays, it allows a course-graining by
// specifying the number of characters to produce, where each
// character covers a part of the array. The height of each character
// is determined from the maximum of the values within that
// part. There's an option for specifying whether the bottom of the
// characters should represent zero, i.e., whether the y-axis includes
// zero.  By default, to maximize resolution, zero is not included in
// the y-axis (in contrast to the sparkhist functions).
//
// input parameters:
//  x:      rarray of values
//  width:  width of the graph (int)
//  zero:   whether the bottom of the characters should represent zero (bool)
// 
// returns: the sparkline string in utf-8 format.
//
std::string sparkline(const rarray<char,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<short,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<int,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<long,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<long long,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<unsigned char,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<unsigned short,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<unsigned int,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<unsigned long,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<unsigned long long,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<float,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<double,1>& x, int width=-1, bool zero=false);
std::string sparkline(const rarray<long double,1>& x, int width=-1, bool zero=false);

//
// The sparkhist functions produce a one-line string with a graph made
// up of (unicode) block characters whose height represents the
// histogram of the values in the array.  The number of bars (or
// "bins") in the histogram is given by the width parameter, or, if
// not given, will be 21. There's an option for specifying whether the
// bottom of the characters should represent zero, i.e., whether the
// y-axis includes zero. In contrast to the sparkline functions, by
// default, zero is included in the y-axis for the sparkhist functions.
//
// The sparkhist functions come in two forms. In the first, the range
// over which to apply the histogram is automatically detected from
// the range of values. In the second, two arguments, xbegin and xend
// preceed the argument list, and give the lowest and highest value to
// be represented by the histogram.
//
// input parameters:
//  x:      rarray of values
//  width:  number of histogram bins (int)
//  zero:   whether the bottom of the characters should represent zero (bool)
//
// additional input parameters for the second form:
//  xbegin: lowest value of x to consider
//  xend:   highest value of x, but non-inclusive, i.e., this value will
//          not be taken into account.
//
// returns: the sparkline string in utf-8 format.
//
// first form
std::string sparkhist(const rarray<char,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<short,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<int,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<long,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<long long,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<unsigned char,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<unsigned short,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<unsigned int,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<unsigned long,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<unsigned long long,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<float,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<double,1>& x, int width=-1, bool zero=true);
std::string sparkhist(const rarray<long double,1>& x, int width=-1, bool zero=true);
// second form
std::string sparkhist(char x1, char x2, const rarray<char,1>& x, int width=-1, bool zero=true);
std::string sparkhist(short x1, short x2, const rarray<short,1>& x, int width=-1, bool zero=true);
std::string sparkhist(int x1, int x2, const rarray<int,1>& x, int width=-1, bool zero=true);
std::string sparkhist(long x1, long x2, const rarray<long,1>& x, int width=-1, bool zero=true);
std::string sparkhist(long long x1, long long x2, const rarray<long long,1>& x, int width=-1, bool zero=true);
std::string sparkhist(unsigned char x1, unsigned char x2, const rarray<unsigned char,1>& x, int width=-1, bool zero=true);
std::string sparkhist(unsigned short x1, unsigned short x2, const rarray<unsigned short,1>& x, int width=-1, bool zero=true);
std::string sparkhist(unsigned int x1, unsigned int x2, const rarray<unsigned int,1>& x, int width=-1, bool zero=true);
std::string sparkhist(unsigned long x1, unsigned long x2, const rarray<unsigned long,1>& x, int width=-1, bool zero=true);
std::string sparkhist(unsigned long long x1, unsigned long long x2, const rarray<unsigned long long,1>& x, int width=-1, bool zero=true);
std::string sparkhist(float x1, float x2, const rarray<float,1>& x, int width=-1, bool zero=true);
std::string sparkhist(double x1, double x2, const rarray<double,1>& x, int width=-1, bool zero=true);
std::string sparkhist(long double x1, long double x2, const rarray<long double,1>& x, int width=-1, bool zero=true);

#endif
