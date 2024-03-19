#pragma once
/*************************************************************************************
 功能简述：多线程内存池栈，初始化可以生成指定数量，指定大小的内存块，通过pop获取其中一块，以供外界使用，
	      在外面使用完成之后，可以使用push函数将内存块回收到内存池栈中。
 使用场景：需要多线程高性能开发的场景
 作    者: WangMin
 时    间：2021-8
 版    本：1.0
 *************************************************************************************/

class CMemoryPool
{
	public:
		/*
		@brief 				 内存池初始化
		@param 	iCount[in]： 内存块的数量
				 iSize[in]:	 每个内存块的大小
		*/
		CMemoryPool(int iCount, int iSize); 

		~CMemoryPool();

		/*
		@brief 				 随机弹出一块空的内存块
		@param 	 void
		@return	 void*		 >1 内存块首字节地址； =0 栈空
		*/
		void* pop(void);

		
		/*
		@brief 				 回收不使用的内存块
		@param 	 void*[in]	 不使用的内存块的首地址
		@return  int         0 成功； 1 栈满
		*/
		int push(void * pMember);//将不用内存块首地址地址入栈，

		
		/*
		@brief 				 获取内存块最小地址
		@param 
		@return	 void*		 内存块最小地址
		*/
		void* getMinAddress();

		
		/*
		@brief 				 获取内存块最大地址
		@param 	 void
		@return	 void*		 内存块最大地址
		*/
		void* getMaxAddress();

	private:
		int iMaximum;
		int iStackTop;
		char *pMaxAddress;
		void* (*pStackArray)[];
		char* pMemory;
};
