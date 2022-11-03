
/********************************************************************
	CREATED:	2012/01/18
	FILENAME:	Work.h
	AUTHOR:		By Robot
	
	PURPOSE:	Work类，维护一个具体状态子类的实例，这个实例定义Work的当前状态
*********************************************************************/

class State;

class Work
{
public:
	Work();

public:
	void SetHour(double hour);
	double GetHour();

	void SetTaskFinished(bool finish);
	bool GetTaskFinished();

	void SetState(State *pState);
	State* GetState();

public:
	void WriteProgram();

private:
	// 维系一个具体状态子类的实例指针
	State *m_pCurState;
	double m_hour;
	bool m_finish;
};

