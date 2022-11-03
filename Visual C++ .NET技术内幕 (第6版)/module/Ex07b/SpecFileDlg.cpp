// SpecFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex07b.h"
#include "SpecFileDlg.h"


// CSpecialFileDialog dialog

IMPLEMENT_DYNAMIC(CSpecialFileDialog, CFileDialog)
CSpecialFileDialog::CSpecialFileDialog(BOOL bOpenFileDialog,
		LPCTSTR lpszDefExt, LPCTSTR lpszFileName, DWORD dwFlags,
		LPCTSTR lpszFilter, CWnd* pParentWnd)
	: CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName,
		dwFlags, lpszFilter, pParentWnd)
{
	m_ofn.Flags |= OFN_ENABLETEMPLATE;
	m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_FILESPECIAL);
	m_ofn.lpstrTitle = "Delete File";
	m_bDeleteAll = FALSE;
}

CSpecialFileDialog::~CSpecialFileDialog()
{
}

void CSpecialFileDialog::DoDataExchange(CDataExchange* pDX)
{
	CFileDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSpecialFileDialog, CFileDialog)
	ON_BN_CLICKED(IDC_DELETE, OnBnClickedDelete)
END_MESSAGE_MAP()


// CSpecialFileDialog message handlers

BOOL CSpecialFileDialog::OnInitDialog()
{
	BOOL bRet = CFileDialog::OnInitDialog();
	if (bRet == TRUE) {
		GetParent()->GetDlgItem(IDOK)->SetWindowText("Delete");
	}

    HICON hIcon = AfxGetApp()->LoadIcon(IDI_MYICON);
    GetParent()->SetIcon(hIcon, TRUE);        // Set big icon
    GetParent()->SetIcon(hIcon, FALSE);       // Set small icon

	return bRet;
}

void CSpecialFileDialog::OnBnClickedDelete()
{
	m_bDeleteAll = TRUE;
	// 0x480 is the child window ID of the File Name edit control
	//  (as determined by SPYXX)
	GetParent()->GetDlgItem(0x480)->GetWindowText(m_strFilename);
	GetParent()->SendMessage(WM_COMMAND, IDCANCEL);
}
