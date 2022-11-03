// ComputeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex11b.h"
#include "ComputeDlg.h"

int g_nCount = 0;

UINT ComputeThreadProc(LPVOID pParam)
{
	volatile int nTemp; // volatile else compiler optimizes too much

	for (g_nCount = 0; g_nCount < CComputeDlg::nMaxCount;
	                   ::InterlockedIncrement((long*) &g_nCount)) {
		for (nTemp = 0; nTemp < 50000; nTemp++) {
			// uses up CPU cycles
		}
	}
	// WM_THREADFINISHED is user-defined message
	::PostMessage((HWND) pParam, WM_THREADFINISHED, 0, 0);
	g_nCount = 0;
	return 0; // ends the thread
}

// CComputeDlg dialog

IMPLEMENT_DYNAMIC(CComputeDlg, CDialog)
CComputeDlg::CComputeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComputeDlg::IDD, pParent)
{
}

CComputeDlg::~CComputeDlg()
{
}

void CComputeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CComputeDlg, CDialog)
	ON_MESSAGE(WM_THREADFINISHED, OnThreadFinished)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, OnBnClickedStart)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CComputeDlg message handlers

void CComputeDlg::OnTimer(UINT_PTR nIDEvent)
{
	CProgressCtrl* pBar = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
	pBar->SetPos(g_nCount * 100 / nMaxCount);

	CDialog::OnTimer(nIDEvent);
}

void CComputeDlg::OnBnClickedStart()
{
	m_nTimer = SetTimer(1, 100, NULL); // 1/10 second
	ASSERT(m_nTimer != 0);
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	AfxBeginThread(ComputeThreadProc, GetSafeHwnd(),
	               THREAD_PRIORITY_NORMAL);
}

void CComputeDlg::OnBnClickedCancel()
{
	if (g_nCount == 0) { // prior to Start button
		CDialog::OnCancel();
	}
	else { // computation in progress
		g_nCount = nMaxCount; // Force thread to exit
	}
}

LRESULT CComputeDlg::OnThreadFinished(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_START)->EnableWindow(TRUE);

	CDialog::OnOK();
	return 0;
}