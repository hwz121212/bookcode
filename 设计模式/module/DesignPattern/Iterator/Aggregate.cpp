
#include "stdafx.h"
#include "Aggregate.h"
#include <assert.h>

/**
	具体聚集类实现
*/

Iterator* ConcreateAggregate::CreateIterater()
{
	//创建迭代器
	return new ConcreateIterater(this);
}

ConcreateAggregate::~ConcreateAggregate()
{
	if (m_pData != NULL)
	{
		delete m_pData;
		m_pData = NULL;
	}
}

ConcreateAggregate::ConcreateAggregate(int Size)
{  
	m_pData = NULL;
	//创建测试数据
	int i = 0;
	m_pData = new DATA[Size];
	for(;i<Size;i++)
	{
		m_pData[i] = i+1;
	}
	m_iSize = Size;
}

int ConcreateAggregate::GetSize()
{
	return m_iSize;
}

DATA ConcreateAggregate::GetItem(int nIndex)
{
	if (nIndex < m_iSize)
	{
		return m_pData[nIndex];
	}
	else
	{
		assert(false);
		return 0;
	}
}
