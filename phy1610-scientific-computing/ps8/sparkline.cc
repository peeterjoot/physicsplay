// 
// sparkline.cc
//
// write 1d rarray as a sparkline

#include "sparkline.h"
#include <algorithm>
#include <limits>
#include <cmath>

template<class T>
static std::string sparkline_g(const rarray<T,1>& x, int width, bool zero)
{
    // sparkline_g is a template function produces a one-line string
    // with a graph made up of (unicode) block characters whose height
    // represents the value of the array.  For long arrays, it allows
    // a course-graining by specifying the number of characters to
    // produce, where each character covers a part of the array. The
    // height of each character is determined from the maximum of the
    // values within that part. There's an option for specifying
    // whether the bottom of the characters should represent zero.
    //
    // This is a generic function that is used in the implementation
    // of the sparkline functions for char, short, int, long, long
    // long, their unsigned variants, and the floating point types
    // float, double and long double.
    //
    // input parameters:
    //  x:      rarray of values
    //  width:  width of the graph (int)
    //  zero:   whether the bottom of the characters should represent zero (bool)
    // 
    // returns: the sparkline string in utf-8 format.
    //
    int per = (width<1)?1:((x.size()+width-1)/width);
    std::string result(3*((x.size()+per-1)/per), ' ');
    auto minmaxval = std::minmax_element(&x[0], &x[0] + x.size());
    T min, max;
    if (zero) 
        min = std::min(T(0),*minmaxval.first);
    else
        min = *minmaxval.first;
    if (zero) 
        max = std::max(T(0),*minmaxval.second);
    else
        max = *minmaxval.second;
    T range = max - min;
    int i = 0;
    const unsigned char sparkchars[9] = {129,130,131,132,133,134,135,136,171};
    for (int j=0;j<x.size();j+=per) {
        if (per > x.size()-j) per = x.size()-j;
        T value = *std::max_element(&x[j], &x[j] + per);
        if (!std::isnan(value)) {
            int level = (int)round(7*(value-min)/range);
            if (level>=0 and level<8) {
                result[i++] = 226;
                result[i++] = 150;
                result[i++] = sparkchars[level];
            } else {
                result[i++] = 226;
                result[i++] = 150;
                result[i++] = sparkchars[8];
            }
        } else {
            result[i++] = 226;
            result[i++] = 150;
            result[i++] = sparkchars[8];
        }
    }
    return result;
}

template<class T>
static std::string sparkhist_g(T x1, T x2, const rarray<T,1>& x, int width, bool zero)
{
    if (width<1) width = 21;
    rarray<unsigned int,1> hist(width);
    T deltax = (x2-x1)/width;
    if (deltax==T(0)) deltax=T(1);
    hist.fill(0);
    for (auto& xvalue: x)
        hist[(unsigned int)((xvalue-x1)/deltax)]++;
    return sparkline_g(hist, width, zero);
}

template<class T>
static std::string sparkhist_g(const rarray<T,1>& x, int width, bool zero)
{
    auto minmaxval = std::minmax_element(&x[0], &x[0] + x.size());
    T min = *minmaxval.first;
    T max = *minmaxval.second;
    T x1 = min, x2;
    if (max < T(0)) {
        x2 = max*(1-2*std::numeric_limits<T>::epsilon()) + std::numeric_limits<T>::is_integer;
    } else {
        x2 = max*(1+2*std::numeric_limits<T>::epsilon()) + std::numeric_limits<T>::is_integer;
    }
    return sparkhist_g(x1, x2, x, width, zero);
}

// sparkline implementation

std::string sparkline(const rarray<char,1>& x,               int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<short,1>& x,              int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<int,1>& x,                int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<long,1>& x,               int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<long long,1>& x,          int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<unsigned char,1>& x,      int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<unsigned short,1>& x,     int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<unsigned int,1>& x,       int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<unsigned long,1>& x,      int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<unsigned long long,1>& x, int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<float,1>& x,              int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<double,1>& x,             int width, bool zero) { return sparkline_g(x, width, zero); }
std::string sparkline(const rarray<long double,1>& x,        int width, bool zero) { return sparkline_g(x, width, zero); }

// sparkhist implementation, first form

std::string sparkhist(const rarray<char,1>& x, int width, bool zero)               { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<short,1>& x, int width, bool zero)              { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<int,1>& x, int width, bool zero)                { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<long,1>& x, int width, bool zero)               { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<long long,1>& x, int width, bool zero)          { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<unsigned char,1>& x, int width, bool zero)      { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<unsigned short,1>& x, int width, bool zero)     { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<unsigned int,1>& x, int width, bool zero)       { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<unsigned long,1>& x, int width, bool zero)      { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<unsigned long long,1>& x, int width, bool zero) { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<float,1>& x, int width, bool zero)              { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<double,1>& x, int width, bool zero)             { return sparkhist_g(x, width, zero); }
std::string sparkhist(const rarray<long double,1>& x, int width, bool zero)        { return sparkhist_g(x, width, zero); }

// sparkhist implementation, second form

std::string sparkhist(char x1, char x2, const rarray<char,1>& x, int width, bool zero)                                           { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(short x1, short x2, const rarray<short,1>& x, int width, bool zero)                                        { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(int x1, int x2, const rarray<int,1>& x, int width, bool zero)                                              { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(long x1, long x2, const rarray<long,1>& x, int width, bool zero)                                           { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(long long x1, long long x2, const rarray<long long,1>& x, int width, bool zero)                            { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(unsigned char x1, unsigned char x2, const rarray<unsigned char,1>& x, int width, bool zero)                { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(unsigned short x1, unsigned short x2, const rarray<unsigned short,1>& x, int width, bool zero)             { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(unsigned int x1, unsigned int x2, const rarray<unsigned int,1>& x, int width, bool zero)                   { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(unsigned long x1, unsigned long x2, const rarray<unsigned long,1>& x, int width, bool zero)                { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(unsigned long long x1, unsigned long long x2, const rarray<unsigned long long,1>& x, int width, bool zero) { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(float x1, float x2, const rarray<float,1>& x, int width, bool zero)                                        { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(double x1, double x2, const rarray<double,1>& x, int width, bool zero)                                     { return sparkhist_g(x1,x2,x,width,zero); }
std::string sparkhist(long double x1, long double x2, const rarray<long double,1>& x, int width, bool zero)                      { return sparkhist_g(x1,x2,x,width,zero); }

// done
