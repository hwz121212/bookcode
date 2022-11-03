// Ex28aView.h : interface of the CEx28aView class
//


#pragma once


class CEx28aView : public CEditView
{
protected: // create from serialization only
	CEx28aView();
	DECLARE_DYNCREATE(CEx28aView)

// Attributes
public:
	CEx28aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CEx28aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnInternetStartServer();
    afx_msg void OnUpdateInternetStartServer(CCmdUI *pCmdUI);
    afx_msg void OnInternetRequestSock();
    afx_msg void OnInternetRequestInet();
    afx_msg void OnInternetStopServer();
    afx_msg void OnUpdateInternetStopServer(CCmdUI *pCmdUI);
    afx_msg void OnInternetConfiguration();
    afx_msg void OnUpdateInternetConfiguration(CCmdUI *pCmdUI);
	afx_msg void OnEditClearAll();
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
    afx_msg void OnRequest();
};

#ifndef _DEBUG  // debug version in Ex28aView.cpp
inline CEx28aDoc* CEx28aView::GetDocument() const
   { return reinterpret_cast<CEx28aDoc*>(m_pDocument); }
#endif

