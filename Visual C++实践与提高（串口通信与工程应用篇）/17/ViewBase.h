#if !defined(AFX_VIEWBASE_H__E20EB6A2_3D99_45B2_ABF4_5D3E34C2E253__INCLUDED_)
#define AFX_VIEWBASE_H__E20EB6A2_3D99_45B2_ABF4_5D3E34C2E253__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewBase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewBase view
class CViewBase : public CListView
{
protected:

	CViewBase();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewBase)

// Attributes
public:

// Operations
public:
	virtual void InitColumns();	
	void ClearLogs();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewBase)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewBase();	
	void SetLVCheck(WPARAM ItemIndex, BOOL bCheck);
	void SetColumns(int nCols, int *nWidth, int *pCol);
	void AddExStyle(DWORD dwExStyle);

	CArray<int, int> _gColText;
	CArray<int, int> _gColWidth;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewBase)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWBASE_H__E20EB6A2_3D99_45B2_ABF4_5D3E34C2E253__INCLUDED_)
