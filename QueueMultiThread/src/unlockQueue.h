#pragma once
class Queue
{
public:
//#define enQueue(pMember) {asm("sti");  _enQueue(void *pMember);}	
		Queue();
		~Queue();
		/*
		@brief 					初始化函数
		@param iQueueLen[in]：	队列最大长度
		@return bool：			false 失败；true 成功
		*/	
		bool init(int iQueueLen);
		void close();

		/*
		@brief 					获取队列最大长度
		@param 
		@return int：			队列最大长度
		*/
		int getQueueLength();
		
		/*
		@brief 					获取当前队长
		@param
		@return int：			当前队长
		*/
		int getQueueMemberCount();

		/*
		@brief 					入队函数
		@param pMember[in]：	需要入队的指针变量
		@return int：			0、成功；1、队满
		*/
		int _enQueue(void *pMember);

		/*
		@brief 					出队函数
		@param 
		@return void*：			1:队空; 大于1:出队指针
		*/
		void* _deQueue();
private:
		long long	llFront;
		long long	llRear;
		int 		iMemberCount;
		int 		iEmptySeatCount;
		int 		iMaximum; //原来是整型
		void*		(*pArray)[];
};