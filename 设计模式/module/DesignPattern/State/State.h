
/********************************************************************
	CREATED:	2012/01/18
	FILENAME:	State.h
	AUTHOR:		By Robot
	
	PURPOSE:	定义各个状态类
*********************************************************************/


class Work;

/**
	状态虚基类
*/
class State
{
public:
	virtual void WriteProgram(Work *pWk) = 0;
};


/**
	上午工作状态
*/
class ForenoonSate : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	中午工作状态
*/
class NoonState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	下午工作状态
*/
class AfternoonState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	晚间工作状态
*/
class EveningState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	睡眠状态
*/
class SleepingState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};


/**
	下班休息状态
*/
class RestState : public State
{
public:
	virtual void WriteProgram(Work *pWk);
};

