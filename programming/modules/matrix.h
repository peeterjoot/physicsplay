#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <cstddef>
#include <cassert>

enum what : int
{
   zero,
   identity
};

class matrix
{
private:
   typedef std::size_t size_type;

   enum sz : int
   {
      size = 4
   };

   float x[size*size]{};
   // 1 2 3 4
   // 1 2 3 4
   // 1 2 3 4
   // 1 2 3 4

   static inline size_type index( size_type i, size_type j ) {
      assert( i > 0 );
      assert( j > 0 );
      assert( i <= size );
      assert( j <= size );

      size_type v = size*(i - 1) + j - 1;

      return v;
   }
public:

   matrix() {}

   void set( what );

   float & elem( size_type i, size_type j ) {
      size_type e = index(i, j);
      return x[e];
   }

   const float & elem( size_type i, size_type j ) const {
      size_type e = index(i, j);
      return x[e];
   }
};

#endif
