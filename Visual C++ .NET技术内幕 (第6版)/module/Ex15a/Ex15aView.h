// Ex15aView.h : interface of the CEx15aView class
//


#pragma once


class CEx15aView : public CFormView
{
protected: // create from serialization only
	CEx15aView();
	DECLARE_DYNCREATE(CEx15aView)

public:
	enum{ IDD = IDD_EX15A_FORM };

// Attributes
public:
	CEx15aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CEx15aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEnter();
	afx_msg void OnEditClearall();
	afx_msg void OnUpdateEditClearall(CCmdUI *pCmdUI);
	int m_nGrade;
	CString m_strName;
private:
	void UpdateControlsFromDoc(void);
};

#ifndef _DEBUG  // debug version in Ex15aView.cpp
inline CEx15aDoc* CEx15aView::GetDocument() const
   { return reinterpret_cast<CEx15aDoc*>(m_pDocument); }
#endif

