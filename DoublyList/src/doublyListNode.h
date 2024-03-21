#pragma once
template<class TDataType>
class CDoublyListNode
{
public:
	CDoublyListNode<TDataType> *pNext;
	CDoublyListNode<TDataType> *pPrev;
	TDataType value;
};