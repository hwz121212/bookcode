// SaveReadDoc.h : interface of the CSaveReadDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVEREADDOC_H__70B4B52E_1DEE_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_SAVEREADDOC_H__70B4B52E_1DEE_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSaveReadDoc : public CDocument
{
protected: // create from serialization only
	CSaveReadDoc();
	DECLARE_DYNCREATE(CSaveReadDoc)

// Attributes
public:
	CString  name ;                    //����
	struct {
		 int  subject;              //  ��Ŀ���
		 float score;                   //  �ÿƳɼ�
	}  m_nSubject[8]; 
	float total;                          //   �ܳɼ�    

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveReadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSaveReadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSaveReadDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEREADDOC_H__70B4B52E_1DEE_11D4_B0E6_00001A012804__INCLUDED_)
