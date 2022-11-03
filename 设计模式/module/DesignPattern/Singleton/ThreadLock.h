
/********************************************************************
	CREATED:	2012/01/19
	FILENAME:	ThreadLock.h
	AUTHOR:		By Robot
	
	PURPOSE:	�߳��Զ�������
*********************************************************************/

#ifndef __THREAD_LOCK__
#define __THREAD_LOCK__

#include <Windows.h>

/**
	������
*/
class ThreadLock
{
public:
	ThreadLock()
	{ 
		InitializeCriticalSection(&m_Lock); 
	}
	~ThreadLock() 
	{ 
		DeleteCriticalSection(&m_Lock); 
	}
	// ����
	VOID Lock() 
	{ 
		EnterCriticalSection(&m_Lock); 
	}
	// ����
	VOID UnLock() 
	{ 
		LeaveCriticalSection(&m_Lock); 
	}
	// ���Լ���
	BOOL TryLock() 
	{ 
		return TryEnterCriticalSection(&m_Lock); 
	}

private:
	CRITICAL_SECTION m_Lock;
};


/**
	�Զ�������
*/
class AutoLock
{
public:
	AutoLock(ThreadLock& cs) : m_pLock(&cs)
	{
		m_pLock->Lock();
	}
	~AutoLock()
	{
		m_pLock->UnLock();
	}

private:
	AutoLock() 
	{
	}
	ThreadLock *m_pLock;
};


#endif

