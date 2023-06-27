// ex34aView.h : interface of the CEx34aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx34aView : public CEditView
{
protected: // create from serialization only
	CEx34aView();
	DECLARE_DYNCREATE(CEx34aView)

// Attributes
public:
	CEx34aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx34aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx34aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx34aView)
	afx_msg void OnInternetStartServer();
	afx_msg void OnUpdateInternetStartServer(CCmdUI* pCmdUI);
	afx_msg void OnInternetRequestSocket();
	afx_msg void OnInternetRequestWininet();
	afx_msg void OnInternetStopServer();
	afx_msg void OnUpdateInternetStopServer(CCmdUI* pCmdUI);
	afx_msg void OnInternetConfiguration();
	afx_msg void OnUpdateInternetConfiguration(CCmdUI* pCmdUI);
	afx_msg void OnEditClearAll();
	afx_msg void OnRequest();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex34aView.cpp
inline CEx34aDoc* CEx34aView::GetDocument()
   { return (CEx34aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
