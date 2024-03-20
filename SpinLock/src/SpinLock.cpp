#include"SpinLock.h"
SpinLock::SpinLock()
{
	pAddress=new long long();
}
SpinLock::~SpinLock()
{
	delete pAddress;
}

inline void SpinLock::leave()
{
	asm("movq $0,%0;":"=m"(*pAddress));
}
inline void SpinLock::enter()
{
    asm("loop:lock btsl $0,%0;jc loop;":"+m"(*pAddress));
}

