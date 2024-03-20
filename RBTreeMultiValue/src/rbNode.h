#pragma once
#include <stdlib.h>
#define RED 0
#define BLACK 1
#include "CSinglyList.h"
template <class KeyType, class ValueType>
class CRedBlackTreeNode
{
public:
        CRedBlackTreeNode<KeyType, ValueType> *pLeft;
        CRedBlackTreeNode<KeyType, ValueType> *pRight;
        CRedBlackTreeNode<KeyType, ValueType> *pFather;
        KeyType key;
        bool bColor;
        CSinglyList<ValueType> *pRecordList; // 键重复时的链表
        CRedBlackTreeNode(CRedBlackTreeNode<KeyType, ValueType> *pFatherNode = NULL)
        {
                pLeft = NULL;
                pRight = NULL;
                pFather = pFatherNode;
                bColor = BLACK;
                pRecordList = NULL; // 不支持键重复
        }
        ~CRedBlackTreeNode(){};
};