#pragma once
/***********************************************************************************************
 功能简述：多线程安全队列，入队成员为空指针。
 注	   意：放进队列的指针不能为0
 使用场景：需要多线程高性能开发的场景
 作    者: WangMin
 时    间：2021-5
 版    本：1.0
 ************************************************************************************************/
namespace unlockQueue
{
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
			bool initialize(int iQueueLen);
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
			int enQueue(void *pMember);

			/*
			@brief 					出队函数
			@param 
			@return void*：			1:队空; 大于1:出队指针
			*/
			void* deQueue();
	private:
			long long	llFront;
			long long	llRear;
			int 		iMemberCount;
			int 		iEmptySeatCount;
			int 		iMaximum; //原来是整型
			void*		(*pArray)[];
	};
};