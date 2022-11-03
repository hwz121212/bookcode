
/********************************************************************
	CREATED:	2012/01/19
	FILENAME:	Singleton.h
	AUTHOR:		By Robot
	
	PURPOSE:	����ģʽ���̰߳�ȫ��ģ����
		��֤һ�������һ��ʵ������������������Ψһʵ���������ṩһ����������ȫ�ֽӿڡ�
*********************************************************************/

#ifndef __SINGLETON__
#define __SINGLETON__

#include "ThreadLock.h"

/**
	����ģ����
*/
template<class T> 
class Singleton
{
public:
	static T* GetSinglePtr()
	{
		if (NULL == m_pSingleton)
		{
			// ����
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
	��Ա��ʼ����
*/
#define WX_IMPLEMENT_SINGLEON(className)\
	template<> className* Singleton<className>::m_pSingleton = NULL; \
	template<> ThreadLock Singleton<className>::m_ThreadLock;

#endif
