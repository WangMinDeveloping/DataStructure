#pragma once
#include"readDeleteList.h"
template<class TVALUE>
class CReadOnlyList:public CReadDeleteList<TVALUE>
{
public:
	CReadOnlyList(){}
	~CReadOnlyList(){this->pHeadNode=0;}
};
#include "readDeleteList.hpp"