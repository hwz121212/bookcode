// State.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/18
	FILENAME:	State.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	状态模式
		状态模式主要解决的是：当控制一个对象状态转换的条件表达式过于复杂时的情况；
		通过把各种状态转移逻辑分布到State的子类之间，来减少相互间的依赖。

		当一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为，就可以
		考虑使用状态模式。
*********************************************************************/

#include "stdafx.h"
#include "Work.h"
#include <iostream>
using namespace std;

///**
//	状态值枚举
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
//	Context类，维护一个ConcreteState子类的实例，这个实例定义当前的状态
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
//	State类，抽象状态类
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
//	具体State子类声明
//*/
//class ConcreteStateB;
//
//class ConcreteStateA : public State
//{
//public:
//	// 从A状态切换到B状态
//	virtual void Handle(Context *pContext);
//	virtual int GetType();
//};
//
//class ConcreteStateB : public State
//{
//public:
//	// 从B状态切换到A状态
//	virtual void Handle(Context *pContext);
//	virtual int GetType();
//};
//
//
///**
//	Context类的实现
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
//	cout << "当前状态为:" << pState->GetType() <<endl;
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
//	具体State子类的实现
//*/
//
//// 从A状态切换到B状态
//void ConcreteStateA::Handle(Context *pContext)
//{
//	if (pContext)
//	{
//		State* pState = new ConcreteStateB();
//		pContext->SetState(pState);
//	}
//}
//
//// 状态值
//int ConcreteStateA::GetType()
//{
//	return STATE_A;
//}
//
//// 从B状态切换到A状态
//void ConcreteStateB::Handle(Context *pContext)
//{
//	if (pContext)
//	{
//		State *pState = new ConcreteStateA();
//		pContext->SetState(pState);
//	}
//}
//
//// 状态值
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
