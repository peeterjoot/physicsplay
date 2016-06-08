#if defined __cplusplus
   #define EXTERNC extern "C"
   #define NOEXCEPT noexcept
#else
   #define EXTERNC
   #define NOEXCEPT
#endif

EXTERNC int foo(void) NOEXCEPT ;
