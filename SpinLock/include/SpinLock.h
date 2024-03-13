#pragma once
#include"Lock.h" 
class SpinLock : public Lock
{
	private:
		long long *pAddress;
	public:
		~SpinLock();
		SpinLock();
		void enter();
		void leave();
};