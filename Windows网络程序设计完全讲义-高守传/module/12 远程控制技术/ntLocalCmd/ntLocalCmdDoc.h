/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 管道编程－本地CMD.

  Project: ntLocalCmd.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////

// ntLocalCmdDoc.h : interface of the CNtLocalCmdDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NTLOCALCMDDOC_H__51E4FC50_03F9_4B0B_BA8F_3F1428DD0E43__INCLUDED_)
#define AFX_NTLOCALCMDDOC_H__51E4FC50_03F9_4B0B_BA8F_3F1428DD0E43__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CNtLocalCmdDoc : public CDocument
{
protected: // create from serialization only
	CNtLocalCmdDoc();
	DECLARE_DYNCREATE(CNtLocalCmdDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNtLocalCmdDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNtLocalCmdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNtLocalCmdDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTLOCALCMDDOC_H__51E4FC50_03F9_4B0B_BA8F_3F1428DD0E43__INCLUDED_)
