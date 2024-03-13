#pragma once
#include"Lock.h"
class LockAuto
{
	private:
		Lock *lock;
	public:
		LockAuto(Lock *lock);
		~LockAuto();
};

	
	
