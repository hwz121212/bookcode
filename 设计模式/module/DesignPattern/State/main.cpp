// State.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/18
	FILENAME:	State.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	״̬ģʽ
		״̬ģʽ��Ҫ������ǣ�������һ������״̬ת�����������ʽ���ڸ���ʱ�������
		ͨ���Ѹ���״̬ת���߼��ֲ���State������֮�䣬�������໥���������

		��һ���������Ϊȡ��������״̬������������������ʱ�̸���״̬�ı�������Ϊ���Ϳ���
		����ʹ��״̬ģʽ��
*********************************************************************/

#include "stdafx.h"
#include "Work.h"
#include <iostream>
using namespace std;

///**
//	״ֵ̬ö��
//*/
//enum
//{
//	STATE_INVALID = -1,
//	STATE_A,
//	STATE_B,
//	STATE_NUM,
//};
//
//
///**
//	Context�࣬ά��һ��ConcreteState�����ʵ�������ʵ�����嵱ǰ��״̬
//*/
//class State;
//
//class Context
//{
//public:
//	Context();
//	State* GetState();
//	void SetState(State* pState);
//	void Request();
//
//protected:
//	State *_pState;
//};
//
//
///**
//	State�࣬����״̬��
//*/
//class State
//{
//public:
//	virtual void Handle(Context *pContext) = 0;
//	virtual int GetType() = 0;
//};
//
//
///**
//	����State��������
//*/
//class ConcreteStateB;
//
//class ConcreteStateA : public State
//{
//public:
//	// ��A״̬�л���B״̬
//	virtual void Handle(Context *pContext);
//	virtual int GetType();
//};
//
//class ConcreteStateB : public State
//{
//public:
//	// ��B״̬�л���A״̬
//	virtual void Handle(Context *pContext);
//	virtual int GetType();
//};
//
//
///**
//	Context���ʵ��
//*/
//Context::Context()
//{
//	_pState = NULL;
//}
//
//State* Context::GetState() 
//{ 
//	return _pState; 
//}
//
//void Context::SetState(State* pState) 
//{ 
//	_pState = pState;
//	cout << "��ǰ״̬Ϊ:" << pState->GetType() <<endl;
//}
//
//void Context::Request()
//{
//	if(_pState)
//	{
//		_pState->Handle(this);
//	}
//}
//
//
///**
//	����State�����ʵ��
//*/
//
//// ��A״̬�л���B״̬
//void ConcreteStateA::Handle(Context *pContext)
//{
//	if (pContext)
//	{
//		State* pState = new ConcreteStateB();
//		pContext->SetState(pState);
//	}
//}
//
//// ״ֵ̬
//int ConcreteStateA::GetType()
//{
//	return STATE_A;
//}
//
//// ��B״̬�л���A״̬
//void ConcreteStateB::Handle(Context *pContext)
//{
//	if (pContext)
//	{
//		State *pState = new ConcreteStateA();
//		pContext->SetState(pState);
//	}
//}
//
//// ״ֵ̬
//int ConcreteStateB::GetType()
//{
//	return STATE_B;
//}
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	Context *pContext = new Context();
//	pContext->SetState(new ConcreteStateA());
//	pContext->Request();
//	pContext->Request();
//	pContext->Request();
//	pContext->Request();
//
//	system("pause");
//	return 0;
//}


int _tmain(int argc, _TCHAR* argv[])
{
	Work *pWk = new Work();

	pWk->SetHour(9);
	pWk->WriteProgram();

	pWk->SetHour(10);
	pWk->WriteProgram();

	pWk->SetHour(12);
	pWk->WriteProgram();

	pWk->SetHour(13);
	pWk->WriteProgram();

	pWk->SetHour(14);
	pWk->WriteProgram();

	pWk->SetHour(17);
	pWk->SetTaskFinished(false); //true
	pWk->WriteProgram();

	pWk->SetHour(19);
	pWk->WriteProgram();

	pWk->SetHour(22);
	pWk->WriteProgram();

	system("pause");
	return 0;
}
