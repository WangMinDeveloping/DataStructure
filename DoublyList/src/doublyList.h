#pragma once
#include "doublyListNode.h"
#include "doublyListIterator.h"

#define InitNodeNum (512)
#define PieceCount (1024*1024)

template <class TNodeType>
class CDoublyList
{
public:
	typedef DoublyListIterator<TNodeType> iterator;
	CDoublyList();
	~CDoublyList();

	/*
	@brief 					双向链表尾插法
	@param 	value[in]： 	插入的值
	@return CDoublyListNode<TNodeType>*
			大于0 该数据存入的链表结点地址；0 new分配空间失败
	*/
	CDoublyListNode<TNodeType> *insertTail(TNodeType value);

	/*
	@brief 				删除节点函数
	@param 	pNode[in]： 被删除点的子结点
	@return int：		0 成功  1 失败（参数无效）
	*/
	int deleteNode(CDoublyListNode<TNodeType> *pNode);

	/*
	@brief 				返回双向链表第一个节点
	@param
	@return CDoublyListNode<TNodeType>&: 第一个链表节点引用
	*/
	DoublyListIterator<TNodeType> begin();

	/*
	@brief 				返回尾节点
	@param
	@return CDoublyListNode<TNodeType>& 尾节点
	*/
	DoublyListIterator<TNodeType>& end();

private:
	CDoublyListNode<TNodeType> *pHeadNode;
	CDoublyListNode<TNodeType> *pTailNode;
	CDoublyListNode<TNodeType> *pCurrentNode; //当前的空节点 ，用户插入节点
	CDoublyListNode<TNodeType>** pieceArray;
	unsigned long long pieceNum;
	iterator tailIterator;
};

template <class TNodeType>
CDoublyList<TNodeType>::CDoublyList()
{
	CDoublyListNode<TNodeType> *p  = new CDoublyListNode<TNodeType>[InitNodeNum]();
	pieceArray  = new CDoublyListNode<TNodeType>*[PieceCount]();
	for (int i = 0; i < PieceCount; i++)
	{
		pieceArray[i] = nullptr;
	}

	pHeadNode = &p[0];
	pHeadNode->pNext = &p[1];
	pHeadNode->pPrev = nullptr;

	for (int i = 1; i < InitNodeNum - 1; i++)
	{
		p[i].pNext = &p[i+1];
		p[i].pPrev = &p[i-1];
	}
	
	pTailNode = &p[InitNodeNum - 1];
	pTailNode->pPrev = &p[InitNodeNum - 2];
	pTailNode->pNext = nullptr;

	pCurrentNode = &p[0];

	pieceNum = 0;
	pieceArray[pieceNum++] = p;
}

template <class TNodeType>
CDoublyList<TNodeType>::~CDoublyList()
{
	// 删除所有结点
	CDoublyListNode<TNodeType> *pSeekNode = pHeadNode;
	CDoublyListNode<TNodeType> *pNode;

	int i = 0;
	while (i < PieceCount && pieceArray[i] != 0)
	{
		delete[] pieceArray[i];
		pieceArray[i] = nullptr;
		i++;
	}
}

template <class TNodeType>
DoublyListIterator<TNodeType> CDoublyList<TNodeType>::begin()
{
	iterator headIterator;
	headIterator.setValue(pHeadNode->pNext);
	return headIterator;
}

template <class TNodeType>
DoublyListIterator<TNodeType>& CDoublyList<TNodeType>::end()
{
	tailIterator.setValue(pCurrentNode);
	return tailIterator;
}

//尾插法
template <class TNodeType>
CDoublyListNode<TNodeType> *CDoublyList<TNodeType>::insertTail(TNodeType value)
{
	CDoublyListNode<TNodeType> *pRetNode = nullptr;
	if (pCurrentNode != pTailNode)
	{
		pCurrentNode->value = value;
		pRetNode = pCurrentNode;
		pCurrentNode = pCurrentNode->pNext;
	}
	else
	{
		CDoublyListNode<TNodeType> *p  = new CDoublyListNode<TNodeType>[InitNodeNum]();
		if (pieceNum < PieceCount)
		{
			pieceArray[pieceNum++] = p;
		}
		else
		{
			return 0;
		}

		//处理中间部分，防止数组越界
		for (int i = 1; i < InitNodeNum - 1; i++)
		{
			p[i].pNext = &p[i+1];
			p[i].pPrev = &p[i-1];
		}
		
		pCurrentNode = &p[0];
		pCurrentNode->pNext = &p[1];
		pCurrentNode->pPrev = pTailNode->pPrev;
		pTailNode->pPrev->pNext = pCurrentNode;

		pTailNode->pPrev = &p[InitNodeNum - 1];
		p[InitNodeNum - 1].pNext = pTailNode;
		p[InitNodeNum - 1].pPrev = &p[InitNodeNum - 2];

		pCurrentNode->value = value;
		pRetNode = pCurrentNode;
		pCurrentNode = pCurrentNode->pNext;
	}

	return pRetNode;
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