class foo
{
   public:
   char v ;
} ;

struct blah
{
   char z ;
} ;

typedef blah moo ;
#define Moo blah

union uu
{
   int ui ;
   char uc ;
} ;

struct Test
{
   int a, b ;

   moo c ;
   Moo d ;

   uu umember ;

   blah bb[ 3 ] ;
} ;

class bar : public foo
{
   public:
   char w ;

   Test t ;
} ;
