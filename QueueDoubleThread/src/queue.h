#pragma once
/*************************************************************************************
 功能简述：双线程安全队列，一入一出线程安全。
 注    意：队列初始化长度必须大于1
 作    者: WangMin
 时    间：2021-9
 版    本：1.0
 *************************************************************************************/
class queue
{
public:
    queue(/* args */);
    ~queue();

  
    /*
		@brief 				    队列初始化
		@param 	iMaximum[in]：  队列初始化最大长度
        @return	                true-成功  false-失败
	*/
    bool initialize(int iMaximum);

    /*
		@brief 				    关闭函数
		@param 
        @return	                
	*/
    void close();

    
    /*
		@brief 				    获取队列最大长度
		@param 
        @return	                队列长度
	*/
    int getQueueLength();

    
    /*
		@brief 				    获取队列已有成员
		@param 	
        @return	                队列成员数量
	*/
    int getQueueMemberCount();

    /*
		@brief 				    入队函数
		@param 	pMember[in]：   队列指针
        @return	                0-成功  1-队满
	*/
    int enQueue(void* pMember);


    /*
		@brief 				    出队函数
		@param 	pMember[out]：  出队指针的地址
        @return	                0-成功  1-队空
	*/
    int deQueue(void**pMember);

private:
    unsigned int m_iFront;
	unsigned int m_iRear;
	unsigned int m_iMaximum;//定义队列的大小
	void *(*m_pQueueArray)[];//队列首字节地址，队列成员变量首字节地址
};

