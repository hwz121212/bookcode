
#include "stdafx.h"
#include "Work.h"
#include "State.h"


Work::Work() 
{
	m_pCurState = new ForenoonSate();
}

void Work::SetHour(double hour)
{
	m_hour = hour;
}

double Work::GetHour()
{
	return m_hour;
}

void Work::SetTaskFinished(bool finish)
{
	m_finish = finish;
}

bool Work::GetTaskFinished()
{
	return m_finish;
}

void Work::SetState(State *pState)
{
	m_pCurState = pState;
}

State* Work::GetState()
{
	return m_pCurState;
}

void Work::WriteProgram()
{
	if (m_pCurState)
	{
		m_pCurState->WriteProgram(this);
	}
}

