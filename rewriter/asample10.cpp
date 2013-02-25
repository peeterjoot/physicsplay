// memberdumper with isDependentType() checking misses the m_pNext field:
template <class DATA_TYP>
struct noInheritance
{
   noInheritance<DATA_TYP>* m_pNext;
   int m_priKey;
};

