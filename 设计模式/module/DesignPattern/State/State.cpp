
#include "stdafx.h"
#include "State.h"
#include "Work.h"
#include <iostream>
using namespace std;


/**
	上午工作状态
*/
void ForenoonSate::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		if (pWk->GetHour() < 12)
		{
			cout << "当前时间："<< pWk->GetHour() <<"点，上午工作，精神百倍!" << endl;
		}
		else
		{
			// 切换到下个状态
			pWk->SetState(new NoonState());
			pWk->WriteProgram();
		}
	}
}


/**
	中午工作状态
*/
void NoonState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		if (pWk->GetHour() < 13)
		{
			cout << "当前时间："<< pWk->GetHour() <<"点，饿了，午饭，犯困，午休!" << endl;
		}
		else
		{
			// 切换到下个状态
			pWk->SetState(new AfternoonState());
			pWk->WriteProgram();
		}
	}
}


/**
	下午工作状态
*/
void AfternoonState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		if (pWk->GetHour() < 17)
		{
			cout << "当前时间："<< pWk->GetHour() <<"点，下午状态还不错，继续努力!" << endl;
		}
		else
		{
			// 切换到下个状态
			pWk->SetState(new EveningState());
			pWk->WriteProgram();
		}
	}
}


/**
	晚间工作状态
*/
void EveningState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		if (pWk->GetTaskFinished())
		{
			// 切换到下个状态
			pWk->SetState(new RestState());
			pWk->WriteProgram();
		}
		else
		{
			if (pWk->GetHour() < 21)
			{
				cout << "当前时间："<< pWk->GetHour() <<"点，加班哦，疲累至极!" << endl;
			}
			else
			{
				// 切换到下个状态
				pWk->SetState(new SleepingState());
				pWk->WriteProgram();
			}
		}
	}
}


/**
	睡眠状态
*/
void SleepingState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		cout << "当前时间："<< pWk->GetHour() <<"点，不行啦，睡着啦!" << endl;
	}
}


/**
	下班休息状态
*/
void RestState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		cout << "当前时间："<< pWk->GetHour() <<"点，下班回家啦!" << endl;
	}
}

