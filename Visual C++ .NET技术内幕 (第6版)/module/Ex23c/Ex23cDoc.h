// Ex23cDoc.h : interface of the CEx23cDoc class
//


#pragma once

#include "alarm.h"

class CEx23cDoc : public CDocument
{
public:
	CString m_strFigure[4];

    CAlarm* m_pAlarm;

protected: // create from serialization only
	CEx23cDoc();
	DECLARE_DYNCREATE(CEx23cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CEx23cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions

public:
    DATE m_time;

protected:
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
    void OnTimeChanged(void);

    enum 
    {
        dispidFigure = 5,        
        dispidRefreshWin = 4L,
        dispidCreateAlarm = 3L,        
        dispidShowWin = 2L,        
        dispidTime = 1
    };
    void ShowWin(void);
    IDispatch* CreateAlarm(DATE time);
    void RefreshWin(void);
    VARIANT GetFigure(SHORT n);
    void SetFigure(SHORT n, VARIANT FAR& newVal);
};


