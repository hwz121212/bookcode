// ex28bDoc.h : interface of the CEx28bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28BDOC_H__1EAAB6DF_6011_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX28BDOC_H__1EAAB6DF_6011_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

void ITrace(REFIID iid, const char* str);

class CEx28bDoc : public CDocument
{
protected: // create from serialization only
	CEx28bDoc();
	DECLARE_DYNCREATE(CEx28bDoc)

	BEGIN_INTERFACE_PART(OleClientSite, IOleClientSite)
		STDMETHOD(SaveObject)();
		STDMETHOD(GetMoniker)(DWORD, DWORD, LPMONIKER*);
		STDMETHOD(GetContainer)(LPOLECONTAINER*);
		STDMETHOD(ShowObject)();
		STDMETHOD(OnShowWindow)(BOOL);
		STDMETHOD(RequestNewObjectLayout)();
	END_INTERFACE_PART(OleClientSite)

	BEGIN_INTERFACE_PART(AdviseSink, IAdviseSink)
		STDMETHOD_(void,OnDataChange)(LPFORMATETC, LPSTGMEDIUM);
		STDMETHOD_(void,OnViewChange)(DWORD, LONG);
		STDMETHOD_(void,OnRename)(LPMONIKER);
		STDMETHOD_(void,OnSave)();
		STDMETHOD_(void,OnClose)();
	END_INTERFACE_PART(AdviseSink)

	DECLARE_INTERFACE_MAP()

friend class CEx28bView;
private:
	LPOLEOBJECT m_lpOleObj;
	LPSTORAGE m_pTempStgRoot;
	LPSTORAGE m_pTempStgSub;
	BOOL m_bHatch;
	static const OLECHAR* s_szSub;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual void DeleteContents();
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28bDoc)
	afx_msg void OnEditClearAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations
//  immediately before the previous line.

#endif 
// !defined(AFX_EX28BDOC_H__1EAAB6DF_6011_11D0_848F_00400526305B__INCLUDED_)
