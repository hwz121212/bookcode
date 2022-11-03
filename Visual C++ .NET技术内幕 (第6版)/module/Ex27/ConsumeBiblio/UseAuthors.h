#pragma once

#include "authors.h"
#include "titles.h"

// CUseAuthors dialog

class CUseAuthors : public CDialog
{

protected:
    CAuthors m_authors;
    CTitles m_titles;

	DECLARE_DYNAMIC(CUseAuthors)

public:
	CUseAuthors(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUseAuthors();

// Dialog Data
	enum { IDD = IDD_USEAUTHORS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CString m_strAuthor;
    afx_msg void OnBnClickedNext();
    virtual BOOL OnInitDialog();
    CString m_strTitle;
    afx_msg void OnBnClickedNexttitle();
};
