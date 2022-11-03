// Test20cDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Ex20b.h"
#include "Test20cDialog.h"


// CTest20cDialog dialog

IMPLEMENT_DYNAMIC(CTest20cDialog, CDialog)
CTest20cDialog::CTest20cDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTest20cDialog::IDD, pParent)
	, m_dInput(0)
	, m_dOutput(0)
{
}

CTest20cDialog::~CTest20cDialog()
{
}

void CTest20cDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT, m_dInput);
	DDX_Text(pDX, IDC_OUTPUT, m_dOutput);
}


BEGIN_MESSAGE_MAP(CTest20cDialog, CDialog)
	ON_BN_CLICKED(IDC_COMPUTE, OnBnClickedCompute)
END_MESSAGE_MAP()


// CTest20cDialog message handlers

void CTest20cDialog::OnBnClickedCompute()
{
	UpdateData(TRUE);
    m_dOutput = Ex20cSquareRoot(m_dInput);
    UpdateData(FALSE);

}
