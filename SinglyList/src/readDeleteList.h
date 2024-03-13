#pragma once
#include "CSinglyList.h"
template<class TValueType>
class CReadDeleteList:public CSinglyList<TValueType>
{
protected:
		using CSinglyList<TValueType>::insertHead;
		using CSinglyList<TValueType>::deleteNode;
public:
		TValueType iterator(void);
		CReadDeleteList(){pIteratorPosition=0;}
		~CReadDeleteList(){}
private:
		  SSinglyListNode<TValueType>* pIteratorPosition;
};

template<class TValueType>
/**********************************
  迭代器
  参数：无
  返回值：存储的数据 
 **********************************/
TValueType CReadDeleteList<TValueType>::iterator(void)
{
	if(pIteratorPosition==nullptr)
		pIteratorPosition=this->pHeadNode;
	else
		pIteratorPosition=pIteratorPosition->pNext;
	if(pIteratorPosition!=nullptr)
		return pIteratorPosition->value;
	return 0;
}
