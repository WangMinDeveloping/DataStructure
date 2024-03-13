#pragma once
template<class TDataType>
class CDoublyListNode
{
public:
	CDoublyListNode<TDataType> *pNext;
	CDoublyListNode<TDataType> *pPrev;
	TDataType value;
	CDoublyListNode<TDataType>& operator++();
	CDoublyListNode<TDataType>& operator +(int num);
	bool operator !=(CDoublyListNode<TDataType> &p);
	TDataType& operator*();
};

template<class TDataType>
CDoublyListNode<TDataType>& CDoublyListNode<TDataType>::operator ++()
{
	return *(this->pNext);
}

template<class TDataType>
CDoublyListNode<TDataType>& CDoublyListNode<TDataType>::operator +(int num)
{
	CDoublyListNode<TDataType> *pNode=this;
	while(num--)
	{
		pNode=pNode->pNext;
	}
	return *pNode;
}

template<class TDataType>
TDataType& CDoublyListNode<TDataType>::operator*()
{
	return this->value;
}

template<class TDataType>
bool CDoublyListNode<TDataType>::operator !=(CDoublyListNode<TDataType> &p)
{
	return this->pNext != p.pNext;
}
