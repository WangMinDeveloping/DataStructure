	#pragma once
    #include "doublyListNode.h"
    template <class TNodeType>
	class DoublyListIterator
	{
	private:
		CDoublyListNode<TNodeType>* pIterator;
	public:
		DoublyListIterator(){}
		~DoublyListIterator(){}
	
		void setValue(CDoublyListNode<TNodeType>* p){pIterator = p;}
	
		inline DoublyListIterator& operator++()
		{
			pIterator = pIterator->pNext;
			return *this;
		}

		inline DoublyListIterator& operator++(int)
		{
			CDoublyListNode<TNodeType>* pTemp = this;
			pIterator = pIterator->pNext;
			return *pTemp;
		}

		inline TNodeType& operator*()
		{
			return this->pIterator->value;
		}

		inline bool operator !=(DoublyListIterator<TNodeType>& p)
		{
			return this->pIterator != p.pIterator;
		}
	};
	