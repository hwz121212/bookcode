// Iterator.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/31
	FILENAME:	main.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	������ģʽ
		������Ҫ����һ���ۼ����󣬶��Ҳ�����Щ������ʲô����Ҫ������ʱ��
		���Ӧ�ÿ���ʹ�õ�����ģʽ��Ϊ������ͬ�ľۼ��ṹ�ṩ�磺
		��ʼ����һ�����Ƿ��������ǰ���ͳһ�Ľӿڡ�
*********************************************************************/

#include "stdafx.h"
#include <iostream>
#include "Aggregate.h"

/**
	��ں���
*/
int _tmain(int argc, _TCHAR* argv[])
{
	// ��������
	Aggregate* testAgg = new ConcreateAggregate(5);

	// ���������ĵ�����
	Iterator* testIt = testAgg->CreateIterater();

	// ʹ�õ�������������
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

