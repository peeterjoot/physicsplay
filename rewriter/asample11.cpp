// memberdumper (even with isDependentType()) hits null pointer error deep in clang stack
template <class DATA_TYP>
struct links
{
      links<DATA_TYP>* m_pNext;
};

template <class DATA_TYP>
struct withInheritance : public links<DATA_TYP>
{
      int m_priKey;
};

struct moreInheritance : public withInheritance<int> {
   int x ;
} ;
