// ComputeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex11a.h"
#include "ComputeDlg.h"


// CComputeDlg dialog

IMPLEMENT_DYNAMIC(CComputeDlg, CDialog)
CComputeDlg::CComputeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComputeDlg::IDD, pParent)
{
    m_nCount = 0;
}

CComputeDlg::~CComputeDlg()
{
}

void CComputeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CComputeDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, OnBnClickedStart)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CComputeDlg message handlers

void CComputeDlg::OnTimer(UINT_PTR nIDEvent)
{
    CProgressCtrl* pBar = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
    pBar->SetPos(m_nCount * 100 / nMaxCount);

	CDialog::OnTimer(nIDEvent);
}

void CComputeDlg::OnBnClickedStart()
{
    MSG message;

    m_nTimer = SetTimer(1, 100, NULL); // 1/10 second
    ASSERT(m_nTimer != 0);
    GetDlgItem(IDC_START)->EnableWindow(FALSE);
    volatile int nTemp;
    for (m_nCount = 0; m_nCount < nMaxCount; m_nCount++) {
        for (nTemp = 0; nTemp < 10000; nTemp++) {
            // uses up CPU cycles
        }
        if (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&message);
            ::DispatchMessage(&message);
        }
    }
    GetDlgItem(IDC_START)->EnableWindow(TRUE);
    CDialog::OnOK();
}

void CComputeDlg::OnBnClickedCancel()
{
    TRACE("entering CComputeDlg::OnBnClickedCancel\n");
    if (m_nCount == 0) {      // prior to Start button
        CDialog::OnCancel();
    }
    else {                    // computation in progress
        m_nCount = nMaxCount; // Force exit from OnBnClickedStart
    }
}
