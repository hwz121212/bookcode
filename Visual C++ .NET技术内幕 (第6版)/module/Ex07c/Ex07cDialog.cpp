// Ex07cDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Ex07c.h"
#include "Ex07cDialog.h"


// CEx07cDialog dialog

IMPLEMENT_DYNAMIC(CEx07cDialog, CDialog)
CEx07cDialog::CEx07cDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEx07cDialog::IDD, pParent)
	, m_strEdit1(_T(""))
{
	m_pView = NULL;
}

CEx07cDialog::CEx07cDialog(CView* pView)  // modeless constructor
: m_strEdit1(_T(""))
{
    m_pView = pView;
}

CEx07cDialog::~CEx07cDialog()
{
}

void CEx07cDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
}


BEGIN_MESSAGE_MAP(CEx07cDialog, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CEx07cDialog::Create()
{
    return CDialog::Create(CEx07cDialog::IDD);
}


// CEx07cDialog message handlers

void CEx07cDialog::OnBnClickedCancel()
{
    if (m_pView != NULL) {
        // modeless case -- do not call base class OnCancel
        m_pView->PostMessage(WM_GOODBYE, IDCANCEL);
    }
    else {
        CDialog::OnCancel(); // modal case
    }
}

void CEx07cDialog::OnBnClickedOk()
{
    if (m_pView != NULL) {
        // modeless case -- do not call base class OnOK
        UpdateData(TRUE);
         m_pView->PostMessage(WM_GOODBYE, IDOK);
    }
    else {
        CDialog::OnOK(); // modal case
    }
}
