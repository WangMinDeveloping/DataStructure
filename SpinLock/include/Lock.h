#pragma once
class Lock
{
	public:
		virtual ~Lock(){}
		virtual void enter()=0;
		virtual void leave()=0;
};
