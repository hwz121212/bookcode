// UseAuthors.cpp : implementation file
//

#include "stdafx.h"
#include "ConsumeBiblio.h"
#include "UseAuthors.h"


// CUseAuthors dialog

IMPLEMENT_DYNAMIC(CUseAuthors, CDialog)
CUseAuthors::CUseAuthors(CWnd* pParent /*=NULL*/)
	: CDialog(CUseAuthors::IDD, pParent)
    , m_strAuthor(_T(""))
    , m_strTitle(_T(""))
{
}

CUseAuthors::~CUseAuthors()
{
}

void CUseAuthors::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_AUTHOR, m_strAuthor);
    DDX_Text(pDX, IDC_TITLE, m_strTitle);
}


BEGIN_MESSAGE_MAP(CUseAuthors, CDialog)
    ON_BN_CLICKED(IDC_NEXT, OnBnClickedNext)
    ON_BN_CLICKED(IDC_NEXTTITLE, OnBnClickedNexttitle)
END_MESSAGE_MAP()


// CUseAuthors message handlers

void CUseAuthors::OnBnClickedNext()
{
	// TODO: Add your control notification handler code here
	m_authors.MoveNext();
	m_strAuthor = m_authors.m_Author;
	UpdateData(FALSE);
}

BOOL CUseAuthors::OnInitDialog()
{
    CDialog::OnInitDialog();

	HRESULT hr = 0;
    hr = m_authors.OpenAll();
    if(SUCCEEDED(hr)) {
    	m_authors.MoveFirst();
	    m_strAuthor = m_authors.m_Author;
	    UpdateData(FALSE);
    }

    hr = m_titles.OpenAll();
    if(SUCCEEDED(hr)) {
    	m_titles.MoveFirst();
        m_strTitle = m_titles.m_Title;
	    UpdateData(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CUseAuthors::OnBnClickedNexttitle()
{
	m_titles.MoveNext();
	m_strTitle = m_titles.m_Title;
	UpdateData(FALSE);
}
