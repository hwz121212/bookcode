// TestDrawDibView.h : interface of the CTestDrawDibView class
//
/////////////////////////////////////////////////////////////////////////////

class CTestDrawDibView : public CView
{
protected: // create from serialization only
	CTestDrawDibView();
	DECLARE_DYNCREATE(CTestDrawDibView)

// Attributes
public:
	CTestDrawDibDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDrawDibView)
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
	virtual ~CTestDrawDibView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HANDLE m_DibMem;

// Generated message map functions
protected:
	//{{AFX_MSG(CTestDrawDibView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestDrawDibView.cpp
inline CTestDrawDibDoc* CTestDrawDibView::GetDocument()
   { return (CTestDrawDibDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
