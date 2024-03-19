#include "unlockQueue.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
using namespace unlockQueue;
Queue::Queue()
{
	llFront = 0;
	llRear = 0;
	iMemberCount = 0;
	iEmptySeatCount = 0;
	iMaximum = 0;
	pArray = NULL;
}
Queue::~Queue()
{

}

bool Queue::initialize(int iQueueLen)
{
	pArray=(void* (*)[])new void*[iQueueLen]();
	memset(pArray,0,sizeof(void*)*iQueueLen);

	iMaximum=iQueueLen;
	iMemberCount=0;
	iEmptySeatCount=iQueueLen;
	llFront=0;
	llRear=0;
	return true;
}

void Queue::close()
{
	delete []pArray;
	pArray=0;
}

int Queue::getQueueLength()
{
	return iMaximum;
}

int Queue::getQueueMemberCount()
{
	return llRear-llFront;
}

int Queue::enQueue(void *pMember)
{
	//纯汇编版本
	asm volatile("\
			movl %3,%%ecx; /*最大队长*/\
            movq %2,%%r9;/*需要入队的数据*/\
			mov %1,%%r14;  /*队尾序号*/ \
	 loopEn:mov %4,%%r15; /*队头序号*/ \
			sub %%r15,%%r14; /*当前队长*/ \
			movslq %%ecx,%%rcx;/* ecx符号扩展为rcx*/ \
			cmp %%rcx,%%r14; /*判断当前队长是否等于最大队长*/ \
			jnz enQueue; /*不满则入队*/ \
            movl $1,%%eax;/*队列为满返回1*/ \
            leaveq;\
            retq;\
	enQueue:add %%r15,%%r14; /*队尾序号恢复 cqto;队尾序号的符号位放入rdx*/ \
			mov %%r14,%%rax; /*队尾序号*/ \
			inc %%r14;/*寄存器队尾序号加1*/ \
			cqto;\
            div %%rcx;/*队尾下标对队长取余,余值在rdx*/ \
            movq $0,%%rax;/*rax=0*/ \
            movq %5,%%r10;/*队列数组首字节地址*/ \
            lea (%%r10,%%rdx,8),%%r10;/*r10存储队尾下标元素的首字节地址*/\
            lock cmpxchgq %%r9,(%%r10);/*原队尾下标元素为0，r9入队，元素非0,就存入rax*/ \
            jnz loopEn;\
			lock incq %0;/*内存队尾序号加1*/ \
			/*sti; 开中断*/ \
			movl $0,%%eax;/*成功返回0*/ \
			leaveq;\
			retq;"\
			:"=m"(llRear)\
			:"m"(llRear),"m"(pMember),"m"(iMaximum),"m"(llFront),"m"(pArray)\
			:"%rax","%rbx","%rdx","%rcx","%r9","%r10","%r14","%r15");

}

void*  Queue::deQueue()
{
	// 纯汇编版本
	asm volatile("\
			movl %2,%%ecx; /*最大队长*/\
			movslq %%ecx,%%rcx;\
			mov %3,%%r14;  /*队头序号*/ \
 	loopDe:	mov %1,%%r15; /*队尾序号*/ \
			cmp %%r14,%%r15; /*判断队空*/ \
			jnz deQueue; /*不空则出队*/ \
            mov $1,%%rax;/*队列为空返回1*/ \
            leaveq;\
            retq;\
	deQueue:mov %%r14,%%rax; /*队头序号*/ \
			inc %%r14;/*寄存器队头序号加1*/ \
			cqto;\
            div %%rcx;/*队头下标对队长取余,余值在rdx*/ \
            movq $0,%%rax;/*rax=0*/ \
            movq %4,%%r10;/*队列数组首字节地址*/ \
            lea (%%r10,%%rdx,8),%%r10;/*r10存储队尾下标元素的首字节地址*/\
            lock xchgq %%rax,(%%r10);/*0与队列队头下标元素交换*/ \
			test %%rax,%%rax;/*判断出队值是否为0*/\
            jz loopDe;/*rax若为0则说明没有抢到再回去抢下一个*/\
			lock incq %0;/*内存队头序号加1*/ \
			/*sti; 开中断*/ \
			leaveq;\
			retq;"\
			:"=m"(llFront)\
			:"m"(llRear),"m"(iMaximum),"m"(llFront),"m"(pArray)\
			:"%rax","%rdx","%rcx","%r10","%r14","%r15");
}
