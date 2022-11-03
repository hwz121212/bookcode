
/********************************************************************
	CREATED:	2012/01/18
	FILENAME:	Work.h
	AUTHOR:		By Robot
	
	PURPOSE:	Work�࣬ά��һ������״̬�����ʵ�������ʵ������Work�ĵ�ǰ״̬
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
	// άϵһ������״̬�����ʵ��ָ��
	State *m_pCurState;
	double m_hour;
	bool m_finish;
};

