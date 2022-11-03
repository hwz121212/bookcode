// Iterator.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/31
	FILENAME:	main.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	迭代器模式
		当你需要访问一个聚集对象，而且不管这些对象是什么都需要遍历的时候，
		你就应该考虑使用迭代器模式；为遍历不同的聚集结构提供如：
		开始、下一个、是否结束、当前项等统一的接口。
*********************************************************************/

#include "stdafx.h"
#include <iostream>
#include "Aggregate.h"

/**
	入口函数
*/
int _tmain(int argc, _TCHAR* argv[])
{
	// 创建容器
	Aggregate* testAgg = new ConcreateAggregate(5);

	// 创建容器的迭代器
	Iterator* testIt = testAgg->CreateIterater();

	// 使用迭代器访问容器
	while(!testIt->IsEnd())
	{
		cout <<testIt->CurrentItem()<<endl;
		testIt->MoveToNext();
	}
	
	testIt->MoveToFirst();
	cout <<testIt->CurrentItem()<<endl;
	testIt->MoveToNext();
	cout <<testIt->CurrentItem()<<endl;

	system("pause");
	return 0;
}

