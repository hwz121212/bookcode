// EX35A.H - Header file for your Internet Server
//    ex35a Extension

#include "resource.h"

class CEx35aExtension : public CHttpServer
{
public:
	CEx35aExtension();
	~CEx35aExtension();
private:
	CCriticalSection m_cs;
	int m_nTotalPizzaOrders;

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CEx35aExtension)
	public:
	virtual BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	virtual LPCTSTR GetTitle() const;
	//}}AFX_VIRTUAL

	// TODO: Add handlers for your commands here.
	// For example:

	void Default(CHttpServerContext* pCtxt);
	void ConfirmOrder(CHttpServerContext* pCtxt, LPCTSTR pstrName);
	void ProcessPizzaForm(CHttpServerContext* pCtxt, LPCTSTR pstrName, LPCTSTR pstrAddr, int nQuantity,
			LPCTSTR pstrSize, LPCTSTR pstrTop1, LPCTSTR pstrTop2, LPCTSTR pstrTop3, LPCTSTR pstrTop4);
	void ProcessTimesheet(CHttpServerContext* pCtxt, int nPeriod, LPCTSTR pstrEmployee,
			double dHours, int nJob);

	DECLARE_PARSE_MAP()

	//{{AFX_MSG(CEx35aExtension)
	//}}AFX_MSG
};

