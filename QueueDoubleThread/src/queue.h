#pragma once
class queue
{
public:
    queue(/* args */);
    ~queue();

    /*
     队列初始化
    输入:1、队列对象指针;2、队列长度
    返回值:1、失败; 0、成功
    */
    bool initialize(int iMaximum);

    void close();
    int getQueueLength();
    int getQueueMemberCount();

    /*
    入队函数:
    输入：1、队列对象指针；2、入队变量指针 
    返回值：0、成功；1、队满;
    */
    int enQueue(void* pMember);

    /*
    出队函数
    输入：1、队列对象指针；2、出队变量指针
    返回值：0、成功;1、队空;
    */
    int deQueue(void**pMember);

private:
    unsigned int m_iFront;
	unsigned int m_iRear;
	unsigned int m_iMaximum;//定义队列的大小
	void *(*m_pQueueArray)[];//队列首字节地址，队列成员变量首字节地址
};

