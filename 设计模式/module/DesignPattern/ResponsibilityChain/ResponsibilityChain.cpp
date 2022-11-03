// ResponsibilityChain.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/30
	FILENAME:	ResponsibilityChain.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	ְ����ģʽ����һְ��ԭ�� & ���ŷ��ԭ��
*********************************************************************/


#include "stdafx.h"
#include <iostream>
#include <assert.h>

///**
//	�����Handler
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
//	������1
//*/
//class ConcreteHandler1 : public Handler
//{
//public:
//	void HandleRequest(int request)
//	{
//		if (request >=0 && request < 10)
//		{
//			std::cout<<"ConcreteHandler1��������"<<std::endl;
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
//	������2
//*/
//class ConcreteHandler2 : public Handler
//{
//public:
//	void HandleRequest(int request)
//	{
//		if (request >= 10 && request < 20)
//		{
//			std::cout<<"ConcreteHandler2��������"<<std::endl;
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
//	������3
//*/
//class ConcreteHandler3 : public Handler
//{
//public:
//	void HandleRequest(int request)
//	{
//		if (request >= 20 && request < 30)
//		{
//			std::cout<<"ConcreteHandler3��������"<<std::endl;
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
//	��ں���
//*/
//int _tmain(int argc, _TCHAR* argv[])
//{
//	Handler *pHandler1 = new ConcreteHandler1();
//	Handler *pHandler2 = new ConcreteHandler2();
//	Handler *pHandler3 = new ConcreteHandler3();
//
//	// ����ְ�������¹�ϵ
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
	���Ͷ���
*/
#ifdef UNICODE
typedef	std::wstring	STRING;
#else
typedef	std::string		STRING;
#endif


/**
	��������
*/
#ifdef UNICODE
#define COUT	std::wcout
#else
#define COUT	std::cout
#endif


/**
	�ַ�������
*/
const STRING strQingJia = _T("���");
const STRING strJiaXin = _T("��н");


/**
	������
*/
class Request
{
public:
	// ��������
	STRING GetRequestType() { return m_strRequestType; }
	void SetRequestType(STRING val) { m_strRequestType = val; }
	// ��������
	STRING GetRequestContent() { return m_strRequestContent;}
	void SetRequestContent(STRING val) { m_strRequestContent = val; }
	// ��������
	int GetNumber() { return m_nNumber; }
	void SetNumber(int val) { m_nNumber = val; }

private:
	STRING m_strRequestType;
	STRING m_strRequestContent;
	int m_nNumber;
};


/**
	Handler����࣬������
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
	����
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
					<<_T(" ���� ")<<pRequest->GetNumber()<<_T("����׼")<<std::endl;
			}
			else if (m_pSuperior != NULL)
			{
				m_pSuperior->RequestApplications(pRequest);
			}
		}
	}
};


/**
	�ܼ�
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
				<<_T(" ���� ")<<pRequest->GetNumber()<<_T("����׼")<<std::endl;
		}
		else if (m_pSuperior != NULL)
		{
			m_pSuperior->RequestApplications(pRequest);
		}
	}
};


/**
	�ܾ���
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
				<<_T(" ���� ")<<pRequest->GetNumber()<<_T("����׼")<<std::endl;
		}
		else if (requestType.compare(strJiaXin) == 0 && pRequest->GetNumber() <= 500)
		{
			COUT<<m_strName.c_str()<<":"<<pRequest->GetRequestContent().c_str()
				<<_T(" ���� ")<<pRequest->GetNumber()<<_T("����׼")<<std::endl;
		}
		else if (requestType.compare(strJiaXin) == 0 && pRequest->GetNumber() > 500)
		{
			COUT<<m_strName.c_str()<<":"<<pRequest->GetRequestContent().c_str()
				<<_T(" ���� ")<<pRequest->GetNumber()<<_T("��˵��")<<std::endl;
		}
	}
};


/**
	��ں���
*/
int _tmain(int argc, _TCHAR* argv[])
{
#ifdef UNICODE
	COUT.imbue(std::locale(std::locale(),"",LC_CTYPE));
#endif

	CommonManager *pJingLi = new CommonManager(_T("����"));
	Majordomo *pZongJian = new Majordomo(_T("�ܼ�"));
	GeneralManager *pZongJingLi = new GeneralManager(_T("�ܾ���"));

	assert(pJingLi && pZongJian && pZongJingLi);

	// �������¹�ϵ
	pJingLi->SetSuperior(pZongJian);
	pZongJian->SetSuperior(pZongJingLi);

	// ���
	Request *pRequest = new Request();
	if (pRequest != NULL)
	{
		pRequest->SetRequestType(_T("���"));
		pRequest->SetRequestContent(_T("С�����"));
		pRequest->SetNumber(1);
	}
	
	pJingLi->RequestApplications(pRequest);

	Request *pRequest2 = new Request();
	if (pRequest2 != NULL)
	{
		pRequest2->SetRequestType(_T("���"));
		pRequest2->SetRequestContent(_T("С�����"));
		pRequest2->SetNumber(4);
	}
	
	pJingLi->RequestApplications(pRequest2);

	// �����н
	Request *pRequest3 = new Request();
	if (pRequest3 != NULL)
	{
		pRequest3->SetRequestType(_T("��н"));
		pRequest3->SetRequestContent(_T("С�������н"));
		pRequest3->SetNumber(500);
	}

	pJingLi->RequestApplications(pRequest3);

	Request *pRequest4 = new Request();
	if (pRequest4 != NULL)
	{
		pRequest4->SetRequestType(_T("��н"));
		pRequest4->SetRequestContent(_T("С�������н"));
		pRequest4->SetNumber(1000);
	}

	pJingLi->RequestApplications(pRequest4);

	system("pause");
	return 0;
}
