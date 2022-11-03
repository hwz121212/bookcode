// ResponsibilityChain.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/30
	FILENAME:	ResponsibilityChain.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	职责连模式（单一职责原则 & 开放封闭原则）
*********************************************************************/


#include "stdafx.h"
#include <iostream>
#include <assert.h>

///**
//	虚基类Handler
//*/
//class Handler
//{
//public:
//	void SetSuccessor(Handler *pSuccessor)
//	{
//		this->m_pSuccessor = pSuccessor;
//	}
//
//public:
//	virtual void HandleRequest(int request) = 0;
//
//protected:
//	Handler* m_pSuccessor;
//};
//
//
///**
//	具体类1
//*/
//class ConcreteHandler1 : public Handler
//{
//public:
//	void HandleRequest(int request)
//	{
//		if (request >=0 && request < 10)
//		{
//			std::cout<<"ConcreteHandler1处理请求"<<std::endl;
//		}
//		else if (m_pSuccessor != NULL)
//		{
//			m_pSuccessor->HandleRequest(request);
//		}
//	}
//};
//
//
///**
//	具体类2
//*/
//class ConcreteHandler2 : public Handler
//{
//public:
//	void HandleRequest(int request)
//	{
//		if (request >= 10 && request < 20)
//		{
//			std::cout<<"ConcreteHandler2处理请求"<<std::endl;
//		}
//		else if (m_pSuccessor != NULL)
//		{
//			m_pSuccessor->HandleRequest(request);
//		}
//	}
//};
//
//
///**
//	具体类3
//*/
//class ConcreteHandler3 : public Handler
//{
//public:
//	void HandleRequest(int request)
//	{
//		if (request >= 20 && request < 30)
//		{
//			std::cout<<"ConcreteHandler3处理请求"<<std::endl;
//		}
//		else if (m_pSuccessor != NULL)
//		{
//			m_pSuccessor->HandleRequest(request);
//		}
//	}
//};
//
//
///**
//	入口函数
//*/
//int _tmain(int argc, _TCHAR* argv[])
//{
//	Handler *pHandler1 = new ConcreteHandler1();
//	Handler *pHandler2 = new ConcreteHandler2();
//	Handler *pHandler3 = new ConcreteHandler3();
//
//	// 设置职责连上下关系
//	pHandler1->SetSuccessor(pHandler2);
//	pHandler2->SetSuccessor(pHandler3);
//	
//	int requestArray[] = {2,5,14,22,18,3,27,20};
//	for (int i=0; i < sizeof(requestArray)/sizeof(int); i++)
//	{
//		pHandler1->HandleRequest(requestArray[i]);
//	}
//
//	system("pause");
//	return 0;
//}


/**
	类型定义
*/
#ifdef UNICODE
typedef	std::wstring	STRING;
#else
typedef	std::string		STRING;
#endif


/**
	函数定义
*/
#ifdef UNICODE
#define COUT	std::wcout
#else
#define COUT	std::cout
#endif


/**
	字符串常量
*/
const STRING strQingJia = _T("请假");
const STRING strJiaXin = _T("加薪");


/**
	申请类
*/
class Request
{
public:
	// 申请类型
	STRING GetRequestType() { return m_strRequestType; }
	void SetRequestType(STRING val) { m_strRequestType = val; }
	// 申请内容
	STRING GetRequestContent() { return m_strRequestContent;}
	void SetRequestContent(STRING val) { m_strRequestContent = val; }
	// 申请数量
	int GetNumber() { return m_nNumber; }
	void SetNumber(int val) { m_nNumber = val; }

private:
	STRING m_strRequestType;
	STRING m_strRequestContent;
	int m_nNumber;
};


/**
	Handler虚基类，管理者
*/
class Manager
{
public:
	Manager(STRING strName)
	{
		m_strName = strName; 
	}

	void SetSuperior(Manager *pSuperior)
	{
		m_pSuperior = pSuperior;
	}

	virtual void RequestApplications(Request *pRequest) = 0;
	
protected:
	STRING m_strName;
	Manager* m_pSuperior;
};


/**
	经理
*/
class CommonManager : public Manager
{
public:
	CommonManager(STRING strName) : Manager(strName)
	{}

	void RequestApplications(Request *pRequest)
	{
		if (pRequest != NULL)
		{
			STRING requestType = pRequest->GetRequestType();
			if (requestType.compare(strQingJia) == 0 && pRequest->GetNumber() <= 2)
			{
				COUT<<m_strName.c_str()<<":"<<pRequest->GetRequestContent().c_str()
					<<_T(" 数量 ")<<pRequest->GetNumber()<<_T("被批准")<<std::endl;
			}
			else if (m_pSuperior != NULL)
			{
				m_pSuperior->RequestApplications(pRequest);
			}
		}
	}
};


/**
	总监
*/
class Majordomo : public Manager
{
public:
	Majordomo(STRING strName) : Manager(strName)
	{}

	void RequestApplications(Request *pRequest)
	{
		STRING requestType = pRequest->GetRequestType();
		if (requestType.compare(strQingJia) == 0 && pRequest->GetNumber() <= 5)
		{
			COUT<<m_strName.c_str()<<":"<<pRequest->GetRequestContent().c_str()
				<<_T(" 数量 ")<<pRequest->GetNumber()<<_T("被批准")<<std::endl;
		}
		else if (m_pSuperior != NULL)
		{
			m_pSuperior->RequestApplications(pRequest);
		}
	}
};


/**
	总经理
*/
class GeneralManager : public Manager
{
public:
	GeneralManager(STRING strName) : Manager(strName)
	{}
	
	void RequestApplications(Request *pRequest)
	{
		STRING requestType = pRequest->GetRequestType();
		if (requestType.compare(strQingJia) == 0)
		{
			COUT<<m_strName.c_str()<<":"<<pRequest->GetRequestContent().c_str()
				<<_T(" 数量 ")<<pRequest->GetNumber()<<_T("被批准")<<std::endl;
		}
		else if (requestType.compare(strJiaXin) == 0 && pRequest->GetNumber() <= 500)
		{
			COUT<<m_strName.c_str()<<":"<<pRequest->GetRequestContent().c_str()
				<<_T(" 数量 ")<<pRequest->GetNumber()<<_T("被批准")<<std::endl;
		}
		else if (requestType.compare(strJiaXin) == 0 && pRequest->GetNumber() > 500)
		{
			COUT<<m_strName.c_str()<<":"<<pRequest->GetRequestContent().c_str()
				<<_T(" 数量 ")<<pRequest->GetNumber()<<_T("再说吧")<<std::endl;
		}
	}
};


/**
	入口函数
*/
int _tmain(int argc, _TCHAR* argv[])
{
#ifdef UNICODE
	COUT.imbue(std::locale(std::locale(),"",LC_CTYPE));
#endif

	CommonManager *pJingLi = new CommonManager(_T("经理"));
	Majordomo *pZongJian = new Majordomo(_T("总监"));
	GeneralManager *pZongJingLi = new GeneralManager(_T("总经理"));

	assert(pJingLi && pZongJian && pZongJingLi);

	// 设置上下关系
	pJingLi->SetSuperior(pZongJian);
	pZongJian->SetSuperior(pZongJingLi);

	// 请假
	Request *pRequest = new Request();
	if (pRequest != NULL)
	{
		pRequest->SetRequestType(_T("请假"));
		pRequest->SetRequestContent(_T("小菜请假"));
		pRequest->SetNumber(1);
	}
	
	pJingLi->RequestApplications(pRequest);

	Request *pRequest2 = new Request();
	if (pRequest2 != NULL)
	{
		pRequest2->SetRequestType(_T("请假"));
		pRequest2->SetRequestContent(_T("小菜请假"));
		pRequest2->SetNumber(4);
	}
	
	pJingLi->RequestApplications(pRequest2);

	// 申请加薪
	Request *pRequest3 = new Request();
	if (pRequest3 != NULL)
	{
		pRequest3->SetRequestType(_T("加薪"));
		pRequest3->SetRequestContent(_T("小菜请求加薪"));
		pRequest3->SetNumber(500);
	}

	pJingLi->RequestApplications(pRequest3);

	Request *pRequest4 = new Request();
	if (pRequest4 != NULL)
	{
		pRequest4->SetRequestType(_T("加薪"));
		pRequest4->SetRequestContent(_T("小菜请求加薪"));
		pRequest4->SetNumber(1000);
	}

	pJingLi->RequestApplications(pRequest4);

	system("pause");
	return 0;
}
