
#include "stdafx.h"
#include "Iterator.h"
#include "Aggregate.h"

/**
	具体迭代器类实现
*/
ConcreateIterater::ConcreateIterater(Aggregate* pAggregate)
{
	m_iCurrPosition = 0;
	m_pAggreatate = pAggregate;
}

void ConcreateIterater::MoveToFirst()
{
	m_iCurrPosition = 0;
}

void ConcreateIterater::MoveToNext()
{
	if (m_iCurrPosition < m_pAggreatate->GetSize())
	{
		m_iCurrPosition++;
	}
}

bool ConcreateIterater::IsEnd()
{
	return m_iCurrPosition == m_pAggreatate->GetSize();
}

DATA ConcreateIterater::CurrentItem()
{
	return m_pAggreatate->GetItem(m_iCurrPosition);
}

ConcreateIterater::~ConcreateIterater()
{
	if (m_pAggreatate != NULL)
	{
		delete m_pAggreatate;
		m_pAggreatate = NULL;
	}
}
