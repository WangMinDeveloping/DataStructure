#pragma once
/***********************************************************************************************
 功能简述：支持一键多值的红黑树，多个值以单向链表的形式存储。
 作    者: WangMin
 时    间：2021-10
 版    本：1.0
 ************************************************************************************************/
#include <assert.h>
#include "rbNode.h"
#include "readOnlyList.h"
#include "readDeleteList.h"
template <class TKey, class TValue>
class CRedBlackTree
{
public:
	CRedBlackTree() { pRootNode = 0; }
	~CRedBlackTree(); // 删除所有结点

	/*
	@brief 插入函数：
	@param	key[in] 	键
			value[out]	值
	@return 0 成功；1 new分配空间失败
	*/
	int insert(TKey key, TValue value);

	/*
	@brief 	删除函数：
	@param 	key[in] 	键
			value[out] 	值
	@return 0 成功；1 删除键不存在
	*/
	int deleteNode(TKey key, TValue value);

	/*
	@brief 删除函数：
	@param 	key[in] 	键
			pList[in] 	键对应的值链表
	@return 0 成功；1 删除键不存在
	*/
	int deleteNode(TKey key, CReadDeleteList<TValue> *pList);

	/*
	@brief	查找函数
	@param 	key[in] 需要查找的键指针
	@return CReadOnlyList<TValue>*
			大于 0 目标键键的链表; 0 没有找到该键值;
	*/
	CReadOnlyList<TValue> *find(TKey key);

private:
	/*
	@brief 右旋函数
	@param pCenterNode[in] 旋转的中心结点
	@return int -1 参数无效;1 传入的参数为叶子结点;2传进来的结点无左子结点;0 成功
	*/
	int rightRotate(CRedBlackTreeNode<TKey, TValue> *pCenterNode);

	/*
	@brief 左旋函数
	@param pCenterNode[in] 旋转的中心结点
	@return int -1 参数无效；1 传入的参数为叶子结点；2传进来的结点无左子结点
	*/
	int leftRotate(CRedBlackTreeNode<TKey, TValue> *pCenterNode);

	/*
	@brief 插入平衡树函数
	@param pNewNode[in]  新插入的结点
	@return void
	*/
	void balanceInsert(CRedBlackTreeNode<TKey, TValue> *p);

	/*
	@brief 删除平衡函数
	@param p[in] 被删除点的子结点
	@return void
	*/
	void balanceDelete(CRedBlackTreeNode<TKey, TValue> *p);

	/*
	@brief 查找函数
	@param	key[in]：					需要查找的键
			pInsertPosition[out]：		该键值应该插入的位置的地址
	@return CRedBlackTreeNode<TKey,TValue>*
			大于0 目标键键的结点指针; 0 没有找到该键值
	*/
	CRedBlackTreeNode<TKey, TValue> *seek(TKey key, CRedBlackTreeNode<TKey, TValue> **pInsertPosition = 0);

	/*
	@brief 递归方式删除红黑树
	@param pNode[in] 根节点
	@return void
	*/
	static void deleteAll(CRedBlackTreeNode<TKey, TValue> *pNode);

private:
	CRedBlackTreeNode<TKey, TValue> *pRootNode;
};

template <class TKey, class TValue>
int CRedBlackTree<TKey, TValue>::rightRotate(CRedBlackTreeNode<TKey, TValue> *pCenterNode)
{
	CRedBlackTreeNode<TKey, TValue> *pLeftNode; // 中心结点的左子节点
	if (pCenterNode == 0)
		return -1; // 参数无效
	if (pCenterNode->pLeft == 0 && pCenterNode->pRight == 0)
		return 1; // 传进来的结点为叶子结点
	if (pCenterNode->pLeft->pLeft == 0)
		return 2; // 左子结点为叶子结点

	pLeftNode = pCenterNode->pLeft;
	pCenterNode->pLeft = pLeftNode->pRight;	   // 中心结点的左孩子的右孩子赋值给中心结点的左孩子
	pLeftNode->pRight->pFather = pCenterNode;  // 将中心结点赋值为中心结点的左孩子的右孩子的父亲
	pLeftNode->pFather = pCenterNode->pFather; // 将中心结点的父亲赋值为中心结点的左孩子的父亲

	if (pCenterNode->pFather == 0)
		pRootNode = pLeftNode; // 情况1：如果中心结点为根结点，右旋后重新设置根结点
	else if (pCenterNode == pCenterNode->pFather->pRight)
		pCenterNode->pFather->pRight = pLeftNode; // 情况2：如果中心结点是右孩子，更改中心结点父亲的右孩子为中心结点的左孩子
	else
		pCenterNode->pFather->pLeft = pLeftNode; // 情况3：如果中心结点是左孩子，更改中心结点父亲的左孩子为中心结点的左孩子

	pLeftNode->pRight = pCenterNode;  // 将中心结点修正为其左孩子的右孩子
	pCenterNode->pFather = pLeftNode; // 将中心结点的父结点修正为其左孩子
	return 0;
}

template <class TKey, class TValue>
int CRedBlackTree<TKey, TValue>::leftRotate(CRedBlackTreeNode<TKey, TValue> *pCenterNode)
{
	CRedBlackTreeNode<TKey, TValue> *pRightNode; // 中心结点的右子节点
	if (pCenterNode == 0)
		return -1; // 参数无效
	if (pCenterNode->pLeft == 0 && pCenterNode->pRight == 0)
		return 1; // 传进来的结点为叶子结点
	if (pCenterNode->pRight->pLeft == 0)
		return 2; // 右子结点为叶子结点

	pRightNode = pCenterNode->pRight;
	pCenterNode->pRight = pRightNode->pLeft;	// 中心结点的右孩子的左孩子赋值给中心结点的右孩子
	pRightNode->pLeft->pFather = pCenterNode;	// 将中心结点赋值为中心结点的右孩子的左孩子的父亲
	pRightNode->pFather = pCenterNode->pFather; // 将中心结点的父亲赋值为中心结点的右孩子的父亲

	if (pCenterNode->pFather == 0)
		pRootNode = pRightNode; // 情况1：如果中心结点为根结点，右旋后重新设置根结点
	else if (pCenterNode == pCenterNode->pFather->pRight)
		pCenterNode->pFather->pRight = pRightNode; // 情况2：如果中心结点是右孩子，更改中心结点父亲的右孩子为中心结点的右孩子
	else
		pCenterNode->pFather->pLeft = pRightNode; // 情况3：如果中心结点是左孩子，更改中心结点父亲的左孩子为中心结点的右孩子

	pRightNode->pLeft = pCenterNode;   // 将中心结点修正为其右孩子的左孩子
	pCenterNode->pFather = pRightNode; // 将中心结点的父结点修正为其右孩子
	return 0;
}
template <class TKey, class TValue>
CRedBlackTreeNode<TKey, TValue> *CRedBlackTree<TKey, TValue>::seek(TKey key, CRedBlackTreeNode<TKey, TValue> **pInsertPosition)
{
	CRedBlackTreeNode<TKey, TValue> *pSeekNode = pRootNode; // 将根结点的指针赋给pSeekNode
	if (pSeekNode == 0)
		return 0; // 根结点为0
	while (pSeekNode->pLeft != nullptr)
	{
		if (pSeekNode->key == key) // 找到了该键
			return pSeekNode;
		if (key > pSeekNode->key) // 目标键值大于某结点键值
			pSeekNode = pSeekNode->pRight;
		else // 目标键值小于当前结点键值
			pSeekNode = pSeekNode->pLeft;
	}
	if (pInsertPosition != 0) // 如果需要知道目标键值的插入位置
		*pInsertPosition = pSeekNode;
	return 0; // 没有找到对应的键
}

template <class TKey, class TValue>
CReadOnlyList<TValue> *CRedBlackTree<TKey, TValue>::find(TKey key)
{
	CRedBlackTreeNode<TKey, TValue> *pSeekNode = pRootNode; // 将根结点的指针赋给pSeekNode
	CReadOnlyList<TValue> *pReturnList = new CReadOnlyList<TValue>();
	if (pSeekNode == nullptr)
		return 0; // 根结点为0
	while (pSeekNode->pLeft != nullptr)
	{
		if (pSeekNode->key == key) // 找到了该键
		{
			pReturnList->pHeadNode = pSeekNode->pRecordList->pHeadNode;
			return pReturnList;
		}
		if (key > pSeekNode->key) // 目标键值大于某结点键值
			pSeekNode = pSeekNode->pRight;
		else // 目标键值小于当前结点键值
			pSeekNode = pSeekNode->pLeft;
	}
	return 0; // 没有找到对应的键
}

template <class TKey, class TValue>
void CRedBlackTree<TKey, TValue>::balanceInsert(CRedBlackTreeNode<TKey, TValue> *pNewNode)
{
	assert(pNewNode != nullptr);
	CRedBlackTreeNode<TKey, TValue> *pNode = pNewNode; // 用于判断是否平衡
	while (pNode != pRootNode && pNode->pFather->bColor == RED)
	{
		if (pNode->pFather->pFather->pLeft == pNode->pFather) // 如果父结点是祖父的左孩子
		{
			if (pNode->pFather->pLeft == pNode) // 当前结点是父结点的左孩子
			{
				pNode->bColor = BLACK;				  // 新插入的结点改为黑色
				rightRotate(pNode->pFather->pFather); // 右旋成功
				pNode = pNode->pFather;				  // 重新设置pNode
			}
			else // 当前结点为右孩子
			{
				pNewNode = pNode->pFather;
				leftRotate(pNode->pFather);
				pNode = pNewNode;
			}
		}
		else // 父亲结点是右孩子
		{
			if (pNode->pFather->pRight == pNode) // 当前结点是父结点的右孩子
			{
				pNode->bColor = BLACK; // 设置当前结点为黑色
				leftRotate(pNode->pFather->pFather);
				pNode = pNode->pFather;
			}
			else // 当前结点为左孩子
			{
				pNewNode = pNode->pFather;
				rightRotate(pNode->pFather);
				pNode = pNewNode;
			}
		}
	}
	pRootNode->bColor = BLACK;
}
template <class TKey, class TValue>
void CRedBlackTree<TKey, TValue>::deleteAll(CRedBlackTreeNode<TKey, TValue> *pNode)
{
	if (pNode != 0)
	{
		deleteAll(pNode->pLeft);
		deleteAll(pNode->pRight);
		delete pNode->pRecordList;
		delete pNode; // 删除结点
	}
}

template <class TKey, class TValue>
CRedBlackTree<TKey, TValue>::~CRedBlackTree()
{
	if (pRootNode)
	{
		deleteAll(pRootNode);
		pRootNode = 0;
	}
}

template <class TKey, class TValue>
void CRedBlackTree<TKey, TValue>::balanceDelete(CRedBlackTreeNode<TKey, TValue> *p)
{
	CRedBlackTreeNode<TKey, TValue> *pBotherNode;
	CRedBlackTreeNode<TKey, TValue> *pAdjustNode = p;
	while (pAdjustNode != pRootNode && pAdjustNode->bColor == BLACK)
	{
		if (pAdjustNode->pFather->pRight == pAdjustNode) // 当前调整结点是右结点
		{
			pBotherNode = pAdjustNode->pFather->pLeft;
			if (pBotherNode->bColor == RED) // 当前结点的兄弟结点为红色
			{
				pBotherNode->bColor = BLACK;
				pBotherNode->pFather->bColor = RED;
				rightRotate(pBotherNode->pFather);
			}
			else // 当前结点的兄弟结点是黑色
			{
				if (pBotherNode->pLeft->bColor == BLACK && pBotherNode->pRight->bColor == BLACK)
				{
					pBotherNode->bColor = RED;
					pAdjustNode = pAdjustNode->pFather;
				}
				else if (pBotherNode->pLeft->bColor == BLACK && pBotherNode->pRight->bColor == RED)
				{
					pBotherNode->pRight->bColor = BLACK;
					pBotherNode->bColor = RED;
					leftRotate(pBotherNode);
					pBotherNode = pAdjustNode->pFather->pLeft;
				}
				else
				{
					pBotherNode->bColor = pBotherNode->pFather->bColor;
					pBotherNode->pFather->bColor = BLACK;
					pBotherNode->pLeft->bColor = BLACK;
					rightRotate(pBotherNode->pFather);
					pAdjustNode = pRootNode; // 退出循坏
				}
			}
		}
		else // 当前调整结点是左结点
		{
			pBotherNode = pAdjustNode->pFather->pRight;
			if (pBotherNode->bColor == RED) // 当前结点的兄弟结点为红色
			{
				pBotherNode->bColor = BLACK;
				pBotherNode->pFather->bColor = RED;
				leftRotate(pBotherNode->pFather);
				pBotherNode = pAdjustNode->pFather->pRight; // 重新设置兄弟结点
			}
			else // 当前结点的兄弟结点是黑色
			{
				if (pBotherNode->pLeft->bColor == BLACK && pBotherNode->pRight->bColor == BLACK)
				{
					pBotherNode->bColor = RED;
					pAdjustNode = pAdjustNode->pFather;
				}
				else if (pBotherNode->pLeft->bColor == RED && pBotherNode->pRight->bColor == BLACK)
				{
					pBotherNode->pLeft->bColor = BLACK;
					pBotherNode->bColor = BLACK;
					rightRotate(pBotherNode);
					pBotherNode = pAdjustNode->pFather->pRight;
				}
				else
				{
					pBotherNode->bColor = pBotherNode->pFather->bColor;
					pBotherNode->pFather->bColor = BLACK;
					pBotherNode->pRight->bColor = BLACK;
					leftRotate(pBotherNode->pFather);
					pAdjustNode = pRootNode; // 退出循坏
				}
			}
		}
	}
	pAdjustNode->bColor = BLACK;
}
template <class TKey, class TValue>
int CRedBlackTree<TKey, TValue>::insert(TKey key, TValue value)
{
	CRedBlackTreeNode<TKey, TValue> *pNewNode = 0;
	CRedBlackTreeNode<TKey, TValue> *pExistNode; // 如果插入的键经查找已存在，存放该键值的红黑树结点
	pExistNode = this->seek(key, &pNewNode);
	if (pExistNode == 0) // 对应键值不存在
	{
		if (pRootNode == 0) ////插入的键的是根结点
		{
			pNewNode = new CRedBlackTreeNode<TKey, TValue>();
			if (!pNewNode)
				return 1;

			pNewNode->key = key;
			pNewNode->pRecordList = new CSinglyList<TValue>();
			if (pNewNode->pRecordList->insertHead(value) == 1)
				return 1; // 插入失败

			pNewNode->pLeft = new CRedBlackTreeNode<TKey, TValue>(pNewNode); // 叶子结点
			if (!pNewNode->pLeft)
				return 1;

			pNewNode->pRight = new CRedBlackTreeNode<TKey, TValue>(pNewNode); // 叶子结点
			if (!pNewNode->pRight)
				return 1;

			pRootNode = pNewNode; // 设置根结点
			return 0;
		}
		else
		{
			pNewNode->pRecordList = new CSinglyList<TValue>();
			if (pNewNode->pRecordList->insertHead(value) == 1)
				return 1; // 插入失败
			pNewNode->key = key;
			pNewNode->bColor = RED;

			pNewNode->pLeft = new CRedBlackTreeNode<TKey, TValue>(pNewNode); // 叶子结点
			if (!pNewNode->pLeft)
				return 1;													  // 空间分配失败
			pNewNode->pRight = new CRedBlackTreeNode<TKey, TValue>(pNewNode); // 叶子结点
			if (!pNewNode->pRight)
				return 1;
			/*设置叶子结点的父结点*/
			if (pNewNode->pFather->bColor == RED)
				this->balanceInsert(pNewNode);
			return 0;
		}
	}
	else // 插入的键已存在
	{
		if (pExistNode->pRecordList->insertHead(value) == 1) // 插入失败
			return 1;
		return 0;
	}
}
template <class TKey, class TValue>
int CRedBlackTree<TKey, TValue>::deleteNode(TKey key, TValue value)
{
	CRedBlackTreeNode<TKey, TValue> *pInheritedNode; // 继承被删除结点位置的结点
	CRedBlackTreeNode<TKey, TValue> *pDeleteNode;	 // 被删除的结点
	CRedBlackTreeNode<TKey, TValue> *pDeleteKeyNode; // 需要被删除键值的结点
	int iListExist;
	pDeleteKeyNode = this->seek(key);
	if (pDeleteKeyNode == 0)
		return 1; // 没有找到需要删除的结点
	else		  // 找到了需要删除的键值结点
	{
		iListExist = pDeleteKeyNode->pRecordList->deleteNode(value);
		if (iListExist == 1) // 表示数据删除成功，且链表不空
			return 0;
		if (iListExist == -1) // 表示对应值没有找到
			return 1;		  // 失败
		/*删除的值后，链表为空*/
		if (pDeleteKeyNode->pLeft->pLeft == 0 || pDeleteKeyNode->pRight->pLeft == 0) // 被删除结点有一个或没有非空子节点
			pDeleteNode = pDeleteKeyNode;											 // 被删除结点就等于需要被删除键值结点
		else
		{
			pDeleteNode = pDeleteKeyNode->pLeft;
			// 找到左边的最大值
			while (pDeleteNode->pRight->pLeft != 0)
				pDeleteNode = pDeleteNode->pRight;
		}

		if (pDeleteNode->pLeft->pLeft != 0) // 被删除结点左子结点不为空
		{
			pInheritedNode = pDeleteNode->pLeft; // 就把左子结点给继承结点
			delete pDeleteNode->pRight;			 // 删除一个叶子结点
		}
		else // 被删除结点左子节点为空
		{
			pInheritedNode = pDeleteNode->pRight; // 否则把右子结点给继承结点，右子节点可能为叶子结点
			delete pDeleteNode->pLeft;			  // 删除一个叶子结点
		}

		pInheritedNode->pFather = pDeleteNode->pFather; // 将继承结点的父结点修正为被删除的父结点

		if (pDeleteNode->pFather == 0) // 删除点是根结点
		{
			if (pInheritedNode->pKey == nullptr)
			{
				pRootNode = 0; // 将继承结点赋值给根结点
				delete pInheritedNode;
				pInheritedNode = 0;
			}
			else
				pRootNode = pInheritedNode;
		}
		else // 被删除点不是根结点
		{
			if (pDeleteNode->pFather->pRight == pDeleteNode)   // 被删除结点是右孩子
				pDeleteNode->pFather->pRight = pInheritedNode; // 继承结点为右孩子
			else
				pDeleteNode->pFather->pLeft = pInheritedNode; // 继承结点为左孩子
		}
		delete pDeleteKeyNode->pRecordList;
		pDeleteKeyNode->key = pDeleteNode->key;
		pDeleteKeyNode->pRecordList = pDeleteNode->pRecordList;

		if (pDeleteNode->bColor == BLACK && pRootNode != nullptr) // 被删除的结点为黑色
			this->balanceDelete(pInheritedNode);				  // 调用删除平衡调节函数
		delete pDeleteNode;
	}
	return 0; // 删除成功
}
template <class TKey, class TValue>
int CRedBlackTree<TKey, TValue>::deleteNode(TKey key, CReadDeleteList<TValue> *pList)
{
	CRedBlackTreeNode<TKey, TValue> *pInheritedNode; // 继承被删除结点位置的结点
	CRedBlackTreeNode<TKey, TValue> *pDeleteNode;	 // 被删除的结点
	CRedBlackTreeNode<TKey, TValue> *pDeleteKeyNode; // 需要被删除键值的结点
	pDeleteKeyNode = this->seek(key);
	if (pDeleteKeyNode == 0)
		return 1; // 没有找到需要删除的结点
	else		  // 找到了需要删除的键值结点
	{
		/*没有指定删除哪一个值*/
		if (pDeleteKeyNode->pLeft->pLeft == 0 || pDeleteKeyNode->pRight->pLeft == 0) // 被删除结点有一个空子节点或两个空结点
			pDeleteNode = pDeleteKeyNode;											 // 被删除结点就等于需要被删除键值结点
		else
		{
			pDeleteNode = pDeleteKeyNode->pLeft;
			// 找到左边的最大值
			while (pDeleteNode->pRight->pLeft != 0)
				pDeleteNode = pDeleteNode->pRight;
		}

		if (pDeleteNode->pLeft->pLeft != 0) // 被删除结点左子结点不为空
		{
			pInheritedNode = pDeleteNode->pLeft; // 就把左子结点给继承结点
			delete pDeleteNode->pRight;
		}
		else // 被删除结点左子节点为空
		{
			pInheritedNode = pDeleteNode->pRight; // 否则把右子结点给继承结点，右子节点可能为叶子结点
			delete pDeleteNode->pLeft;
		}

		pInheritedNode->pFather = pDeleteNode->pFather; // 将继承结点的父结点修正为被删除的父结点

		if (pDeleteNode->pFather == 0) // 删除点是根结点
		{
			if (pInheritedNode->key == 0)
			{
				pRootNode = 0; // 将继承结点赋值给根结点
				delete pInheritedNode;
				pInheritedNode = 0;
			}
			else
				pRootNode = pInheritedNode;
		}
		else // 被删除点不是根结点
		{
			if (pDeleteNode->pFather->pRight == pDeleteNode)   // 被删除结点是右孩子
				pDeleteNode->pFather->pRight = pInheritedNode; // 继承结点为右孩子
			else
				pDeleteNode->pFather->pLeft = pInheritedNode; // 继承结点为左孩子
		}
		pList->pHeadNode = pDeleteKeyNode->pRecordList->pHeadNode; // 把删除结点的链表插入到传进来参数的链表

		pDeleteKeyNode->pRecordList->pHeadNode = 0; // 不删除链表
		delete pDeleteKeyNode->pRecordList;

		pDeleteKeyNode->key = pDeleteNode->key;
		pDeleteKeyNode->pRecordList = pDeleteNode->pRecordList;

		if (pDeleteNode->bColor == BLACK && pRootNode != nullptr) // 被删除的结点为黑色
			this->balanceDelete(pInheritedNode);				  // 调用删除平衡调节函数
		delete pDeleteNode;										  // 删除红黑树结点
	}
	return 0; // 删除成功
}