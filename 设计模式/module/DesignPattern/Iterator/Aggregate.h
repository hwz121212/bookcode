

#ifndef __AGGREGATE_H__
#define __AGGREGATE_H__

#include "Iterator.h"

/**
	容器的抽象基类
*/
class Aggregate
{
public:
	Aggregate(){}
	virtual ~Aggregate(){}
	virtual Iterator* CreateIterater() = 0;
	virtual int GetSize() = 0;
	virtual DATA GetItem(int nIndex) = 0;
};


/**
	具体容器类
*/
class ConcreateAggregate : public Aggregate
{
public:
	ConcreateAggregate(int Size);
	~ConcreateAggregate();
	Iterator* CreateIterater();
	int GetSize();
	DATA GetItem(int nIndex);
private:
	int m_iSize;
	DATA* m_pData;
};


#endif

