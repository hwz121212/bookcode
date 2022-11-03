
/********************************************************************
	CREATED:	2012/01/19
	FILENAME:	ThreadLock.h
	AUTHOR:		By Robot
	
	PURPOSE:	线程自动共享锁
*********************************************************************/

#ifndef __THREAD_LOCK__
#define __THREAD_LOCK__

#include <Windows.h>

/**
	共享锁
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
	// 加锁
	VOID Lock() 
	{ 
		EnterCriticalSection(&m_Lock); 
	}
	// 解锁
	VOID UnLock() 
	{ 
		LeaveCriticalSection(&m_Lock); 
	}
	// 尝试加锁
	BOOL TryLock() 
	{ 
		return TryEnterCriticalSection(&m_Lock); 
	}

private:
	CRITICAL_SECTION m_Lock;
};


/**
	自动共享锁
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

