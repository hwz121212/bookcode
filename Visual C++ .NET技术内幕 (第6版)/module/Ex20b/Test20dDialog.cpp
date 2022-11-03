// Test20dDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Ex20b.h"
#include "Test20dDialog.h"


// CTest20dDialog dialog

IMPLEMENT_DYNAMIC(CTest20dDialog, CDialog)
CTest20dDialog::CTest20dDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTest20dDialog::IDD, pParent)
{
	m_nState = OFF;
    Ex20dEntry(); // Make sure DLL gets loaded
}

CTest20dDialog::~CTest20dDialog()
{
}

void CTest20dDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


void CTest20dDialog::OnClickedRyg()
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

BEGIN_MESSAGE_MAP(CTest20dDialog, CDialog)
   ON_CONTROL(0, IDC_RYG, OnClickedRyg) // Notification code is 0
END_MESSAGE_MAP()



// CTest20dDialog message handlers
