
#include "stdafx.h"
#include "State.h"
#include "Work.h"
#include <iostream>
using namespace std;


/**
	���繤��״̬
*/
void ForenoonSate::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		if (pWk->GetHour() < 12)
		{
			cout << "��ǰʱ�䣺"<< pWk->GetHour() <<"�㣬���繤��������ٱ�!" << endl;
		}
		else
		{
			// �л����¸�״̬
			pWk->SetState(new NoonState());
			pWk->WriteProgram();
		}
	}
}


/**
	���繤��״̬
*/
void NoonState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		if (pWk->GetHour() < 13)
		{
			cout << "��ǰʱ�䣺"<< pWk->GetHour() <<"�㣬���ˣ��緹������������!" << endl;
		}
		else
		{
			// �л����¸�״̬
			pWk->SetState(new AfternoonState());
			pWk->WriteProgram();
		}
	}
}


/**
	���繤��״̬
*/
void AfternoonState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		if (pWk->GetHour() < 17)
		{
			cout << "��ǰʱ�䣺"<< pWk->GetHour() <<"�㣬����״̬����������Ŭ��!" << endl;
		}
		else
		{
			// �л����¸�״̬
			pWk->SetState(new EveningState());
			pWk->WriteProgram();
		}
	}
}


/**
	��乤��״̬
*/
void EveningState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		if (pWk->GetTaskFinished())
		{
			// �л����¸�״̬
			pWk->SetState(new RestState());
			pWk->WriteProgram();
		}
		else
		{
			if (pWk->GetHour() < 21)
			{
				cout << "��ǰʱ�䣺"<< pWk->GetHour() <<"�㣬�Ӱ�Ŷ��ƣ������!" << endl;
			}
			else
			{
				// �л����¸�״̬
				pWk->SetState(new SleepingState());
				pWk->WriteProgram();
			}
		}
	}
}


/**
	˯��״̬
*/
void SleepingState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		cout << "��ǰʱ�䣺"<< pWk->GetHour() <<"�㣬��������˯����!" << endl;
	}
}


/**
	�°���Ϣ״̬
*/
void RestState::WriteProgram(Work *pWk)
{
	if (pWk)
	{
		cout << "��ǰʱ�䣺"<< pWk->GetHour() <<"�㣬�°�ؼ���!" << endl;
	}
}

