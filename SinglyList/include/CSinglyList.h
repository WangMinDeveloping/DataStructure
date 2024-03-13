#pragma once
#include "SSinglyListNode.h"
template<class TDATA>
class CSinglyList
{
public:
	CSinglyList(){pHeadNode=0;}
	virtual ~CSinglyList();//删除所有结点
	int insertHead(TDATA value);
	int deleteNode(TDATA value);
private:
	SSinglyListNode<TDATA> *pHeadNode;
};

template <class TDATA>
/*删除所有链表结点*/
CSinglyList<TDATA>::~CSinglyList()
{
	SSinglyListNode<TDATA> *pSeekNode = pHeadNode;
	SSinglyListNode<TDATA> *pNode;

	while (pSeekNode != 0)
	{
		pNode = pSeekNode->pNext; // 保存删除的下一个结点
		delete pSeekNode;
		pSeekNode = pNode;
	}
	pHeadNode = 0;
}
/************************************
  插入函数（头插法）
  参数：值
  返回值：0 成功；1 失败
 ************************************/
template <class TDATA>
int CSinglyList<TDATA>::insertHead(TDATA value)
{
	SSinglyListNode<TDATA> *pNewNode = new SSinglyListNode<TDATA>();
	if (!pNewNode)
		return 1;
	pNewNode->pNext = pHeadNode;
	pNewNode->value = value;
	pHeadNode = pNewNode;

	return 0;
}

/************************************************************************************
  删除函数
  参数：存入链表的值
  返回值：1 删除成功且链表为空；-1 没有找到需要删除的结点；0结点删除成功且链表不为空
 **************************************************************************************/
template <class TDATA>
int CSinglyList<TDATA>::deleteNode(TDATA value)
{
	int iNull = -1; // 返回值
	SSinglyListNode<TDATA> *pSeekNode = pHeadNode;
	SSinglyListNode<TDATA> *pSeekNodeLast = 0;
	SSinglyListNode<TDATA> *pSeekNodeNext;
	while (pSeekNode != 0)
	{
		if (pSeekNode->value != value)
		{
			pSeekNodeLast = pSeekNode;
			pSeekNode = pSeekNode->pNext;
		}
		else
		{
			pSeekNodeNext = pSeekNode->pNext;
			if (pSeekNodeLast != 0)
				pSeekNodeLast->pNext = pSeekNodeNext;
			else
				pHeadNode = pSeekNodeNext;

			delete pSeekNode;
			pSeekNode = pSeekNodeNext;
			iNull = 1;
		}
	}
	if (pHeadNode == 0) // 检测链表是否为空
		return 0;
	return iNull;
}
