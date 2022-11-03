// ComputeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex11c.h"
#include "ComputeDlg.h"


volatile int g_nCount;
CEvent g_eventStart; // creates autoreset events
CEvent g_eventKill;

UINT ComputeThreadProc(LPVOID pParam)
{
	volatile int nTemp;

	::WaitForSingleObject(g_eventStart, INFINITE);
	TRACE("starting computation\n");
	for (g_nCount = 0; g_nCount < CComputeDlg::nMaxCount;
	                   g_nCount++) {
		for (nTemp = 0; nTemp < 10000; nTemp++) {
			// Simulate computation
		}
		if (::WaitForSingleObject(g_eventKill, 0) == WAIT_OBJECT_0) {
			break;
		}
	}
	// Tell owner window we're finished
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
	g_eventStart.SetEvent();
}

void CComputeDlg::OnBnClickedCancel()
{
	if (g_nCount == 0) { // prior to Start button
		// must start it before we can kill it
		g_eventStart.SetEvent();
	}
	g_eventKill.SetEvent();
}

BOOL CComputeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	AfxBeginThread(ComputeThreadProc, GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CComputeDlg::OnThreadFinished(WPARAM wParam, LPARAM lParam)
{
    CDialog::OnOK();
    return 0;
}
