// Test22cDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex22b.h"
#include "Test22cDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest22cDialog dialog


CTest22cDialog::CTest22cDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTest22cDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest22cDialog)
	m_dInput = 0.0;
	m_dOutput = 0.0;
	//}}AFX_DATA_INIT
}


void CTest22cDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest22cDialog)
	DDX_Text(pDX, IDC_INPUT, m_dInput);
	DDX_Text(pDX, IDC_OUTPUT, m_dOutput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTest22cDialog, CDialog)
	//{{AFX_MSG_MAP(CTest22cDialog)
	ON_BN_CLICKED(IDC_COMPUTE, OnCompute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest22cDialog message handlers

void CTest22cDialog::OnCompute() 
{
    UpdateData(TRUE);
    m_dOutput = Ex22cSquareRoot(m_dInput);
    UpdateData(FALSE);
	
}
