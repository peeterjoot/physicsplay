// This was triggering an abort in memberdumper:

template <class T, size_t extraSize >
struct OSS_STRUCTURE_PAD_DELTA : public T
{
   char pad[ extraSize ] ;
} ;
