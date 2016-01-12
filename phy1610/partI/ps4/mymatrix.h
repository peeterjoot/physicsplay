//
// mymatrix.h - reference matrix class, header file
//
// Part of the "Profiling and optimization" assignment of the
// "Scientific Software Development" mini-course by SciNet.
//
// For instructional purpose only.  Don't use in production code.
//
// Ramses van Zon, January 2015
//

#ifndef MYMATRIX
#define MYMATRIX

class MyMatrix 
{
  public:
    MyMatrix(int r, int c);
    ~MyMatrix();
    int      get_rows();
    int      get_columns();
    double   get_element(int i, int j);
    void     set_element(int i, int j, double value);
    void     output(const char* filename);
  private:
    int      row;
    int      col;
    double** el;
};

#endif
