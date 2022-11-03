// cadDoc.h : interface of the CCadDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CADDOC_H__B3512371_3762_465C_A8A7_96653CB2B298__INCLUDED_)
#define AFX_CADDOC_H__B3512371_3762_465C_A8A7_96653CB2B298__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Shape.h"
#include "CommandManager.h"
#include "ShapeCollection.h"


class CCadDoc : public CDocument
{
protected: // create from serialization only
	CCadDoc();
	DECLARE_DYNCREATE(CCadDoc)

// Attributes
public:
	CShapeCollection m_ShapeCollection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:

	void RemoveShape(CShape* pShape);
	void AddShape(CShape* pShape);
	virtual ~CCadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCadDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADDOC_H__B3512371_3762_465C_A8A7_96653CB2B298__INCLUDED_)
