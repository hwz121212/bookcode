// ex36aView.h : interface of the CEx36aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx36aCntrItem;

class CEx36aView : public CRichEditView
{
protected: // create from serialization only
	CEx36aView();
	DECLARE_DYNCREATE(CEx36aView)

// Attributes
public:
	CEx36aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx36aView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx36aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx36aView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnEditClearAll();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex36aView.cpp
inline CEx36aDoc* CEx36aView::GetDocument()
   { return (CEx36aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
