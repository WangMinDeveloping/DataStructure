#include "queue.h"
#include <stdio.h>

queue::queue(/* args */)
{
}

queue::~queue()
{
}

bool queue::initialize(int iMaximum)
{
    m_iMaximum = iMaximum;
    m_pQueueArray = (void *(*)[])new void*[iMaximum];
    if (!m_pQueueArray)
        return false;
    m_iFront = 0;
    m_iRear = 0;
    return true;
}

// 销毁对象
void queue::close()
{
    delete []m_pQueueArray;
}

// 获取队列长度
int queue::getQueueLength()
{
    return m_iMaximum;
}

// 获取队列里成员个数
int queue::getQueueMemberCount()
{
    return (m_iRear - m_iFront + m_iMaximum) % m_iMaximum;
}

int queue::enQueue(void *pMember)
{
    unsigned int iRear;
    iRear = (m_iRear + 1) % m_iMaximum;
    if (iRear == m_iFront) // 如果队尾下标加1 等于 队头下标 则认为队列已满
    {
        return 1;
    }
    (*m_pQueueArray)[m_iRear] = pMember;
    m_iRear = iRear;
    return 0;
}

int queue::deQueue(void **pMember)
{
    if (m_iFront == m_iRear) 
    {
        return 1;
    }
    *pMember = (*m_pQueueArray)[m_iFront];
    m_iFront = (m_iFront + 1) % (m_iMaximum);
    return 0;
}