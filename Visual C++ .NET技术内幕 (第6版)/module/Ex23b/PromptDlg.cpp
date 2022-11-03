// PromptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex23b.h"
#include "PromptDlg.h"


// CPromptDlg dialog

IMPLEMENT_DYNCREATE(CPromptDlg, CDialog)

CPromptDlg::CPromptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPromptDlg::IDD, pParent)
    , m_lData(0)
    , m_strData(_T(""))
{
}

CPromptDlg::~CPromptDlg()
{
}

void CPromptDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LONGDATA, m_lData);
    DDX_Text(pDX, cIDC_STRINGDATA, m_strData);
}

BOOL CPromptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CPromptDlg, CDialog)
END_MESSAGE_MAP()


// CPromptDlg message handlers

