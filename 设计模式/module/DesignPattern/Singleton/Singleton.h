
/********************************************************************
	CREATED:	2012/01/19
	FILENAME:	Singleton.h
	AUTHOR:		By Robot
	
	PURPOSE:	单例模式（线程安全）模板类
		保证一个类仅有一个实例（让类自身保存它的唯一实例），并提供一个访问它的全局接口。
*********************************************************************/

#ifndef __SINGLETON__
#define __SINGLETON__

#include "ThreadLock.h"

/**
	单例模板类
*/
template<class T> 
class Singleton
{
public:
	static T* GetSinglePtr()
	{
		if (NULL == m_pSingleton)
		{
			// 加锁
			AutoLock aLock(m_ThreadLock);
			if(NULL == m_pSingleton)	
			{
				m_pSingleton = new T();
			}
		}
		return m_pSingleton;
	}

protected:
	Singleton() {}

private:
	static T* m_pSingleton;
	static ThreadLock m_ThreadLock;
};


template<class T> 
T* Singleton<T>::m_pSingleton = NULL;

template<class T> 
ThreadLock Singleton<T>::m_ThreadLock;




/**
	成员初始化宏
*/
#define WX_IMPLEMENT_SINGLEON(className)\
	template<> className* Singleton<className>::m_pSingleton = NULL; \
	template<> ThreadLock Singleton<className>::m_ThreadLock;

#endif
