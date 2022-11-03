
/********************************************************************
	CREATED:	2012/01/18
	FILENAME:	State.h
	AUTHOR:		By Robot
	
	PURPOSE:	�������״̬��
*********************************************************************/


class Work;

/**
	״̬�����
*/
class State
{
public:
	virtual void WriteProgram(Work *pWk) = 0;
};


/**
	���繤��״̬
*/
class ForenoonSate : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	���繤��״̬
*/
class NoonState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	���繤��״̬
*/
class AfternoonState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	��乤��״̬
*/
class EveningState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	˯��״̬
*/
class SleepingState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	�°���Ϣ״̬
*/
class RestState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};

