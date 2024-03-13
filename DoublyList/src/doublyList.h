#pragma once
#include"doublyListNode.h"
template<class TNodeType>
class CDoublyList
{
public:
		typedef CDoublyListNode<TNodeType> iterator;
		CDoublyList();	
		~CDoublyList();

		/*
		@brief 					双向链表头插法
		@param 	value[in]： 	插入的值
		@return CDoublyListNode<TNodeType>*		
				大于0 该数据存入的链表结点地址；0 new分配空间失败
		*/
		CDoublyListNode<TNodeType>* insert(TNodeType value);

		/*
		@brief 				删除节点函数
		@param 	pNode[in]： 被删除点的子结点
		@return int：		0 成功  1 失败（参数无效）
		*/
		int deleteNode(CDoublyListNode<TNodeType>* pNode);

		/*
		@brief 				返回双向链表第一个节点
		@param
		@return CDoublyListNode<TNodeType>&: 第一个链表节点引用
		*/
		CDoublyListNode<TNodeType>& begin();

		/*
		@brief 				返回尾节点
		@param
		@return CDoublyListNode<TNodeType>& 尾节点
		*/
		CDoublyListNode<TNodeType>& end();

private:
		CDoublyListNode<TNodeType> *pHeadNode;
		CDoublyListNode<TNodeType> *pTailNode;

};

template <class TNodeType>
CDoublyList<TNodeType>::CDoublyList()
{
	//生成一个头节点和一个尾节点
	pHeadNode = new CDoublyListNode<TNodeType>();//插入函数统一代码，不然每次插入都需要判断pheadNode是否存在，降低效率，只有双向链表需要
	pTailNode = new CDoublyListNode<TNodeType>();//目的是增加一个结束标注，方便迭代器的使用end()
	pHeadNode->pNext = pTailNode;
	pTailNode->pPrev = pHeadNode;
}

template <class TNodeType>
CDoublyList<TNodeType>::~CDoublyList()
{
	//删除所有结点
	CDoublyListNode<TNodeType> *pSeekNode = pHeadNode;
	CDoublyListNode<TNodeType> *pNode;

	while (pSeekNode != 0)
	{
		pNode = pSeekNode->pNext; // 保存删除的下一个结点
		delete pSeekNode;
		pSeekNode = pNode;
	}
	pHeadNode = 0;
}

template <class TNodeType>
CDoublyListNode<TNodeType>& CDoublyList<TNodeType>::begin()
{
	return *(pHeadNode->pNext);
}

template <class TNodeType>
CDoublyListNode<TNodeType> &CDoublyList<TNodeType>::end()
{
	return *pTailNode;
}

template <class TNodeType>
CDoublyListNode<TNodeType> *CDoublyList<TNodeType>::insert(TNodeType value)
{
	CDoublyListNode<TNodeType> *pNewNode = new CDoublyListNode<TNodeType>();
	if (!pNewNode)
		return 0;

	pNewNode->pNext = pHeadNode->pNext;
	pHeadNode->pNext->pPrev = pNewNode;
	
	pNewNode->value = value;
	pNewNode->pPrev = pHeadNode;
	pHeadNode->pNext = pNewNode;
	return pNewNode;
}

template <class TNodeType>
int CDoublyList<TNodeType>::deleteNode(CDoublyListNode<TNodeType> *pNode)
{
	assert(pNode != nullptr);
	pNode->pPrev->pNext = pNode->pNext;
	pNode->pNext->pPrev = pNode->pPrev;
	delete pNode;
	return 0;
}