// Test22dDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex22b.h"
#include "Test22dDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest22dDialog dialog


CTest22dDialog::CTest22dDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTest22dDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest22dDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_nState = OFF;
    Ex22dEntry(); // Make sure DLL gets loaded
}


void CTest22dDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest22dDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTest22dDialog, CDialog)
	//{{AFX_MSG_MAP(CTest22dDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_CONTROL(0, IDC_RYG, OnClickedRyg) // Notification code is 0
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest22dDialog message handlers

void CTest22dDialog::OnClickedRyg()
{
    switch(m_nState) {
    case OFF:
        m_nState = RED;
        break;
    case RED:
        m_nState = YELLOW;
        break;
    case YELLOW:
        m_nState = GREEN;
        break;
    case GREEN:
        m_nState = OFF;
        break;
    }
    GetDlgItem(IDC_RYG)->SendMessage(RYG_SETSTATE, m_nState);
    return;
}
