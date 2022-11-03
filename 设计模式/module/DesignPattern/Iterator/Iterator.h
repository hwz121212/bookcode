
/********************************************************************
	CREATED:	2012/01/31
	FILENAME:	Iterator.h
	AUTHOR:		By Robot
	
	PURPOSE:	迭代器模式
		当你需要访问一个聚集对象，而且不管这些对象是什么都需要遍历的时候，
		你就应该考虑使用迭代器模式；为遍历不同的聚集结构提供如：开始、下一个、
		是否结束、当前哪一项等统一的接口。
*********************************************************************/


#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <iostream>
using std::cout;
using std::endl;

typedef int DATA;

class Aggregate;

/**
	迭代器抽象类
*/
class Iterator
{
public:
	Iterator(){}
	virtual ~Iterator(){}
	// 定义标准通用接口
	virtual void MoveToFirst() = 0;		//!< 指向第一个
	virtual void MoveToNext() = 0;		//!< 指向当前的下一个
	virtual bool IsEnd() = 0;			//!< 判断当前是否在容器的End位置
	virtual DATA CurrentItem() = 0;		//!< 获取当前元素
};


/**
	具体迭代器类
*/
class ConcreateIterater : public Iterator
{
public:
	ConcreateIterater(Aggregate* pAggregate);
	~ConcreateIterater();
	void MoveToFirst();
	void MoveToNext();
	bool IsEnd();
	DATA CurrentItem();
private:
	Aggregate* m_pAggreatate;
	int m_iCurrPosition;
};


#endif
