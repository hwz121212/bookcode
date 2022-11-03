// Property.cpp : implementation file
//

#include "stdafx.h"
#include "Ex12a.h"
#include "Property.h"

CView* g_pView;

// CPage1 dialog

IMPLEMENT_DYNAMIC(CPage1, CPropertyPage)
CPage1::CPage1()
	: CPropertyPage(CPage1::IDD)
{
	m_nFont = -1;
}

CPage1::~CPage1()
{
}

BOOL CPage1::OnApply()
{
    TRACE("CPage1::OnApply\n");
    g_pView->SendMessage(WM_USERAPPLY);
    return TRUE;
}

BOOL CPage1::OnCommand(WPARAM wParam, LPARAM lParam)
{
    SetModified(TRUE);
    return CPropertyPage::OnCommand(wParam, lParam);
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	TRACE("Entering CPage1::DoDataExchange -- %d\n",
          pDX->m_bSaveAndValidate);
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_FONT, m_nFont);
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
END_MESSAGE_MAP()


// CPage1 message handlers
// property.cpp : implementation file


// CPage2 dialog

IMPLEMENT_DYNAMIC(CPage2, CPropertyPage)
CPage2::CPage2()
	: CPropertyPage(CPage2::IDD)
{
	m_bBold = FALSE;
    m_bItalic = FALSE;
    m_bUnderline = FALSE;

}

CPage2::~CPage2()
{
}

BOOL CPage2::OnCommand(WPARAM wParam, LPARAM lParam)
{
    SetModified(TRUE);
    return CPropertyPage::OnCommand(wParam, lParam);
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	TRACE("Entering CPage2::DoDataExchange -- %d\n",
          pDX->m_bSaveAndValidate);

	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_BOLD, m_bBold);
    DDX_Check(pDX, IDC_ITALIC, m_bItalic);
    DDX_Check(pDX, IDC_UNDERLINE, m_bUnderline);

}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
END_MESSAGE_MAP()


// CPage2 message handlers

// CPage3 dialog

IMPLEMENT_DYNAMIC(CPage3, CPropertyPage)
CPage3::CPage3()
	: CPropertyPage(CPage3::IDD)
{
	m_nColor = -1;
}

CPage3::~CPage3()
{
}

BOOL CPage3::OnCommand(WPARAM wParam, LPARAM lParam)
{
    SetModified(TRUE);
    return CPropertyPage::OnCommand(wParam, lParam);
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	TRACE("Entering CPage3::DoDataExchange -- %d\n",
          pDX->m_bSaveAndValidate);
	
	CPropertyPage::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_COLOR, m_nColor);

}


BEGIN_MESSAGE_MAP(CPage3, CPropertyPage)
END_MESSAGE_MAP()


// CPage3 message handlers

// CPage4 dialog

IMPLEMENT_DYNAMIC(CPage4, CPropertyPage)
CPage4::CPage4()
	: CPropertyPage(CPage4::IDD)
{
	m_nFontSize = 0;
}

CPage4::~CPage4()
{
}

BOOL CPage4::OnCommand(WPARAM wParam, LPARAM lParam)
{
    SetModified(TRUE);
    return CPropertyPage::OnCommand(wParam, lParam);
}

void CPage4::DoDataExchange(CDataExchange* pDX)
{
	TRACE("Entering CPage4::DoDataExchange -- %d\n",
          pDX->m_bSaveAndValidate);
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FONTSIZE, m_nFontSize);
    DDV_MinMaxInt(pDX, m_nFontSize, 8, 24);

}


BEGIN_MESSAGE_MAP(CPage4, CPropertyPage)
END_MESSAGE_MAP()


// CPage4 message handlers

BOOL CPage4::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	((CSpinButtonCtrl*) GetDlgItem(IDC_SPIN1))->SetRange(8, 24);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// CFontSheet

IMPLEMENT_DYNAMIC(CFontSheet, CPropertySheet)
CFontSheet::CFontSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CFontSheet::CFontSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_page1);
    AddPage(&m_page2);
    AddPage(&m_page3);
    AddPage(&m_page4);

}

CFontSheet::~CFontSheet()
{
}


BEGIN_MESSAGE_MAP(CFontSheet, CPropertySheet)
END_MESSAGE_MAP()


// CFontSheet message handlers
