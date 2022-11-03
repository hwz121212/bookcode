// Ex12aDoc.h : interface of the CEx12aDoc class
//


#pragma once

class CEx12aDoc : public CDocument
{
protected: // create from serialization only
	CEx12aDoc();
	DECLARE_DYNCREATE(CEx12aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CEx12aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditCleardocument();
	afx_msg void OnUpdateEditCleardocument(CCmdUI *pCmdUI);
public:
    CString m_strText;

};


