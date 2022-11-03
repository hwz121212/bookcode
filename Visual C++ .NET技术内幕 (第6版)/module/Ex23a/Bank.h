
#pragma once


// CBank command target

class CBank : public CCmdTarget
{
	DECLARE_DYNCREATE(CBank)

public:
	CBank();
	virtual ~CBank();

	virtual void OnFinalRelease();

    DOUBLE m_dBalance;

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CBank)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
    DOUBLE Withdrawal(DOUBLE dAmount);

    enum 
    {
        dispidBalance = 3,        dispidDeposit = 2L,        dispidWithdrawal = 1L
    };
    void Deposit(DOUBLE dAmount);
    DOUBLE GetBalance(void);
    void SetBalance(DOUBLE newVal);
};


